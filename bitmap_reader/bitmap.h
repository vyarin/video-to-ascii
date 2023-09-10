#ifndef BITMAP_READER_BITMAP_H_INCLUDED
#define BITMAP_READER_BITMAP_H_INCLUDED

#include <stdint.h>

#pragma pack(push, 1)
struct BITMAPFILEHEADER {
    uint16_t file_type;          // BMP header field
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
};

struct BITMAPINFOHEADER {
    uint32_t size;
    int32_t  width;
    int32_t  height;
    uint16_t color_planes;
    uint16_t bits_per_pixel;     // Color depth
    uint32_t compression_method;
    uint32_t image_size;         // Raw size of bitmap
    uint32_t x_resolution;       // Pixels per metre (x)
    uint32_t y_resolution;       // Pixels per metre (y)
    uint32_t colors;             // Amount of colors
    uint32_t important_colors;
};
struct RGB24 {
    uint8_t rgb_blue;
    uint8_t rgb_green;
    uint8_t rgb_red;
};
#pragma pack(pop)

#endif