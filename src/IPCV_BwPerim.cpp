/////////////////////////////////////////////////////////////////////
//                                                                 //
//      Finds  and returns  the  perimeter  pixels of              //
//      given  boundary  objects. Perimeter  pixel is              //
//      defined  as a  pixel  which  has  atleast one              //
//      background (black) pixel in its neighborhood.              //
//      Neighborhood is taken from given connectivity              //
//      criterion.                                                 //
//                                                                 //
//      File Name: bwPerim.cpp                                     //
//      File Type: C++ source                                      //
//      Auther: Asanka Wickramasinghe                              //
//      Project: Image Processing CV               //
//      Module: Image Processing Library (ImageProcCV)            //
//      Date Created: 2012 - Mar                                   //
//                                                                 //
/////////////////////////////////////////////////////////////////////
#include "ImageProcCV.h"


int ImageProcCV::bwPerim(cv::Mat &_input, cv::Mat &_output, int conn)
{
    cv::Mat& input = _input, &output = _output;
    output = cv::Mat::zeros(input.size(),input.type());

    for(int i = 0; i < input.rows; i++)
    {
        uchar *data = input.ptr<uchar>(i);
        uchar *data_above = input.ptr<uchar>(i-1);
        uchar *data_below = input.ptr<uchar>(i+1);
        uchar *data_out = output.ptr<uchar>(i);
        for(int j = 0; j < input.cols; j++)
        {
            if (data[j] != 0)
            {
                uchar northeast = ((i == 0) || (j == (input.cols - 1)))? 0 : data_above[j+1];
                uchar northwest = ((i == 0) || (j == 0))? 0 :data_above[j-1];
                uchar southwest = ((i == (input.rows - 1)) || (j == 0))? 0 : data_below[j-1];
                uchar southeast = ((i == (input.rows - 1)) || (j == (input.cols - 1)))? 0 : data_below[j+1];
                uchar east = (j == (input.cols - 1))? 0 : data[j+1];
                uchar north = (i == 0)? 0 : data_above[j];
                uchar west  = (j == 0)? 0 : data[j-1];
                uchar south = (i == (input.rows - 1))? 0 : data_below[j];

                if(conn == 4 )
                {
                   // uchar test = east & north & west & south;

                    if(( east & north & west & south) == 0x00 )
                    {
                        data_out[j] = 0xff;
                    }
                }
                if(conn == 8)
                {
                    if((northeast & northwest & southeast & southwest & east & north & west & south) == 0x00 )
                    {
                        data_out[j] = 0xff;
                    }
                }
            }
        }
    }
    return NO_ERRORS;
}
