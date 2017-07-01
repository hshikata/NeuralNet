#include <gtest/gtest.h>
#include <utility>
#include "OneMatrix.hpp"

TEST(Matrix, Default)
{
	onesimus::Matrix<int> mat;
	ASSERT_EQ(mat.Rows(), 0);
	ASSERT_EQ(mat.Cols(), 0);
}

TEST(Matrix, Size)
{
    onesimus::Matrix<int> mat(3, 4);
    ASSERT_EQ(mat.Rows(), 3);
    ASSERT_EQ(mat.Cols(), 4);
}

TEST(Matrix, Assignment)
{
	onesimus::Matrix<int> mat(4, 5);
	mat(1, 1) = 10;
	ASSERT_EQ(mat(1, 1), 10);
}

TEST(Matrix, Iterator)
{
	onesimus::Matrix<int> mat(5, 10);
	std::fill(mat.begin(), mat.end(), 1);
	for (size_t ir = 0; ir < mat.Rows(); ++ir)
	{
		for (size_t ic = 0; ic < mat.Cols(); ++ic)
		{
			ASSERT_EQ(mat(static_cast<int>(ir), static_cast<int>(ic)), 1);
		}
	}
}

TEST(Matrix, Addition)
{
	onesimus::Matrix<int> m1(3, 3);
	std::fill(m1.begin(), m1.end(), 5);

	onesimus::Matrix<int> m2(3, 3);
	std::fill(m2.begin(), m2.end(), 3);

	auto const result = m1 + m2;
	for (size_t ir = 0; ir < result.Rows(); ++ir)
	{
		for (size_t ic = 0; ic < result.Cols(); ++ic)
		{
			ASSERT_EQ(result(static_cast<int>(ir), static_cast<int>(ic)), 8);
		}
	}
}

TEST(Matrix, Subtraction)
{
	onesimus::Matrix<int> m1(3, 3);
	std::fill(m1.begin(), m1.end(), 4);

	onesimus::Matrix<int> m2(3, 3);
	std::fill(m2.begin(), m2.end(), 6);

	auto const result = m1 - m2;
	for (size_t ir = 0; ir < result.Rows(); ++ir)
	{
		for (size_t ic = 0; ic < result.Cols(); ++ic)
		{
			ASSERT_EQ(result(static_cast<int>(ir), static_cast<int>(ic)), -2);
		}
	}
}

TEST(Matrix, ConstPostMultiplication)
{
	onesimus::Matrix<int> mat(3, 3);
	std::fill(mat.begin(), mat.end(), 4);

	auto const result = mat * 4;
	for (size_t ir = 0; ir < result.Rows(); ++ir)
	{
		for (size_t ic = 0; ic < result.Cols(); ++ic)
		{
			ASSERT_EQ(result(static_cast<int>(ir), static_cast<int>(ic)), 16);
		}
	}
}

TEST(Matrix, ConstPreMultiplication)
{
	onesimus::Matrix<int> mat(3, 3);
	std::fill(mat.begin(), mat.end(), 4);

	auto const result = 4 * mat;
	for (size_t ir = 0; ir < result.Rows(); ++ir)
	{
		for (size_t ic = 0; ic < result.Cols(); ++ic)
		{
			ASSERT_EQ(result(static_cast<int>(ir), static_cast<int>(ic)), 16);
		}
	}
}

TEST(Matrix, ConstDivision)
{
	onesimus::Matrix<int> mat(3, 3);
	std::fill(mat.begin(), mat.end(), 4);

	auto const result = mat / 4;
	for (size_t ir = 0; ir < result.Rows(); ++ir)
	{
		for (size_t ic = 0; ic < result.Cols(); ++ic)
		{
			ASSERT_EQ(result(static_cast<int>(ir), static_cast<int>(ic)), 1);
		}
	}
}