//
// Created by mat on 6/9/2022.
//

#include "color.h"

COLOR color_get(int argb) {
    return (COLOR) {
            .r = (float) ((argb >> 16) & 0xFF) / 255.0f,
            .g = (float) ((argb >> 8) & 0xFF) / 255.0f,
            .b = (float) (argb & 0xFF) / 255.0f,
            .a = (float) ((argb >> 24) & 0xFF) / 255.0f,
            .argb = argb
    };
}