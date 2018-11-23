#include <stdio.h>
#include <stdlib.h>

int get_square_feet(int length, int width, int height) {
    int sideA = length * width;
    int sideB = width * height;
    int sideC = height * length;

    int min = sideA;
    min = min < sideB ? (min < sideC ? min : sideC) : (sideB < sideC ? sideB : sideC);

    return 2 * sideA + 2 * sideB + 2 * sideC + min;

}

int cmp(const void *a, const void *b) {
    return ( *(int *) a - *(int *) b );
}

int get_feet_ribbon(int length, int width, int height) {
    int array[3] = {length, width, height};
    qsort(array, 3, sizeof(int), cmp);
    return 2 * array[0] + 2 * array[1] + length * width * height;
}

int main() {
    int total_wrapping_paper = 0;
    int total_feet_ribbon = 0;

    int length, width, height;

    while (scanf("%dx%dx%d", &length, &width, &height) > 1) {
        total_wrapping_paper += get_square_feet(length, width, height);
        total_feet_ribbon += get_feet_ribbon(length, width, height);
    }

    printf("%d\n", total_wrapping_paper);
    printf("%d\n", total_feet_ribbon);

    return 0;
}
