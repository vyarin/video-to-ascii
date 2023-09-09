#include "bitmap.h"
#include <cstdint>

#pragma pack(push, 1)

struct BITMAPFILEHEADER {
    uint16_t file_type{0x4D42};     // BMP header field
    uint32_t file_size{0};
    uint16_t reserved1{0};
    uint16_t reserved2{0};
    uint32_t offset{0};
};

struct BITMAPINFOHEADER {
    uint32_t size{0};
    int32_t  width{0};
    int32_t  height{0};
    uint16_t color_planes{1};       // Planes are always 1
    uint16_t bits_per_pixel{0};     // Color depth
    uint32_t compression_method{0};
    uint32_t image_size{0};         // Raw size of bitmap
    uint32_t x_resolution{0};       // Pixels per metre (x)
    uint32_t y_resolution{0};       // Pixels per metre (y)
    uint32_t colors{0};             // Amount of colors
    uint32_t important_colors{0};
};

struct RGB24 {
    uint8_t rgb_blue{0};
    uint8_t rgb_green{0};
    uint8_t rgb_red{0};
};

#pragma pack(pop)