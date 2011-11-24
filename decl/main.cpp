#include "decl.h"

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

	gladeBuilder = Gtk::Builder::create_from_file("decl.glade");

	wireMainWindow();

	Gtk::Main::run(*mainWindow);
}
