IF (NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/t10k-images.idx3-ubyte")
FILE(DOWNLOAD https://github.com/mrgloom/MNIST-dataset-in-different-formats/raw/master/data/Original%20dataset/t10k-images.idx3-ubyte ${CMAKE_CURRENT_BINARY_DIR}/t10k-images.idx3-ubyte)
ENDIF ()
IF (NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/t10k-labels.idx1-ubyte")
FILE(DOWNLOAD https://github.com/mrgloom/MNIST-dataset-in-different-formats/raw/master/data/Original%20dataset/t10k-labels.idx1-ubyte ${CMAKE_CURRENT_BINARY_DIR}/t10k-labels.idx1-ubyte)
ENDIF ()
IF (NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/train-images.idx3-ubyte")
FILE(DOWNLOAD https://github.com/mrgloom/MNIST-dataset-in-different-formats/raw/master/data/Original%20dataset/train-images.idx3-ubyte ${CMAKE_CURRENT_BINARY_DIR}/train-images.idx3-ubyte)
ENDIF ()
IF (NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/train-labels.idx1-ubyte")
FILE(DOWNLOAD https://github.com/mrgloom/MNIST-dataset-in-different-formats/raw/master/data/Original%20dataset/train-labels.idx1-ubyte ${CMAKE_CURRENT_BINARY_DIR}/train-labels.idx1-ubyte)
ENDIF ()

FILE(WRITE ${CMAKE_CURRENT_BINARY_DIR}/OneMNISTData.hpp
"namespace onesimus { namespace NN {\n"
"\n"
"char const* const t10k_images_idx3_ubyte = \"${CMAKE_CURRENT_BINARY_DIR}/t10k-images.idx3-ubyte\";\n"
"char const* const t10k_labels_idx1_ubyte = \"${CMAKE_CURRENT_BINARY_DIR}/t10k-labels.idx1-ubyte\";\n"
"char const* const train_images_idx3_ubyte = \"${CMAKE_CURRENT_BINARY_DIR}/train-images.idx3-ubyte\";\n"
"char const* const train_labels_idx1_ubyte = \"${CMAKE_CURRENT_BINARY_DIR}/train-labels.idx1-ubyte\";\n"
"\n"
"} // end namespace NN\n"
"} // end namespace onesimus")

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/src
)

ADD_EXECUTABLE(mnist mnist.cpp)
TARGET_LINK_LIBRARIES(mnist NeuralNet ${CMAKE_THREAD_LIBS_INIT})
