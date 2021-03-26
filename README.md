# RDRAND-Tester
This is an application to test the functionality of the RDRAND instruction in x86 CPUs. It additionally shows the presence of the RDSEED instruction. This may be useful to test for the presence of buggy RDRAND implementations which are present on some CPUs that causes issues with certain software which depends on this instruction.

## Pre-built Binaries
The pre-built binaries can be found in the [releases](https://github.com/cjee21/RDRAND-Tester/releases) section. The binaries were built as described below.
### Windows
1. Obtain MinGW/GCC from winlibs.
2. Prepare manifest for UAC by executing `windres win_manifest/resource.rc manifest.o`.
3. Build the binary by executing `gcc RDRAND_Tester.c manifest.o -o RDRAND_Tester.exe -Wall -Wconversion -Wformat-security -std=c17 -O3 -Wl,--nxcompat,--dynamicbase,--high-entropy-va -s`.
### Linux
1. Install GCC.
2. Build the binary by executing `gcc RDRAND_Tester.c -o RDRAND_Tester -Wall -Wconversion -Wformat-security -O3 -fstack-protector-strong -D_FORTIFY_SOURCE=2 -fPIE -fstack-clash-protection -fcf-protection -Wl,-z,relro,-z,now,-pie,--hash-style=gnu,--no-copy-dt-needed-entries,--as-needed -s`.

## Example Output
Below is an example of the output produced by this application on a CPU with a properly functioning RDRAND instruction.
```
================================================================================
RDRAND Tester v20210325 x86_64
--------------------------------------------------------------------------------
Compiled on Mar 25 2021
Compiled with GNU Compiler Collection (GCC) 10.2.0
================================================================================

Running on Intel(R) Core(TM) i5-7500 CPU @ 3.40GHz
This CPU supports the following instructions:
 RDRAND: Supported
 RDSEED: Supported

Testing RDRAND...

try: 1   success: 1   random number:  9945190003039608398 (0x8a04699daaf11e4e)
try: 2   success: 1   random number:  3395727470799627623 (0x2f200c24b30c2567)
try: 3   success: 1   random number:  9825688122838044683 (0x885bdb49fb89500b)
try: 4   success: 1   random number:  4449178948850472862 (0x3dbea8ae6460d79e)
try: 5   success: 1   random number:   572366417622630268 (0x07f174396bc27f7c)

The RDRAND instruction of this CPU appears to be working.
The numbers generated should be different and random.
If the numbers generated appears to be similar, the RDRAND instruction is
broken.
```
