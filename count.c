/* 
	Author:
	Quinlan DeVal
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *input, *output;
	int fileSize, stringLength, matches, position, tempPosition;
	char search[20];
	char string[20];
	char size[60];
	char match[60];

	// Check number of arguments.
	if (argc < 4) {
		printf("Usage is: count <inputfile> <searchstring> <outputfile> \n");
		exit(1);
	}

	// Check length of search string.
	stringLength = strlen(argv[2]);
	if (stringLength > 20) {
		printf("Search string must be 20 bytes or less. \n");
		exit(-1);
	}
	strcpy(string, argv[2]);

	// Attempt to open input file.
	input = fopen(argv[1], "rb");
	if (input == NULL) {
		printf("Error opening input file. \n");
		exit(-1);
	}

	// Attempt to open output file.
	output = fopen(argv[3], "w");
	if (output == NULL) {
		printf("Error opening output file. \n");
		exit(-1);
	}
	
	// Evaluate size of file.
	fseek(input, 0, SEEK_END);
	fileSize = ftell(input);
	snprintf(size, 30, "Size of file is %d\n", fileSize);	
	fwrite(size, 1, 30, output);
	fseek(input, 0, SEEK_SET);
	printf(size);

	// Set up variables for loop.
	matches = 0;
	position = 0;
	tempPosition = 0;
	while (1) {
			// Read line from file.
			tempPosition += fread(search, 1, stringLength, input);

			// Compare line to search string.
			if (strcmp(search, string) == 0) {
				matches++;
			} else if (tempPosition >= fileSize) {
				break;
			} 
			
			// Increment position.
			position += 1;
			tempPosition = position;
			fseek(input, position, SEEK_SET);

	}
	
	// Output results of search.
	snprintf(match, 40, "Number of matches = %i \n", matches);
	fwrite(match, 1, 40, output);
	printf(match);

	// Close input and output files.
	fclose(input);
	fclose(output);

	return 0;

}
