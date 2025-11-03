/* File name: store.cpp */

#include "food_track.h"
#include "store.h"

#include <iostream>
#include <string>
#include <iomanip> 
#include <limits> 
#include <fstream> 
using namespace std;



void STORE::clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void STORE::display_data (string text_file) {
    ifstream in_file(text_file, ios::in);
    string line;
    
    cout << string(60, '-') << endl;
    cout << "Codes" << setw(21) << "Foods & Beverages" << setw(34) << "Prices" << endl;
    cout << string(60, '-') << endl;

    while (getline(in_file, line)) {
        size_t delimeter_idx1 = line.find('|');
        size_t delimeter_idx2 = line.find('|', delimeter_idx1 + 1);
        string current_code = line.substr(0, delimeter_idx1);
        string current_food = line.substr(delimeter_idx1 + 1, delimeter_idx2 - delimeter_idx1 - 1);
        string current_price = line.substr(delimeter_idx2 + 1);

        cout << left << setw(9) << current_code << setw(41) << current_food << setw(10) 
        << right << fixed << setprecision(2) << stod(current_price) << endl;
    }

    in_file.close();
}

bool STORE::check_code(string text_file, string code) {
    ifstream in_file(text_file, ios::in);

    string line;
    while (getline(in_file, line)) {
        size_t delimeter_idx = line.find('|'); // Get The 1st Delimeter From Line
        if (code == line.substr(0, delimeter_idx)) {
            in_file.close(); // Avoid Non-Void Function Error
            return true;
        } 
    }
    in_file.close();
    return false;
}

void STORE::add_data(string text_file, string code, string food, double f_price) {
    clear_screen();
    ofstream out_file(text_file, ios::app);

    display_data(text_file);
    cout << string(60, '-') << endl;
    cout << "Add Food Details (type 'Q' to quit)\n";
    cout << string(60, '-') << endl;

    int step = 1;
    while (true) {    
        if (step == 1) {
            cout << "Enter Food Code: ";
            cin >> code;
            if (code == "q" || code == "Q") {
                break;

            } else if (check_code(text_file, code)) {

                cout << "-------------Code Exist, Pls Add Another Code---------------\n";
            } else {
                step++;
            }
        }
 
        if (step == 2) {
            cout << "Enter Food Description: ";
            cin.ignore(); 
            getline(cin, food);
            if (food == "q" || food == "Q") {
                cout << "----------------------Successfully Quit---------------------" << endl;
                break;
            } else {
                step++;
            }
        }

        if (step == 3) {
            cout << "Enter Food Price: ";
            while (!(cin >> f_price) || f_price < 0) {
                cout << "Please Enter a Valid Price: ";
                
                cin.clear(); // Clear The Error Input (Avoid Infinite Loop)
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Handle Buffer
            } 

            out_file << code << "|" << food << "|" << f_price << endl;
            break;
        } 
    }
    out_file.close();
}

void STORE::modify_data(string text_file, string code, string food, double f_price) {
    clear_screen();

    display_data(text_file);
    cout << string(60, '-') << endl;
    cout << "Modify Food Details (type 'Q' to quit)\n";
    cout << string(60, '-') << endl;

    int step = 1;
    while (true) {    
        if (step == 1) {
            cout << "Enter Food Code: ";
            cin >> code;
            if (code == "q" || code == "Q") {
                break;

            } else if (check_code(text_file, code)) {
                step++;

            } else {
                cout << "----------Code Does Not Exist, Cannot Be Modified-----------";

                cin.clear(); // Clear The Error Input (Avoid Infinite Loop)
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Handle Buffer
                cin.get();
            }
        }

        if (step == 2) {
            char modify_opt;
            string new_code, new_food;
            double new_price;

            cout << "<C>ode <D>escription <P>rice   <Q>uit: ";
            cin >> modify_opt;
            cout << string(60, '-') << endl;

            ifstream in_file(text_file);
            ofstream temp_file("temp.txt"); // Create a Temporary File to Store Original Data

            if (modify_opt == 'q' || modify_opt == 'Q') {
                break;

            } else if (modify_opt == 'c' || modify_opt == 'C') {
                cout << "Enter New Food Code: ";
                cin >> new_code;
                if (new_code == "q" || new_code == "Q") {
                    break;

                } else if (check_code(text_file, new_code)) {
                    cout << "----------New Code Same As Old Code, Please Reenter---------\n\n";

                } else {
                    string line;
                    
                    while (getline(in_file, line)) { 
                        size_t delimeter_idx1 = line.find('|');
                        size_t delimeter_idx2 = line.find('|', delimeter_idx1 + 1);
                        string current_code = line.substr(0, delimeter_idx1);
                        string current_food = line.substr(delimeter_idx1 + 1, delimeter_idx2 - delimeter_idx1 - 1);
                        string current_price = line.substr(delimeter_idx2 + 1);

                        if (code != current_code) {
                            temp_file << line << endl;
                        } else {
                            temp_file << new_code << "|" << current_food << "|" << current_price << endl;
                        }
                    }
                }

            } else if (modify_opt == 'd' || modify_opt == 'D') {
                cout << "Enter New Food Description: ";
                cin.ignore(); // Avoid Input Buffer from 'cin >> modify_opt' (\n) 
                getline(cin, new_food); 
                if (new_food == "q" || new_food == "Q") {
                    break;

                } else {
                    string line;
                    while (getline(in_file, line)) { 
                        size_t delimeter_idx1 = line.find('|');
                        size_t delimeter_idx2 = line.find('|', delimeter_idx1 + 1);
                        string current_code = line.substr(0, delimeter_idx1);
                        string current_food = line.substr(delimeter_idx1 + 1, delimeter_idx2 - delimeter_idx1 - 1);
                        string current_price = line.substr(delimeter_idx2 + 1);

                        if (code != current_code) {
                            temp_file << line << endl;
                        } else {
                            temp_file << current_code << "|" << new_food << "|" << current_price << endl;
                            break;
                        }
                    }
                }

            } else if (modify_opt == 'p' || modify_opt == 'P') {
                cout << "Enter New Food Price: ";
                cin >> new_price;

                if (new_price < 0) {   
                    cout << "---------------Invalid Price, Please Reenter----------------";

                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Handle Buffer
                    cin.get(); // Pause
                    break;

                } else if (new_price >= 0) {
                    string line;
                    while (getline(in_file, line)) { 
                        size_t delimeter_idx1 = line.find('|');
                        size_t delimeter_idx2 = line.find('|', delimeter_idx1 + 1);
                        string current_code = line.substr(0, delimeter_idx1);
                        string current_food = line.substr(delimeter_idx1 + 1, delimeter_idx2 - delimeter_idx1 - 1);
                        string current_price = line.substr(delimeter_idx2 + 1);

                        // If not modifying, write the original line to temp file
                        if (code != current_code) {
                            temp_file << line << endl;
                        } else {
                            temp_file << current_code << "|" << current_food << "|" << new_price << endl;
                        }
                    }

                } else {
                    cout << "---------------Invalid Price, Please Reenter----------------";

                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Handle Buffer
                    cin.get(); // Pause
                    break;
                } 
            }

            in_file.close();
            temp_file.close();

            remove(text_file.c_str());
            rename("temp.txt", text_file.c_str());
            break;
        }   
    }
}


void STORE::delete_data(string text_file, string code, string food, double f_price) {
    clear_screen();

    display_data(text_file);
    cout << string(60, '-') << endl;
    cout << "Delete Food Details (type 'Q' to quit)\n";
    cout << string(60, '-') << endl;

    int step = 1;
    while (true) {    
        if (step == 1) {
            cout << "Enter Food Code: ";
            cin >> code;
            if (code == "q" || code == "Q") {
                cout << "----------------------Successfully Quit---------------------" << endl;
                break;

            } else if (check_code(text_file, code)) {
                step++;

            } else {
                cout << "----------Code Does Not Exist, Cannot Be Deleted------------";

                cin.clear(); // Clear The Error Input (Avoid Infinite Loop)
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Handle Buffer
                cin.get();
            }
        }

        
        if (step == 2) {
            ifstream in_file(text_file);
            ofstream temp_file("temp.txt"); // Create a Temporary File to Store Original Data
            
            string line;
            while (getline(in_file, line)) { 
                size_t delimeter_idx1 = line.find('|');
                string current_code = line.substr(0, delimeter_idx1);
                
                // Rewrite all lines except the one to be deleted/chosen
                if (code != current_code) {
                    temp_file << line << endl;
                }
            }

            in_file.close();
            temp_file.close();

            remove(text_file.c_str());
            rename("temp.txt", text_file.c_str());

            break;
        }
    }
}

void STORE::calculate(string text_file, string code, int quantity, double f_price) {
    char proceed;
    double cal_price, total_price = 0;
    clear_screen(); 

    display_data(text_file);
    cout << string(60, '-') << endl;
    cout << "\t\t\t Choose Items" << endl;
    cout << string(60, '-') << endl;

    
    do {
        cout << "Enter Food Code: ";
        cin >> code;

        if (code == "q" || code == "Q") {
            cout << "----------------------Successfully Quit---------------------" << endl;
            return;
    
        } else if (check_code(text_file, code)) {
            cout << "Enter Quantity: ";
            cin >> quantity;
            if (quantity < 0) {
                cout << "--------------Invalid Quantity, Please Reenter---------------";
                
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Handle Buffer
                cin.get();
    
            } else {
                ifstream in_file(text_file, ios::in);
                string line;
                while (getline(in_file, line)) {
                    size_t delimeter_idx1 = line.find('|');
                    size_t delimeter_idx2 = line.find('|', delimeter_idx1 + 1);
                    string current_code = line.substr(0, delimeter_idx1);
                    string current_food = line.substr(delimeter_idx1 + 1, delimeter_idx2 - delimeter_idx1 - 1);
                    string current_price = line.substr(delimeter_idx2 + 1);
    
                    if (code == current_code) {
                        f_price = stod(current_price); // Convert string to double
                        break;
                    }
                }
                in_file.close();

                cal_price = f_price * quantity;
                total_price += cal_price;
                cout << "Total Price: RM" << cal_price << endl;

                cout << "Wish to proceed? <Y>es/<N>o: ";
                cin >> proceed;
                if (proceed == 'n' || proceed == 'N') {
                    cout << string(60, '=') << endl;
                    cout << "Overall Price: RM" << total_price << endl;
                    cout << string(60, '=') << endl;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Handle Buffer
                cin.get();                
            }
    
        } else {
            cout << "---------Code Does Not Exist, Cannot Be Calculated----------";
    
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Handle Buffer
            cin.get();
        }
    } while (proceed == 'y' || proceed == 'Y'); 
}

void STORE::track(string text_file, int distance, string hrs) {
    double f_price, operate_hrs;
    string code, food;
    char select;
    int quantity;

    while (true) {
        clear_screen();

        display_data(text_file);
        cout << string(60, '-') << endl;
        cout << "Walking Distance: " << distance << "km" << endl; 
        cout << "Operating Hours: " << hrs << endl; 
        cout << string(60, '-') << endl;
        cout << "<A>dd <M>odify <D>elete <C>alculate    <Q>uit" << endl;
        cout << string(60, '-') << endl;

        cout << "Enter Option: ";
        cin >> select;
        if (select == 'q' || select == 'Q') {
            cout << "----------------------Successfully Quit---------------------" << endl;
            break;
        } else if (select == 'a' || select == 'A') {
            add_data(text_file, code, food, f_price);
        } else if (select == 'm' || select == 'M') {
            modify_data(text_file, code, food, f_price);
        } else if (select == 'd' || select == 'D') {
            delete_data(text_file, code, food, f_price);
        } else if (select == 'c' || select == 'C') {
            calculate(text_file, code, quantity, f_price);
        } else {
            cout << "----------------Invalid Option, Pls Try Again----------------" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Handle Buffer
            cin.get();
        }
    }
}

void STORE::restaurant() {
    while (true) {
        clear_screen();

        cout << string(60, '-') << endl;
        cout << "\t\t     Restaurant Details\n";
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
                    track("ah_ma.txt", 5, "06:30 AM - 09:00 PM");                
                    break;
                case '2':
                    track("desa_ctk.txt", 2, "24 Hours (Whole Day)");                
                    break;
                case '3':
                    track("fun_fun.txt", 3, "08:00 AM - 04:00 PM");                
                    break;
                case '4':
                    track("happy_thai.txt", 5, "11:00 AM - 03:00 PM / 05:00 PM - 10:00 PM");                
                    break;
                case '5':
                    track("mrs_yau.txt", 7, "11:15 AM - 09:30 PM");                
                    break;
                case '6':
                    track("mye_mye.txt", 2, "07:00 AM - 04:00 PM");                
                    break;
                case '7':
                    track("taiwan_dami.txt", 3, "11:30 AM - 09:30 PM");                
                    break;
                case '8':
                    track("wei_duo.txt", 9, "10:00 AM - 09:30 PM");                
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

void STORE::cafe() {
    while (true) {
        clear_screen();

        cout << string(60, '-') << endl;
        cout << "\t\t\t Cafe Details\n";
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
                    track("bingxue.txt", 1, "11:00 AM - 11:00 PM");                
                    break;
                case '2':
                    track("blackboard.txt", 1, "12:00PM - 09:00 PM");                
                    break;
                case '3':
                    track("mixue.txt", 1, "11:00 AM - 10:00 PM");                
                    break;
                case '4':
                    track("secret_penang.txt", 3, "09:00 AM - 08:30 PM");                
                    break;
                case '5':
                    track("snowy.txt", 2, "12:00PM - 09:00 PM");                
                    break;
                case '6':
                    track("zaba_long.txt", 4, "10:00 AM - 10:00 PM");                
                    break;
                case '7':
                    track("zus_coffee.txt", 3, "07:00 AM - 10:40 PM");                
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

void STORE::fast_food() {
    while (true) {
        clear_screen();

        cout << string(60, '-') << endl;
        cout << "\t\t    Fast Food Store Details\n";
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
                    track("burger.txt", 2, "8.00AM - 11.00 PM");                
                    break;
                case '2':
                    track("domino.txt", 8, "10.30AM - 11.00 PM");                
                    break;
                case '3':
                    track("kfc.txt", 8, "08:00 AM - 11:00 PM");                
                    break;
                case '4':
                    track("pizza.txt", 1, "10:00 AM - 11:00 PM");                
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
            
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Handle Buffer
            cin.get(); // Pause
        }
    }
}