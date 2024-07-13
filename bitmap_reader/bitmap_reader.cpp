#include "bitmap.h"
#include "ascii_map.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <map>

std::vector<std::vector<RGB24>> bitmap_to_array(const char *path);
double rgb_to_greyscale(RGB24 color);
char find_ascii(double luminance);
void print_ascii(std::vector<std::vector<RGB24>>& pixel_array);

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
    for (int i = 0; i < height; i++) {
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

double rgb_to_greyscale(RGB24 color) {
    double R{(double) color.rgb_red / 255};
    double G{(double) color.rgb_green / 255};
    double B{(double) color.rgb_blue / 255};

    double c_lin = (0.2126 * R) + (0.7152 * G) + (0.0722 * B);
    return ((c_lin <= 0.0031308) ? 12.92 * c_lin : (1.055 * pow(c_lin, 1 / 2.4)) - 0.055);
}

char find_ascii(double luminance) {
    std::map<double, char>::const_iterator low, prev;

    low = ascii_map.lower_bound(luminance);

    if (low == ascii_map.end()) {
        return '@';
    } else {
        if (low != ascii_map.begin()) {
            prev = low--;
            if ((low->first - luminance) > (luminance - prev->first)) {
                return prev->second;
            } else {
                return low->second; // Upper diff <= lower diff
            }
        } else {
            return ' ';
        } 
    }
}

void print_ascii(std::vector<std::vector<RGB24>>& pixel_array) {
    for (int y = 0; y < pixel_array.size(); y++) {
        for (int x = 0; x < pixel_array[0].size(); x++) {
            std::cout << find_ascii(rgb_to_greyscale(pixel_array[y][x]));
        }
        std::cout << '\n';
    }
}