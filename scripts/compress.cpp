#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main(int argc, char* argv[]) {
	printf("This is the process saved as compress.\n");
	
	//if program does not receive enough paramters then it exits
	if (argc < 3) {
		printf("Error: MISSING INPUT PARAMETERS\n");
		exit(EXIT_FAILURE);
	}

	int numParameters = argc - 2; //number of files to be manipulated
	string files[numParameters]; //file paths of files to be manipulated
	char* archiveType = argv[1]; //type of archive requested by user
	
	//add file paths from paramters to files array	
	for (int i = 0; i < numParameters; i++) {
		files[i] = argv[i+2];
	}


	if (strcmp("zip", archiveType) == 0) {
		printf("run zip commands\n");
	}
	else if (strcmp("rar", archiveType) == 0) {
		printf("run rar commands\n");
	}
	else if (strcmp("tar", archiveType) == 0) {
		printf("run tar commands\n");
	}
	else if (strcmp("7z", archiveType) == 0) {
		printf("run 7z commands\n");
	}
	else {
		printf("SUPPORT FOR REQUESTED ARCHIVE TYPE IS NOT SUPPORTED");
		exit(EXIT_FAILURE);
	}	
}
