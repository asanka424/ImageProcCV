/////////////////////////////////////////////////////////////////////
//                                                                 //
//      Removes  spur  pixels  from  binary  image.                //
//      Connectivity  critirion  determinines which                //
//      pixels should be considered before removing                //
//      a pixel.                                                   //
//                                                                 //
//      File Name: bwSpur.cpp                                      //
//      File Type: C++ source                                      //
//      Auther: Asanka Wickramasinghe                              //
//      Project: Image Processing CV               //
//      Module: Image Processing Library (ImageProcCV)            //
//      Date Created: 2012 - Mar                                   //
//                                                                 //
/////////////////////////////////////////////////////////////////////
#include "ImageProcCV.h"


int ImageProcCV::bwSpur(cv::Mat &_input,int op, int itr)
{
    cv::Mat& input = _input;
    bool changed = true;
    int iterations = 0;
    while(changed)
    {
        //iterating through image to remove spurs
        changed = false;
        std::vector<cv::Point> points;
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
                    std::vector<uchar> holder;
                    if(op == 1)
                    {
                        holder.push_back(northeast);
                        holder.push_back(northwest);
                        holder.push_back(southeast);
                        holder.push_back(southwest);
                        holder.push_back(east);
                        holder.push_back(north);
                        holder.push_back(west);
                        holder.push_back(south);
                    }
                    else if(op == 2)
                    {
                        holder.push_back(east);
                        holder.push_back(north);
                        holder.push_back(west);
                        holder.push_back(south);
                    }
                    else if(op == 3)
                    {
                        holder.push_back(northeast);
                        holder.push_back(northwest);
                        holder.push_back(southeast);
                        holder.push_back(southwest);
                    }
                    int count = 0;
                    for(size_t a = 0; a < holder.size(); a++)
                    {
                        if(holder[a] == 0xff)
                            count++;
                    }

                    //delet the pixel if it has only 1 neighbour
                    if(count == 1)
                    {
                        points.push_back(cv::Point(j,i));
                        changed = true;

                    }
                }
            }
        }
        for(size_t i = 0; i<points.size();i++)
            input.at<uchar>(points[i]) = 0x00;
        //if itr in function input is 0 perform the operation until input does not change
        // if itr has a value check we have done that number of iterations and terminate
        iterations++;
        if(itr != 0)
        {
            if(iterations >= itr)
                changed = false;
        }
        /*cv::namedWindow("inter");
        cv::imshow("inter",input);
        cv::waitKey(0);
        cv::destroyWindow("inter");*/
    }


    return iterations;
}
