//Installer for nautilus actions
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>
#include <string>

using namespace std;

#include "install.h"

int main() {
	//installs nautilus-actions
	system("sudo apt-get install nautilus-actions");
	printf("\nNAUTILUS-ACTIONS INSTALL SUCCESS\n");

	printf("Copying ex into actions folder\n...\n...\n...\n");
	system("cp ex ../.local/share/file-manager/actions/");
	printf("ex is copied");
	
	Install inst;
	
	printf("\nCreating compression.desktop\n...\n...\n..."); 
	string content = inst.createString();
	string path = inst.findActionsFolder();
	string file = ("../.local/share/file-manager/actions/compression.desktop");
	
	fstream optionsFile;
	optionsFile.open(file.c_str(), fstream::out | fstream::trunc);
	optionsFile << content;
	optionsFile.close();
	printf("\ncompression.desktop created!\n");
}

/*
	createString() creates a string that is meant to populate the file 
	meant for nautilus-actions to use to display the additional options
	in the context/dropdown menu. 
*/
string Install::createString() {

	string str = "";
	str += "[Desktop Entry]\n";
	str += "Type=Action\n";
	str += "ToolbarLabel[en_CA]=CompressionManager\n";
	str += "ToolbarLabel[en]=CompressionManager\n";
	str += "ToolbarLabel[C]=CompressionManager\n";
	str += "Name[en_CA]=CompressionManager\n";
	str += "Name[en]=CompressionManager\n";
	str += "Name[C]=CompressionManager\n";
	str += "Profiles=profile-zero;\n";
	str += "\n";
	str += "[X-Action-Profile profile-zero]\n";
	str += "Path=/home/student/NautilusFCM/\n";
	str += "Name[en_CA]=./ex\n";
	str += "Name[en]=./ex\n";
	str += "Name[C]=./ex\n";
	str += "Exec=./ex\n";
	str += "ExecutionMode=DisplayOutput";

	return str;
	
}

/*
	findActionsFolder() returns a string with the path to the actions folder.
	
	MUST CHANGE
		- Must search or take an input rather than being hardcoded in.
		- Should it be relative or from root? 
*/
string Install::findActionsFolder() {
	string str = "../.local/share/file-manager/actions/";
	return str;
}

