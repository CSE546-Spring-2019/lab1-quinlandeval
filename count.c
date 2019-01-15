/* 
	Author:
	Quinlan DeVal
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *input, *output;
	int stringLength;
	long int position, tempPosition, fileSize, matches;
	char search[20];
	char string[20];

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
	fprintf(output, "Size of file is %li \n", fileSize);	
	fseek(input, 0, SEEK_SET);
	printf("Size of file is %li \n", fileSize);

	// Set up variables for loop.
	matches = 0;
	position = 0;
	tempPosition = 0;
	while (1) {
			// Read line from file.
			tempPosition += fread(search, 1, stringLength, input);

			// Compare line to search string.
			if (strstr(search, string) != NULL) {
				matches++;
			} else if (tempPosition >= fileSize) {
				break;
			} 
			
			// Increment position.
			position ++;
			tempPosition = position;
			fseek(input, position, SEEK_SET);

	}
	
	// Output results of search.
	fprintf(output, "Number of matches = %li \n", matches);
	printf("Number of matches = %li \n", matches);

	// Close input and output files.
	fclose(input);
	fclose(output);

	return 0;

}
