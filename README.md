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
