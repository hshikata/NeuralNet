#include <iostream>
#include "OneMNISTData.hpp"
#include "OneMNISTReader.hpp"
#include "OneNetwork.hpp"

int
main(int argc, char** argv)
{
    // reading training data
    typedef onesimus::NN::Network::DataType DataType;

    std::vector<DataType> training_data;
    try
    {
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
        if (10 < images.size())
        {
            for (size_t i = 0; i < 10; ++i)
            {
                auto const& img = images.at(i);
                for (size_t n = 0; n < img.Rows(); ++n)
                {
                    for (size_t m = 0; m < img.Cols(); ++m)
                    {
                        std::cout << (0 < img(n, m) ? 'o' : '-');
                    }
                    std::cout << std::endl;
                }
                std::cout << std::endl;
            }
        }

        if (labels.size() != images.size())
        {
            std::cerr << "size mismatch: " << labels.size() << ", " << images.size() << std::endl;
            return 1;
        }

        training_data.resize(images.size());
        for (size_t i = 0; i < images.size(); ++i)
        {
            auto& dst = training_data.at(i);

            auto const& srcImage = images.at(i);
            auto& dstVec = std::get<0>(dst);
            dstVec.Resize(srcImage.Rows() * srcImage.Cols());
            std::transform(srcImage.cbegin(), srcImage.cend(), dstVec.begin(), [](auto v) { return static_cast<float>(v) / 255.0f; });

            std::get<1>(dst) = labels.at(i);
        }
    }
    catch (std::exception const& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }

    // reading test data
    std::vector<DataType> test_data;
    try
    {
        onesimus::NN::MNISTReader reader(onesimus::NN::t10k_images_idx3_ubyte, onesimus::NN::t10k_labels_idx1_ubyte);

        auto const& labels = reader.Labels();
        std::cout << "Labels: " << labels.size() << std::endl;

        auto const& images = reader.Images();
        std::cout << "Images: " << images.size() << std::endl;

        if (labels.size() != images.size())
        {
            std::cerr << "size mismatch: " << labels.size() << ", " << images.size() << std::endl;
            return 1;
        }

        test_data.resize(images.size());
        for (size_t i = 0; i < images.size(); ++i)
        {
            auto& dst = test_data.at(i);

            auto const& srcImage = images.at(i);
            auto& dstVec = std::get<0>(dst);
            dstVec.Resize(srcImage.Rows() * srcImage.Cols());
            std::transform(srcImage.cbegin(), srcImage.cend(), dstVec.begin(), [](auto v) { return static_cast<float>(v) / 255.0f; });

            std::get<1>(dst) = labels.at(i);
        }
    }
    catch (std::exception const& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }

	// NN training
    onesimus::NN::Network nn = { 784, 30, 10 };
    nn.SGD(training_data, 30, 10, 3.0, test_data);

    return 0;
}