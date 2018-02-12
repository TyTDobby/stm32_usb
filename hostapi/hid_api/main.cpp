#include <iostream>
#include <gtkmm.h>

#include "usb_device.h"

using namespace std;

Gtk::Window *window = 0;

int main(int argc, char *argv[])
{
    // USBDevice device;
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  //Загрузка файла описания пользовательского интерфейса с помощью экземпляра класса Gtk::Builder и создание экземпляров классов описанных в этом файле виджетов:
  Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
    try{
        refBuilder->add_from_file("gui.ui");
    }
    catch(const Glib::FileError& ex){
        std::cerr << "FileError: " << ex.what() << std::endl;
        return 1;
    }  
    catch(const Glib::MarkupError& ex){ 
        std::cerr << "MarkupError: " << ex.what() << std::endl;
        return 1;
    }
    catch(const Gtk::BuilderError& ex){
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        return 1;
    }
    //Получение созданного с помощью объекта типа Gtk::Builder экземпляра класса диалога:
    refBuilder->get_widget("Window", window);
    return app->run(*window);
}
