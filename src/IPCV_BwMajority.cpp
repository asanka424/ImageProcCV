/////////////////////////////////////////////////////////////////////
//                                                                 //
//      File Name: bwMajority.cpp                                  //
//      File Type: C++ source                                      //
//      Auther: Asanka Wickramasinghe                              //
//      Project: Image Processing CV               //
//      Module: Image Processing Library (ImageProcCV)            //
//      Date Created: 2012 - Mar                                   //
//                                                                 //
/////////////////////////////////////////////////////////////////////
#include "ImageProcCV.h"

int ImageProcCV::bwMajority( cv::Mat &_input,cv::Mat &_output)
{
    cv::Mat& input = _input;
    cv::Mat& output = _output;
    output = input.clone();

    for(int i = 0; i < input.rows; i++)
    {
        uchar *data = input.ptr<uchar>(i);
        uchar *out = output.ptr<uchar>(i);
        uchar *data_above = input.ptr<uchar>(i-1);

        uchar *data_below = input.ptr<uchar>(i+1);
        for(int j = 0; j < input.cols; j++)
        {
            uchar northeast = ((i == 0) || (j == (input.cols - 1)))? 0 : data_above[j+1];
            uchar northwest = ((i == 0) || (j == 0))? 0 :data_above[j-1];
            uchar southwest = ((i == (input.rows - 1)) || (j == 0))? 0 : data_below[j-1];
            uchar southeast = ((i == (input.rows - 1)) || (j == (input.cols - 1)))? 0 : data_below[j+1];
            uchar east = (j == (input.cols - 1))? 0 : data[j+1];
            uchar north = (i == 0)? 0 : data_above[j];
            uchar west  = (j == 0)? 0 : data[j-1];
            uchar south = (i == (input.rows - 1))? 0 : data_below[j];
            uchar holder[8] = {northeast,northwest,southwest,southeast,north,west,south,east};

            int count = 0;
            for(int a = 0; a <8; a++)
            {
                if(holder[a] == 0xff)
                    count++;
            }
            if(count >= 5 )
            {
                if(data[j] != 0xff)
                {
                    out[j] = 0xff;
                }
            }
            else
            {
                if(data[j] != 0x00)
                {
                    out[j] = 0x00;
                }
            }
        }
    }
    return NO_ERRORS;
}
