//Installer for nautilus actions
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>
#include <string.h>
#include <unistd.h>

using namespace std;

#include "install.h"

int main() {
	
	//curent working directory path
	
	char cwdpath[256];

	getcwd(cwdpath, 255);
	strcat(cwdpath, "/");
	
	char inspath[256];
	char scrpath[256];

	strncpy(inspath, cwdpath, sizeof(cwdpath));
	strncpy(scrpath, cwdpath, sizeof(cwdpath));

	string installPath = strcat(inspath, "install-bin/");
	string scriptsPath = strcat(scrpath, "scripts/");

	printf("Found Paths:\n%s\n%s\n%s\n", cwdpath, installPath.c_str(), scriptsPath.c_str());

	//installs nautilus-actions
	system("sudo apt-get install nautilus-actions");
	printf("\nNAUTILUS-ACTIONS INSTALL SUCCESS\n");

	printf("Copying ex into actions folder\n...\n...\n...\n");
	system("cp scripts/ex ../.local/share/file-manager/actions/");
	printf("ex is copied");

	printf("Installing unzip..\n");
	system("sudo apt-get install unzip");

	printf("Installing rar..\n");
	system("sudo apt-get install rar");

	printf("Installing unrar\n");
	system("sudo apt-get install unrar");

	//Read www.nongnu.org/atool for more info
	//Will allow us to use the same command structure for different compression methods
	//Example "apack -e (zip or rar or tar.gz) filename(s)"
	printf("Installing atool\n");
	system("sudo apt-get install atool");


	Install inst;

	string path = inst.findActionsFolder();
	fstream optionsFile;

//BEGIN ADDING MAIN MENU .desktop FILE
	
	//CREATE THE MENU
	inst.addMenu("Compress Manager", "pack;unpack;convert;", "compressionmanager");
	inst.addMenu("pack", "packzip;packrar;packtar;pack7z;", "pack");
	inst.addMenu("unpack", "unpackzip;unpackrar;unpacktar;unpack7z;", "unpack");
	inst.addMenu("convert", "convertzip;convertrar;converttar;convert7z;", "convert");

	//CREATE OPTIONS TO FILL MENU
	inst.addOption("zip",    "./pack zip",  "packzip", scriptsPath);
	inst.addOption("rar",    "./pack rar",  "packrar", scriptsPath);
	inst.addOption("tar.gz", "./pack tar",  "packtar", scriptsPath);
	inst.addOption("7zip",   "./pack 7z",   "pack7z", scriptsPath);
	inst.addOption("zip",    "./unpack zip",      "unpackzip", scriptsPath);
	inst.addOption("rar",    "./unpack rar",      "unpackrar", scriptsPath);
	inst.addOption("tar.gz", "./unpack tar",      "unpacktar", scriptsPath);
	inst.addOption("7zip",   "./unpack 7z",      "unpack7z", scriptsPath);
	inst.addOption("zip",    "./convert zip",      "convertzip", scriptsPath);
	inst.addOption("rar",    "./convert rar",      "convertrar", scriptsPath);
	inst.addOption("tar.gz", "./convert tar",      "converttar", scriptsPath);
	inst.addOption("7zip",   "./convert 7z",      "convert7z", scriptsPath);
}

//Takes info needed for new sub-menu option and adds it
//  Note: Must still add the options "name" to itemList in createMenu()
void Install::addOption(string name, string action, string filename, string path) {
	//sets .desktop filename
	filename = filename + ".desktop";
	//gets the text to be added to the file
	string optionText = createOption(name, action, path);
	//gets the fullpath of the file
	string actionFile = (findActionsFolder() + filename);

	//open stream
	fstream optionsFile;

	optionsFile.open(actionFile.c_str(), fstream::out | fstream::trunc);
	optionsFile << optionText;
	optionsFile.close();
	printf("%s", filename.c_str());
	printf(" was created successfully!\n");
}

//Takes info needed for new sub-menu option and adds it
//  Note: Must still add the options "name" to itemList in createMenu()
void Install::addMenu(string name, string options, string filename) {
	//sets .desktop filename
	filename = filename + ".desktop";
	//gets the text to be added to the file
	string optionText = createMenu(name, options);
	//gets the fullpath of the file
	string actionFile = (findActionsFolder() + filename);

	//open stream
	fstream optionsFile;

	optionsFile.open(actionFile.c_str(), fstream::out | fstream::trunc);
	optionsFile << optionText;
	optionsFile.close();
	printf("%s", filename.c_str());
	printf(" was created successfully!\n");
}



//Creates the string to be outputted to an action .desktop file
string Install::createOption(string name, string action, string path) {

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
	str += "Path="; str += path;
	str += "\nName[en_CA]="; str += action;
	str += "\nName[en]=";str += action;
	str += "\nName[C]=";str += action;
	str += "\nExec=";str += action;
	str += " %"; str += "U";
	str += "\nExecutionMode=DisplayOutput";

	return str;
}


// Create a string for NA to use to create a menu to store actions
string Install::createMenu(string name, string options) {

	string str = "";
	str += "[Desktop Entry]\n";
	str += "Type=Menu\n";
	str += "Name[en_CA]="; str += name;
	str += "\nName[en]="; str += name;
	str += "\nName[C]="; str += name;

	//LIST OF ALL OPTION FILES, MUST BE EDITED WHEN REMOVING/ADDING OPTIONS TO SUBMENU
	str += "\nItemsList=";
	str += options;

	return str;

}

/*
	findActionsFolder() returns a string with the path to the actions folder
*/
string Install::findActionsFolder() {
	
	string homeDir = getenv("HOME");
	

	homeDir +=  "/.local/share/file-manager/actions/";

	printf("\n%s\n", homeDir.c_str());
	return homeDir;
}
