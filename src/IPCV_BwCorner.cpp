/////////////////////////////////////////////////////////////////////
//                                                                 //
//      Removes corner pixels from binary image.                   //
//      Uses hit-miss algorithm                                    //
//                                                                 //
//      File Name: bwCorner.cpp                                    //
//      File Type: C++ source                                      //
//      Auther: Asanka Wickramasinghe                              //
//      Project: Image Processing CV               //
//      Module: Image Processing Library (ImageProcCV)            //
//      Date Created: 2012 - Mar                                   //
//                                                                 //
/////////////////////////////////////////////////////////////////////
#include "ImageProcCV.h"


int ImageProcCV::bwCorner(cv::Mat& _image)
{
    int retVal;
    cv::Mat& image = _image;
    if (!image.data)
    {
        retVal = EMPTY_IMAGE_MTRX;
    }
    else
    {
        cv::Mat hit = cv::Mat::zeros(3,3,CV_8UC1);
        cv::Mat miss = cv::Mat::zeros(3,3,CV_8UC1);
        hit.at<uchar>(1,1) = 0xff;
        hit.at<uchar>(1,2) = 0xff;
        hit.at<uchar>(2,1) = 0xff;

        miss.at<uchar>(0,1) = 0xff;
        miss.at<uchar>(0,2) = 0xff;
        miss.at<uchar>(1,0) = 0xff;
        miss.at<uchar>(1,1) = 0xff;
        miss.at<uchar>(1,2) = 0xff;
        miss.at<uchar>(2,0) = 0xff;
        miss.at<uchar>(2,1) = 0xff;
        //miss.at<uchar>(2,2) = 0xff;
        cv::Mat output;
        bwHitMiss(image,hit,miss,output);
        image= image - output;
        ////////////////////////////////////////////////////////////////////////////
        hit = cv::Mat::zeros(3,3,CV_8UC1);
        miss = cv::Mat::zeros(3,3,CV_8UC1);
        hit.at<uchar>(0,1) = 0xff;
        hit.at<uchar>(1,0) = 0xff;
        hit.at<uchar>(1,1) = 0xff;

        miss.at<uchar>(0,1) = 0xff;
        miss.at<uchar>(0,2) = 0xff;
        miss.at<uchar>(1,0) = 0xff;
        miss.at<uchar>(1,1) = 0xff;
        miss.at<uchar>(1,2) = 0xff;
        miss.at<uchar>(2,0) = 0xff;
        miss.at<uchar>(2,1) = 0xff;
        //miss.at<uchar>(0,0) = 0xff;



        bwHitMiss(image,hit,miss,output);
        image= image - output;


        //////////////////////////////////////////////////////////
        hit = cv::Mat::zeros(3,3,CV_8UC1);
        miss = cv::Mat::zeros(3,3,CV_8UC1);
        hit.at<uchar>(1,0) = 0xff;
        hit.at<uchar>(1,1) = 0xff;
        hit.at<uchar>(2,1) = 0xff;

        miss.at<uchar>(0,1) = 0xff;
        miss.at<uchar>(0,2) = 0xff;
        miss.at<uchar>(1,0) = 0xff;
        miss.at<uchar>(1,1) = 0xff;
        //miss.at<uchar>(2,0) = 0xff;
        miss.at<uchar>(2,2) = 0xff;
        miss.at<uchar>(2,1) = 0xff;
        miss.at<uchar>(0,0) = 0xff;



        bwHitMiss(image,hit,miss,output);
        image= image - output;

        //////////////////////////////////////////////////////////
        hit = cv::Mat::zeros(3,3,CV_8UC1);
        miss = cv::Mat::zeros(3,3,CV_8UC1);
        hit.at<uchar>(0,1) = 0xff;
        hit.at<uchar>(1,1) = 0xff;
        hit.at<uchar>(1,2) = 0xff;

        miss.at<uchar>(0,1) = 0xff;
        miss.at<uchar>(0,2) = 0xff;
        miss.at<uchar>(1,0) = 0xff;
        miss.at<uchar>(1,1) = 0xff;
        miss.at<uchar>(1,2) = 0xff;
        miss.at<uchar>(2,2) = 0xff;
        miss.at<uchar>(2,1) = 0xff;
        miss.at<uchar>(0,0) = 0xff;


        bwHitMiss(image,hit,miss,output);
        image = image - output;
        retVal = NO_ERRORS;
    }
    return retVal;
}
