#include "bitmap.h"
#include <iostream>
#include <fstream>
#include <vector>

int index(int columns, int x, int y);
std::vector<std::vector<RGB24>> bitmap_to_array(const char *path);

int main(int argc, char *argv[]) {
    // if (argc < 2) {
    //     return -1;
    // }
    return 0;
}

std::vector<std::vector<RGB24>> bitmap_to_array(const char *path) {
    std::vector<std::vector<RGB24>> pixel_array;

    std::ifstream img;
    img.open(path, std::ios_base::binary);

    if (!img) {
        return pixel_array;
    }

    BITMAPFILEHEADER header;
    img.read((char*) &header, sizeof(BITMAPFILEHEADER));

    BITMAPINFOHEADER info_header;
    img.read((char*) &info_header, sizeof(BITMAPINFOHEADER));

    // Get width and height, take abs of height as it can be negative
    int width{info_header.width};
    int height{abs(info_header.height)};

    // Go to pixel information
    img.seekg(header.offset);

    pixel_array.resize(height);
    for (int i = 0; i < width; i++) {
        pixel_array[i].resize(width);
    }

    // For pixel arrays with no padding
    if (width % 4 == 0) {
        for (int y = height - 1; y >= 0; y--) {
            for (int x = 0; x < width; x++) {
                if (img.peek() == EOF) {
                    // Exception
                    break;
                }
                img.read((char*) &pixel_array[y][x], sizeof(RGB24));
            }
        }
    } else {
        int padding = 4 - (width * 3) % 4;
        
        for (int y = height - 1; y >= 0; y--) {
            for (int x = 0; x < width; x++) {
                img.read((char*) &pixel_array[y][x], sizeof(RGB24));
            }

            // Skip padding
            img.seekg(padding, std::ios_base::cur);
        }
    }
    img.close();

    return pixel_array;
}
