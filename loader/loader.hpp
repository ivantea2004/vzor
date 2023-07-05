#pragma once
#include<vector>
#include<filesystem>

namespace loader
{

	std::vector<char> load_file(std::filesystem::path filename);

}
