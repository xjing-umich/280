#include <iostream>
#include <string>
#include <fstream>
#include "processing.hpp"


int main(int argc, char* argv[]) {
	if ((argc < 4) || (argc > 5)) {
		std::cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
			<< "WIDTH and HEIGHT must be less than or equal to original" << std::endl;
		return 1;
	}
	std::ifstream ppm_file(argv[1]);
	std::ofstream target_file(argv[2]);

	if ((not ppm_file)) {
		std::cout << "Error opening file: " << argv[1] << std::endl;
		return 1;
	}

	if ((not target_file)) {
		std::cout << "Error opening file: " << argv[2] << std::endl;
		return 1;
	}

	Image img;
	Image_init(&img, ppm_file);

	int img_width = Image_width(&img);
	int img_height = Image_height(&img);
	int desired_width = std::stoi(argv[3]);
	int desired_height = img_height;
	if ((desired_width < 0) || (img_width < desired_width)) {
		std::cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
			<< "WIDTH and HEIGHT must be less than or equal to original" << std::endl;
		return 1;
	}
	
	if (argc == 5) {
		int desired_height = std::stoi(argv[4]);
		if ((desired_height < 0) || (desired_height > img_height)) {
			std::cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
				<< "WIDTH and HEIGHT must be less than or equal to original" << std::endl;
			return 1;
		}
	}
	seam_carve(&img, desired_width, desired_height);
	Image_print(&img, target_file);

	return 0;

}