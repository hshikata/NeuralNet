#include <gtest/gtest.h>
#include "OneNetwork.hpp"

TEST(Network, Constructor)
{
	onesimus::NN::Network net = { 2, 3, 1 };
    auto const& layers = net.Layers();
    ASSERT_EQ(layers.size(), 3);
    ASSERT_EQ(layers.at(0), 2);
    ASSERT_EQ(layers.at(1), 3);
    ASSERT_EQ(layers.at(2), 1);
}
