#ifndef INSTALL
#define INSTALL

class Install
{
	public:
		void   mainfunc();
		string createAction();
		string createMenu(string, string, string);
		string findActionsFolder();
		string createOption(string, string,string, string);
		void addOption(string, string,string, string, string);
		void addMenu(string,string, string, string);
		void fixPreferences();
};
#endif
