#ifndef _COLOR_CONV_H_
#define _COLOR_CONV_H_

typedef struct {
    unsigned char r;    // [0,255]
    unsigned char g;    // [0,255]
    unsigned char b;    // [0,255]
} RGB;

typedef struct {
    unsigned short h;   // [0,360]
    unsigned char s;    // [0,255]
    unsigned char v;    // [0,255]
} HSV;

HSV rgb_to_hsv(RGB rgb);
RGB hsv_to_rgb(HSV hsv);

#endif
