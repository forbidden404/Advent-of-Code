#include <iostream>
#include <string>
#include "md5.h"

bool has_n_zeroes(int n, std::string input) {
    if (input.length() < n) return false;

    for (int i = 0; i < n; i++) {
        if (input[i] != '0') 
            return false;
    }

    return true;
}


std::string get_hash_for(std::string input) {
    return md5(input);
}

std::string check_hash(int n, std::string input) {
    int i = 1;

    bool has_found = false;

    std::string key = input + std::to_string(i);

    while ((has_found = has_n_zeroes(n, get_hash_for(key))), !has_found) {
        i++;
        key = input + std::to_string(i);
    }
    
    return std::to_string(i);
}



int main() {
    std::string input;

    std::cin >> input;

    std::cout << check_hash(5, input) << std::endl;
    std::cout << check_hash(6, input) << std::endl;

    return 0;
}

