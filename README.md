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
RDRAND Tester v20210328 x86_64
--------------------------------------------------------------------------------
Compiled on Mar 28 2021
Compiled with GNU Compiler Collection (GCC) 10.2.0
================================================================================

Running on Intel(R) Core(TM) i5-7500 CPU @ 3.40GHz
This CPU supports the following instructions:
 RDRAND: Supported
 RDSEED: Supported

Testing RDRAND...

try:   1   success: 1   random number:  5927373127459600547 (0x52424274716cf8a3)
try:   2   success: 1   random number: 14017878035415681363 (0xc28981cda5b3c953)
try:   3   success: 1   random number: 11368319004864247053 (0x9dc461e72a41750d)
try:   4   success: 1   random number: 18347068400624210050 (0xfe9de180e1001082)
try:   5   success: 1   random number: 14957356374446914942 (0xcf93346005d53d7e)
try:   6   success: 1   random number:  6886028350544393428 (0x5f90164d1377b4d4)
try:   7   success: 1   random number:  5278664944371065288 (0x494195cca18b61c8)
try:   8   success: 1   random number:  4521303152649964506 (0x3ebee5432f8e0bda)
try:   9   success: 1   random number: 15534923940847327720 (0xd797230442ea99e8)
try:  10   success: 1   random number:  3670930976467298914 (0x32f1c4460f4faa62)
try:  11   success: 1   random number: 11958149365487776571 (0xa5f3e17dacf6333b)
try:  12   success: 1   random number:  5020999880033320980 (0x45ae2cc9daaa4014)
try:  13   success: 1   random number: 16330053013882295375 (0xe2a000b21fc0544f)
try:  14   success: 1   random number:  1697571542229226260 (0x178efc52d3629314)
try:  15   success: 1   random number: 12609148070264663482 (0xaefcb15d206d6dba)
try:  16   success: 1   random number: 11259769587200697446 (0x9c42bcc861d82466)
try:  17   success: 1   random number:  4671383702711260616 (0x40d416ba41a755c8)
try:  18   success: 1   random number:  2964570895778270359 (0x29244585d2534c97)
try:  19   success: 1   random number: 16437644231134559834 (0xe41e3e567d063e5a)
try:  20   success: 1   random number: 12484713343223626958 (0xad429ca3896c7cce)

The RDRAND instruction of this CPU appears to be working.
The numbers generated should be different and random.
If the numbers generated appears to be similar, the RDRAND instruction is
broken.
```
