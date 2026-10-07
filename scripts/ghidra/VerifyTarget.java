// Fail-closed attestation for a loaded DXBALL program.
//@author N0zoM1z0
//@category DXBALL

import ghidra.app.util.headless.HeadlessScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;

import java.util.Arrays;

public class VerifyTarget extends HeadlessScript
{
    private void fail(String message)
    {
        if (isRunningHeadless())
            setHeadlessContinuationOption(HeadlessContinuationOption.ABORT);
        throw new IllegalStateException(message);
    }

    private static byte[] decodeHex(String value)
    {
        if ((value.length() & 1) != 0)
            throw new IllegalArgumentException("sample hex must have an even length");
        byte[] result = new byte[value.length() / 2];
        for (int i = 0; i < result.length; ++i)
        {
            int high = Character.digit(value.charAt(i * 2), 16);
            int low = Character.digit(value.charAt(i * 2 + 1), 16);
            if (high < 0 || low < 0)
                throw new IllegalArgumentException("sample contains non-hexadecimal data");
            result[i] = (byte)((high << 4) | low);
        }
        return result;
    }

    @Override
    protected void run() throws Exception
    {
        String[] args = getScriptArgs();
        if (args.length < 10)
            fail("usage: VerifyTarget.java SHA256 MD5 MODULE SIZE IMAGE_BASE " +
                "IMAGE_SIZE ENTRY_POINT TEXT_START SAMPLE_COUNT [ADDRESS HEX]...");

        String expectedHash = args[0].toLowerCase();
        String expectedMd5 = args[1].toLowerCase();
        String expectedModule = args[2];
        long expectedFileSize = Long.parseLong(args[3]);
        long expectedBase = Long.decode(args[4]);
        long expectedImageSize = Long.parseLong(args[5]);
        Address expectedEntry = toAddr(args[6]);
        Address expectedText = toAddr(args[7]);
        int sampleCount = Integer.parseInt(args[8]);
        if (sampleCount <= 0 || args.length != 9 + sampleCount * 2)
            fail("invalid mapped-byte sample count");

        String actualHash = currentProgram.getExecutableSHA256();
        String actualMd5 = currentProgram.getExecutableMD5();

        if (actualHash == null || !actualHash.toLowerCase().equals(expectedHash))
            fail(
                "program SHA-256 mismatch: " + actualHash + " != " + expectedHash);
        if (actualMd5 == null || !actualMd5.toLowerCase().equals(expectedMd5))
            fail("program MD5 mismatch: " + actualMd5 + " != " + expectedMd5);
        if (!currentProgram.getName().equals(expectedModule))
            fail("program module mismatch: " + currentProgram.getName() +
                " != " + expectedModule);
        if (currentProgram.getImageBase().getOffset() != expectedBase)
            fail(
                "image base mismatch: " + currentProgram.getImageBase());
        Address base = currentProgram.getImageBase();
        long peOffset = Integer.toUnsignedLong(getInt(base.add(0x3c)));
        Address pe = base.add(peOffset);
        if (getInt(pe) != 0x00004550 || getShort(pe.add(4)) != 0x014c)
            fail("mapped PE signature/machine mismatch");
        Address optional = pe.add(24);
        if (getShort(optional) != 0x010b ||
            Integer.toUnsignedLong(getInt(optional.add(56))) != expectedImageSize ||
            expectedBase + Integer.toUnsignedLong(getInt(optional.add(16))) !=
                expectedEntry.getOffset())
            fail("mapped PE image size/entry mismatch");
        if (!currentProgram.getMemory().contains(expectedText))
            fail("target .text start is not mapped");
        Function entry = getFunctionContaining(expectedEntry);
        if (entry == null)
            fail(
                "no analyzed function contains expected entry point " + expectedEntry);

        for (int i = 0; i < sampleCount; ++i)
        {
            Address address = toAddr(args[9 + i * 2]);
            byte[] expected = decodeHex(args[10 + i * 2]);
            byte[] actual = new byte[expected.length];
            int count = currentProgram.getMemory().getBytes(address, actual);
            if (count != expected.length || !Arrays.equals(actual, expected))
                fail("mapped-byte mismatch at " + address);
        }

        println(String.join(":",
            "DXBALL_GHIDRA_ATTESTATION_OK",
            expectedHash,
            expectedMd5,
            Long.toString(expectedFileSize),
            String.format("%08X", expectedBase),
            Long.toString(expectedImageSize),
            String.format("%08X", expectedEntry.getOffset()),
            Integer.toString(sampleCount)));
        println("module=" + currentProgram.getName() +
            " image_base=" + currentProgram.getImageBase() +
            " image_size=" + expectedImageSize +
            " entry=" + expectedEntry +
            " function=" + entry.getName(true) +
            " mapped_samples=" + sampleCount);
    }
}
