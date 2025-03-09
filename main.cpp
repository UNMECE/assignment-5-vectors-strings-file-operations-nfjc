#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "pixel.h"
//The function that averages colors.
void average_colors(std::vector<Pixel> &pixels) {
    float sum_r = 0, sum_g = 0, sum_b = 0;
    int total_pixels = pixels.size();
//Summing totals for each color.
    for (const auto &pixel : pixels) {
        sum_r += pixel.r;
        sum_g += pixel.g;
        sum_b += pixel.b;
    }
//Aevring RBG values and outputting them.
    std::cout << "Average R: " << sum_r / total_pixels << "\n";
    std::cout << "Average G: " << sum_g / total_pixels << "\n";
    std::cout << "Average B: " << sum_b / total_pixels << "\n";
}
//The function to flip the pixel values and output them into flippeed.dat.
void flip_vertically(std::vector<Pixel> &pixels) {
    int max_y = 255; // Hardcoded height since input is fixed
    for (auto &pixel : pixels) {
        pixel.y = max_y - pixel.y; // Invert the y-coordinate
    }
}

int main(int argc, char *argv[]) {
//Checking if the correct amount of arguments are given.
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input file>\n";
        return 1;
    }

    std::string input_filename = argv[1];
    std::ifstream input_file(input_filename);
//It kept being unable to get the input file so I added a check.
    if (!input_file) {
        std::cerr << "Error: Could not open file " << input_filename << "\n";
        return 1;
    }

    std::vector<Pixel> pixels;
    std::string line;
//The while loop that gathers and parses through the file to get values for everything.
    while (std::getline(input_file, line)) {
        size_t pos = 0, next_pos;
        Pixel pixel;

        // Parse x
        next_pos = line.find(',', pos);
        pixel.x = std::stoi(line.substr(pos, next_pos - pos));
        pos = next_pos + 1;

        // Parse y
        next_pos = line.find(',', pos);
        pixel.y = std::stoi(line.substr(pos, next_pos - pos));
        pos = next_pos + 1;

        // Parse red
        next_pos = line.find(',', pos);
        pixel.r = std::stof(line.substr(pos, next_pos - pos));
        pos = next_pos + 1;

        // Parse green
        next_pos = line.find(',', pos);
        pixel.g = std::stof(line.substr(pos, next_pos - pos));
        pos = next_pos + 1;

        // Parse blue
        pixel.b = std::stof(line.substr(pos));

        pixels.push_back(pixel);
    }

    input_file.close();
//Function calls!
    average_colors(pixels);
    flip_vertically(pixels);

    std::ofstream output_file("flipped.dat");
//Kept failing to make output file too so I added another check.
    if (!output_file) {
        std::cerr << "Error creating output file.\n";
        return 1;
    }
//Formatting ther output with commas.
    for (const auto &pixel : pixels) {
        output_file << pixel.x << "," << pixel.y << ","
                    << pixel.r << "," << pixel.g << "," << pixel.b << "\n";
    }

    output_file.close();
    return 0;
}

