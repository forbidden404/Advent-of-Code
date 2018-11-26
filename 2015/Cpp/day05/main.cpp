#include <iostream>
#include <string>
#include <map>

bool is_string_nice(std::string input) {
    int vowels = 0;
    char last_char = 0;
    bool is_nice = false;
    for (auto c : input) {
        switch (c) {
            case 'a':
            case 'e': 
            case 'i': 
            case 'o':
            case 'u':
                vowels++;
                break;
            default:
                break;
        }

        if (last_char != 0) {
            if (c == last_char) {
                is_nice = true;
            }
        }

        last_char = c;
    }

    if (vowels < 3) {
        is_nice = false;
    }

    std::size_t found = input.find("ab");
    if (found != std::string::npos)
        is_nice = false;

    found = input.find("cd");
    if (found != std::string::npos)
        is_nice = false;

    found = input.find("pq");
    if (found != std::string::npos)
        is_nice = false;

    found = input.find("xy");
    if (found != std::string::npos)
        is_nice = false;

    return is_nice;
}

bool is_string_nicer(std::string input) {
    bool rule1 = false;
    bool rule2 = false;

    int length = input.length();
    if (length < 4)
        return false;

    char last_char = input[0];
    for (int i = 2; i < length; i += 2) {
        if (input[i] == last_char)
            rule1 = true;
        last_char = input[i];
    }

    last_char = input[1];
    for (int i = 3; i < length; i += 2) {
        if (input[i] == last_char)
            rule1 = true;
        last_char = input[i];
    }

    for (int i = 0; i < length; i++) {
        if (i + 1 >= length) 
            continue;
        
        std::string sub = input.substr(i, 2);
        for (int j = i + 2; j < length; j++) {
            if (sub.compare(input.substr(j, 2)) == 0)
                rule2 = true;
        }

    }

    return rule1 && rule2;
}

int main() {
    std::string input;
    int nice_strings1 = 0;
    int nice_strings2 = 0;

    while (std::cin >> input) {
        if (is_string_nice(input))
            nice_strings1++;
        if (is_string_nicer(input))
            nice_strings2++;
    }

    std::cout << nice_strings1 << std::endl;
    std::cout << nice_strings2 << std::endl;

    return 0;
}
