// Headless-only helper: emit bounded read-only semantic queries.
//@author N0zoM1z0
//@category DXBALL

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.DataIterator;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import ghidra.program.model.symbol.Symbol;

import java.io.File;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Set;

public class QueryProgram extends GhidraScript
{
    private static String hex(long value)
    {
        return String.format("0x%08X", value);
    }

    private static String formattedAddress(Address address)
    {
        return address.isMemoryAddress() ? hex(address.getOffset()) : address.toString();
    }

    private static String flatten(String value)
    {
        return value == null ? "" :
            value.replace("\\", "\\\\").replace("\r", "\\r").replace("\n", "\\n");
    }

    private static String textArgument(String value)
    {
        if (!value.startsWith("text:"))
            throw new IllegalArgumentException("text argument is missing its data prefix");
        return value.substring(5);
    }

    private String symbolName(Address address)
    {
        Symbol symbol = currentProgram.getSymbolTable().getPrimarySymbol(address);
        return symbol == null ? "" : symbol.getName(true);
    }

    private Function functionFor(Address address)
    {
        Function function = getFunctionAt(address);
        return function == null ? getFunctionContaining(address) : function;
    }

    private void writeFunction(PrintWriter output, Address address)
    {
        Function function = functionFor(address);
        if (function == null)
        {
            output.printf("no function contains %s%n", formattedAddress(address));
            return;
        }
        output.printf("address: %s%n", formattedAddress(function.getEntryPoint()));
        output.printf("name: %s%n", function.getName(true));
        output.printf("signature: %s%n", flatten(function.getSignature().getPrototypeString()));
        output.printf("calling_convention: %s%n", function.getCallingConventionName());
        output.printf("body_min: %s%n", formattedAddress(function.getBody().getMinAddress()));
        output.printf("body_max: %s%n", formattedAddress(function.getBody().getMaxAddress()));
        output.printf("body_addresses: %d%n", function.getBody().getNumAddresses());
        output.printf("parameters: %d%n", function.getParameterCount());
        output.printf("is_thunk: %s%n", function.isThunk());
        output.printf("is_external: %s%n%n", function.isExternal());
    }

    private void writeDisassembly(PrintWriter output, Address address, int maximum)
        throws Exception
    {
        Function function = functionFor(address);
        if (function == null)
        {
            output.printf("no function contains %s%n", formattedAddress(address));
            return;
        }
        output.printf("function: %s @ %s%n", function.getName(true),
            formattedAddress(function.getEntryPoint()));
        InstructionIterator iterator =
            currentProgram.getListing().getInstructions(function.getBody(), true);
        int count = 0;
        while (iterator.hasNext() && count < maximum)
        {
            monitor.checkCancelled();
            Instruction instruction = iterator.next();
            byte[] bytes = instruction.getBytes();
            StringBuilder encoded = new StringBuilder();
            for (byte value : bytes)
                encoded.append(String.format("%02X", value & 0xff));
            output.printf("%s  %-20s  %s%n", formattedAddress(instruction.getAddress()),
                encoded.toString(), instruction.toString());
            count++;
        }
        if (iterator.hasNext())
            output.printf("[truncated after %d instructions]%n", maximum);
        output.println();
    }

    private static List<Function> sorted(Set<Function> functions)
    {
        List<Function> result = new ArrayList<>(functions);
        result.sort(Comparator.comparing(Function::getEntryPoint));
        return result;
    }

    private void writeCalls(PrintWriter output, Address address, boolean callers)
        throws Exception
    {
        Function function = functionFor(address);
        if (function == null)
        {
            output.printf("no function contains %s%n", formattedAddress(address));
            return;
        }
        output.printf("function: %s @ %s%n", function.getName(true),
            formattedAddress(function.getEntryPoint()));
        Set<Function> related = callers
            ? function.getCallingFunctions(monitor)
            : function.getCalledFunctions(monitor);
        output.printf("%s: %d%n", callers ? "callers" : "callees", related.size());
        for (Function candidate : sorted(related))
            output.printf("%s  %s%n", formattedAddress(candidate.getEntryPoint()),
                candidate.getName(true));
        output.println();
    }

    private void writeReference(PrintWriter output, Reference reference)
    {
        output.printf("%s -> %s  %s  %s%n",
            formattedAddress(reference.getFromAddress()),
            formattedAddress(reference.getToAddress()),
            reference.getReferenceType(),
            symbolName(reference.getToAddress()));
    }

    private void writeReferencesTo(PrintWriter output, Address address, int maximum)
        throws Exception
    {
        output.printf("references_to: %s  %s%n", formattedAddress(address), symbolName(address));
        ReferenceIterator iterator = currentProgram.getReferenceManager().getReferencesTo(address);
        int count = 0;
        while (iterator.hasNext() && count < maximum)
        {
            monitor.checkCancelled();
            writeReference(output, iterator.next());
            count++;
        }
        if (iterator.hasNext())
            output.printf("[truncated after %d references]%n", maximum);
        output.println();
    }

    private void writeReferencesFrom(PrintWriter output, Address address, int maximum)
        throws Exception
    {
        Function function = functionFor(address);
        output.printf("references_from: %s", formattedAddress(address));
        if (function != null)
            output.printf("  %s", function.getName(true));
        output.println();

        int count = 0;
        if (function == null)
        {
            for (Reference reference : currentProgram.getReferenceManager().getReferencesFrom(address))
            {
                if (count++ >= maximum)
                    break;
                writeReference(output, reference);
            }
        }
        else
        {
            InstructionIterator instructions =
                currentProgram.getListing().getInstructions(function.getBody(), true);
            while (instructions.hasNext() && count < maximum)
            {
                monitor.checkCancelled();
                for (Reference reference : instructions.next().getReferencesFrom())
                {
                    if (count++ >= maximum)
                        break;
                    writeReference(output, reference);
                }
            }
        }
        if (count >= maximum)
            output.printf("[truncated after %d references]%n", maximum);
        output.println();
    }

    private void listFunctions(PrintWriter output, int offset, int limit, String filter)
        throws Exception
    {
        String needle = filter.toLowerCase();
        FunctionIterator functions = currentProgram.getFunctionManager().getFunctions(true);
        int matched = 0;
        int emitted = 0;
        while (functions.hasNext() && emitted < limit)
        {
            monitor.checkCancelled();
            Function function = functions.next();
            String name = function.getName(true);
            if (!needle.isEmpty() && !name.toLowerCase().contains(needle))
                continue;
            if (matched++ < offset)
                continue;
            output.printf("%s  %s%n", formattedAddress(function.getEntryPoint()), name);
            emitted++;
        }
        output.printf("returned: %d  offset: %d  filter: %s%n", emitted, offset,
            flatten(filter));
    }

    private void searchStrings(PrintWriter output, int limit, String query)
        throws Exception
    {
        String needle = query.toLowerCase();
        DataIterator data = currentProgram.getListing().getDefinedData(true);
        int emitted = 0;
        while (data.hasNext() && emitted < limit)
        {
            monitor.checkCancelled();
            Data item = data.next();
            if (!item.hasStringValue())
                continue;
            Object value = item.getValue();
            String text = value == null ? item.getDefaultValueRepresentation() : value.toString();
            if (!text.toLowerCase().contains(needle))
                continue;
            output.printf("%s  %s%n", formattedAddress(item.getAddress()), flatten(text));
            emitted++;
        }
        output.printf("returned: %d  query: %s%n", emitted, flatten(query));
    }

    private static int positive(String value, String name)
    {
        int parsed = Integer.parseInt(value);
        if (parsed <= 0)
            throw new IllegalArgumentException(name + " must be positive");
        return parsed;
    }

    @Override
    protected void run() throws Exception
    {
        String[] args = getScriptArgs();
        if (args.length < 2)
            throw new IllegalArgumentException(
                "usage: QueryProgram.java OUTPUT OPERATION [ARG...]");

        try (PrintWriter output = new PrintWriter(new File(args[0]), "UTF-8"))
        {
            String operation = args[1];
            if (operation.equals("function"))
            {
                for (int i = 2; i < args.length; ++i)
                    writeFunction(output, toAddr(args[i]));
            }
            else if (operation.equals("disassemble"))
            {
                if (args.length < 4)
                    throw new IllegalArgumentException("disassemble requires COUNT ADDRESS...");
                int maximum = positive(args[2], "instruction count");
                for (int i = 3; i < args.length; ++i)
                    writeDisassembly(output, toAddr(args[i]), maximum);
            }
            else if (operation.equals("callers") || operation.equals("callees"))
            {
                for (int i = 2; i < args.length; ++i)
                    writeCalls(output, toAddr(args[i]), operation.equals("callers"));
            }
            else if (operation.equals("xrefs_to"))
            {
                if (args.length < 4)
                    throw new IllegalArgumentException("xrefs_to requires LIMIT ADDRESS...");
                int maximum = positive(args[2], "reference limit");
                for (int i = 3; i < args.length; ++i)
                    writeReferencesTo(output, toAddr(args[i]), maximum);
            }
            else if (operation.equals("xrefs_from"))
            {
                if (args.length < 4)
                    throw new IllegalArgumentException("xrefs_from requires LIMIT ADDRESS...");
                int maximum = positive(args[2], "reference limit");
                for (int i = 3; i < args.length; ++i)
                    writeReferencesFrom(output, toAddr(args[i]), maximum);
            }
            else if (operation.equals("list_functions"))
            {
                if (args.length != 5)
                    throw new IllegalArgumentException(
                        "list_functions requires OFFSET LIMIT FILTER");
                int offset = Integer.parseInt(args[2]);
                if (offset < 0)
                    throw new IllegalArgumentException("offset must not be negative");
                listFunctions(output, offset, positive(args[3], "limit"),
                    textArgument(args[4]));
            }
            else if (operation.equals("search_strings"))
            {
                if (args.length != 4)
                    throw new IllegalArgumentException("search_strings requires LIMIT QUERY");
                searchStrings(output, positive(args[2], "limit"), textArgument(args[3]));
            }
            else
                throw new IllegalArgumentException("unsupported query operation: " + operation);
            if (output.checkError())
                throw new IllegalStateException("query output write failed");
        }
        println("DXBALL_QUERY_OK");
    }
}
