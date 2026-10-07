// Export target-derived DXBALL call-graph and reference metrics.
//@author N0zoM1z0
//@category DXBALL

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.Symbol;

import java.io.BufferedWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

public class ExportArchitecture extends GhidraScript
{
    private static String csv(String value)
    {
        if (value == null)
            return "";
        String flattened = value.replace("\r", "\\r").replace("\n", "\\n");
        if (flattened.contains(",") || flattened.contains("\"") ||
            flattened.contains("\\n"))
            return "\"" + flattened.replace("\"", "\"\"") + "\"";
        return flattened;
    }

    private static String hex(long value)
    {
        return String.format("0x%08X", value);
    }

    private static String formattedAddress(Address address)
    {
        return address.isMemoryAddress() ? hex(address.getOffset()) : address.toString();
    }

    private static void replace(Path temporary, Path destination) throws Exception
    {
        Files.move(temporary, destination, StandardCopyOption.REPLACE_EXISTING);
    }

    private String symbolName(Address address)
    {
        Symbol symbol = currentProgram.getSymbolTable().getPrimarySymbol(address);
        return symbol == null ? "" : symbol.getName(true);
    }

    @Override
    protected void run() throws Exception
    {
        String[] args = getScriptArgs();
        if (args.length != 6)
            throw new IllegalArgumentException(
                "usage: ExportArchitecture.java METRICS EDGES GLOBALS STRINGS " +
                "TEXT_START TEXT_END");

        Path metricsPath = Path.of(args[0]);
        Path edgesPath = Path.of(args[1]);
        Path globalsPath = Path.of(args[2]);
        Path stringsPath = Path.of(args[3]);
        Address textStart = toAddr(args[4]);
        Address textEnd = toAddr(args[5]);
        for (Path path : new Path[] {metricsPath, edgesPath, globalsPath, stringsPath})
            Files.createDirectories(path.toAbsolutePath().getParent());

        Path metricsTemp = Path.of(metricsPath.toString() + ".tmp");
        Path edgesTemp = Path.of(edgesPath.toString() + ".tmp");
        Path globalsTemp = Path.of(globalsPath.toString() + ".tmp");
        Path stringsTemp = Path.of(stringsPath.toString() + ".tmp");
        int functionCount = 0;
        int edgeCount = 0;

        try (
            BufferedWriter metrics = Files.newBufferedWriter(
                metricsTemp, StandardCharsets.UTF_8);
            BufferedWriter edges = Files.newBufferedWriter(
                edgesTemp, StandardCharsets.UTF_8);
            BufferedWriter globals = Files.newBufferedWriter(
                globalsTemp, StandardCharsets.UTF_8);
            BufferedWriter strings = Files.newBufferedWriter(
                stringsTemp, StandardCharsets.UTF_8)
        )
        {
            metrics.write(
                "address,size,name,is_thunk,in_degree,out_degree,internal_callees," +
                "external_callees,call_sites,instructions,conditional_branches," +
                "terminal_instructions,global_refs,string_refs\n");
            edges.write("caller,callee,callee_name,kind,call_sites\n");
            globals.write("function,address,symbol,references\n");
            strings.write("function,address,value,references\n");

            FunctionIterator iterator = currentProgram.getFunctionManager().getFunctions(true);
            while (iterator.hasNext())
            {
                monitor.checkCancelled();
                Function function = iterator.next();
                Address entry = function.getEntryPoint();
                if (function.isExternal() || entry.compareTo(textStart) < 0 ||
                    entry.compareTo(textEnd) > 0)
                    continue;

                Address maximum = function.getBody().getMaxAddress();
                long spanEnd = maximum == null ? entry.getOffset() : maximum.getOffset();
                long size = spanEnd - entry.getOffset() + 1;
                int instructionCount = 0;
                int conditionalBranches = 0;
                int terminalInstructions = 0;
                int callSites = 0;
                Map<String, Integer> edgeSites = new TreeMap<>();
                Map<String, String[]> edgeDetails = new HashMap<>();
                Map<String, Integer> globalReferences = new TreeMap<>();
                Map<String, String> globalNames = new HashMap<>();
                Map<String, Integer> stringReferences = new TreeMap<>();
                Map<String, String> stringValues = new HashMap<>();
                Set<String> internalCallees = new HashSet<>();
                Set<String> externalCallees = new HashSet<>();

                InstructionIterator instructions =
                    currentProgram.getListing().getInstructions(function.getBody(), true);
                while (instructions.hasNext())
                {
                    Instruction instruction = instructions.next();
                    instructionCount++;
                    if (instruction.getFlowType().isConditional())
                        conditionalBranches++;
                    if (instruction.getFlowType().isTerminal())
                        terminalInstructions++;

                    for (Reference reference : instruction.getReferencesFrom())
                    {
                        Address target = reference.getToAddress();
                        if (reference.getReferenceType().isCall())
                        {
                            callSites++;
                            Function callee = getFunctionAt(target);
                            if (callee == null)
                                callee = getFunctionContaining(target);
                            String calleeAddress = callee == null
                                ? formattedAddress(target)
                                : formattedAddress(callee.getEntryPoint());
                            String calleeName = callee == null
                                ? symbolName(target)
                                : callee.getName(true);
                            boolean internal = callee != null && !callee.isExternal() &&
                                callee.getEntryPoint().compareTo(textStart) >= 0 &&
                                callee.getEntryPoint().compareTo(textEnd) <= 0;
                            String kind = internal ? "internal" :
                                (callee != null && callee.isExternal() ? "external" : "unresolved");
                            String key = kind + "|" + calleeAddress + "|" + calleeName;
                            edgeSites.put(key, edgeSites.getOrDefault(key, 0) + 1);
                            edgeDetails.put(key, new String[] {calleeAddress, calleeName, kind});
                            if (internal)
                                internalCallees.add(calleeAddress);
                            else
                                externalCallees.add(calleeAddress);
                            continue;
                        }

                        if (!target.isMemoryAddress() ||
                            !currentProgram.getMemory().contains(target))
                            continue;
                        if (target.compareTo(textStart) >= 0 && target.compareTo(textEnd) <= 0)
                            continue;

                        Data data = currentProgram.getListing().getDefinedDataContaining(target);
                        String address = formattedAddress(target);
                        if (data != null && data.hasStringValue())
                        {
                            Address dataAddress = data.getAddress();
                            address = formattedAddress(dataAddress);
                            stringReferences.put(
                                address, stringReferences.getOrDefault(address, 0) + 1);
                            Object value = data.getValue();
                            stringValues.put(address, value == null
                                ? data.getDefaultValueRepresentation()
                                : value.toString());
                        }
                        else
                        {
                            globalReferences.put(
                                address, globalReferences.getOrDefault(address, 0) + 1);
                            globalNames.put(address, symbolName(target));
                        }
                    }
                }

                for (Map.Entry<String, Integer> edge : edgeSites.entrySet())
                {
                    String[] details = edgeDetails.get(edge.getKey());
                    edges.write(
                        hex(entry.getOffset()) + "," +
                        csv(details[0]) + "," +
                        csv(details[1]) + "," + details[2] + "," + edge.getValue() + "\n");
                    edgeCount++;
                }
                for (Map.Entry<String, Integer> global : globalReferences.entrySet())
                    globals.write(
                        hex(entry.getOffset()) + "," + global.getKey() + "," +
                        csv(globalNames.get(global.getKey())) + "," + global.getValue() + "\n");
                for (Map.Entry<String, Integer> string : stringReferences.entrySet())
                    strings.write(
                        hex(entry.getOffset()) + "," + string.getKey() + "," +
                        csv(stringValues.get(string.getKey())) + "," + string.getValue() + "\n");

                int inDegree = function.getCallingFunctions(monitor).size();
                metrics.write(
                    hex(entry.getOffset()) + "," + size + "," +
                    csv(function.getName(true)) + "," + function.isThunk() + "," +
                    inDegree + "," + (internalCallees.size() + externalCallees.size()) + "," +
                    internalCallees.size() + "," + externalCallees.size() + "," +
                    callSites + "," + instructionCount + "," + conditionalBranches + "," +
                    terminalInstructions + "," + globalReferences.size() + "," +
                    stringReferences.size() + "\n");
                functionCount++;
            }
        }

        replace(metricsTemp, metricsPath);
        replace(edgesTemp, edgesPath);
        replace(globalsTemp, globalsPath);
        replace(stringsTemp, stringsPath);
        println("Exported architecture metrics for " + functionCount +
            " functions and " + edgeCount + " direct edges");
        println("DXBALL_ARCHITECTURE_OK");
    }
}
