#ifndef onesimus_Matrix_hpp
#define onesimus_Matrix_hpp
#include <vector>

namespace onesimus {
	
template<typename T>
class Matrix
{
public:
	typedef std::vector<T> DataContainerType;
	
public:
	Matrix();
	Matrix(size_t rows, size_t cols);
	Matrix(Matrix const& mat);
	
public:
	size_t Rows() const { return m_rows; }
	size_t Cols() const { return m_cols; }
	
	void Resize(size_t rows, size_t cols);	
	
	typename DataContainerType::iterator begin();
	typename DataContainerType::const_iterator cbegin() const;
	typename DataContainerType::iterator end();
	typename DataContainerType::const_iterator cend() const;
	
	T const& operator()(int ir, int ic) const;
	T& operator()(int ir, int rc);

	Matrix& operator+=(Matrix const& mat);
	Matrix& operator-=(Matrix const& mat);
	Matrix& operator*=(T val);
	Matrix& operator/=(T val);
	
private:
	size_t m_rows, m_cols;
	DataContainerType m_data;
};

template<typename T>
Matrix<T>
operator+(Matrix<T> const& m1, Matrix<T> const& m2);

template<typename T>
Matrix<T>
operator-(Matrix<T> const& m1, Matrix<T> const& m2);

template<typename T>
Matrix<T>
operator*(Matrix<T> const& mat, T val);

template<typename T>
Matrix<T>
operator*(T val, Matrix<T> const& mat);

template<typename T>
Matrix<T>
operator/(Matrix<T> const& mat, T val);
	
} // end namespace onesimus


#include "OneMatrix.txx"

#endif // onesimus_Matrix_hpp