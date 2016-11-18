#include <iostream>
#include <stdio.h>

int main(int argc, char* argv[]) {
	printf("This is the process saved as ex.\n");

	//The num of files passed in through command line
	int numParameters = argc - 1;
	
	printf("There are %d files to be processed.\n", numParameters);
	printf("\nThey include:\n");
	
	for (int i = 1; i < numParameters+1; i++) {
		
		printf("    %d)    %s\n", i, argv[i]);
	}
	
}
