/////////////////////////////////////////////////////////////////////
//                                                                 //
//      Adjusts contrast of a gray scale image by normalizing      //
//      image's histogram.                                         //
//                                                                 //
//      File Name: imageAdjust.cpp                                 //
//      File Type: C++ source                                      //
//      Auther: Asanka Wickramasinghe                              //
//      Project: Image Processing CV               //
//      Module: Image Processing Library (ImageProcCV)            //
//      Date Created: 2012 - Mar                                   //
//                                                                 //
/////////////////////////////////////////////////////////////////////
#include "ImageProcCV.h"

int ImageProcCV::imageAdjust( cv::Mat &_input, cv::Mat &_output)
{
    int retVal;
    cv::Mat& input = _input, &output = _output;
    if(!input.data)
    {
        retVal = EMPTY_IMAGE_MTRX;
        return retVal;
    }
    if(input.type() != CV_8UC1)
    {
        retVal = INV_IMG_TYPE;
        return retVal;
    }
    output = cv::Mat(input.size(),input.type());
    cv::Size size = cv::Size(input.cols,input.rows);


    double numPix = size.height*size.width;


    //if image is continuous we can release some calculations on behalf of cpu.
    if(input.isContinuous())
    {
        size.width *= size.height;
        size.height = 1;
    }

    //calculation of histogram

    int x, y;
    const int hist_sz = 256;
    int hist[hist_sz];
    memset(hist, 0, sizeof(hist));

    for( y = 0; y < size.height; y++ )
    {
        const uchar* sptr = input.ptr<uchar>(y);
        for( x = 0; x < size.width; x++ )
            hist[sptr[x]]++;
    }

    //calculation of brightness_contrast



    //calculation of one percent of high and low pixel values
   // float fraction = numPix*0.01;
    int count = cvRound(numPix*0.01);
    int highValue = -1,lowValue = -1;

    int sum = 0;

    for( int i = 0; i < hist_sz; i++ )
    {
        sum += hist[i];
        if(sum >= count)
        {
            lowValue = i;
            break;
        }
    }
    sum = 0;
    for( int i = 255; i >= 0; i-- )
    {
        sum += hist[i];
        if(sum >= count)
        {
            highValue = i;
            break;
        }
    }
    //find lowest and highest bit values. later we prepare a lookup table for values between highest and lowest

    int dynamicRange = highValue - lowValue;
    if (dynamicRange == 0)
    {
        retVal = EQUAL_INTENSITY_PIXELS;
    }
    else
    {
        //prepare a lookup table
        cv::Mat lookuptable(1,256,CV_8U);
        uchar* ptr = lookuptable.data;
        for(int i=0; i<=255; i++)
        {
            if(i<lowValue)
            {
                ptr[i]=0;
            }
            else if (i>highValue)
            {
                ptr[i]=255;
            }
            else
            {
                //int val = i;
                double pix_val = (double)(((i-lowValue)*255)/(double)((dynamicRange == 0)? 1:dynamicRange));

                int cv_round = std::floor(pix_val + 0.5);
               // int cv_round = cvRound(pix_val);
                ptr[i]= CV_CAST_8U(cv_round);

            }

        }
        cv::LUT(input,lookuptable,output);
        retVal = NO_ERRORS;
        return retVal;
    }
    //std::cout <<lookuptable << std::endl;
    //map values in src to dst such that pixel values between lowValue and highValue
    //will use full range of 255
   // int roundval = cvRound(23.5);
    return retVal;

}

