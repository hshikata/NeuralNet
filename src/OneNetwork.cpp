#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "OneNetwork.hpp"

namespace onesimus { namespace NN {

struct Sigmoid
{
    typedef Network::DataValueType value_type;
    value_type operator()(value_type z) const { return static_cast<value_type>(1) / (static_cast<value_type>(1) + std::exp(-z)); }
};

struct SigmoidPrime
{
    typedef Network::DataValueType value_type;
    value_type operator()(value_type z) const { Sigmoid s; return s(z) * (static_cast<value_type>(1) - s(z)); }
};

Network::VectorType
OneHot(unsigned char val, int size)
{
    Network::VectorType result(size);
    std::fill(result.begin(), result.begin(), static_cast<Network::VectorType::value_type>(0));
    result(val) = static_cast<Network::VectorType::value_type>(1);
    return result;
}

Network::VectorType
ElementwiseProduct(Network::VectorType const& v1, Network::VectorType const& v2)
{
    auto result(v1);
    std::transform(result.cbegin(), result.cend(), v2.cbegin(), result.begin(), std::multiplies<Network::VectorType::value_type>());
    return result;
}

Network
::Network(std::initializer_list<size_t> const& layer)
: m_layers(layer)
, m_weights(layer.size())
, m_biases(layer.size())
{
    std::random_device dev;
    std::mt19937 gen(dev());
    std::normal_distribution<double> dist(0, 1);

    for (size_t l = 1; l < m_layers.size(); ++l)
    {
        m_biases.at(l).Resize(m_layers.at(l));
        auto& b = m_biases.at(l);
        std::for_each(b.begin(), b.end(), [&](auto& v) { v = dist(gen); });

		m_weights.at(l).Resize(m_layers.at(l), m_layers.at(l - 1));
        auto& w = m_weights.at(l);
        std::for_each(w.begin(), w.end(), [&](auto& v) { v = dist(gen); });
    }
}

std::vector<size_t> const&
Network
::Layers() const
{
    return m_layers;
}

void
Network
::SGD(std::vector<DataType> const& training_data, size_t epochs, size_t mini_batch_size, DataValueType eta, std::vector<DataType> const& test_data)
{
    auto engine = std::default_random_engine{};
    std::vector<size_t> indexes(training_data.size());
    for (size_t i = 0; i < indexes.size(); ++i)
    {
        indexes.at(i) = i;
    }

    for (size_t it = 0; it < epochs; ++it)
    {
        std::shuffle(indexes.begin(), indexes.end(), engine);
        for (size_t im = 0; im + mini_batch_size < indexes.size(); im += mini_batch_size)
        {
            this->UpdateMiniBatch(training_data, indexes, im, mini_batch_size, eta);
        }

        if (!test_data.empty())
        {
            size_t const count = this->Evaluate(test_data);
			std::cout << "Epoch: " << it << ": " << count << " / " << test_data.size() << std::endl;
        }
    }
}

void
Network
::UpdateMiniBatch(std::vector<DataType> const& training_data, std::vector<size_t> const& indexes, size_t startIndex, size_t mini_batch_size, DataValueType eta)
{
    std::vector<MatrixType> nabla_w(m_weights);
    std::for_each(nabla_w.begin(), nabla_w.end(), [](auto& w) { std::fill(w.begin(), w.end(), 0); });
    std::vector<VectorType> nabla_b(m_biases);
    std::for_each(nabla_b.begin(), nabla_b.end(), [](auto& b) { std::fill(b.begin(), b.end(), 0); });

    std::vector<MatrixType> nabla_delta_w(m_layers.size());
    std::vector<VectorType> nabla_delta_b(m_layers.size());
	for (size_t i = 0; i < mini_batch_size; ++i)
	{
		auto const& data = training_data.at(indexes.at(startIndex + i));
		this->Backprop(data, nabla_delta_w, nabla_delta_b);
        for (size_t l = 1; l < m_layers.size(); ++l)
        {
            nabla_w.at(l) += nabla_delta_w.at(l);
            nabla_b.at(l) += nabla_delta_b.at(l);
        }
	}

    for (size_t l = 1; l < m_layers.size(); ++l)
    {
        m_weights.at(l) -= (eta / static_cast<DataValueType>(mini_batch_size)) * nabla_w.at(l);
        m_biases.at(l) -= (eta / static_cast<DataValueType>(mini_batch_size)) * nabla_b.at(l);
    }
}

void
Network
::Backprop(DataType const& data, std::vector<MatrixType>& nabla_w, std::vector<VectorType>& nabla_b)
{
    auto const& x = std::get<0>(data);
    auto const y = OneHot(std::get<1>(data), 10);

    // forward
    std::vector<VectorType> activations(m_layers.size());
    activations.front() = x;
    std::vector<VectorType> zs(m_layers.size());
    for (size_t l = 1; l < m_layers.size(); ++l)
    {
        auto& z = zs.at(l);
        z = m_weights.at(l) * activations.at(l - 1) + m_biases.at(l);
		auto& a = activations.at(l);
		a = z;
        std::transform(a.cbegin(), a.cend(), a.begin(), Sigmoid());
    }

    // backward
    auto spv(zs.back());
    std::transform(spv.cbegin(), spv.cend(), spv.begin(), SigmoidPrime());
    auto delta = ElementwiseProduct(activations.back() - y, spv); // (BP1)

    nabla_b.back() = delta; // (BP3)
    nabla_w.back() = delta * Transpose(activations.at(m_layers.size() - 2)); // (BP4)

    for (size_t l = m_layers.size() - 2; 0 < l; --l)
    {
        spv = zs.at(l);
        std::transform(spv.cbegin(), spv.cend(), spv.begin(), SigmoidPrime());
        delta = ElementwiseProduct(Transpose(m_weights.at(l + 1)) * delta, spv); // (BP2)
        nabla_b.at(l) = delta; // (BP3)
        nabla_w.at(l) = delta * Transpose(activations.at(l - 1)); // (BP4)
    }
}

size_t
Network
::Evaluate(std::vector<DataType> const& test_data) const
{
    size_t count = 0;
    for (size_t i = 0; i < test_data.size(); ++i)
    {
        auto const& data = test_data.at(i);
        auto const a = this->FeedForward(std::get<0>(data));
        auto const mm = std::max_element(a.cbegin(), a.cend());
        count += (std::distance(a.cbegin(), mm) == std::get<1>(data) ? 1 : 0);
    }
    return count;
}

Network::VectorType
Network
::FeedForward(VectorType const& x) const
{
    auto result(x);
    for (size_t l = 1; l < m_layers.size(); ++l)
    {
        result = m_weights.at(l) * result + m_biases.at(l);
        std::transform(result.begin(), result.end(), result.begin(), Sigmoid());
    }
    return result;
}

} // end namespace NN
} // end namespace onesimus