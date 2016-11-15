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

	printf("Installing unzip..\n");
	system("sudo apt-get install unzip");

	printf("Installing rar..\n");
	system("sudo apt-get install rar");

	printf("Installing unrar\n");
	system("sudo apt-get install unrar");


	Install inst;

	string path = inst.findActionsFolder();
	fstream optionsFile;

	printf("\nCreating compress.desktop\n...\n...\n...");
	string compressAction = inst.createAction();
	string actionFile = ("../.local/share/file-manager/actions/compress.desktop");

	optionsFile.open(actionFile.c_str(), fstream::out | fstream::trunc);
	optionsFile << compressAction;
	optionsFile.close();
	printf("\ncompress.desktop created!\n");

	printf("\nCreating compressionmanager.desktop\n...\n...\n...");
	string compressMenu = inst.createMenu();
	string menuFile = ("../.local/share/file-manager/actions/compressionmanager.desktop");

	optionsFile.open(menuFile.c_str(), fstream::out | fstream::trunc);
	optionsFile << compressMenu;
	optionsFile.close();
}

// Create a string for NA to use to create an action
string Install::createAction() {

	string str = "";
	str += "[Desktop Entry]\n";
	str += "Type=Action\n";
	str += "ToolbarLabel[en_CA]=Compress\n";
	str += "ToolbarLabel[en]=Compress\n";
	str += "ToolbarLabel[C]=Compress\n";
	str += "Name[en_CA]=Compress\n";
	str += "Name[en]=Compress\n";
	str += "Name[C]=Compress\n";
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

// Create a string for NA to use to create a menu to store actions
string Install::createMenu() {

	string str = "";
	str += "[Desktop Entry]\n";
	str += "Type=Menu\n";
	str += "Name[en_CA]=CompressionManager\n";
	str += "Name[en]=CompressionManager\n";
	str += "Name[C]=CompressionManager\n";
	str += "ItemsList=compress;\n";

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
