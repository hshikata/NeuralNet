#include <iostream>
#include "OneMNISTData.hpp"
#include "OneMNISTReader.hpp"
#include "OneNetwork.hpp"

int
main(int argc, char** argv)
{
    onesimus::Matrix<int> mat(3, 5);
    onesimus::Vector<int> vec(5);
    auto const m = mat * vec;

    onesimus::NN::MNISTReader reader(onesimus::NN::train_images_idx3_ubyte, onesimus::NN::train_labels_idx1_ubyte);
	auto const& labels = reader.Labels();
	std::cout << "Labels: " << labels.size() << std::endl;
	if (10 < labels.size())
	{
		for (size_t i = 0; i < 10; ++i)
		{
			std::cout << static_cast<int>(labels.at(i)) << " ";
		}
		std::cout << std::endl;
	}

	auto const& images = reader.Images();
	std::cout << "Images: " << images.size() << std::endl;
	if (!images.empty())
	{
		auto const& i = images.front();
		for (size_t n = 0; n < i.Rows(); ++n)
		{
			for (size_t m = 0; m < i.Cols(); ++m)
			{
				std::cout << (0 < i(n, m) ? 'o' : 'x');
			}
			std::cout << std::endl;
		}
	}

    onesimus::NN::Network nn = { 2, 3, 1 };

    return 0;
}