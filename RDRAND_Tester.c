// Tests RDRAND CPU Instruction
// https://github.com/cjee21/RDRAND-Tester
// Last modified 2021-03-25

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <cpuid.h>  // for __get_cpuid intrinsic

#define VERSION 20210325
#define TEST_NUM 5

#ifdef __x86_64__
#define ARCH "x86_64"
typedef uint64_t UintRand;
#endif
#ifdef __i386__
#define ARCH "x86"
typedef uint32_t UintRand;
#endif

char *cpuid_get_brand_string(void);
_Bool supports_rdrand();
_Bool supports_rdseed();
int rdrand_step(UintRand *rand);
int rdrand_retry(unsigned int retries, UintRand *rand);

// main
int main() {
    int success = 0;                   // flag for RDRAND success
    UintRand rand_num[TEST_NUM] = {0}; // 5 random numbers from RDRAND
    char *brand_string = NULL;         // pointer to CPU brand string
    const char support[2][15] = {      // string indicating support
        "Not Supported",
        "Supported"
    };
    _Bool bug = 0; // boolean for AMD RDRAND bug

    // header
    printf("================================================================================\n"
           "RDRAND Tester v%i %s\n"
           "--------------------------------------------------------------------------------\n"
           "Compiled on %s\nCompiled with GNU Compiler Collection (GCC) %s\n"
           "================================================================================\n\n",
           VERSION, ARCH, __DATE__, __VERSION__);

    // display CPU name
    brand_string = cpuid_get_brand_string();
    printf("Running on %s\n", brand_string);
    free(brand_string);

    // check that CPU supports RDRAND
    if (!supports_rdrand()) {
        printf("This CPU does NOT support the RDRAND instruction!\n\n");
        return 0;
    }

    // check RDSEED support and display results
    printf("This CPU supports the following instructions:\n"
           " RDRAND: %s\n"
           " RDSEED: %s\n\n"
           "Testing RDRAND...\n\n",
           support[1], support[supports_rdseed()]);

    // test 5 times
    for (int i = 0; i < 5; ++i) {
        // max 10 retires to get a successful RDRAND
        success = rdrand_retry(10, &rand_num[i]);
        if (!success) {
            printf("The RDRAND instruction of this CPU appears to be NOT working.\n\n");
            return 0;
        }

        // display results
#ifdef __x86_64__
        printf("try: %i   success: %i   random number: %20llu (0x%016llx)\n", i + 1, success, (unsigned long long)rand_num[i], (unsigned long long)rand_num[i]);
#endif
#ifdef __i386__
        printf("try: %i   success: %i   random number: %10u (0x%08x)\n", i + 1, success, (unsigned)rand_num[i], (unsigned)rand_num[i]);
#endif
    }

    // check for AMD bug where numbers generated are similar
    for (int a = 0; a < TEST_NUM; ++a) {
        for (int b = (a + 1); b < TEST_NUM; ++b) {
            if (rand_num[a] == rand_num[b]) {
                bug = 1;
                break;
            }
        }
    }
    if (bug) {
        printf("\nThe RDRAND instruction of this CPU appears to be broken!\n"
               "The numbers generated are NOT random but the CPU returns the success flag.\n\n");
    }
    else {
        printf("\nThe RDRAND instruction of this CPU appears to be working.\n"
               "The numbers generated should be different and random.\n"
               "If the numbers generated appears to be similar, the RDRAND instruction is \nbroken.\n\n");
    }

    return 0;
}

// remove trailing space
void remove_leading_space(char *string) {
    unsigned p = 0;
    if (string[0] != ' ') return;                        // return if no space to be removed
    while (string[p] == ' ') ++p;                        // find first character
    memmove(string, string + p, strlen(string) - p + 1); // move string to beginning
}

// get CPU name
// adapted from https://github.com/vusec/ridl/blob/master/source/x86/cpuid.c
char *cpuid_get_brand_string(void) {
    char name[48] = {0};
    unsigned regs[4] = {0};

    if (__get_cpuid_max(0x80000000, NULL) < 0x80000004)
        return strdup("Unknown");

    for (unsigned level = 0; level < 3; ++level) {
        __get_cpuid(0x80000002 + level, regs + 0, regs + 1, regs + 2, regs + 3);
        memcpy(name + level * 16, regs, 16);
    }

    name[47] = '\0';

    remove_leading_space(name); // shift brand string to beginning for some CPU that use right justify

    return strdup(name);
}

// check RDRAND support
_Bool supports_rdrand() {
    const unsigned RDRAND_bit = (1 << 30);

    unsigned eax = 0, ebx = 0, ecx = 0, edx = 0;
    if (__get_cpuid(1, &eax, &ebx, &ecx, &edx))
        return ((ecx & RDRAND_bit) == RDRAND_bit);
    else
        return 0;
}

// check RDSEED support
_Bool supports_rdseed() {
    const unsigned RDSEED_bit = (1 << 18);

    unsigned eax = 0, ebx = 0, ecx = 0, edx = 0;
    if (__get_cpuid_count(7, 0, &eax, &ebx, &ecx, &edx))
        return ((ebx & RDSEED_bit) == RDSEED_bit);
    else
        return 0;
}

// invoke RDRAND
// adapted from https://software.intel.com/en-us/articles/intel-digital-random-number-generator-drng-software-implementation-guide
int rdrand_step(UintRand *rand) {
    unsigned char ok;

    __asm__ volatile("rdrand %0;"
                     "setc %1"
                     : "=r"(*rand), "=qm"(ok));

    return (int)ok;
}

// RDRAND retry loop
// adapted from https://software.intel.com/en-us/articles/intel-digital-random-number-generator-drng-software-implementation-guide
int rdrand_retry(unsigned int retries, UintRand *rand) {
    unsigned count = 0;

    while (count <= retries) {
        if (rdrand_step(rand)) {
            return 1;
        }
        ++count;
    }

    return 0;
}
