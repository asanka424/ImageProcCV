/////////////////////////////////////////////////////////////////////
//                                                                 //
//      Removes single pixels binary image                         //
//      which do not have any neighbors                            //
//                                                                 //
//      File Name: bwClean.cpp                                     //
//      File Type: C++ source                                      //
//      Auther: Asanka Wickramasinghe                              //
//      Project: Image Processing CV               //
//      Module: Image Processing Library (ImageProcCV)            //
//      Date Created: 2012 - Mar                                   //
//                                                                 //
/////////////////////////////////////////////////////////////////////
#include "ImageProcCV.h"


int ImageProcCV::bwClean(cv::Mat &_input)
{
    int retVal;
    cv::Mat& input = _input;
    if(!input.data)
    {
        retVal = EMPTY_IMAGE_MTRX;
    }
    else
    {
        //iterating through image to remove spurs
        for(int i = 0; i < input.rows; i++)
        {
            uchar *data = input.ptr<uchar>(i);
            uchar *data_above = input.ptr<uchar>(i-1);
            uchar *data_below = input.ptr<uchar>(i+1);
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


                    if((northeast | northwest | southeast | southwest | east | north | west | south) == 0x00 )
                    {
                        data[j] = 0x00;
                    }
                }
            }
        }
        retVal = NO_ERRORS;
    }
    return retVal;
}
