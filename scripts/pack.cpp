#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main(int argc, char* argv[]) {
	printf("This is the process saved as pack.\n");
	
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
		files[i] = files[i].substr(7);
		printf("\n%s", files[i].c_str());
	}
	
	//get the path to be saved at from first parameter
	int position;

	string path = files[0];
	position = path.find_last_of("/");
	path = path.substr(0, position + 1);

	//get the name of the file to be compressed to
	string fileName = path;
	position = fileName.find_last_of("/");
	fileName = fileName.substr(0, position);
	position = fileName.find_last_of("/");
	fileName = fileName.substr(position+1);


	string commandLine = "";
	
	//actions based off the command
	if (strcmp("zip", archiveType) == 0) {
		printf("run zip commands\n");
		/*
			-r gets zip to recurse through directories, adding all files
			-j takes away the directory structure   //NOT A PERMANENT SOLUTION
		*/
		commandLine += "zip -r -j ";
		commandLine += path;
		commandLine += fileName;
		commandLine += ".zip ";
		for (int i = 0; i < sizeof(files)/sizeof(*files); i++) {
			position = files[i].find_last_of("/");
			commandLine += files[i];
			commandLine += " ";
		}
		system(commandLine.c_str());
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
