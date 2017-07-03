#include <fstream>
#include <iterator>
#include <algorithm>
#include "OneMNISTReader.hpp"

namespace onesimus { namespace NN {

MNISTReader
::MNISTReader(std::string const& image_filename, std::string const& label_filename)
{
    this->ReadLabel(label_filename);
    this->ReadImage(image_filename);
}

void
MNISTReader
::ReadLabel(std::string const& filename)
{
    std::ifstream fp(filename.c_str(), std::ios::binary);
    if (!fp.is_open())
    {
        return;
    }

	char magic[4];
	fp.read(magic, sizeof(int));
	if (magic[0] != 0 || magic[1] != 0 || magic[2] != 8 || magic[3] != 1)
	{
		return;
	}

	char valstr[4];
    fp.read(valstr, sizeof(int));
	std::swap(valstr[0], valstr[3]);
	std::swap(valstr[1], valstr[2]);
	int const numItems = *reinterpret_cast<int const*>(valstr);
    if (numItems <= 0)
    {
        return;
    }

    try
    {
        m_labels.resize(numItems);
    }
    catch (std::bad_alloc const&)
    {
        return;
    }

    LabelType l;
    for (int i = 0; i < numItems; ++i)
    {
        fp.read(reinterpret_cast<char*>(&l), sizeof(LabelType));
        m_labels.at(i) = l;
    }
}

void
MNISTReader
::ReadImage(std::string const& filename)
{
    std::ifstream fp(filename.c_str(), std::ios::binary);
    if (!fp.is_open())
    {
        return;
    }

	char magic[4];
	fp.read(magic, sizeof(int));
	if (magic[0] != 0 || magic[1] != 0 || magic[2] != 8 || magic[3] != 3)
	{
		return;
	}

	char valstr[4];
	fp.read(valstr, sizeof(int));
	std::swap(valstr[0], valstr[3]);
	std::swap(valstr[1], valstr[2]);
	int const numItems = *reinterpret_cast<int const*>(valstr);
    if (numItems <= 0)
    {
        return;
    }

	fp.read(valstr, sizeof(int));
	std::swap(valstr[0], valstr[3]);
	std::swap(valstr[1], valstr[2]);
	int const numRows = *reinterpret_cast<int const*>(valstr);
    if (numRows <= 0)
    {
        return;
    }

	fp.read(valstr, sizeof(int));
	std::swap(valstr[0], valstr[3]);
	std::swap(valstr[1], valstr[2]);
	int const numCols = *reinterpret_cast<int const*>(valstr);
	if (numCols <= 0)
    {
        return;
    }

    try
    {
        m_images.resize(numItems, ImageType(numRows, numCols));
    }
    catch (std::bad_alloc const&)
    {
        return;
    }

    std::istreambuf_iterator<char> itr(fp);
    for (int i = 0; i < numItems; ++i)
    {
        auto& image = m_images.at(i);
        std::for_each(image.begin(), image.end(), [&](auto& v) { v = *itr++; });
    }
}

} // end namespace NN
} // end namespace onesimus