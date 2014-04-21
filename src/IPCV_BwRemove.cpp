/////////////////////////////////////////////////////////////////////
//                                                                 //
//      This function removes all interior pixels from a binary    //
//      image leaving only boundary pixels                         //
//                                                                 //
//      File Name: bwRemove.cpp                                    //
//      File Type: C++ source                                      //
//      Auther: Asanka Wickramasinghe                              //
//      Project: Image Processing CV               //
//      Module: Image Processing Library (ImageProcCV)            //
//      Date Created: 2012 - Mar                                   //
//                                                                 //
/////////////////////////////////////////////////////////////////////

#include "ImageProcCV.h"


int ImageProcCV::bwRemove(cv::Mat &_input)
{
    int retVal = NO_ERRORS;
    cv::Mat& input = _input;
    std::vector<cv::Point> points_delete;
    bool foreground_found = false;
    for(int i = 0; i < input.rows; i++)
    {
        uchar *data = input.ptr<uchar>(i);
        uchar *data_above = input.ptr<uchar>(i-1);
        uchar *data_below = input.ptr<uchar>(i+1);
        for(int j = 0; j < input.cols; j++)
        {
            if (data[j] != 0)
            {
                foreground_found = true;
                uchar east = (j == (input.cols - 1))? 0 : data[j+1];
                uchar north = (i == 0)? 0 : data_above[j];
                uchar west  = (j == 0)? 0 : data[j-1];
                uchar south = (i == (input.rows - 1))? 0 : data_below[j];

                if((east & north & west & south) == 0xff)
                {
                    points_delete.push_back(cv::Point(j,i));
                }
            }
        }
    }
    if(!foreground_found)
    {
        retVal = BW_IMG_NO_FGRND_PIXELS;
    }
    if(points_delete.size() == 0)
    {
        retVal = BW_IMG_NO_INTROR_PIXELS;
    }
    for(size_t i = 0; i < points_delete.size(); i++)
    {
        input.at<uchar>(points_delete[i]) = 0x00;
    }
    return retVal;
}
