#ifndef onesimus_Vector_txx
#define onesimus_Vector_txx

namespace onesimus {

template<typename T>
Vector<T>
::Vector()
{}

template<typename T>
Vector<T>
::Vector(size_t size)
: Matrix<T>(size, 1)
{}

template<typename T>
Vector<T>
::Vector(std::initializer_list<T> const& init)
: Matrix<T>(init.size(), 1)
{
	std::copy(init.begin(), init.end(), this->begin());
}

template<typename T>
size_t
Vector<T>
::Size() const
{
	return Matrix<T>::Rows();
}

template<typename T>
void
Vector<T>
::Resize(size_t size)
{
	Matrix<T>::Resize(size, 1);
}

template<typename T>
T const&
Vector<T>
::operator()(int index) const
{
	return Matrix<T>::operator()(index, 0);
}

template<typename T>
T&
Vector<T>
::operator()(int index)
{
	return Matrix<T>::operator()(index, 0);
}

template<typename T>
T const&
Vector<T>
::operator[](int index) const
{
	return this->operator()(index);
}

template<typename T>
T&
Vector<T>
::operator[](int index)
{
	return this->operator()(index);
}

template<typename T>
Vector<T>&
Vector<T>
::operator+=(Vector<T> const& vec)
{
	Matrix<T>::operator+=(vec);
	return *this;
}

template<typename T>
Vector<T>&
Vector<T>
::operator-=(Vector<T> const& vec)
{
	Matrix<T>::operator-=(vec);
	return *this;
}

template<typename T>
Vector<T>&
Vector<T>
::operator*=(T val)
{
	Matrix<T>::operator*=(val);
	return *this;
}

template<typename T>
Vector<T>&
Vector<T>
::operator/=(T val)
{
	Matrix<T>::operator/=(val);
	return *this;
}

template<typename T>
Vector<T>
operator+(Vector<T> const& v1, Vector<T> const& v2)
{
	Vector<T> result(v1);
	result += v2;
	return result;
}

template<typename T>
Vector<T>
operator-(Vector<T> const& v1, Vector<T> const& v2)
{
	Vector<T> result(v1);
	result -= v2;
	return result;
}

template<typename T>
Vector<T>
operator*(Vector<T> const& vec, T val)
{
	Vector<T> result(vec);
	result *= val;
	return result;
}

template<typename T>
Vector<T>
operator*(T val, Vector<T> const& vec)
{
	return vec * val;
}

template<typename T>
Vector<T>
operator*(Matrix<T> const& mat, Vector<T> const& vec)
{
	Matrix<T> const m = operator*(mat, static_cast<Matrix<T>>(vec));
	Vector<T> result(m.Rows());
	std::copy(m.cbegin(), m.cend(), result.begin());
	return result;
}

template<typename T>
Vector<T>
operator/(Vector<T> const& vec, T val)
{
	Vector<T> result(vec);
	result /= val;
	return result;
}

template<typename T>
T
Dot(Vector<T> const& v1, Vector<T> const& v2)
{
	T result = 0;
	auto itr1 = v1.cbegin();
	auto itr2 = v2.cbegin();
	for (; itr1 != v1.cend(); ++itr1, ++itr2)
	{
		result += (*itr1) * (*itr2);
	}
	return result;
}

} // end namespace onesimus

#endif // onesimus_Vector_txx