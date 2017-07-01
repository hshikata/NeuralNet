#ifndef onesimus_Vector_hpp
#define onesimus_Vector_hpp
#include "OneMatrix.hpp"

namespace onesimus {

template<typename T>
class Vector : public Matrix<T>
{
public:
	Vector();
	Vector(size_t size);
	
public:
	void Resize(size_t size);
	
	size_t Size() const;
	
	T const& operator()(int index) const;
	T& operator()(int index);
	T const& operator[](int index) const;
	T& operator[](int index);
	
	Vector& operator+=(Vector const& vec);
	Vector& operator-=(Vector const& vec);
	Vector& operator*=(T val);
	Vector& operator/=(T val);
};

template<typename T>
Vector<T>
operator+(Vector<T> const& v1, Vector<T> const& v2);

template<typename T>
Vector<T>
operator-(Vector<T> const& v1, Vector<T> const& v2);

template<typename T>
Vector<T>
operator*(Vector<T> const& vec, T val);

template<typename T>
Vector<T>
operator*(T val, Vector<T> const& vec);

template<typename T>
Vector<T>
operator*(Matrix<T> const& mat, Vector<T> const& vec);

template<typename T>
Vector<T>
operator/(Vector<T> const& vec, T val);
	
} // end namespace onesimus

#include "OneVector.txx"

#endif // onesimus_Vector_hpp