#include <iostream>
#include <string>

int main() {
    std::string input;
    std::getline(std::cin, input);


    int floor = 0;
    int position = 0;
    bool has_found_position = false;
    for (auto c : input) {
        if (c == '(')
            floor++;
        else if (c == ')')
            floor--;

        if (!has_found_position) {
            position++;
            if (floor == -1) 
                has_found_position = true;
        }
    }

    std::cout << floor << "\n";
    std::cout << position << "\n";

    return 0;
}
