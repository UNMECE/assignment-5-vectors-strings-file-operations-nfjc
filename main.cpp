#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "pixel.h"

void average_colors(std::vector<Pixel> &pixel_list){
	float sum_red = 0, sum_green = 0, sum_blue = 0;
	int count = pixel_list.size();
	
	for(const auto &pixel : pixel_list) {
		sum_red += pixel.r;
		sum_green += pixel.g;
		sum_blue += pixel.b;
	}
	std::cout << "Average red value: " << sum_red;
	std::cout << "Average green value: " << sum_green;
	std::cout << "Average blue value: " << sum_blue;
}
void flip_vertically(std::vector<Pixel> &pixel_list){
int height = 256; // Given y-length of the image
    std::vector<Pixel> flipped_list(pixel_list.size());

    for (const auto &pixel : pixel_list) {
        Pixel flipped_pixel = pixel;
        flipped_pixel.y = height - 1 - pixel.y; // Invert y-coordinate
        flipped_list.push_back(flipped_pixel);
    }

    pixel_list = std::move(flipped_list);






}

int main(int argc, char* argv[]){
//Delcaring vectors, strings, and file input for my program.
//This took SO long to figure out correctly. kept getting a million syntax errors.
	std::vector<Pixel> pixel_list;
	std::string pixels = argv[1];
	std::ifstream inputFile(pixels);
	std::string line;

while (std::getline(inputFile, line)) {
//The pixel values kept getting overridden so I make a separate pixel. every loop.
    Pixel pixel;
//Using int was giving me problems, size_t is better for indexing strings anyway.
    size_t pos = 0;

    //Exdracting x-coordinate
    size_t nextPos = line.find(',', pos);
    pixel.x = std::stoi(line.substr(pos, nextPos - pos));
    pos = nextPos + 1;

    //Extracting y-coordinate
    nextPos = line.find(',', pos);
    pixel.y = std::stoi(line.substr(pos, nextPos - pos));
    pos = nextPos + 1;

    //Extracting red
    nextPos = line.find(',', pos);
    pixel.r = std::stof(line.substr(pos, nextPos - pos));
    pos = nextPos + 1;

    //Extracting green
    nextPos = line.find(',', pos);
    pixel.g = std::stof(line.substr(pos, nextPos - pos));
    pos = nextPos + 1;

    //Extracting blue. This one doesnt have a comma so it's not included.
    pixel.b = std::stof(line.substr(pos));

    pixel_list.push_back(pixel);
}

inputFile.close();

    //Function calls
    average_colors(pixel_list);
    flip_vertically(pixel_list);

    //Savving the pixels to the outputted flipped.dat file.
    std::ofstream outFile("flipped.dat");
//Just in case the file isnt made or the program fails somehow.
//Should be good now I just used for bug testing.
    if (!outFile) {
        std::cerr << "Error creating output file." << std::endl;
        return 1;
    }
//Formatting the x,y,r,g,b values back into flipped.dat.
    for (const auto& pixel : pixel_list) {
        outFile << pixel.x << "," << pixel.y << ","
                << pixel.r << "," << pixel.g << "," << pixel.b << "\n";
    }

    outFile.close();
    return 0;
}
