#include<iostream>
#include<vector>
#include<fstream>
#include<filesystem>
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
	
	std::filesystem::path dir = __FILE__;
	dir = dir.parent_path();
		
	std::filesystem::path path = dir / "red.png";

	auto data = read_file(path.string());

	vzor::image img = vzor::decode_image<vzor::rgba_t>(data.data(), data.size());
	
	std::cout << "Width: " << img.width() << "\nHeight: " << img.height() << "\n";

	return 0;
}
