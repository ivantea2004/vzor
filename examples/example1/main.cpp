#include<iostream>
#include<vector>
#include<fstream>
#include<format>
#include<vzor/image.hpp>
#include<vzor/decode_image.hpp>

std::vector<char> read_file(std::string filename)
{
	std::ifstream file(filename, std::ios::binary | std::ios::ate);

	if (!file)
		return {};

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

	path = __FILE__ "/../";

	path += "red.png";

	auto data = read_file(path);

	vzor::image img = vzor::decode_image<vzor::rgba_t>(data.data(), data.size());
	
	std::cout << std::format("Width: {}\nHeight: {}\n", img.width(), img.height());

	return 0;
}
