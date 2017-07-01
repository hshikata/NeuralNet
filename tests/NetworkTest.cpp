#include <gtest/gtest.h>
#include "OneNetwork.hpp"

TEST(Network, Constructor)
{
	onesimus::NN::Network net = { 2, 3, 1 };
    auto const& size = net.Size();
    ASSERT_EQ(size.size(), 3);
    ASSERT_EQ(size.at(0), 2);
    ASSERT_EQ(size.at(1), 3);
    ASSERT_EQ(size.at(2), 1);

    for (size_t layer = 0; layer < size.size(); ++layer)
    {
        auto const& bias = net.Bias(layer);
        ASSERT_EQ(bias.Size(), size.at(0));
    }
    for (size_t layer = 1; layer < size.size(); ++layer)
    {
        auto const& weight = net.Weight(layer - 1);
        ASSERT_EQ(weight.Rows(), size.at(layer - 1));
        ASSERT_EQ(weight.Cols(), size.at(layer));
    }
}
