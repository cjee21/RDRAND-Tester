# RDRAND-Tester
This is an application to test the functionality of the RDRAND instruction in x86 CPUs. It additionally shows the presence of the RDSEED instruction. This may be useful to test for the presence of buggy RDRAND implementations which are present on some CPUs that causes issues with certain software which depends on this instruction.

## Pre-built Binaries
The pre-built binaries can be found in the [releases](https://github.com/cjee21/RDRAND-Tester/releases) section. The binaries were built as described below.
### Windows
1. Obtain MinGW/GCC from [winlibs](https://github.com/brechtsanders/winlibs_mingw).
2. Prepare manifest for UAC by executing `windres win_manifest\resource.rc obj\manifest.o`.
3. Build the binary by executing `gcc RDRAND_Tester.c obj\manifest.o -o release\RDRAND_Tester_Windows.exe -Wall -Wconversion -Wformat-security -std=c17 -O3 -static -fstack-protector-strong -D_FORTIFY_SOURCE=2 -fPIE -fstack-clash-protection -fcf-protection -Wl,-pie,--no-copy-dt-needed-entries,--as-needed,--nxcompat,--dynamicbase,--high-entropy-va -s`.
### Linux
1. Install GCC.
2. Build the binary by executing `gcc RDRAND_Tester.c -o release/RDRAND_Tester_Linux -Wall -Wconversion -Wformat-security -O3 -fstack-protector-strong -D_FORTIFY_SOURCE=2 -fPIE -fstack-clash-protection -fcf-protection -Wl,-z,relro,-z,now,-pie,--hash-style=gnu,--no-copy-dt-needed-entries,--as-needed -s`.

## Example Output
Below is an example of the output produced by this application on a CPU with a properly functioning RDRAND instruction.
```
================================================================================
RDRAND Tester v20210328 x86_64
--------------------------------------------------------------------------------
Compiled on Apr 16 2021
Compiled with GNU Compiler Collection (GCC) 10.3.0
================================================================================

Running on Intel(R) Core(TM) i5-7500 CPU @ 3.40GHz
This CPU supports the following instructions:
 RDRAND: Supported
 RDSEED: Supported

Testing RDRAND...

try:   1   success: 1   random number:  5012598193280705724 (0x4590537fb842e4bc)
try:   2   success: 1   random number: 13057969725578991747 (0xb5373a4804f0d883)
try:   3   success: 1   random number: 15258542471905877516 (0xd3c13b88f4291e0c)
try:   4   success: 1   random number:  2878339394249548515 (0x27f1ea6dd141e2e3)
try:   5   success: 1   random number:  5238856747007213768 (0x48b428746a8600c8)
try:   6   success: 1   random number: 12836524077560437497 (0xb2247ea341bd1af9)
try:   7   success: 1   random number: 15869268653934935726 (0xdc3af7c303087eae)
try:   8   success: 1   random number: 17374580931805302711 (0xf11ee94d9187cfb7)
try:   9   success: 1   random number:  2260023498090627146 (0x1f5d3765bbba404a)
try:  10   success: 1   random number:   380621888462874021 (0x05483d97479165a5)
try:  11   success: 1   random number: 17765201729153443702 (0xf68aacd93d58a776)
try:  12   success: 1   random number: 17666429294697117999 (0xf52bc3d7bff9f92f)
try:  13   success: 1   random number: 10586101450554073644 (0x92e9632e8485e22c)
try:  14   success: 1   random number:  3888766898547441689 (0x35f7ace40237c019)
try:  15   success: 1   random number:  5764275204437754665 (0x4ffed1c20c1ac329)
try:  16   success: 1   random number:  8845614113758411495 (0x7ac1ef2b9ec07ae7)
try:  17   success: 1   random number:  4829856922400078030 (0x43071947ff9e38ce)
try:  18   success: 1   random number:  6630984605313841605 (0x5c05fd5db6d0b9c5)
try:  19   success: 1   random number:  6917881360425400011 (0x60014071de73b6cb)
try:  20   success: 1   random number: 18115961797194281831 (0xfb68d345a64ff367)

The RDRAND instruction of this CPU appears to be working.
The numbers generated should be different and random.
If the numbers generated appears to be similar, the RDRAND instruction is
broken.
```
