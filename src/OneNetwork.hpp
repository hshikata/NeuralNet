#include "OneMatrix.hpp"

namespace onesimus { namespace NN {
	
class Network
{
public:
	Network(std::initializer_list<size_t> const& sizes);
	
private:
	std::vector<size_t> m_size;
	std::vector<Vector<double>> m_biases;
	std::vector<Matrix<double>> m_weights;
};
	
} // end namespace NN
} // end namespace onesimus