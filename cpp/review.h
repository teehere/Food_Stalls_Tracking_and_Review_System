#include <string>
using namespace std;

class REVIEW {
    public:
    // Core Functions
    void restaurant_r();
    void cafe_r();
    void fast_food_r();

    // Data Management Functions
    void user_info(string &name, string &city, string &state);
    void user_review(string name, string city, string state, string &rate, string &main_reason, string &comments);
    void display_review(string text_file);
    void temp_review();
    void modify_review(string text_file, string name, string city, string state, string rate, string main_reason, string comments);
    void delete_review(string text_file, string name, string city, string state, string rate, string main_reason, string comments); 
    void confirmation(string text_file, string name, string city, string state, string rate, string main_reason, string comments); 
    void give_comment(string text_file); 
    void track(string text_file); 

    // Clear All Data
    void clear_screen();
};


