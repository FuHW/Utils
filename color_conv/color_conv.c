#include <stdio.h>
#include "color_conv.h"

RGB hsv_to_rgb(HSV hsv) {
    RGB rgb;
    int h = hsv.h;
    int s = hsv.s;
    int v = hsv.v;
    
    if (s == 0) {
        // 灰度颜色，R=G=B=V
        rgb.r = rgb.g = rgb.b = v;
        return rgb;
    }

    int region = h / 60;  // 区间 (0-5)
    int remainder = (h % 60) * 255 / 60;  // 余数部分，归一化到 [0,255]

    int p = (v * (255 - s)) / 255;
    int q = (v * (255 - (s * remainder) / 255)) / 255;
    int t = (v * (255 - (s * (255 - remainder)) / 255)) / 255;

    switch (region) {
        case 0: rgb.r = v; rgb.g = t; rgb.b = p; break;
        case 1: rgb.r = q; rgb.g = v; rgb.b = p; break;
        case 2: rgb.r = p; rgb.g = v; rgb.b = t; break;
        case 3: rgb.r = p; rgb.g = q; rgb.b = v; break;
        case 4: rgb.r = t; rgb.g = p; rgb.b = v; break;
        case 5: rgb.r = v; rgb.g = p; rgb.b = q; break;
        default: rgb.r = rgb.g = rgb.b = 0; break;  // 兜底
    }
    
    return rgb;
}

HSV rgb_to_hsv(RGB rgb) {
    HSV hsv;
    int r = rgb.r, g = rgb.g, b = rgb.b;
    int max = (r > g) ? ((r > b) ? r : b) : ((g > b) ? g : b);
    int min = (r < g) ? ((r < b) ? r : b) : ((g < b) ? g : b);
    int delta = max - min;
    
    // 计算 V
    hsv.v = max;

    // 计算 S
    hsv.s = (max == 0) ? 0 : (delta * 255 / max);

    // 计算 H
    if (delta == 0) {
        hsv.h = 0; // 灰色
    } else {
        if (max == r) {
            hsv.h = 60 * (g - b) / delta;
        } else if (max == g) {
            hsv.h = 60 * (2 * delta + (b - r)) / delta;
        } else {
            hsv.h = 60 * (4 * delta + (r - g)) / delta;
        }

        if (hsv.h < 0) {
            hsv.h += 360;
        }
    }
    
    return hsv;
}
