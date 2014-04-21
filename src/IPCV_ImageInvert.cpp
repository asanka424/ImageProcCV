/////////////////////////////////////////////////////////////////////
//                                                                 //
//      File Name: imageInvert.cpp                                //
//      File Type: C++ source                                      //
//      Auther: Asanka Wickramasinghe                              //
//      Project: Image Processing CV               //
//      Module: Image Processing Library (ImageProcCV)            //
//      Date Created: 2012 - Mar                                   //
//                                                                 //
/////////////////////////////////////////////////////////////////////
#include "ImageProcCV.h"


void ImageProcCV::imageInvert(cv::Mat &_input, cv::Mat &_output)
{
    cv::Mat& input = _input, &output = _output;
    output = cv::Mat(input.size(),input.type());
    cv::Mat lut(1,256,CV_8U);
    uchar* p = lut.data;
    for( int i = 0; i < 256; ++i)
        p[i] = 255 - i;
    cv::LUT(input,lut,output);
}
