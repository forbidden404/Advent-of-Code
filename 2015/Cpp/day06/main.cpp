#include <iostream>
#include <utility>
#include <map>

enum Action {
    TurnOn,
    TurnOff,
    Toggle
};

std::pair<std::pair<int, int>, std::pair<int, int> > get_range(std::string input) {
    int initial_x = 0, initial_y = 0, final_x = 0, final_y = 0;
    std::string numbers = "0123456789";

    std::size_t n = input.find_first_of(numbers);
    if (n != std::string::npos) {
        std::size_t m = input.find_first_not_of(numbers, n);
        initial_x = std::stoi(input.substr(n, m != std::string::npos ? m-n : m));

        n = input.find_first_of(numbers, m);
        if (n != std::string::npos) {
            m = input.find_first_not_of(numbers, n);
            initial_y = std::stoi(input.substr(n, m != std::string::npos ? m-n : m));

            n = input.find_first_of(numbers, m);
            if (n != std::string::npos) {
                m = input.find_first_not_of(numbers, n);
                final_x = std::stoi(input.substr(n, m != std::string::npos ? m-n : m));

                n = input.find_first_of(numbers, m);
                if (n != std::string::npos) {
                    m = input.find_first_not_of(numbers, n);
                    final_y = std::stoi(input.substr(n, m != std::string::npos ? m-n : m));
                }
            }
        }
    }

    return std::make_pair(std::make_pair(initial_x, initial_y), std::make_pair(final_x, final_y));
}

Action get_action(std::string input) { 
    auto found = input.find("turn off");
    if (found != std::string::npos)
        return TurnOff;

    found = input.find("turn on");
    if (found != std::string::npos)
        return TurnOn;

    return Toggle;
}


int main() {
    std::map<std::pair<int, int>, bool> grid;
    std::map<std::pair<int, int>, int> grid_brightness;

    int lights_on = 0;
    int light_brightness = 0;

    std::string input;
    while (std::getline(std::cin, input)) {
        int initial_x, initial_y, final_x, final_y;
        auto range = get_range(input);

        initial_x = range.first.first;
        initial_y = range.first.second;
        final_x = range.second.first;
        final_y = range.second.second;

        for (int x = initial_x; x <= final_x; x++) {
            for (int y = initial_y; y <= final_y; y++) {
                auto pair = std::make_pair(x, y);
                auto it = grid.find(pair);
                if (it == grid.end()) grid[pair] = false;

                auto it_brightness = grid_brightness.find(pair);
                if (it_brightness == grid_brightness.end()) grid[pair] = 0;

                switch (get_action(input)) {
                    case TurnOn:
                        if (!grid[pair]) lights_on++;

                        grid_brightness[pair]++;
                        light_brightness++;

                        grid[pair] = true;
                        break;
                    case TurnOff:
                        if (grid[pair]) lights_on--;

                        light_brightness -= grid_brightness[pair];
                        grid_brightness[pair]--;
                        if (grid_brightness[pair] < 0) grid_brightness[pair] = 0;
                        light_brightness += grid_brightness[pair];

                        grid[pair] = false;
                        break;
                    case Toggle:
                        light_brightness += 2;
                        grid_brightness[pair] += 2;

                        grid[pair] = !grid[pair];
                        if (grid[pair]) lights_on++;
                        else lights_on--;
                        break;
                }
            }
        }
    }

    std::cout << lights_on << std::endl;
    std::cout << light_brightness << std::endl;

    return 0;
}
