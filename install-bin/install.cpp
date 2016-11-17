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

//STARTS ADDING SUBMENU OPTION .desktop FILES
	printf("\nCreating compress.desktop\n...\n...\n...");
	string compressAction = inst.createOption("Compress", "./ex");
	string option1 = inst.createOption("Option1", "ls");
	string option2 = inst.createOption("Option2", "./install");

	string compressActionFile = ("../.local/share/file-manager/actions/compress.desktop");
	string option1ActionFile = ("../.local/share/file-manager/actions/option1.desktop");
	string option2ActionFile = ("../.local/share/file-manager/actions/option2.desktop");
	
	optionsFile.open(compressActionFile.c_str(), fstream::out | fstream::trunc);
	optionsFile << compressAction;
	optionsFile.close();
	printf("\ncompress.desktop created!\n");

	optionsFile.open(option1ActionFile.c_str(), fstream::out | fstream::trunc);
	optionsFile << option1;
	optionsFile.close();
	printf("\noption1.desktop created!\n");

	optionsFile.open(option2ActionFile.c_str(), fstream::out | fstream::trunc);
	optionsFile << option2;
	optionsFile.close();
	printf("\noption2.desktop created!\n");
//ENDS

//BEGIN ADDING MAIN MENU .desktop FILE
	printf("\nCreating compressionmanager.desktop\n...\n...\n...");
	string compressMenu = inst.createMenu();
	string menuFile = ("../.local/share/file-manager/actions/compressionmanager.desktop");

	optionsFile.open(menuFile.c_str(), fstream::out | fstream::trunc);
	optionsFile << compressMenu;
	optionsFile.close();
//ENDS

}

/*
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
*/
string Install::createOption(string name, string action) {

	string str = "";
	str += "[Desktop Entry]\n";
	str += "Type=Action\n";
	str += "ToolbarLabel[en_CA]="; str += name;
	str += "\nToolbarLabel[en]="; str += name;
	str += "\nToolbarLabel[C]="; str += name;
	str += "\nName[en_CA]="; str += name;
	str += "\nName[en]="; str += name;
	str += "\nName[C]="; str += name;
	str += "\nProfiles=profile-zero;\n";
	str += "\n";
	str += "[X-Action-Profile profile-zero]\n";
	str += "Path=/home/student/NautilusFCM/\n";
	str += "Name[en_CA]="; str += action;
	str += "\nName[en]=";str += action;
	str += "\nName[C]=";str += action;
	str += "\nExec=";str += action;
	str += "\nExecutionMode=DisplayOutput";

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

	//LIST OF ALL OPTION FILES, MUST BE EDITED WHEN REMOVING/ADDING OPTIONS TO SUBMENU
	str += "ItemsList=compress;option1;option2;\n";

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
