//
// Created by mat on 6/9/2022.
//

#include "color.h"

/**
 * Gets a color from rgba value
 *
 * @param argb argb value that you want to generate the color from
 * @return color struct
 */


COLOR color_get(int argb) {
    return (COLOR) {
            .r = (float) ((argb >> 16) & 0xFF) / 255.0f,
            .g = (float) ((argb >> 8) & 0xFF) / 255.0f,
            .b = (float) (argb & 0xFF) / 255.0f,
            .a = (float) ((argb >> 24) & 0xFF) / 255.0f,
            .argb = argb
    };
}