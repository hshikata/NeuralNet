#ifndef onesimus_NN_Network_hpp
#define onesimus_NN_Network_hpp
#include "OneMatrix.hpp"
#include "OneVector.hpp"

namespace onesimus { namespace NN {
	
class Network
{
public:
	typedef float DataValueType;
	typedef Matrix<DataValueType> MatrixType;
	typedef Vector<DataValueType> VectorType;
	typedef std::pair<VectorType, unsigned char> DataType;

public:
	Network(std::initializer_list<size_t> const& layer);

public:
	std::vector<size_t> const& Layers() const;
	
	void SGD(std::vector<DataType> const& training_data, size_t epochs, size_t mini_batch_size, DataValueType eta, std::vector<DataType> const& test_data);

protected:
	void UpdateMiniBatch(std::vector<DataType> const& training_data, std::vector<size_t> const& indexes, size_t startIndex, size_t mini_batch_size, DataValueType eta);
	void Backprop(DataType const& data, std::vector<MatrixType>& nabla_w, std::vector<VectorType>& nabla_b);
	size_t Evaluate(std::vector<DataType> const& test_data) const;
	VectorType FeedForward(VectorType const& input) const;

private:
	std::vector<size_t> m_layers;
	std::vector<MatrixType> m_weights;
	std::vector<VectorType> m_biases;
};
	
} // end namespace NN
} // end namespace onesimus

#endif // onesimus_NN_Network_hpp