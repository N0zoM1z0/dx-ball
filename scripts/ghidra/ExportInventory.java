// Export provisional Ghidra function and origin ledgers for DXBALL.
//@author N0zoM1z0
//@category DXBALL

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;

import java.io.BufferedWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;

public class ExportInventory extends GhidraScript
{
    private static String csv(String value)
    {
        if (value == null)
            return "";
        if (value.contains(",") || value.contains("\"") || value.contains("\n"))
            return "\"" + value.replace("\"", "\"\"") + "\"";
        return value;
    }

    private static String hex(long value)
    {
        return String.format("0x%08X", value);
    }

    private void writeLedgers(
        Path functionsPath,
        Path originsPath,
        Address textStart,
        Address textEnd,
        String evidenceId) throws Exception
    {
        Files.createDirectories(functionsPath.toAbsolutePath().getParent());
        Files.createDirectories(originsPath.toAbsolutePath().getParent());
        Path functionsTemp = Path.of(functionsPath.toString() + ".tmp");
        Path originsTemp = Path.of(originsPath.toString() + ".tmp");
        int count = 0;

        try (
            BufferedWriter functions = Files.newBufferedWriter(
                functionsTemp, StandardCharsets.UTF_8);
            BufferedWriter origins = Files.newBufferedWriter(
                originsTemp, StandardCharsets.UTF_8)
        )
        {
            functions.write(
                "address,size,span_end,current_name,proposed_name,module,status," +
                "match_percent,calling_convention,signature,is_thunk,source_file," +
                "evidence,owner,notes\n");
            origins.write(
                "address,origin,subsystem,disposition,confidence,evidence_id\n");

            FunctionIterator iterator = currentProgram.getFunctionManager().getFunctions(true);
            while (iterator.hasNext())
            {
                Function function = iterator.next();
                Address entry = function.getEntryPoint();
                if (function.isExternal() || entry.compareTo(textStart) < 0 ||
                    entry.compareTo(textEnd) > 0)
                    continue;

                Address max = function.getBody().getMaxAddress();
                long spanEnd = max == null ? entry.getOffset() : max.getOffset();
                long size = spanEnd - entry.getOffset() + 1;
                if (size <= 0)
                    throw new IllegalStateException("invalid function span at " + entry);

                String address = hex(entry.getOffset());
                String observation =
                    "Ghidra 12.1.3 auto-analysis candidate; boundary unreviewed";
                functions.write(
                    address + "," + size + "," + hex(spanEnd) + "," +
                    csv(function.getName(true)) + ",,,unclassified,0.00,,," +
                    function.isThunk() + ",," + csv(observation) + ",,\n");
                origins.write(
                    address + ",unknown,,review,unknown," + csv(evidenceId) + "\n");
                count++;
            }
        }

        Files.move(
            functionsTemp, functionsPath, StandardCopyOption.REPLACE_EXISTING);
        Files.move(originsTemp, originsPath, StandardCopyOption.REPLACE_EXISTING);
        println("Exported " + count + " provisional DXBALL functions");
        println("DXBALL_INVENTORY_OK");
    }

    @Override
    protected void run() throws Exception
    {
        String[] args = getScriptArgs();
        if (args.length != 5)
            throw new IllegalArgumentException(
                "usage: ExportInventory.java FUNCTIONS ORIGINS TEXT_START TEXT_END EVIDENCE");
        writeLedgers(
            Path.of(args[0]), Path.of(args[1]), toAddr(args[2]), toAddr(args[3]), args[4]);
    }
}
