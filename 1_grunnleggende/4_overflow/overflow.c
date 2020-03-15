#include <sys/mman.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define SHELLCODE_ADDRESS 0x303030303030
#define KGREEN "\033[01;32m"
#define KRED "\033[31m"
#define KRESET "\033[0m"

/*
 * Allocate a page of executable memory at SHELLCODE_ADDRESS,
 * and fill it with nop-sled and contents of environment variable SHC.
 * If SHC is not set, fill with breakpoints to trap program flow.
 */
char *
prep_shellcode(void)
{
	char *shc    = getenv("SHC");
	char *retval = mmap((char *)(SHELLCODE_ADDRESS & ~(4096 - 1)),
	                    4096,
	                    PROT_READ | PROT_WRITE | PROT_EXEC,
	                    MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED,
	                    -1,
	                    0);

	if (retval == MAP_FAILED) {
		printf("Failed to mmap area for shellcode: %s\n", strerror(errno));
		exit(1);
	}

	if (shc && strlen(shc) < 4096) {
		/* SHC is set; fill memory page with nops and stuff shellcode at the end */
		memset(retval, 0x90, 4096);
		memcpy(retval + 4096 - strlen(shc), shc, strlen(shc));
	} else {
		/* No SHC; trigger trace/breakpoint trap */
		memset(retval, 0xcc, 4096);
	}

	/* Returning retval is more precise, but leaves a confusing null-byte in the address. */
	return (char *)SHELLCODE_ADDRESS;
}

/*
 * Print hexdump of memory, with one memory range ('modified') highlighted.
 * Optional arguments are address/name pairs to describe content of each line.
 */
void
hexdump(unsigned char *base, long len, long width,
        unsigned char *modified_start, long modified_length,
        long name_list_len, ...)
{
	void *  named_addresses[name_list_len / 2];
	char *  named_addresses_name[name_list_len / 2];
	va_list name_list;
	va_start(name_list, name_list_len);

	for (int n = 0; n < name_list_len / 2; n++) {
		named_addresses[n]      = va_arg(name_list, void *);
		named_addresses_name[n] = va_arg(name_list, char *);
	}

	for (int i = len; i >= 0; i -= width) {
		/* Print memory address, and possibly overwrite with name from named_addresses */
		printf("%-16p", base + i);
		for (int n = 0; n < name_list_len / 2; n++) {
			if (base + i == named_addresses[n]) {
				printf("\r%-16s", named_addresses_name[n]);
				break;
			}
		}

		/* Print hex dump of next `width` bytes */
		/* Use red color for bytes modified by strcpy */
		for (int n = 0; n < width; n++) {
			if (modified_start <= base + i + n && base + i + n < modified_start + modified_length)
				printf(KRED);
			printf(" %02x" KRESET, base[i + n]);
		}

		/* Print ascii representation, or '.' if byte is non-printable */
		/* Use red color for bytes modified by strcpy */
		printf("  |");
		for (int n = 0; n < width; n++) {
			if (modified_start <= base + i + n && base + i + n < modified_start + modified_length)
				printf(KRED);
			printf("%c" KRESET, (base[i + n] >= 0x20 && base[i + n] < 0x7f) ? base[i + n] : '.');
		}
		printf("|\n");
	}
}

int
main(int argc, char *argv[])
{
	long           above = 0;
	unsigned char  buffer[32];
	long           below         = 0x6867666564636261;
	long           width         = 8;
	unsigned char *shellcode_ptr = prep_shellcode();
	unsigned char *p             = (void *)&p;

	printf("\nBefore strcpy:\n");
	printf("above = 0x%16lx\n", above);
	printf("below = 0x%16lx\n", below);

	/* Copy first argument to buffer, potentially overflowing the stack */
	if (argc >= 2)
		strcpy(buffer, argv[1]);

	printf("\nAfter strcpy:\n");
	printf("above = 0x%16lx\n", above);
	printf("below = 0x%16lx\n", below);

	printf("\nStackdump:\n");
	hexdump(p, 128, width, buffer, argc >= 2 ? strlen(argv[1]) + 1 : 0, 16, &above, "&above", &buffer, "&buffer", &below, "&below", &width, "&width", &shellcode_ptr, "&shellcode_ptr", &p, "&p", p + 96, "stored rbp", p + 104, "stored rip");

	/* Now that output and overflows are done with, inspect the results */

	if (above == 0x4847464544434241) {
		printf(KGREEN "\nabove is correct!\n" KRESET);
		printf("Next step is to adjust the stored rip to point to shellcode\n");
	} else if (argc > 1 && strlen(argv[1]) >= (unsigned char *)&above - buffer) {
		printf(KRED "\nabove has incorrect value.\n" KRESET);
		printf("Read source code to find the magic number.\n");
		/* Call exit() to avoid returning to user controlled memory */
		exit(1);
	} else {
		printf("\nabove has not been overwritten.\n");
		printf("Supply an argument which is long enough to overflow buffer, ");
		printf("and modify the value of 'above'.\n");
	}

	/* Return, possibly to user controlled memory */
	return 0;
}
