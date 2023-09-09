#include "bitmap.h"
#include <iostream>
#include <fstream>
#include <cstdint>

int index(int columns, int x, int y);

int main(int argc, char *argv[]) {
    // if (argc < 2) {
    //     return -1;
    // }

    std::ifstream img;
    img.open("./img/bunny.bmp", std::ios_base::binary);

    // Get header
    BITMAPFILEHEADER header;
    img.read((char*) &header, sizeof(BITMAPFILEHEADER));

    // Get info header
    BITMAPINFOHEADER info_header;
    img.read((char*) &info_header, sizeof(BITMAPINFOHEADER));

    // Get width and height, take abs of height as it can be negative
    int width{info_header.width};
    int height{abs(info_header.height)};

    // Go to pixel information
    img.seekg(header.offset);

    // Initialize pixel array
    RGB24 *pixel_array = new RGB24[width * height];

    // For pixel arrays with no padding
    if (width % 4 == 0) {

        // Iterate as such 
        for (int y = height - 1; y >= 0; y--) {
            for (int x = 0; x < width; x++) {
                if (img.peek() == EOF) {
                    // Exception
                    break;
                }
                img.read((char*) &pixel_array[index(width, x, y)], sizeof(RGB24));
            }
        }
    } else {
        int padding = 4 - (width * 3) % 4;
        
        for (int y = height - 1; y >= 0; y--) {
            for (int x = 0; x < width; x++) {
                img.read((char*) &pixel_array[index(width, x, y)], sizeof(RGB24));
            }

            // Skip padding
            img.seekg(padding, std::ios_base::cur);
        }
    }
    img.close();

    return 0;
}

// Return index for 1D array given coordinates
int index(int columns, int x, int y) {
    return (y * columns + x);
}
