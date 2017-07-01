#include <random>
#include <algorithm>
#include "OneNetwork.hpp"

namespace onesimus { namespace NN {

Network
::Network(std::initializer_list<size_t> const& sizes)
: m_size(sizes)
, m_biases(sizes.size())
, m_weights(sizes.size())
{
    std::random_device dev;
    std::mt19937 gen(dev());
    std::normal_distribution<double> dist(0, 1);

    for (size_t layer = 1; layer < m_size.size(); ++layer)
    {
        m_biases.at(layer - 1).Resize(m_size.at(layer - 1));
        auto& b = m_biases.at(layer - 1);
        std::for_each(b.begin(), b.end(), [&](auto& v) { v = dist(gen); });
        
		m_weights.at(layer - 1).Resize(m_size.at(layer - 1), m_size.at(layer));
        auto& w = m_weights.at(layer - 1);
        std::for_each(w.begin(), w.end(), [&](auto& v) { v = dist(gen); });
    }
}

std::vector<size_t> const&
Network
::Size() const
{
    return m_size;
}

Vector<double> const&
Network
::Bias(size_t layer) const
{
    return m_biases.at(layer);
}

Vector<double>&
Network
::Bias(size_t layer)
{
    return m_biases.at(layer);
}

Matrix<double> const&
Network
::Weight(size_t layer) const
{
    return m_weights.at(layer);
}

Matrix<double>&
Network
::Weight(size_t layer)
{
    return m_weights.at(layer);
}

} // end namespace NN
} // end namespace onesimus