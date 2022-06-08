#include <stdio.h>

#include "res/bit_font.ttf.h"

int main() {
    printf("%d\n", (size_t) (res_bit_font_end - res_bit_font_start));
    return 0;
}
