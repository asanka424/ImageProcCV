/////////////////////////////////////////////////////////////////////
//                                                                 //
//      Finds pixels which have only one neighbor                  //
//                                                                 //
//      File Name: skelEndPoints.cpp                               //
//      File Type: C++ source                                      //
//      Auther: Asanka Wickramasinghe                              //
//      Project: Image Processing CV               //
//      Module: Image Processing Library (ImageProcCV)            //
//      Date Created: 2012 - Mar                                   //
//                                                                 //
/////////////////////////////////////////////////////////////////////
#include "ImageProcCV.h"


int ImageProcCV::skelEndPoints(cv::Mat &_input, std::vector<cv::Point>& _endPoints)
{
    cv::Mat& input = _input;
    std::vector<cv::Point>& endPoints = _endPoints;
    int numOfBranches = 0;
    for(int i = 0; i < input.rows; i++)
    {
        uchar *data = input.ptr<uchar>(i);
        uchar *data_above = input.ptr<uchar>(i-1);
        uchar *data_below = input.ptr<uchar>(i+1);
        for(int j = 0; j < input.cols; j++)
        {
            //uchar test = data[j];
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
                uchar holder[8] = {northeast,northwest,southwest,southeast,north,west,south,east};

                int count = 0;
                for(int a = 0; a <8; a++)
                {
                    if(holder[a] == 0xff)
                        count++;
                }

                //delet the pixel if it has only 1 neighbour
                if(count == 1)
                {
                    endPoints.push_back(cv::Point(j,i));
                    numOfBranches++;
                }
            }
        }
    }
    return numOfBranches;

}
