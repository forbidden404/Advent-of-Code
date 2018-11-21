#include <stdio.h>

int main() {
    int floor = 0;
    int position_in_basement = 0;
    int has_found_position = 0;
    char current_char = 'a';

    while (scanf("%c", &current_char) == 1) {
        if (current_char == '(') {
            floor++;
        } else if (current_char == ')') {
            floor--;
        }

        if (!has_found_position) {
            position_in_basement++;
            if (floor == -1)
                has_found_position = 1;
        }
    }

    printf("%d\n", floor);
    printf("%d\n", position_in_basement);

    return 0;
}
