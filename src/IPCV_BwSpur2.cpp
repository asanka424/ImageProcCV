#include <ImageProcCV.h>


int ImageProcCV::bwSpur2(cv::Mat &input, cv::Mat &output, int itr)
{
    int retVal = NO_ERRORS;
    if (input.type() != CV_8UC1)
    {
        retVal = INV_IMG_TYPE;
        return retVal;
    }

    output = input.clone();
    bool changed = true;
    int runs = 0;
    while (changed)
    {
        runs++;
        cv::Mat previous = output.clone();
        spurOnce(output);
        changed = !std::equal(previous.begin<uchar>(),previous.end<uchar>(),output.begin<uchar>());
        if (runs == itr)
            changed = false;
    }

    return retVal;
}

void ImageProcCV::spurOnce(cv::Mat &output)
{
    //image inversion
    output = 255 - output;

    cv::Mat endPoints = cv::Mat::zeros(output.size(),output.type());
    cv::Mat lut;
    bool changed;
    getLutSpur(lut);

    applyLUT(output,lut,true,endPoints,changed);

    //remove endpoints in first field
    for (int row = 0; row < output.rows; row += 2)
    {
        uchar* pimage = output.ptr<uchar>(row);
        uchar* pendpoints = endPoints.ptr<uchar>(row);

        for (int col = 0; col < output.cols; col += 2)
        {
            pimage[col] = pimage[col]^pendpoints[col];
        }
    }

    //second field

    cv::Mat newEndPoints = cv::Mat::zeros(output.size(),output.type());
    applyLUT(output,lut,true,newEndPoints,changed);
    cv::bitwise_and(endPoints,newEndPoints,newEndPoints);

    for (int row = 0; row < output.rows; row += 2)
    {
        uchar* pimage = output.ptr<uchar>(row);
        uchar* pendpoints = newEndPoints.ptr<uchar>(row);

        for (int col = 1; col < output.cols; col += 2)
        {
            pimage[col] = pimage[col]^pendpoints[col];
        }
    }

    //third field
    newEndPoints = cv::Mat::zeros(output.size(),output.type());
    applyLUT(output,lut,true,newEndPoints,changed);
    cv::bitwise_and(endPoints,newEndPoints,newEndPoints);

    for (int row = 1; row < output.rows; row += 2)
    {
        uchar* pimage = output.ptr<uchar>(row);
        uchar* pendpoints = newEndPoints.ptr<uchar>(row);

        for (int col = 0; col < output.cols; col += 2)
        {
            pimage[col] = pimage[col]^pendpoints[col];
        }
    }

    //forth field

    newEndPoints = cv::Mat::zeros(output.size(),output.type());
    applyLUT(output,lut,true,newEndPoints,changed);
    cv::bitwise_and(endPoints,newEndPoints,newEndPoints);

    for (int row = 1; row < output.rows; row += 2)
    {
        uchar* pimage = output.ptr<uchar>(row);
        uchar* pendpoints = newEndPoints.ptr<uchar>(row);

        for (int col = 1; col < output.cols; col += 2)
        {
            pimage[col] = pimage[col]^pendpoints[col];
        }
    }


    output = 255 - output;
}
