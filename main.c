#include <stdio.h>

extern int decode_file(FILE*);

int main(int argc, const char* argv[]) {
	if (argc < 2) {
		printf("Usage: decoder <file1> <file2> ... <fileN>\n");
		return 1;
	}

	argv++; // remove executable name
	
	while (*argv) {
		FILE* file = fopen(*argv, "rb");
		if (!file) {
			printf("Failed to open file %s. Skipping\n", *argv);
			continue;
		}

		if (decode_file(file)) {
			printf("Error decoding file %s. Exiting\n", *argv);
			fclose(file);
			break;
		}

		fclose(file);
		argv++;
	}
	return 0;
}
