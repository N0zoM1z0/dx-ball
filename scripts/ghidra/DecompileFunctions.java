// Headless-only helper: emit decompiler hypotheses for explicit addresses.
//@author N0zoM1z0
//@category DXBALL

import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;

import java.io.File;
import java.io.PrintWriter;

public class DecompileFunctions extends GhidraScript
{
    @Override
    protected void run() throws Exception
    {
        String[] args = getScriptArgs();
        if (args.length < 2)
            throw new IllegalArgumentException(
                "usage: DecompileFunctions.java OUTPUT ADDRESS...");

        DecompInterface decompiler = new DecompInterface();
        decompiler.toggleCCode(true);
        decompiler.toggleSyntaxTree(true);
        if (!decompiler.openProgram(currentProgram))
            throw new IllegalStateException(decompiler.getLastMessage());

        try (PrintWriter output = new PrintWriter(new File(args[0]), "UTF-8"))
        {
            for (int i = 1; i < args.length; ++i)
            {
                Address address = toAddr(args[i]);
                Function function = getFunctionAt(address);
                if (function == null)
                {
                    throw new IllegalArgumentException("no function at " + address);
                }

                DecompileResults result = decompiler.decompileFunction(function, 300, monitor);
                output.printf("/* %s at %s */%n", function.getName(true), address);
                if (!result.decompileCompleted())
                    throw new IllegalStateException(result.getErrorMessage());
                else
                    output.println(result.getDecompiledFunction().getC());
            }
            if (output.checkError())
                throw new IllegalStateException("decompiler output write failed");
        }
        finally
        {
            decompiler.dispose();
        }
        println("DXBALL_DECOMPILE_OK");
    }
}
