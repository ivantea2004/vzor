#include<iostream>
#include<vzor/decode_image.hpp>
#include<load_file.hpp>

int main()
{
	std::string path;

	std::cin >> path;

	auto file = vzor::load_file(path);

	size_t width, height, real_components;

	std::uint8_t* image = vzor::decode_image(
		file.data(),
		file.size(),
		4,
		width,
		height,
		real_components
	);

	delete image;

	std::cout << "Width: " << width<< "\nHeight: " << height << "\n";



	return 0;
}
