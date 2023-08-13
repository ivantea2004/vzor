#include<gtest/gtest.h>
#include<vzor/decode_image.hpp>
#include<load_file.hpp>

TEST(decode, size_and_color)
{
	auto file = vzor::load_file("white_100x50.png");
    

    std::size_t width, height, real_components;

    std::uint8_t* img = vzor::decode_image(
            file.data(),
            file.size(),
            4,
            width,
            height,
            real_components,
            std::allocator<char>()
        );
	
    EXPECT_EQ(img[0], 255); 
    EXPECT_EQ(img[1], 255);
    EXPECT_EQ(img[2], 255);   
    EXPECT_EQ(img[3], 255); // check white color
    
    

	//EXPECT_EQ(img.data()[0], white);
	EXPECT_EQ(width, 100);
	EXPECT_EQ(height, 50);
}
