#include "decl.h"

Glib::RefPtr<Gtk::Builder> gladeBuilder;

#define WIRE_WIDGET_NAMED(gladeName, name)		\
	gladeBuilder->get_widget(gladeName, name)

#define WIRE_WIDGET(name)				\
	WIRE_WIDGET_NAMED(#name, name)

#define WIDGET_CLICK_NAMED(className, gladeName, name, handler)		\
	if(!name)					\
		WIRE_WIDGET_NAMED(gladeName, name);			\
	if(name)					\
		name->signal_clicked()			\
			.connect(			\
				sigc::mem_fun(		\
					*this,		\
					&className::handler))

#define WIDGET_CLICK(className, name, handler)		\
	WIDGET_CLICK_NAMED(className, #name, name, handler)

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
	Gtk::ListStore *typeStore;
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
	
		WIRE_WIDGET_NAMED("new_nameEntry", nameEntry);
		WIRE_WIDGET_NAMED("new_fileEntry", fileEntry);
		WIRE_WIDGET_NAMED("new_typeList", typeList);
		WIRE_WIDGET(typeStore);

		WIDGET_CLICK_NAMED(newDeclWindow, "new_browseButton", browseButton, browseButton_clicked);
		WIDGET_CLICK_NAMED(newDeclWindow, "new_okButton", okButton, okButton_clicked);
		WIDGET_CLICK_NAMED(newDeclWindow, "new_cancelButton", cancelButton, cancelButton_clicked);
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
static Gtk::ListStore *declStore = 0;

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

	gladeBuilder->get_widget("browser_addButton", addButton);
	WIRE_WIDGET(declStore);

	if(addButton)	// TODO exceptions
	{
		addButton->signal_clicked().connect(sigc::ptr_fun(addButton_clicked));
	}
}
