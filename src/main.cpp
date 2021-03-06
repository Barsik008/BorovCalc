//FOR LINUX:
//g++ main.cpp -o borovCalc `pkg-config gtkmm-3.0 --cflags --libs` -g
//FOR WINDOWS:
//g++ -std=c++2a -o borovCalc.exe src/main.cpp res/resources.res $(pkg-config gtkmm-3.0 --cflags --libs | sed 's/ -I/ -isystem /g') -mwindows

#include <iostream>
#include <gtkmm.h>

Gtk::Window* window = nullptr;
Gtk::Entry* inputOne = nullptr;
Gtk::Entry* inputTwo = nullptr;
Gtk::Entry* inputThree = nullptr;
Gtk::Entry* outputBox = nullptr;

Gtk::Entry* inputLiqLvlOne = nullptr;
Gtk::Entry* inputLiqLvlTwo = nullptr;
Gtk::Entry* outputHumidity = nullptr; 

void calcHumidity() {

    try {

        Glib::ustring strLiqLvlOne, strLiqLvlTwo;

        strLiqLvlOne = inputLiqLvlOne -> get_text(); 
        strLiqLvlTwo = inputLiqLvlTwo -> get_text();

        float numLiqLvlOne = std::stod(strLiqLvlOne); 
        float numLiqLvlTwo = std::stod(strLiqLvlTwo);

        outputHumidity -> set_text(std::to_string((numLiqLvlOne + (numLiqLvlOne * (50 - numLiqLvlTwo)) / numLiqLvlTwo) / (50 - (numLiqLvlOne + (numLiqLvlOne * (50 - numLiqLvlTwo)) / numLiqLvlTwo))));

    } catch (...) {

        outputHumidity -> set_text("Enter a value");

    }
}

void calcMud() {

    try {

        Glib::ustring strDenSolute, strDenSolvent, strDenSolution;

        strDenSolute = inputOne -> get_text();
        strDenSolvent = inputTwo -> get_text();
        strDenSolution = inputThree -> get_text();

        float denSolute = std::stod(strDenSolute);
        float denSolvent = std::stod(strDenSolvent);
        float denSolution = std::stod(strDenSolution);

        float volSolute = (denSolution - denSolvent) / (denSolute - denSolvent);
        float volSolvent = 1 - volSolute;

        outputBox -> set_text(std::to_string(volSolvent / volSolute));

    } catch(...) {

        outputBox -> set_text("Enter a value");

    }

}

int main(int argc, char** argv) {

    auto app = Gtk::Application::create(argc, argv, "");

    auto refBuilder = Gtk::Builder::create();

    try {

        refBuilder->add_from_file("../res/gui.glade");

    } catch (const Glib::FileError& ex) {

        std::cerr << "FileError: " << ex.what() << std::endl;
        return 1;

    } catch (const Glib::MarkupError& ex) {

        std::cerr << "MarkupError: " << ex.what() << std::endl;
        return 1;

    } catch(const Gtk::BuilderError& ex) {

        std::cerr << "BuilderError: " << ex.what() << std::endl;
        return 1;

    }

    refBuilder -> get_widget("mainWindow", window);

    if (window) {

        Gtk::Button* calcButton = nullptr;
        Gtk::Button* calculateHumidity = nullptr;

        refBuilder -> get_widget("calcButton", calcButton);
        refBuilder -> get_widget("inputOne", inputOne);
        refBuilder -> get_widget("inputTwo", inputTwo);
        refBuilder -> get_widget("inputThree", inputThree);
        refBuilder -> get_widget("outputBox", outputBox);

        refBuilder -> get_widget("calculateHumidity", calculateHumidity);
        refBuilder -> get_widget("inputLiqLvlOne", inputLiqLvlOne);
        refBuilder -> get_widget("inputLiqLvlTwo", inputLiqLvlTwo);
        refBuilder -> get_widget("outputHumidity", outputHumidity);

        if (calcButton) {

            calcButton -> signal_clicked().connect(sigc::ptr_fun(calcMud));

        }

        if (calculateHumidity) {

            calculateHumidity -> signal_clicked().connect(sigc::ptr_fun(calcHumidity));

        }

        app -> run(*window);
    }

    delete window; 
    delete inputOne; 
    delete inputTwo; 
    delete inputThree; 
    delete outputBox;

    delete inputLiqLvlOne;
    delete inputLiqLvlOne;
    delete outputHumidity; 

    return 0;
}
