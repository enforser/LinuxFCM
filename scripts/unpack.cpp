#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main(int argc, char* argv[]) {
	printf("This is the process saved as unpack.\n");
	
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
	
	/*

	actions based off the command
	
	Each section of the following else/if statements constructes a string (commandLine)
	which is meant to be passed to a system command. 

	These are the commands that call the compression tools. 

	*/

	if (strcmp("zip", archiveType) == 0 || strcmp("rar", archiveType) == 0 ||
	    strcmp("tar", archiveType) == 0 || strcmp("7z", archiveType) == 0) {  //zip
		/*
			-r gets zip to recurse through directories, adding all files
			-j takes away the directory structure   //NOT A PERMANENT SOLUTION
		*/
		commandLine += "atool -X ";
		//commandLine += " -d ";
		commandLine += " "; 
		commandLine += path;
		commandLine += " ";
		commandLine += files[0];
		
	}
	else {
		printf("SUPPORT FOR REQUESTED ARCHIVE TYPE IS NOT SUPPORTED");
		exit(EXIT_FAILURE);
	}

	//run the corresponding command on the system
	system(commandLine.c_str());	
}
