#include<iostream>
#include<vector>
#include<fstream>
#include<format>
#include<vzor/image.hpp>
#include<vzor/decode_image.hpp>

using rgba_t = std::array<uint8_t, 4>;

std::vector<char> read_file(std::string filename)
{
	std::ifstream file(filename, std::ios::binary | std::ios::ate);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	std::vector<char> buffer(size);
	if (file.read(buffer.data(), size))
	{
		
	}
	return buffer;
}

int main()
{
	
	std::string path;
	std::cin >> path;

	auto data = read_file(path);

	auto img = vzor::decode_image<rgba_t>(data.data(), data.size());
	
	std::cout << std::format("Width: {}\nHeight: {}\n", img.width(), img.height());

	return 0;
}
