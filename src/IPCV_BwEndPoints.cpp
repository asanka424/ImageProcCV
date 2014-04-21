#include <ImageProcCV.h>

int ImageProcCV::bwEndPoints(cv::Mat &bw, std::vector<cv::Point> &endPoints)
{
    int retVal = NO_ERRORS;
    if (bw.type() != CV_8UC1)
    {
        retVal = INV_IMG_TYPE;
        return retVal;
    }
    cv::Mat lut;
    getLutEndPoints(lut);
    cv::Mat output = cv::Mat::zeros(bw.size(),bw.type());
    bool changed;
    applyLUT(bw,lut,false,output,changed);

    endPoints.clear();
    for (int i = 0; i < output.rows; i++)
    {
        uchar* pdata = output.ptr<uchar>(i);
        for (int j = 0; j<output.cols; j++)
        {
            if (pdata[j] == 0xff)
                endPoints.push_back(cv::Point(j,i));
        }
    }
    return retVal;
}
