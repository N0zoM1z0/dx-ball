// One real REA MCP session for sequential project-native queries. Invoked only
// through scripts/rea, after Python attests target and every analysis input.
import { Client } from '../.tools/rea-runtime/node_modules/@modelcontextprotocol/client/dist/index.mjs';
import { StdioClientTransport } from '../.tools/rea-runtime/node_modules/@modelcontextprotocol/client/dist/stdio.mjs';
import { readFileSync, writeFileSync, mkdirSync, existsSync } from 'node:fs';
import { fileURLToPath } from 'node:url';
import { dirname, resolve } from 'node:path';

const root = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const directory = resolve(root, '.analysis/rea');
mkdirSync(directory, { recursive: true, mode: 0o700 });
const snapshot = resolve(directory, 'dxball.snapshot.json');
const requests = JSON.parse(readFileSync(process.argv[2], 'utf8'));
const allowed = new Set(['binary_overview', 'binary_session', 'analyze_function',
  'batch_decompile', 'read_bytes', 'inspect_native_load_image', 'procedure_info',
  'procedure_pseudo_code', 'procedure_assembly', 'procedure_callers', 'procedure_callees',
  'search_strings', 'search_procedures', 'xrefs', 'get_call_graph',
  'inspect_native_instruction', 'inspect_native_data_type', 'resolve_native_call_targets',
  'inspect_native_api', 'trace_native_values', 'address_to_file_offset']);
if (!Array.isArray(requests) || requests.some(r => !allowed.has(r.name))) {
  throw new Error('session request must select a supported native inspection tool');
}
const client = new Client({ name: 'dxball-rea-showcase', version: '1.0.0' });
const transport = new StdioClientTransport({command: process.execPath,
  args: [resolve(root, '.tools/rea-runtime/node_modules/rea-agents/scripts/rea.mjs'), 'mcp'],
  env: process.env, stderr: 'inherit'});
let opened = false;
async function call(name, args) {
  const response = await client.callTool({name, arguments: args}, undefined,
    {timeout: 360000, maxTotalTimeout: 360000});
  const data = response.structuredContent ?? JSON.parse(response.content.find(c => c.type === 'text').text);
  if (response.isError) throw new Error(JSON.stringify(data));
  return data;
}
try {
  await client.connect(transport);
  const catalog = await client.listTools();
  writeFileSync(resolve(directory, 'catalog.json'), JSON.stringify(catalog, null, 2), {mode: 0o600});
  const open = await call('open_binary', {path: resolve(root, 'original/DXBALL.EXE'),
    provider_id: 'ghidra', ...(existsSync(snapshot) ? {snapshot_path: snapshot} : {})});
  opened = true;
  writeFileSync(resolve(directory, 'open.json'), JSON.stringify(open, null, 2), {mode: 0o600});
  console.log(`REA opened ${open.result.sha256}; ${catalog.tools.length} MCP tools`);
  for (const [index, request] of requests.entries()) {
    if (!catalog.tools.some(t => t.name === request.name)) throw new Error(`unadvertised tool: ${request.name}`);
    const data = await call(request.name, request.arguments ?? {});
    const filename = `${String(index).padStart(2, '0')}-${request.name}.json`;
    writeFileSync(resolve(directory, filename), JSON.stringify(data, null, 2), {mode: 0o600});
    console.log(`${request.name}: ${data.evidence_id ?? 'session state'} -> .analysis/rea/${filename}`);
  }
  const closed = await call('close_binary', {snapshot_path: snapshot, overwrite: existsSync(snapshot)});
  opened = false;
  writeFileSync(resolve(directory, 'close.json'), JSON.stringify(closed, null, 2), {mode: 0o600});
  const saved = JSON.parse(readFileSync(snapshot, 'utf8'));
  console.log(`REA snapshot saved: ${saved.evidence_bundle.records.length} Evidence records, ${closed.result.entries} primitive cache entries; session closed`);
} finally {
  if (opened) await call('close_binary', {});
  await client.close();
}
