/////////////////////////////////////////////////////////////////////
//                                                                 //
//      Normalize image by the given method. Methods are Global    //
//      normalization and standard normalization                   //
//                                                                 //
//      File Name: imageNormalize.cpp                              //
//      File Type: C++ source                                      //
//      Auther: Asanka Wickramasinghe                              //
//      Project: Image Processing CV               //
//      Module: Image Processing Library (ImageProcCV)            //
//      Date Created: 2012 - Mar                                   //
//                                                                 //
/////////////////////////////////////////////////////////////////////
#include "ImageProcCV.h"


int ImageProcCV::imageNormalize(cv::Mat &_input, cv::Mat &_output, int method)
{
    //this function only accepts CV_8U data type
    int retVal = NO_ERRORS;
    cv::Mat& input = _input;
    cv::Mat& output = _output;

    //check input
    if (!input.data)
    {
        retVal = EMPTY_IMAGE_MTRX;
        return retVal;
    }
    else if (input.type() != CV_8UC1)
    {
        retVal = INV_IMG_TYPE;
        return retVal;
    }

    output = cv::Mat::zeros(input.size(),CV_64F);

    int rows = input.rows;
    int cols = input.cols;
    if(input.isContinuous() && output.isContinuous())
    {
        cols *= rows;
        rows = 1;
    }
    switch (method)
    {
    case NORM_GLOBAL:

        for(int i = 0; i < rows; i++)
        {
            uchar *_input = input.ptr<uchar>(i);
            double *_output = output.ptr<double>(i);
            for(int j = 0; j < cols; j++)
            {

                //double val = (double)_input[j]/255.0f;
                _output[j] = (double)_input[j]/255.0f;
            }
        }

        break;

    case NORM_STD:
        int max = 0, min = 255;
        //finding maximu and minimum elements in the matrix

        max = *std::max_element(input.begin<uchar>(), input.end<uchar>());
        min = *std::min_element(input.begin<uchar>(), input.end<uchar>());
        /*for(cv::MatIterator_<uchar> it = input.begin<uchar>(); it != input.end<uchar>(); it++)
        {
            if(*it >= max)
            {
                max = *it;
            }
            if(*it <= min)
            {
                min = *it;
            }
        }*/
        if(min == max)
        {
            retVal = EQUAL_INTENSITY_PIXELS;
        }
        else
        {
            retVal = NO_ERRORS;
        }
        cv::Mat lut(1, 256, CV_8U);
        uchar* p = lut.data;
        for( int i = 0; i < 256; ++i)
            p[i] = (i - min) /(double)((min == max)? 1:(max -min));
        cv::LUT(input,lut,output);
        break;

    }
    return retVal;
}
