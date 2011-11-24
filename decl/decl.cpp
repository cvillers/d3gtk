#include "decl.h"

Glib::RefPtr<Gtk::Builder> gladeBuilder;

// these macros assume the name in the glade file and the member name
// are identical

#define WIRE_WIDGET(name)		\
	gladeBuilder->get_widget(#name, name)

#define WIDGET_CLICK(className, name, handler)		\
	if(!name)					\
		WIRE_WIDGET(name);			\
	if(name)					\
		name->signal_clicked()			\
			.connect(			\
				sigc::mem_fun(		\
					*this,		\
					&className::handler))

// maybe these should be subclasses instead of encapsulating gtk windows?

/****************************************************************************
				NEW DECL WINDOW
 ****************************************************************************/

class newDeclWindow
{
public:
	newDeclWindow()
	{
		window = NULL;
		browseButton = okButton = cancelButton = NULL;
		nameEntry = fileEntry = NULL;

		gladeBuilder->get_widget("newDeclWindow", window);

		if(window)
		{
			wire();
			window->show();
		}
	}

	~newDeclWindow()
	{
	}

private:
	Gtk::Window *window;
	Gtk::Button *browseButton, *okButton, *cancelButton;
	Gtk::Entry *nameEntry, *fileEntry;
	Gtk::ComboBox *typeList;
	std::string filename;

	void wire()
	{
		//gladeBuilder->get_widget("browseButton", browseButton);
		//gladeBuilder->get_widget("okButton", okButton);
		//gladeBuilder->get_widget("cancelButton", cancelButton);

		// TODO error handling

		//browseButton->signal_clicked().connect(sigc::mem_fun(*this,
		//	&newDeclWindow::browseButton_clicked));
		//okButton->signal_clicked().connect(sigc::mem_fun(*this,
		//	&newDeclWindow::okButton_clocked));
		//cancelButton->signal_clicked().connect(sigc::mem_fun(*this,
		//	&newDeclWindow::cancelButton_clicked));
	
		WIRE_WIDGET(nameEntry);
		WIRE_WIDGET(fileEntry);
		WIRE_WIDGET(typeList);

		WIDGET_CLICK(newDeclWindow, browseButton, browseButton_clicked);
		WIDGET_CLICK(newDeclWindow, okButton, okButton_clicked);
		WIDGET_CLICK(newDeclWindow, cancelButton, cancelButton_clicked);
	}

	/****************
	  Event handlers
	 ****************/
	void browseButton_clicked()
	{
		printf("browseButton_clicked\n");
		Gtk::FileChooserDialog dialog(*window, "Save as...",
			Gtk::FILE_CHOOSER_ACTION_SAVE);

		dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
		// save and ok don't quite match but that's fine
		dialog.add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);

		// TODO filters

		int response = dialog.run();
		if(response == Gtk::RESPONSE_OK)
			filename = dialog.get_filename();
		else
			filename = "";

		printf("filename: %s\n", filename.c_str());
		fileEntry->set_text(filename);
	}

	void okButton_clicked()
	{
		printf("okButton_clicked\n");
	}

	void cancelButton_clicked()
	{
		printf("cancelButton_clicked\n");
	}
};

static newDeclWindow *_newDeclWindow = 0;


/****************************************************************************
				  MAIN WINDOW
				aka the browser
 ****************************************************************************/

Gtk::Window *mainWindow = 0;
static Gtk::Button *addButton = 0;

static void addButton_clicked()
{
	_newDeclWindow = new newDeclWindow;

	//gladeBuilder->get_widget("newDeclWindow", _newDeclWindow);

	//if(_newDeclWindow)
	//{
	//	_newDeclWindow->show();
	//}
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
