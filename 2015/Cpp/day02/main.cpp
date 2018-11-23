#include <iostream>
#include <vector>
#include <string>

class WrappingPaper {
    private:
        int _length, _width, _height;

    public:
        WrappingPaper(int length=0, int width=0, int height=0): _length(length), _width(width), _height(height) {} 
        int get_square_feet();
        int get_feet_ribbon();

    friend std::istream& operator>> (std::istream &in, WrappingPaper &wrappingPaper);
};

std::istream& operator>> (std::istream &in, WrappingPaper &wrappingPaper) {
    std::string input;
    std::getline(in, input);
    size_t pos = 0;
    int count = 0;

    if (input.length() < 2) return in;

    while ((pos = input.find("x")) != std::string::npos) {
        switch (count) {
            case 0:
                wrappingPaper._length = std::stoi(input.substr(0, pos));
                break;
            case 1:
                wrappingPaper._width = std::stoi(input.substr(0, pos));
                break;
            default:
                break;
        }
        count++;
        input.erase(0, pos + 1);
    }

    wrappingPaper._height = std::stoi(input.substr(0, pos));
    return in;
}

int WrappingPaper::get_square_feet() {
    int sideA = _length * _width;
    int sideB = _width * _height;
    int sideC = _height * _length;

    int min = sideA;
    min = min < sideB ? (min < sideC ? min : sideC) : (sideB < sideC ? sideB : sideC);

    return 2 * sideA + 2 * sideB + 2 * sideC + min;
}

int WrappingPaper::get_feet_ribbon() {
    std::vector<int> vec = { _length, _width, _height };
    std::sort(vec.begin(), vec.end());
    return 2 * vec[0] + 2 * vec[1] + _length * _width * _height;
}

int main() {
    std::string input;

    int total_wrapping_paper = 0;
    int total_feet_ribbon = 0;

    WrappingPaper wrappingPaper;

    while (std::cin >> wrappingPaper) {
        total_wrapping_paper += wrappingPaper.get_square_feet();
        total_feet_ribbon += wrappingPaper.get_feet_ribbon();
    }

    std::cout << total_wrapping_paper << std::endl;
    std::cout << total_feet_ribbon << std::endl;
    return 0;
}
