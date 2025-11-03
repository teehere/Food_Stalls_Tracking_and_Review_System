/* File name: food_track.cpp */

#include "food_track.h"
#include "store.h"
#include "review.h"
STORE st; 
REVIEW rw;

#include <iostream>
#include <string>
#include <iomanip> // system, setw()
#include <limits>  // cin.ignore
#include <fstream> //ifstream, ofstream
using namespace std;



void FOOD_TRACK::clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void FOOD_TRACK::instruct() {
    cout << string(60, '-') << endl;
    cout << string(23, ' ') << "Types of Store" << endl;
    cout << string(60, '-') << endl;
    cout << "<1> Restaurant" << endl;
    cout << "<2> Cafe" << endl;
    cout << "<3> Fast Food Store" << endl;
    cout << "<Q>uit" << endl;
    cout << string(60, '-') << endl;
}

void FOOD_TRACK::choose_option() {
    while(true) {
        clear_screen();
        instruct();

        char Opt;
        cout << "Enter Option <Q>uit >> ";
        cin >> Opt;
        if (Opt >= '1' && Opt <= '3') {
            switch (Opt) {
                case '1':
                    st.restaurant();
                    break;
                case '2':
                    st.cafe();
                    break;
                case '3':
                    st.fast_food();
                    break;
                default:
                    cout << "--------------Invalid Input! Please Try Again!--------------" << endl;
                  
                    break;
            }
        } else if (Opt == 'q' || Opt == 'Q') {
            cout << "---------------------Successfully Quit----------------------" << endl;
            break;

        } else {
            cout << "--------------Invalid Input! Please Try Again!--------------" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore incorrect input
            cin.get(); // Read single character (including whitespace) ---> input()
        }
    }
}

void FOOD_TRACK::choose_option_r() {
    while(true) {
        clear_screen();
        instruct();

        char Opt;
        cout << "Enter Option <Q>uit >> ";
        cin >> Opt;
        if (Opt >= '1' && Opt <= '3') {
            switch (Opt) {
                case '1':
                    rw.restaurant_r();
                    break;
                case '2':
                    rw.cafe_r();
                    break;
                case '3':
                    rw.fast_food_r();
                    break;
                default:
                    cout << "--------------Invalid Input! Please Try Again!--------------" << endl;
                    break;
            }

        } else if (Opt == 'q' || Opt == 'Q') {
            cout << "---------------------Successfully Quit ---------------------" << endl;
            break;

        } else {
            cout << "--------------Invalid Input! Please Try Again!--------------" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore incorrect input
            cin.get(); // Read single character (including whitespace) ---> input()
        }
    }
}