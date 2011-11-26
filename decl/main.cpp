#include "decl.h"
#include <iostream>

using namespace std;

/*
 * Entry point.
 *
 * This file is only responsible for creating the GtkBuilder which constructs
 * widgets from the glade file and kicking off the main window. Thus it can
 * easily be replaced with an implementation that reads the file using idLib
 * and integrates with the existing event loops.
 */

int main(int argc, char **argv)
{
	Gtk::Main _main(argc, argv);

	try
	{
		gladeBuilder = Gtk::Builder::create_from_file("./decl.glade");
	}
	catch(Gtk::BuilderError &e)
	{
		cout << "ERROR: " << e.what() << endl;
		return 1;
	}

	wireMainWindow();

	Gtk::Main::run(*mainWindow);
}
