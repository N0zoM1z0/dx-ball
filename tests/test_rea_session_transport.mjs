// Run with node --experimental-vm-modules. No provider/process/network starts.
import assert from 'node:assert/strict';
import {readFileSync} from 'node:fs';
import {dirname, resolve} from 'node:path';
import {fileURLToPath} from 'node:url';
import vm from 'node:vm';

const root = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const filename = resolve(root, 'scripts/rea-session.mjs');
const source = readFileSync(filename, 'utf8');
const transport = {category: 'resource_constraint', details: {resource: 'transport'}};
const invalid = {category: 'invalid_input'};
const view = {name: 'inspect_analysis_view', arguments: {
  source: {kind: 'retained-evidence', evidence_id: 'retained-completed-result'},
  view: {kind: 'native', facet: 'pseudocode', offset: 0, limit: 64},
}};
const inspect = {name: 'analyze_function', arguments: {procedure: '0x0040d968'}};
const cases = [
  {name: 'interactive-success', replies: [null]},
  {name: 'interactive-invalid-recovery', replies: [invalid, invalid, null], errors: 2},
  {name: 'interactive-transport-page', replies: [transport, null], requests: [inspect, view], errors: 1, skip: true},
  {name: 'interactive-two-transport-pages', replies: [transport, null, transport, null],
    requests: [inspect, view, inspect, view], errors: 2, skip: true},
  {name: 'interactive-memory-fatal', replies: [{category: 'resource_constraint', details: {resource: 'memory'}}], fatal: true},
  {name: 'interactive-provider-fatal', replies: [{category: 'provider_unavailable'}], fatal: true},
  {name: 'interactive-connection-fatal', replies: ['connection'], fatal: true},
  {name: 'batch-invalid-fatal', replies: [invalid], batch: true, fatal: true},
  {name: 'batch-transport-fatal-safe-close', replies: [transport], batch: true, fatal: true, skip: true},
];
for (const test of cases) {
  const requests = test.requests ?? test.replies.map(() => inspect);
  const snapshot = resolve(root, '.analysis/rea/vc4-backend/vc4-backend.snapshot.json');
  const initial = JSON.stringify({evidence_bundle: {records: []}, sentinel: 'prior-snapshot'});
  const memory = new Map([[snapshot, initial], ['/requests.json', JSON.stringify(requests)]]);
  const calls = []; let closed = false; let replyIndex = 0;
  class Client {
    async connect() {}
    async listTools() {return {tools: [{name: 'analyze_function'}, {name: 'inspect_analysis_view'}]};}
    async callTool(call) {
      calls.push(call);
      if (call.name === 'open_binary') return {structuredContent: {result: {sha256: '0'.repeat(64)}}};
      if (call.name === 'close_binary') {
        if (call.arguments.snapshot_path) memory.set(snapshot,
          JSON.stringify({evidence_bundle: {records: []}, sentinel: 'saved-snapshot'}));
        return {structuredContent: {result: {primitive_entries: 0}}};
      }
      assert.ok(call.name === 'analyze_function' || call.name === 'inspect_analysis_view');
      const reply = test.replies[replyIndex++];
      if (reply === 'connection') throw new Error('mock connection closed');
      if (reply) return {isError: true, structuredContent: {error: reply}};
      return {structuredContent: {evidence_id: 'small-page-or-result', normalized_result: {text: 'bounded'}}};
    }
    async close() {closed = true;}
  }
  class StdioClientTransport {}
  const context = vm.createContext({process: {
    argv: ['node', filename, test.batch ? '/requests.json' : '--interactive', 'vc4-backend', '0'.repeat(64)],
    env: {}, pid: 1, execPath: process.execPath, stdin: {},
  }, console: {log() {}, error() {}}, performance, Buffer});
  const module = new vm.SourceTextModule(source, {context, identifier: filename,
    initializeImportMeta(meta) {meta.url = new URL('file://' + filename).href;}});
  const modules = new Map();
  await module.link(async specifier => {
    if (modules.has(specifier)) return modules.get(specifier);
    let exports;
    if (specifier.includes('/client/dist/index.mjs')) exports = {Client};
    else if (specifier.includes('/client/dist/stdio.mjs')) exports = {StdioClientTransport};
    else if (specifier === 'node:fs') exports = {
      readFileSync: path => {assert.ok(memory.has(path), path); return memory.get(path);},
      writeFileSync: (path, value) => memory.set(path, value), mkdirSync() {}, existsSync: path => memory.has(path),
    };
    else if (specifier === 'node:readline') exports = {createInterface: () => ({close() {},
      async *[Symbol.asyncIterator]() {
        for (const request of requests) yield JSON.stringify(request);
        yield JSON.stringify({close: true});
      },
    })};
    else exports = await import(specifier);
    const imported = new vm.SyntheticModule(Object.keys(exports), function() {
      for (const [key, value] of Object.entries(exports)) this.setExport(key, value);
    }, {context});
    modules.set(specifier, imported); return imported;
  });
  let failure;
  try {await module.evaluate();} catch (error) {failure = error;}
  assert.equal(Boolean(failure), Boolean(test.fatal), test.name);
  assert.equal(closed, true, test.name);
  assert.equal(replyIndex, test.replies.length, test.name);
  assert.equal(calls[0].name, 'open_binary');
  assert.equal(calls.at(-1).name, 'close_binary');
  const close = calls.at(-1).arguments;
  assert.equal(close.snapshot_path, test.skip ? undefined : snapshot, test.name);
  assert.equal(JSON.parse(memory.get(snapshot)).sentinel, test.skip ? 'prior-snapshot' : 'saved-snapshot', test.name);
  const errors = [...memory.keys()].filter(path => /\/\d+-.*\.error\.json$/.test(path));
  assert.equal(errors.length, test.errors ?? 0, test.name);
  if (test.fatal) assert.ok([...memory.keys()].some(path => path.endsWith('/failure.json')), test.name);
  for (let i = 0; i < requests.length; i++) {
    assert.deepEqual(JSON.parse(JSON.stringify(calls[i + 1])), requests[i], test.name);
  }
}
console.log(`Pass: ${cases.length} actual-module, provider-free transport/recovery/fatal-path cases.`);
