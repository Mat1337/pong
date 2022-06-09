//
// Created by mat on 6/9/2022.
//

#ifndef PONG_CLONE_COLOR_H
#define PONG_CLONE_COLOR_H

typedef struct {
    float r;
    float g;
    float b;
    float a;
    int argb;
} COLOR;

/**
 * Gets a color from rgba value
 *
 * @param argb argb value that you want to generate the color from
 * @return color struct
 */

COLOR color_get(int argb);

#endif //PONG_CLONE_COLOR_H
