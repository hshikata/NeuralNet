#ifndef onesimus_NN_Network_hpp
#define onesimus_NN_Network_hpp
#include "OneMatrix.hpp"
#include "OneVector.hpp"

namespace onesimus { namespace NN {
	
class Network
{
public:
	Network(std::initializer_list<size_t> const& sizes);

public:
	std::vector<size_t> const& Size() const;
	Vector<double> const& Bias(size_t layer) const;
	Vector<double>& Bias(size_t layer);
	Matrix<double> const& Weight(size_t layer) const;
	Matrix<double>& Weight(size_t layer);
	
private:
	std::vector<size_t> m_size;
	std::vector<Vector<double>> m_biases;
	std::vector<Matrix<double>> m_weights;
};
	
} // end namespace NN
} // end namespace onesimus

#endif // onesimus_NN_Network_hpp