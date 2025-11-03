/*File name: main_menu.cpp 
Tool (IDE) : VS CODE */


// Import food_track Module 
#include "food_track.h" 
#include "review.h"
FOOD_TRACK ft;

#include <iostream>
#include <cstdlib> // system
#include <string>
#include <limits> // cin.ignore
using namespace std;



// Clear The Screen Before Displaying Data
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void instruct() {
    cout << string(60, '-') << endl;
        cout << string(12, ' ') << "Food Stalls Tracking & Review System" << endl;
        cout << string(60, '-') << endl;
        cout << "<1> Food Stalls Tracking" << endl;
        cout << "<2> Review" << endl;
        cout << "<Q>uit" << endl;
        cout << string(60, '-') << endl;
}

bool is_digit(char Opt) {
    return Opt >= '1' && Opt <= '2';
}

void select_option(char Opt, bool &loop) {
    cout << "Select Option <Q>uit >> ";
    cin >> Opt;

    if (is_digit(Opt)) {
        switch (Opt) {
            case '1':
                // Import choose_option() Function From food_track.h File
                ft.choose_option();
                break;
            case '2':
                // Import choose_option_r() Function From food_track.h File
                ft.choose_option_r();
                break;
            default:
                cout << "--------------Invalid Input! Please Try Again!--------------" << endl;
                break;
        }
    } else if (Opt == 'q' || Opt == 'Q') {
        loop = false;
        cout << "----------------------Successfully Quit---------------------" << endl;
    } else {
        cout << "--------------Invalid Input! Please Try Again!--------------" << endl;
    }

    // Handle Buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // Read Single Character (including whitespace) ---> input()
    cin.get(); 
}

int main() {
    bool loop = true;
    while (loop) {
        char Opt;

        clear_screen(); 
        instruct();
        select_option(Opt, loop);
    }

    return 0;
}