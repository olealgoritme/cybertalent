#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Usage: %s <file>\n\n", argv[0]);
		printf("Suid-wrapper rundt md5sum.\n");
		exit(0);
	}

	char cmd[512];
	snprintf(cmd, sizeof(cmd), "/usr/bin/md5sum %s", argv[1]);

	printf("Kjører kommando:\n");
	printf(cmd);
	printf("\n\n");

	setreuid(geteuid(), geteuid());
	printf("Resultat:\n");
	system(cmd);
}
