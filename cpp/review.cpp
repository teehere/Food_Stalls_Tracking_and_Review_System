/* File name: review.cpp */ 

#include "food_track.h"
#include "store.h"
#include "review.h"

#include <iostream>
#include <string>
#include <limits>
#include <fstream>
using namespace std;



void REVIEW::clear_screen() {
#ifdef _WIN32
    // Only for Window user
    system("cls"); 
#else
    // For Linux/Mac... user
    system("clear");
#endif
}

void REVIEW::user_info(string &name, string &city, string &state) {
    cout << string(60, '-') << endl;
    cout << string(20, ' ') << "Enter Personal Info" << endl;
    cout << string(60, '-') << endl;

    // Flush buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    
    cout << "Name (Joey Chong): ";
    // To read a line of text
    getline(cin, name); 
    cout << "City (Bandar Sungai Long): ";
    getline(cin, city);
    cout << "State (Selangor): ";
    getline(cin, state);
    // cout << "Date (01/01/2025): ";
    // getline(cin, date);
}

void REVIEW::user_review(string name, string city, string state, string &rate, string &main_reason, string &comments) {
    ofstream out_file("temp_review.txt", ios::trunc);

    cout << string(60, '-') << endl;
    cout << string(12, ' ') << "Please rate your overall experience" << endl;
    cout << string(60, '-') << endl;

    cout << "Rating (*****): ";
    getline(cin, rate);
    cout << "Main Reason (Exceptional Service): ";
    getline(cin, main_reason);
    cout << "Comments/Feedbacks: ";
    getline(cin, comments);

    // Save it into temparary file for preview purpose
    out_file << name << ", from " << city << ", " << state
    << endl << rate << " for " << main_reason << endl << comments;

    out_file.close();
}

void REVIEW::display_review(string text_file) {
    ifstream in_file(text_file);

    cout << string(60, '-') << endl;
    cout << string(20, ' ') << "Feedbacks from Users" << endl;
    cout << string(60, '-') << endl;

    string line;
    while (getline(in_file, line)) {    
        cout << line << endl;
    }
    in_file.close();
}

void REVIEW::temp_review() {
    ifstream in_file("temp_review.txt");

    cout << string(60, '-') << endl;
    cout << string(27, ' ') << "Preview" << endl;
    cout << string(60, '-') << endl;

    string line;
    while (getline(in_file, line)) {
        cout << line << endl;
    }
    in_file.close();
}

void REVIEW::modify_review(string text_file, string name, string city, string state, string rate, string main_reason, string comments) {
    clear_screen();

    temp_review();

    user_info(name, city, state);
    user_review(name, city, state, rate, main_reason, comments);
    confirmation(text_file, name, city, state, rate, main_reason, comments);
}

void REVIEW::delete_review(string text_file, string name, string city, string state, string rate, string main_reason, string comments) {
    // Overwrite Contents
    ofstream out_file("temp_review.txt", ios::trunc); 
    out_file.close();
    cout << "-----------------------Review Deleted-----------------------" << endl;
    cin.ignore();
    cin.get();
}

void REVIEW::confirmation(string text_file, string name, string city, string state, string rate, string main_reason, string comments) {
    // Append temp_review to review.txt
    ifstream temp_file("temp_review.txt");
    ofstream out_file(text_file, ios::app);

    string line;
    bool found=true;
    while (getline(temp_file, line)) {
        // Save The Data In Next Line
        if (found) {
            out_file << endl;
            found = false;
        }
        out_file << line << endl;
    }
    temp_file.close();
    out_file.close();

    clear_screen();
    // Now Show All Confirmed Reviews
    display_review(text_file); 
    cout << "------------------Review Confirmed and Saved------------------" << endl;
    cin.ignore();
    cin.get();
}

void REVIEW::give_comment(string text_file) {
    char select;
    string name, city, state, rate, main_reason, comments;

    user_info(name, city, state);
    user_review(name, city, state, rate, main_reason, comments);

    while (true) {
        clear_screen();

        temp_review();
        cout << string(60, '-') << endl;
        cout << "<C>onfirm <M>odify <D>elete    <Q>uit" << endl;
        cout << string(60, '-') << endl;

        cout << "Enter Option: ";
        cin >> select;
        if (select == 'q' || select == 'Q') {
            cout << "----------------------Successfully Quit---------------------" << endl;
            break;

        } else if (select == 'c' || select == 'C') {
            confirmation(text_file, name, city, state, rate, main_reason, comments);
            break;

        } else if (select == 'm' || select == 'M') {
            modify_review(text_file, name, city, state, rate, main_reason, comments);
            break;

        } else if (select == 'd' || select == 'D') {
            delete_review(text_file, name, city, state, rate, main_reason, comments);
            break;

        } else {
            cout << "----------------Invalid Option, Pls Try Again---------------" << endl;

            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Handle buffer
            cin.get();
        }
    }
}

void REVIEW::track(string text_file) {
    char select;
    string name, city, state, rate, main_reason, comments;

    while (true) {
        clear_screen();

        cout << string(60, '-') << endl;
        cout << "\t\t  Select Option" << endl;
        cout << string(60, '-') << endl;
        cout << "<1> " << "Give Comment" << endl;
        cout << "<2> " << "View Review" << endl;
        cout << "<Q> " << "Quit" << endl;
        cout << string(60, '-') << endl;

        cout << "Enter Option: ";
        cin >> select;
        if (select == '1') {
            clear_screen();
            give_comment(text_file);
            break;

        } else if (select == '2') {
            clear_screen();
            display_review(text_file);
            cin.ignore();
            cin.get();

        } else if (select == 'q' || select == 'Q') {
            cout << "----------------------Successfully Quit---------------------" << endl;
            break;

        } else {
            cout << "----------------Invalid Option, Pls Try Again---------------" << endl;

            cin.clear(); // Clear The Error Input (Avoid Infinite Loop)
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Handle buffer
            cin.get();
        }
    }
}

void REVIEW::restaurant_r() {
    while (true) {
        clear_screen();

        cout << string(60, '-') << endl;
        cout << "\t\tRestaurant Details\n";
        cout << string(60, '-') << endl;

        ifstream in_file("restaurant_data.txt", ios::in);
        string line;
        int i=1;
        char ch;

        while (getline(in_file, line)) {
            cout << "<" << i << "> " << line << endl;
            i++;
        }
        cout << string(60, '-') << endl;
        in_file.close();

        cout << "Enter Number of Restaurant   <Q>uit: ";
        cin >> ch;
        if (ch>='1' && ch<='8') {
            switch (ch) {
                case '1':
                    track("ah_ma_review.txt");                
                    break;
                case '2':
                    track("desa_review.txt");                
                    break;
                case '3':
                    track("fun_review.txt");                
                    break;
                case '4':
                    track("happy_thai_review.txt");                
                    break;
                case '5':
                    track("mrs_yau_review.txt");                
                    break;
                case '6':
                    track("mye_review.txt");                
                    break;
                case '7':
                    track("taiwan_review.txt");                
                    break;
                case '8':
                    track("wei_duo_review.txt");                
                    break;
                default:
                    cout << "--------------Invalid Input! Please Try Again!--------------" << endl;
                    break;
            }

        } else if (ch == 'q' || ch == 'Q') {
            cout << "---------------------Successfully Quit----------------------" << endl;
            break;

        } else {
            cout << "--------------Invalid Input! Please Try Again!--------------" << endl;

            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Handle Buffer
            cin.get(); // Pause
        }
    }
}

void REVIEW::cafe_r() {
    while (true) {
        clear_screen();

        cout << string(60, '-') << endl;
        cout << "\t\t  Cafe Details\n";
        cout << string(60, '-') << endl;

        ifstream in_file("cafe_data.txt", ios::in);
        string line;
        int i=1;
        char ch;

        while (getline(in_file, line)) {
            cout << "<" << i << "> " << line << endl;
            i++;
        }
        cout << string(60, '-') << endl;
        in_file.close();

        cout << "Enter Number of Cafe   <Q>uit: ";
        cin >> ch;
        if (ch>='1' && ch<='7') {
            switch (ch) {
                case '1':
                    track("bingxue_review.txt");                
                    break;
                case '2':
                    track("blackboard_review.txt");                
                    break;
                case '3':
                    track("mixue_review.txt");                
                    break;
                case '4':
                    track("secret_review.txt");                
                    break;
                case '5':
                    track("snowy_review.txt");                
                    break;
                case '6':
                    track("zaba_review.txt");                
                    break;
                case '7':
                    track("zus_review.txt");                
                    break;
                default:
                    cout << "--------------Invalid Input! Please Try Again!--------------" << endl;
                    break;
            }

        } else if (ch == 'q' || ch == 'Q') {
            cout << "---------------------Successfully Quit ---------------------" << endl;
            break;

        } else {
            cout << "--------------Invalid Input! Please Try Again!--------------" << endl;

            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Handle Buffer
            cin.get(); // Pause
        }
    }   
}

void REVIEW::fast_food_r() {
    while (true) {
        clear_screen();

        cout << string(60, '-') << endl;
        cout << "\t\t      Fast Food Store Details\n";
        cout << string(60, '-') << endl;

        ifstream in_file("fast_food_data.txt", ios::in);
        string line;
        int i=1;
        char ch;

        while (getline(in_file, line)) {
            cout << "<" << i << "> " << line << endl;
            i++;
        }
        cout << string(60, '-') << endl;
        in_file.close();

        cout << "Enter Number of Fast Food Store   <Q>uit: ";
        cin >> ch;
        if (ch>='1' && ch<='4') {
            switch (ch) {
                case '1':
                    track("burger_review.txt");                
                    break;
                case '2':
                    track("domino_review.txt");                
                    break;
                case '3':
                    track("kfc_review.txt");                
                    break;
                case '4':
                    track("pizza_review.txt");                
                    break;
                default:
                    cout << "--------------Invalid Input! Please Try Again!--------------" << endl;
                    break;
            }

        } else if (ch == 'q' || ch == 'Q') {
            cout << "---------------------Successfully Quit----------------------" << endl;
            break;

        } else {
            cout << "--------------Invalid Input! Please Try Again!--------------" << endl;

            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Handle Buffer
            cin.get(); // Pause
        }
    }
}