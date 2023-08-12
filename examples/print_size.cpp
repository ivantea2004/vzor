#include<iostream>
#include<vzor/image.hpp>
#include<vzor/decode_image.hpp>
#include<load_file.hpp>

int main()
{
	std::string path;

	std::cin >> path;

	auto file = vzor::load_file(path);

	vzor::image img = vzor::decode_image<vzor::rgba_t>(file.data(), file.size());
	
	std::cout << "Width: " << img.width() << "\nHeight: " << img.height() << "\n";

	return 0;
}
