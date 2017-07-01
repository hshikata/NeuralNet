#ifndef onesimus_NN_MNISTReader_hpp
#define onesimus_NN_MNISTReader_hpp
#include <string>
#include <vector>
#include "OneMatrix.hpp"

namespace onesimus { namespace NN {

class MNISTReader
{
public:
    typedef unsigned char LabelType;
    typedef Matrix<unsigned char> ImageType;

public:
    MNISTReader(std::string const& image_filename, std::string const& label_filename);

public:
    std::vector<LabelType> Labels() const { return m_labels; }
    std::vector<ImageType> Images() const { return m_images; }

protected:
    void ReadLabel(std::string const& filename);
    void ReadImage(std::string const& filename);

private:
    std::vector<LabelType> m_labels;
    std::vector<ImageType> m_images;
};

} // end namespace NN
} // end namespace onesimus

#endif // onesimus_NN_MNISTReader_hpp