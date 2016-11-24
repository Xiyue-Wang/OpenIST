#ifndef CNNCONVSEGMENTNETH
#define CNNCONVSEGMENTNETH

#include <tiny_dnn/tiny_dnn.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

namespace segnet {

using namespace tiny_dnn;
/**
 * @brief The base abstract class for convolutional segment networks
 * @note Derived classes should override __createNet() method
 */
class CNNConvSegmentnet
{
public:    
    CNNConvSegmentnet();
    virtual ~CNNConvSegmentnet();
    /**
     * @brief train - prepares data and starts training for particular number of epoch with desired minibatch
     * @param _vvis - raw images vector, could have arbitrary quantity of channels and 8-bit or 16-bit per channel depth
     * @param _vseg - label images vector, could have arbitrary quantity of channels and 8-bit or 16-bit per channel depth, each channel will be associated with particular object class
     * @param _epoch - number of training iterations (one iteration is performed on whole training data set)
     * @param _minibatch - how many samples should be enrolled before parameters of the network will be updated (select in range from 1 to 16), the greater value is used the smoothed loss function will be that in general prevents local minimum jam
     */
    void train(cv::InputArrayOfArrays _vraw, cv::InputArrayOfArrays _vlabel, int _epoch, int _minibatch, int _t2c);
    /**
     * @brief update - prepares data and runs another training session, note that update() differs from train() by weight initialization method. The train() method use random weights seeding whereas update() preserves weights that has been learned from previous train() or update() or loaded by load()
     * @param _vvis - same as in train()
     * @param _vseg - same as in train()
     * @param _epoch - same as in train()
     * @param _minibatch - same as in train()
     */
    void update(cv::InputArrayOfArrays _vraw, cv::InputArrayOfArrays _vlabel, int _epoch, int _minibatch, int _t2c);

    void save(const char *filename) const;
    bool load(const char *filename);

    cv::Size getInputSize() const;
    void setInputSize(const cv::Size &_size);

    int getInputChannels() const;
    void setInputChannels(int _value);

    int getOutputChannels() const;
    void setOutputChannels(int _value);

    cv::Mat predict(const cv::Mat &image) const;

protected:
    // It is caller responsibility to provide _weights vector with appropriate number of values
    void initNet(const cv::Size &size, const int inchannels, const int outchannels, const tiny_dnn::float_t *_weights);
    void setUniqueName(const cv::String & _name);

private:
    void __train(cv::InputArrayOfArrays _vraw, cv::InputArrayOfArrays _vlabel, int _epoch, int _minibatch, bool preservedata, int _t2c);
    virtual tiny_dnn::network<tiny_dnn::sequential> __createNet(const cv::Size &size, int inchannels, int outchannels);
    void __mosaic(const cv::Size &_msize, const cv::Mat &_rawimg, const cv::Mat &_labelimg, std::vector<vec_t> &_vparts, std::vector<label_t> &_vmarks);
    label_t __getLabel(const cv::Mat &_img);

    mutable tiny_dnn::network<tiny_dnn::sequential> m_net;
    cv::Size m_inputsize;
    int m_inputchannels;
    int m_outputchannels;
    cv::String m_uniquename;
};
/**
 * @brief __mat2vec_t - converts cv::Mat into tiny_dnn::vec_t
 * @param img - input image
 * @param targetSize - target size after conversion
 * @param targetChannels - desired quantity of the output channels
 * @param min - output minimum values
 * @param max - output maximum values
 * @return image in vector format that is used by tiny_dnn::network::fit()/train()
 */
tiny_dnn::vec_t __mat2vec_t(const cv::Mat &img, int targetChannels, double min=-1.0, double max=1.0);

/**
 * @brief visualizeActivations - draws activations of all layers in a bunch of windows
 * @param _net - network to parse
 */
void visualizeActivations(const tiny_dnn::network<tiny_dnn::sequential> &_net);

/**
 * @brief visualizeLastLayerActivation - self explained
 * @param _net - network to parse
 */
void visualizeLastLayerActivation(const tiny_dnn::network<tiny_dnn::sequential> &_net);

/**
 * @brief tinyimage2mat - converts tiny_dnn::image to cv::Mat image
 * @param _image - image that should be converted
 * @return converted image
 */
template<typename T>
cv::Mat tinyimage2mat(const tiny_dnn::image<T> &_image);

/**
 * Divides data into two subset for training and for validation purposes
 */
template<typename T>
void __subsetdata(const std::vector<T> &_vin, int _mod, std::vector<T> &_vbig, std::vector<T> &_vsmall);

/**
 * Shuffles and unskew data simultaneously
 */
template<typename T1, typename T2>
void __shuffle_and_unskew(const std::vector<T1> &vraw, const std::vector<T2> &vlabel, std::vector<T1> &_outraw, std::vector<T2> &_outlabel, size_t *_ulabels=0);


class TextSegmentConvNet : public CNNConvSegmentnet
{
public:
    TextSegmentConvNet(bool pretrained=false);

private:
    static tiny_dnn::float_t v_pretrainedweights[452];
    tiny_dnn::network<tiny_dnn::sequential> __createNet(const cv::Size &size, int inchannels, int outchannels) override;
};

} // end of the segnet namespace

#endif // CNNCONVSEGMENTNETH
