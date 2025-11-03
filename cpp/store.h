#include <string>
using namespace std;

class STORE {
    public:
    // Core Functions
    void restaurant();
    void cafe();
    void fast_food();

    // Data Management Functions
    void display_data(string text_file);
    bool check_code(string text_file, string code);
    void add_data(string text_file, string code, string food, double f_price);
    void modify_data(string text_file, string code, string food, double f_price);
    void delete_data(string text_file, string code, string food, double f_price);
    void calculate(string text_file, string code, int quantity, double f_price);
    void track(string text_file, int distance, string hrs);

    // Clear All Data
    void clear_screen();
};