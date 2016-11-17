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

	//Read www.nongnu.org/atool for more info
	//Will allow us to use the same command structure for different compression methods
	//Example "apack -e (zip or rar or tar.gz) filename(s)"
	printf("Installing atool\n");
	system("sudo apt-get install atool");


	Install inst;

	string path = inst.findActionsFolder();
	fstream optionsFile;

//STARTS ADDING SUBMENU OPTION .desktop FILES

	inst.addOption("Compress", "./ex", "compress");
	inst.addOption("Option1", "./install", "option1");
	inst.addOption("Option2", "ls", "option2");

//BEGIN ADDING MAIN MENU .desktop FILE
	printf("\nCreating compressionmanager.desktop\n...\n...\n...");
	string compressMenu = inst.createMenu();
	string menuFile = ("../.local/share/file-manager/actions/compressionmanager.desktop");

	optionsFile.open(menuFile.c_str(), fstream::out | fstream::trunc);
	optionsFile << compressMenu;
	optionsFile.close();
//ENDS

}

//Takes info needed for new sub-menu option and adds it
//  Note: Must still add the options "name" to itemList in createMenu()
void Install::addOption(string name, string action, string filename) {
	//sets .desktop filename
	filename = filename + ".desktop";
	//gets the text to be added to the file
	string optionText = createOption(name, action);
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
	str += "Path=/home/student/LinuxFCM/\n";
	str += "Name[en_CA]="; str += action;
	str += "\nName[en]=";str += action;
	str += "\nName[C]=";str += action;
	str += "\nExec=";str += action;
	str += " %"; str += "U";
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
