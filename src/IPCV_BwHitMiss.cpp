/////////////////////////////////////////////////////////////////////
//                                                                 //
//      Binary hitmiss operation                                   //
//                                                                 //
//                                                                 //
//      File Name: bwHitMiss.cpp                                   //
//      File Type: C++ source                                      //
//      Auther: Asanka Wickramasinghe                              //
//      Project: Image Processing CV               //
//      Module: Image Processing Library (ImageProcCV)            //
//      Date Created: 2012 - Mar                                   //
//                                                                 //
/////////////////////////////////////////////////////////////////////
#include "ImageProcCV.h"


void ImageProcCV::bwHitMiss( cv::Mat &_input, cv::Mat &_hit, cv::Mat &_miss,
                             cv::Mat &_output,  bool _middleElement)
{
    cv::Mat& input = _input;
    cv::Mat& output = _output;
    cv::Mat& hit = _hit;
    cv::Mat& miss = _miss;

    output = cv::Mat::zeros(input.size(),CV_8UC1);
    //1's count in hit
    int hit_count = cv::countNonZero(hit);
    //0's count in miss
    int miss_count = (miss.rows * miss.cols) - cv::countNonZero(miss);

    for(int i = 0; i < input.rows; i++)
    {
        uchar* input_data = input.ptr<uchar>(i);
        uchar* input_data_above = input.ptr<uchar>(i-1);
        uchar* input_data_below = input.ptr<uchar>(i+1);
        uchar* output_data = output.ptr<uchar>(i);
        for(int j = 0; j < input.cols; j++)
        {
            //get neighbourhood

            if(_middleElement)
            {
                if(input_data[j] == 0xff)
                {
                    uchar x02 = ((i == 0) || (j == (input.cols - 1)))? 0 : input_data_above[j+1];
                    uchar x00 = ((i == 0) || (j == 0))? 0 :input_data_above[j-1];
                    uchar x20 = ((i == (input.rows - 1)) || (j == 0))? 0 : input_data_below[j-1];
                    uchar x22 = ((i == (input.rows - 1)) || (j == (input.cols - 1)))? 0 : input_data_below[j+1];
                    uchar x12 = (j == (input.cols - 1))? 0 : input_data[j+1];
                    uchar x01 = (i == 0)? 0 : input_data_above[j];
                    uchar x10  = (j == 0)? 0 : input_data[j-1];
                    uchar x21 = (i == (input.rows - 1))? 0 : input_data_below[j];

                    cv::Mat temp = cv::Mat::zeros(3,3,CV_8UC1);
                    //fill temp mat
                    temp.at<uchar>(0,0) = x00;
                    temp.at<uchar>(0,1) = x01;
                    temp.at<uchar>(0,2) = x02;
                    temp.at<uchar>(1,0) = x10;
                    temp.at<uchar>(1,1) = input_data[j];
                    temp.at<uchar>(1,2) = x12;
                    temp.at<uchar>(2,0) = x20;
                    temp.at<uchar>(2,1) = x21;
                    temp.at<uchar>(2,2) = x22;

                    //AND operation with hit

                    cv::Mat result;
                    cv::bitwise_and(hit,temp,result);
                    //int hitss = cv::countNonZero(result);
                    if(hit_count == cv::countNonZero(result))
                    {
                        cv::bitwise_or(miss,temp,result);
                        cv::Mat not_result;
                        cv::bitwise_not(result,not_result);
                        if(miss_count == cv::countNonZero(not_result))
                        {
                            output_data[j] = 0xff;
                        }
                    }
                }
            }
            else
            {
                if(input_data[j] == 0x00)
                {
                    uchar x02 = ((i == 0) || (j == (input.cols - 1)))? 0 : input_data_above[j+1];
                    uchar x00 = ((i == 0) || (j == 0))? 0 :input_data_above[j-1];
                    uchar x20 = ((i == (input.rows - 1)) || (j == 0))? 0 : input_data_below[j-1];
                    uchar x22 = ((i == (input.rows - 1)) || (j == (input.cols - 1)))? 0 : input_data_below[j+1];
                    uchar x12 = (j == (input.cols - 1))? 0 : input_data[j+1];
                    uchar x01 = (i == 0)? 0 : input_data_above[j];
                    uchar x10  = (j == 0)? 0 : input_data[j-1];
                    uchar x21 = (i == (input.rows - 1))? 0 : input_data_below[j];

                    cv::Mat temp = cv::Mat::zeros(3,3,CV_8UC1);
                    //fill temp mat
                    temp.at<uchar>(0,0) = x00;
                    temp.at<uchar>(0,1) = x01;
                    temp.at<uchar>(0,2) = x02;
                    temp.at<uchar>(1,0) = x10;
                    temp.at<uchar>(1,1) = input_data[j];
                    temp.at<uchar>(1,2) = x12;
                    temp.at<uchar>(2,0) = x20;
                    temp.at<uchar>(2,1) = x21;
                    temp.at<uchar>(2,2) = x22;

                    //AND operation with hit

                    cv::Mat result;
                    cv::bitwise_and(hit,temp,result);
                    //int hitss = cv::countNonZero(result);
                    if(hit_count == cv::countNonZero(result))
                    {
                        cv::bitwise_or(miss,temp,result);
                        cv::Mat not_result;
                        cv::bitwise_not(result,not_result);
                        if(miss_count == cv::countNonZero(not_result))
                        {
                            output_data[j] = 0xff;
                        }
                    }
                }
            }
        }
    }
}
