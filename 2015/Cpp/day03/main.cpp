#include <iostream>
#include <map>
#include <utility>
#include <string>

int get_unique_houses(std::string input) {
    int x = 0, y = 0;
    std::map<std::pair<int, int>, bool> visited;

    for (auto c : input) {
        switch (c) {
            case '^':
                y += 1;
                break;
            case '>':
                x += 1;
                break;
            case '<':
                x -=1;
                break;
            case 'v':
                y -= 1;
                break;
        }

        visited[std::make_pair(x, y)] = true;
    }

    return visited.size();
}

int get_unique_houses_with_robot(std:: string input) {
    int x_santa = 0, y_santa = 0;
    int x_robot = 0, y_robot = 0;
    std::map<std::pair<int, int>, bool> visited;

    bool is_santa_turn = true;

    for (auto c : input) {
        switch (c) {
            case '^':
                if (is_santa_turn) { y_santa += 1; } else { y_robot += 1; }
                break;
            case '>':
                if (is_santa_turn) { x_santa += 1; } else { x_robot += 1; }
                break;
            case '<':
                if (is_santa_turn) { x_santa -= 1; } else { x_robot -= 1; }
                break;
            case 'v':
                if (is_santa_turn) { y_santa -= 1; } else { y_robot -= 1; }
                break;
        }

        is_santa_turn = !is_santa_turn;

        visited[std::make_pair(x_santa, y_santa)] = true;
        visited[std::make_pair(x_robot, y_robot)] = true;
    }

    return visited.size();
}

int main() {
    std::string input;

    std::cin >> input;

    std::cout << get_unique_houses(input) << "\n";
    std::cout << get_unique_houses_with_robot(input) << "\n";

    return 0;
}
