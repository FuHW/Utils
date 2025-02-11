#include "math.h"
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
    int h, s, v;
    int r = rgb.r, g = rgb.g, b = rgb.b;
    int max = (r > g) ? ((r > b) ? r : b) : ((g > b) ? g : b);
    int min = (r < g) ? ((r < b) ? r : b) : ((g < b) ? g : b);
    int delta = max - min;
    
    // 计算 V
    v = max;

    // 计算 S
    s = (max == 0) ? 0 : (delta * 255 / max);

    // 计算 H
    if (delta == 0) {
        h = 0; // 灰色
    } else {
        if (max == r) {
            h = 60 * (g - b) / delta;
        } else if (max == g) {
            h = 60 * (2 * delta + (b - r)) / delta;
        } else {
            h = 60 * (4 * delta + (r - g)) / delta;
        }

        if (h < 0) {
            h += 360;
        }
    }

    hsv.h = h;
    hsv.s = (s > 255) ? (255) : (s);
    hsv.v = (v > 255) ? (255) : (v);
    
    return hsv;
}

HSL rgb_to_hsl(RGB rgb)
{
    HSL hsl;
    int h,s,l;
    int r = rgb.r, g = rgb.g, b = rgb.b;
    int max = (r > g) ? ((r > b) ? r : b) : ((g > b) ? g : b);
    int min = (r < g) ? ((r < b) ? r : b) : ((g < b) ? g : b);
    int delta = max - min;

    // 计算亮度 L
    l = (max + min) / 2;

    // 计算饱和度 S
    if (delta == 0) {
        s = 0;  // 灰色
    } else {
        s = (l == 0 || l == 255) ? 0 : (delta * 255) / (255 - abs(2 * l - 255));
    }

    // 计算色相 H
    if (delta == 0) {
        h = 0;  // 灰色
    } else {
        if (max == r) {
            h = 60 * (g - b) / delta;
        } else if (max == g) {
            h = 60 * (2 * delta + (b - r)) / delta;
        } else {
            h = 60 * (4 * delta + (r - g)) / delta;
        }
    }

    if (h < 0) {
        h += 360;
    }

    hsl.h = h;
    hsl.s = (s > 255) ? (255) : (s);
    hsl.l = (l > 255) ? (255) : (l);

    return hsl;
}

RGB hsl_to_rgb(HSL hsl)
{
    RGB rgb;
    int h = hsl.h, s = hsl.s, l = hsl.l;
    int r1,g1,b1;
    int region;

    if (s == 0) {
        // 灰色
        rgb.r = rgb.g = rgb.b = l;
        return rgb;
    }

    int c = (255 - abs(2 * l - 255)) * s / 255;
    int x = c * (60 - abs((h % 120) - 60)) / 60;
    int m = l - c / 2;

    region = h / 60;

    switch (region) {
        case 0: r1 = c; g1 = x; b1 = 0; break;
        case 1: r1 = x; g1 = c; b1 = 0; break;
        case 2: r1 = 0; g1 = c; b1 = x; break;
        case 3: r1 = 0; g1 = x; b1 = c; break;
        case 4: r1 = x; g1 = 0; b1 = c; break;
        case 5: r1 = c; g1 = 0; b1 = x; break;
        default: r1 = g1 = b1 = 0; break;
    }

    rgb.r = r1 + m;
    rgb.g = g1 + m;
    rgb.b = b1 + m;

    return rgb;
}
