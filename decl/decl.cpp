#include "decl.h"

Glib::RefPtr<Gtk::Builder> gladeBuilder;

Gtk::Window *mainWindow = 0;
Gtk::Window *newDeclWindow = 0;

static Gtk::Button *addButton = 0;

static void addButton_clicked()
{
	gladeBuilder->get_widget("newDeclWindow", newDeclWindow);

	if(newDeclWindow)
	{
		newDeclWindow->show();
	}
}

void wireMainWindow()
{
	gladeBuilder->get_widget("declBrowser", mainWindow);

	gladeBuilder->get_widget("addButton", addButton);

	if(addButton)	// TODO exceptions
	{
		addButton->signal_clicked().connect(sigc::ptr_fun(addButton_clicked));
	}
}
