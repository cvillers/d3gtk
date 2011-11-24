#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/combobox.h>

class DialogPDAEditor : public Gtk::Window
{
protected:
	Gtk::ComboBox	pdaList;
	Gtk::ComboBox	emailList;
	Gtk::ComboBox	audioList;
	Gtk::ComboBox	videoList;

	

	Gtk::Button	saveButton;
};
