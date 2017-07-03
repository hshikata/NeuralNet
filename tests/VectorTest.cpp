#include <gtest/gtest.h>
#include <utility>
#include "OneVector.hpp"

TEST(Vector, Default)
{
	onesimus::Vector<int> vec;
    ASSERT_EQ(vec.Size(), 0);
}

TEST(Vector, Init)
{
	onesimus::Vector<int> const vec{ 1, 2, 3, 4, 5 };
    ASSERT_EQ(vec.Size(), 5);
	ASSERT_EQ(vec(0), 1);
	ASSERT_EQ(vec[4], 5);
}

TEST(Vector, Size)
{
    onesimus::Vector<int> vec(3);
    ASSERT_EQ(vec.Size(), 3);
}

TEST(Vector, Assignment)
{
	onesimus::Vector<int> vec(4);
	vec(1) = 10;
	ASSERT_EQ(vec(1), 10);
	vec[2] = 8;
	ASSERT_EQ(vec[2], 8);
}

TEST(Vector, CopyAssignment)
{
	onesimus::Vector<int> v1{ 1, 2, 3, 4 };
	ASSERT_EQ(v1.Size(), 4);
	ASSERT_EQ(v1(0), 1);

	onesimus::Vector<int> v2{ 4, 5 };
	ASSERT_EQ(v2.Size(), 2);
	ASSERT_EQ(v2(0), 4);

	v1 = v2;
	ASSERT_EQ(v1.Size(), 2);
	ASSERT_EQ(v1(0), 4);
}

TEST(Vector, CopyConstructor)
{
	onesimus::Vector<int> v1(5);
	v1(2) = 5;
	ASSERT_EQ(v1(2), 5);

	onesimus::Vector<int> v2(v1);
	ASSERT_EQ(v1.Size(), v2.Size());
	ASSERT_EQ(v2(2), 5);
}

TEST(Vector, Iterator)
{
	onesimus::Vector<int> vec(5);
	std::fill(vec.begin(), vec.end(), 1);
	for (size_t i = 0; i < vec.Size(); ++i)
	{
    	ASSERT_EQ(vec(static_cast<int>(i)), 1);
        ASSERT_EQ(vec[static_cast<int>(i)], 1);
	}
}

TEST(Vector, Addition)
{
	onesimus::Vector<int> v1(10);
	std::fill(v1.begin(), v1.end(), 5);

	onesimus::Vector<int> v2(10);
	std::fill(v2.begin(), v2.end(), 3);

	auto const result = v1 + v2;
	for (size_t i = 0; i < result.Size(); ++i)
	{
		ASSERT_EQ(result(static_cast<int>(i)), 8);
        ASSERT_EQ(result[static_cast<int>(i)], 8);
	}
}

TEST(Vector, Subtraction)
{
	onesimus::Vector<int> v1(10);
	std::fill(v1.begin(), v1.end(), 4);

	onesimus::Vector<int> v2(10);
	std::fill(v2.begin(), v2.end(), 6);

	auto const result = v1 - v2;
	for (size_t i = 0; i < result.Size(); ++i)
	{
		ASSERT_EQ(result(static_cast<int>(i)), -2);
        ASSERT_EQ(result[static_cast<int>(i)], -2);
	}
}

TEST(Vector, ConstPostMultiplication)
{
	onesimus::Vector<int> vec(10);
	std::fill(vec.begin(), vec.end(), 4);

	auto const result = vec * 4;
	for (size_t i = 0; i < result.Size(); ++i)
	{
		ASSERT_EQ(result(static_cast<int>(i)), 16);
        ASSERT_EQ(result[static_cast<int>(i)], 16);
	}
}

TEST(Vector, ConstPreMultiplication)
{
	onesimus::Vector<int> vec(10);
	std::fill(vec.begin(), vec.end(), 4);

	auto const result = 4 * vec;
	for (size_t i = 0; i < result.Size(); ++i)
	{
		ASSERT_EQ(result(static_cast<int>(i)), 16);
        ASSERT_EQ(result[static_cast<int>(i)], 16);
	}
}

TEST(Vector, MatrixVectorMultiplication)
{
	onesimus::Matrix<int> mat(3, 5);
	std::fill(mat.begin(), mat.end(), 4);
	onesimus::Vector<int> vec(5);
	std::fill(vec.begin(), vec.end(), 5);

	auto const result = mat * vec;
	ASSERT_EQ(result.Size(), mat.Rows());
	for (size_t ir = 0; ir < result.Size(); ++ir)
	{
		ASSERT_EQ(result(static_cast<int>(ir)), 100);
	}
}

TEST(Vector, RowVectorColumnVectorMultiplication)
{
	onesimus::Vector<int> v1{ 1, 2, 3 };
	onesimus::Vector<int> v2{ 2, 3, 4 };

	auto const result = v1 * Transpose(v2);
	ASSERT_EQ(result.Rows(), 3);
	ASSERT_EQ(result.Cols(), 3);
	ASSERT_EQ(result(0, 0), 2);
	ASSERT_EQ(result(0, 1), 3);
	ASSERT_EQ(result(1, 0), 4);
}

TEST(Vector, ConstDivision)
{
	onesimus::Vector<int> vec(10);
	std::fill(vec.begin(), vec.end(), 4);

	auto const result = vec / 4;
	for (size_t i = 0; i < result.Size(); ++i)
	{
		ASSERT_EQ(result(static_cast<int>(i)), 1);
        ASSERT_EQ(result[static_cast<int>(i)], 1);
	}
}

TEST(Vector, Dot)
{
	onesimus::Vector<int> const v1{ 1, 2, 3 };
	onesimus::Vector<int> const v2{ 2, 3, 4 };

	auto const result = Dot(v1, v2);
	ASSERT_EQ(result, 20);
}
