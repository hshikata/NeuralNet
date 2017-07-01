#ifndef onesimus_Matrix_txx
#define onesimus_Matrix_txx
#include <algorithm>
#include <functional>

namespace onesimus {
	
template<typename T>
Matrix<T>
::Matrix()
: m_rows(0)
, m_cols(0)
{}

template<typename T>
Matrix<T>
::Matrix(size_t rows, size_t cols)
: m_rows(rows)
, m_cols(cols)
, m_data(rows * cols)
{}

template<typename T>
Matrix<T>
::Matrix(Matrix const& mat)
: m_rows(mat.Rows())
, m_cols(mat.Cols())
, m_data(m_rows * m_cols)
{
	std::copy(mat.m_data.cbegin(), mat.m_data.cend(), m_data.begin());
}

template<typename T>
void
Matrix<T>
::Resize(size_t rows, size_t cols)
{
	try
	{
		m_data.resize(rows * cols);
		m_rows = rows;
		m_cols = cols;
	}
	catch (std::exception const&)
	{}	
}

template<typename T>
typename Matrix<T>::DataContainerType::iterator
Matrix<T>
::begin()
{
	return m_data.begin();
}

template<typename T>
typename Matrix<T>::DataContainerType::const_iterator
Matrix<T>
::cbegin() const
{
	return m_data.cbegin();
}

template<typename T>
typename Matrix<T>::DataContainerType::iterator
Matrix<T>
::end()
{
	return m_data.end();
}

template<typename T>
typename Matrix<T>::DataContainerType::const_iterator
Matrix<T>
::cend() const
{
	return m_data.cend();
}

template<typename T>
T const&
Matrix<T>
::operator()(int ir, int ic) const
{
	return m_data.at(ir * m_cols + ic);
}

template<typename T>
T&
Matrix<T>
::operator()(int ir, int ic)
{
	return m_data.at(ir * m_cols + ic);
}

template<typename T>
Matrix<T>&
Matrix<T>
::operator+=(Matrix const& mat)
{
	std::transform(mat.m_data.cbegin(), mat.m_data.cend(), m_data.cbegin(), m_data.begin(), std::plus<T>());
	return *this;
}

template<typename T>
Matrix<T>&
Matrix<T>
::operator-=(Matrix const& mat)
{
	std::transform(m_data.cbegin(), m_data.cend(), mat.m_data.cbegin(), m_data.begin(), std::minus<T>());
	return *this;
}

template<typename T>
Matrix<T>&
Matrix<T>
::operator*=(T val)
{
	std::transform(m_data.cbegin(), m_data.cend(), m_data.begin(), std::bind2nd(std::multiplies<T>(), val));
	return *this;
}

template<typename T>
Matrix<T>&
Matrix<T>
::operator/=(T val)
{
	std::transform(m_data.cbegin(), m_data.cend(), m_data.begin(), std::bind2nd(std::divides<T>(), val));
	return *this;
}
	
template<typename T>
Matrix<T>
operator+(Matrix<T> const& m1, Matrix<T> const& m2)
{
	Matrix<T> result(m1);
	result += m2;
	return result;
}

template<typename T>
Matrix<T>
operator-(Matrix<T> const& m1, Matrix<T> const& m2)
{
	Matrix<T> result(m1);
	result -= m2;
	return result;
}

template<typename T>
Matrix<T>
operator*(Matrix<T> const& mat, T val)
{
	Matrix<T> result(mat);
	result *= val;
	return result;
}

template<typename T>
Matrix<T>
operator*(T val, Matrix<T> const& mat)
{
	return mat * val;
}

template<typename T>
Matrix<T>
operator/(Matrix<T> const& mat, T val)
{
	Matrix<T> result(mat);
	result /= val;
	return result;
}

} // namespace onesimus

#endif // onesimus_Matrix_txx
