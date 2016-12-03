//Installer for nautilus actions
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <cstdio>

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

	printf("Installing archive types\n");
	system("sudo apt-get install zip");
	system("sudo apt-get install unzip");
	system("sudo apt-get install p7zip-full");
	system("sudo apt-get install rar");
	system("sudo apt-get install unrar");
	system("sudo apt-get install tar.gz");

	//Read www.nongnu.org/atool for more info
	//Will allow us to use the same command structure for different compression methods
	//Example "apack -e (zip or rar or tar.gz) filename(s)"
	printf("Installing atool\n");
	system("sudo apt-get install atool");

	Install inst;

	string path = inst.findActionsFolder();
	fstream optionsFile;

//BEGIN ADDING MAIN MENU .desktop FILE

	string mimeTypes = "MimeTypes=application/x-7z-compressed;application/zip;application/x-rar-compressed;application/x-gzip;";
	string allTypes = "MimeTypes=*;";
	//string mimeTypes = "MimeTypes=*;";

	//CREATE THE MENU
	inst.addMenu("Compress Manager", "pack;unpack;convert;", allTypes, "compressionmanager");
	inst.addMenu("pack", "packzip;packrar;packtar;pack7z;", mimeTypes, "pack");
	inst.addMenu("convert", "convertzip;convertrar;converttar;convert7z;", mimeTypes, "convert");

	//CREATE OPTIONS TO FILL MENU
	inst.addOption("zip",    "./pack zip",    "packzip",    allTypes,  scriptsPath);
	inst.addOption("rar",    "./pack rar",    "packrar",    allTypes,  scriptsPath);
	inst.addOption("tar.gz", "./pack tar",    "packtar",    allTypes,  scriptsPath);
	inst.addOption("7zip",   "./pack 7z",     "pack7z",     allTypes,  scriptsPath);
	inst.addOption("unpack", "./unpack zip",  "unpack",     mimeTypes, scriptsPath);
	inst.addOption("zip",    "./convert zip", "convertzip", mimeTypes, scriptsPath);
	inst.addOption("rar",    "./convert rar", "convertrar", mimeTypes, scriptsPath);
	inst.addOption("tar.gz", "./convert tar", "converttar", mimeTypes, scriptsPath);
	inst.addOption("7zip",   "./convert 7z",  "convert7z",  mimeTypes, scriptsPath);

	inst.fixPreferences();
}

//Takes info needed for new sub-menu option and adds it
//  Note: Must still add the options "name" to itemList in createMenu()
void Install::addOption(string name, string action, string filename, string mimeType, string path) {
	//sets .desktop filename
	filename = filename + ".desktop";
	//gets the text to be added to the file
	string optionText = createOption(name, action, path, mimeType);
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
void Install::addMenu(string name, string options, string mimeTypes, string filename) {
	//sets .desktop filename
	filename = filename + ".desktop";
	//gets the text to be added to the file
	string optionText = createMenu(name, options, mimeTypes);
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

//Replaces the NA config file with one that has the settings we need, all other parts of the file are added by NA when needed
void Install::fixPreferences() {
	string homeDir = getenv("HOME");
	ofstream fileout((homeDir + "/.config/nautilus-actions/temp.text").c_str()); //Temporary file

	string strTemp;

	strTemp = "[runtime]\n";
	fileout << strTemp;
	strTemp = "items-level-zero-order=compressionmanager;\n";
	fileout << strTemp;
	strTemp = "items-create-root-menu=false\n";
	fileout << strTemp;
	strTemp = "items-add-about-item=false\n";
	fileout << strTemp;
	strTemp = "items-list-order-mode=ManualOrder\n";
	fileout << strTemp;

	remove((homeDir + "/.config/nautilus-actions/nautilus-actions.conf").c_str()); //Remove the NA config file
	rename((homeDir + "/.config/nautilus-actions/temp.text").c_str(), (homeDir + "/.config/nautilus-actions/nautilus-actions.conf").c_str()); //Replace it with the temp file
}

//Creates the string to be outputted to an action .desktop file
string Install::createOption(string name, string action, string path, string mimeTypes) {

	string str = "";
	str += "[Desktop Entry]\n";
	str += "Type=Action\n";
	str += "ToolbarLabel[en_CA]="; str += name;
	str += "\nToolbarLabel[en]="; str += name;
	str += "\nToolbarLabel[C]="; str += name;
	str += "\nName[en_CA]="; str += name;
	str += "\nName[en]="; str += name;
	str += "\nName[C]="; str += name;
	str += "\n";
	str += mimeTypes;
	str += "\nProfiles=profile-zero;\n";
	str += "\n";
	str += "[X-Action-Profile profile-zero]\n";
	str += "Path="; str += path;
	str += "\nName[en_CA]="; str += action;
	str += "\nName[en]=";str += action;
	str += "\nName[C]=";str += action;
	str += "\nExec=";str += action;
	str += " %"; str += "U";

	//UNCOMMENT THE FOLLOWING LINE FOR DEBUGGING
	//str += "\nExecutionMode=DisplayOutput";

	return str;
}


// Create a string for NA to use to create a menu to store actions
string Install::createMenu(string name, string options, string mimeTypes) {

	string str = "";
	str += "[Desktop Entry]\n";
	str += "Type=Menu\n";
	str += "Name[en_CA]="; str += name;
	str += "\nName[en]="; str += name;
	str += "\nName[C]="; str += name;
	//str += "\n";
	//str += mimeTypes;

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
