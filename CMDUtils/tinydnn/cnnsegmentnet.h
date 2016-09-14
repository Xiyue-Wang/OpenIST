#ifndef CNNSEGMENTNETH
#define CNNSEGMENTNETH

#include <tiny_cnn/tiny_cnn.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace tiny_cnn;

class CNNSegmentnet
{
public:
    enum ImageResizeMethod {CropAndResizeFromCenter, PaddZeroAndResize};

    CNNSegmentnet();
    void train(cv::InputArrayOfArrays _vvis, cv::InputArrayOfArrays _vseg, int _epoch, int _minibatch);
    void update(cv::InputArrayOfArrays _vvis, cv::InputArrayOfArrays _vseg, int _epoch, int _minibatch);
    void save(const char *filename) const;
    bool load(const char *filename);
    cv::Size getInputSize() const;
    void setInputSize(const cv::Size &_size);
    int getInputChannels() const;
    void setInputChannels(int _value);
    int getOutputChannels() const;
    void setOutputChannels(int _value);
    void setImageResizeMethod(ImageResizeMethod method);
    ImageResizeMethod getImageResizeMethod() const;
    cv::Mat predict(const cv::Mat &image) const;

private:
    void __train(cv::InputArrayOfArrays _vvis, cv::InputArrayOfArrays _vseg, int _epoch, int _minibatch, bool preservedata);
    tiny_cnn::network<tiny_cnn::sequential> __initNet(const cv::Size &size, int inchannels, int outchannels);
    cv::Mat __cropresize(const cv::Mat &input, const cv::Size size) const;
    cv::Mat __propresize(const cv::Mat &input, const cv::Size size) const;
    tiny_cnn::vec_t __mat2vec_t(const cv::Mat &img, const cv::Size targetSize, int targetChannels, double min=-1.0, double max=1.0) const;

    mutable tiny_cnn::network<tiny_cnn::sequential> m_net;
    cv::Size m_inputsize;
    int m_inputchannels;
    int m_outputchannels;
    ImageResizeMethod m_irm = PaddZeroAndResize;
};

void visualizeActivations(const tiny_cnn::network<tiny_cnn::sequential> &_net);
void visualizeLastLayerActivation(const tiny_cnn::network<tiny_cnn::sequential> &_net);

template<typename T>
cv::Mat tinyimage2mat(const tiny_cnn::image<T> &_image);

template <typename Iterator1, typename Iterator2>
void __random_shuffle (Iterator1 v1first, Iterator1 v1last, Iterator2 v2first, Iterator2 v2last);


#endif // CNNSEGMENTNETH
