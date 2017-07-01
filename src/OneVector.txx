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
::Vector(Matrix<T> const& mat)
{}

template<typename T>
size_t
Vector<T>
::Size() const
{
	return this->Rows();
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
operator/(Vector<T> const& vec, T val)
{
	Vector<T> result(vec);
	result /= val;
	return result;
}

} // end namespace onesimus

#endif // onesimus_Vector_txx