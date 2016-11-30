#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

using namespace std;


int main() {
  string homeDir = getenv("HOME");
  // Remove NA
  system("sudo apt-get purge nautilus-actions");
  // Remove .desktop files and config file
  remove((homeDir + "/.config/nautilus-actions/nautilus-actions.conf").c_str());
  // These are data types defined in the "dirent" header
  DIR *actionsFolder = opendir((homeDir + "/.local/share/file-manager/actions").c_str());
  struct dirent *next_file;
  char filepath[256];

  while ((next_file = readdir(actionsFolder)) != NULL )
  {
      sprintf(filepath, "%s/%s", (homeDir + "/.local/share/file-manager/actions").c_str(), next_file->d_name);
      remove(filepath);
  }
  closedir(actionsFolder);

  //zip and unzip can't be removed without removing file-roller, i.e archive manager, and no package tar.gz can be found, it must be packages with ubuntu
  //the terminal already asks if the user wants to remove the following packages, so no extra code is needed here
  system("sudo apt-get remove p7zip-full");
  system("sudo apt-get remove rar");
  system("sudo apt-get remove unrar");
  system("sudo apt-get remove atool");

  return 0;
}
