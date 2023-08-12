#include<gtest/gtest.h>
#include<vzor/image.hpp>
#include<vzor/decode_image.hpp>
#include<load_file.hpp>

TEST(decode, size_and_color)
{
	auto file = vzor::load_file("white_100x50.png");
	auto img = vzor::decode_image<vzor::rgba_t>(file.data(), file.size());
	auto white = vzor::rgba_t{255, 255, 255, 255};

	EXPECT_EQ(img.data()[0], white);
	EXPECT_EQ(img.width(), 100);
	EXPECT_EQ(img.height(), 50);
}
