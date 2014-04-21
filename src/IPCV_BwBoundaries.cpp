/////////////////////////////////////////////////////////////////////
//                                                                 //
//      Extracts the boundary of given binary object.              //
//      Moore-Neighbor tracing algorithm is used with              //
//      Jacob's stopping criteria                                  //
//                                                                 //
//      File Name: bwBoundaries.cpp                                //
//      File Type: C++ source                                      //
//      Auther: Asanka Wickramasinghe                              //
//      Project: Image Processing CV               //
//      Module: Image Processing Library ( ImageProcCV )            //
//      Date Created: 2012 - March                                 //
//                                                                 //
/////////////////////////////////////////////////////////////////////
#include "ImageProcCV.h"


int ImageProcCV::bwBoundaries( cv::Mat &_input, cv::Mat &_output,
                                std::vector<cv::Point> &_boundary)
{
    int retVal;
    cv::Mat& input = _input;
    cv::Mat& output = _output;
    std::vector<cv::Point>& boundary = _boundary;
    output = cv::Mat::zeros(input.size(),CV_8UC1);
    boundary.clear();
    cv::Point first;
    //get the entry point
    bool entry_found = false;
    for(int i = 0; i < input.rows; i++)
    {

        uchar *data = input.ptr<uchar>(i);

        for(int j = 0; j< input.cols; j++)
        {
            if(data[j] == 0xff)
            {
                first = cv::Point(j,i);
                entry_found = true;
                break;
            }
        }
        if(entry_found)
            break;


    }
    if(entry_found == false)
    {
        retVal = BW_IMG_NO_FGRND_PIXELS;
        std::cout << "image has no white pixels" << std::endl;
    }
    else
    {
        output.at<uchar>(first) = 0xff;
        boundary.push_back(first);
        bool terminate = false;
        cv::Point start = first;
        int startpoint = 1;
        while(!terminate)
        {

            int xx = start.x;
            int yy = start.y;
            uchar x5 = (start.x == (input.cols - 1))? 0 : input.at<uchar>(start.y,start.x+1);
            uchar x3 = (start.y == 0)? 0 : input.at<uchar>(start.y-1,start.x);
            uchar x1 = (start.x == 0)? 0 : input.at<uchar>(start.y,start.x-1);
            uchar x7 = (start.y == (input.rows - 1))? 0 : input.at<uchar>(start.y+1,start.x);
            uchar x4 = ((start.y == 0) || (start.x == (input.cols - 1)))? 0 : input.at<uchar>(start.y-1,start.x+1);
            uchar x2 = ((start.y == 0) || (start.x == 0))? 0 : input.at<uchar>(start.y-1,start.x-1);
            uchar x8 = ((start.y == (input.rows - 1)) || (start.x == 0))? 0 : input.at<uchar>(start.y+1,start.x-1);
            uchar x6 = ((start.y == (input.rows - 1)) || (start.x == (input.cols - 1)))? 0 : input.at<uchar>(start.y+1,start.x+1);


            if(startpoint == 1)
            {
                if(x1 == 0xff)
                {
                    output.at<uchar>(yy,xx-1) = 0xff;
                    boundary.push_back(cv::Point(xx-1,yy));
                    start = cv::Point(xx-1,yy);
                    startpoint = 7;
                    continue;
                }
                else if(x2 == 0xff)
                {
                    output.at<uchar>(yy-1,xx-1) = 0xff;
                    boundary.push_back(cv::Point(xx-1,yy-1));
                    start = cv::Point(xx-1,yy-1);
                    startpoint = 7;

                    continue;
                }
                else if(x3 == 0xff)
                {

                    if(((yy-1) == first.y)&& ((xx) == first.x))
                    {
                        terminate = true;
                        continue;
                    }
                    output.at<uchar>(yy-1,xx) = 0xff;
                    boundary.push_back(cv::Point(xx,yy-1));
                    start = cv::Point(xx,yy-1);
                    startpoint = 1;
                    continue;

                }
                else if(x4 == 0xff)
                {

                    if(((yy-1) == first.y)&& ((xx+1) == first.x))
                    {
                        terminate = true;
                        continue;
                    }
                    output.at<uchar>(yy-1,xx+1) = 0xff;
                    boundary.push_back(cv::Point(xx+1,yy-1));
                    start = cv::Point(xx+1,yy-1);
                    startpoint = 1;
                    continue;

                }
                else if(x5 == 0xff)
                {
                    output.at<uchar>(yy,xx+1) = 0xff;
                    boundary.push_back(cv::Point(xx+1,yy));
                    start = cv::Point(xx+1,yy);
                    startpoint = 3;
                    continue;
                }
                else if(x6 == 0xff)
                {
                    output.at<uchar>(yy+1,xx+1) = 0xff;
                    boundary.push_back(cv::Point(xx+1,yy+1));
                    start = cv::Point(xx+1,yy+1);
                    startpoint = 3;
                    continue;
                }
                else if(x7 == 0xff)
                {
                    output.at<uchar>(yy+1,xx) = 0xff;
                    boundary.push_back(cv::Point(xx,yy+1));
                    start = cv::Point(xx,yy+1);
                    startpoint = 5;
                    continue;
                }
                else if(x8 == 0xff)
                {
                    output.at<uchar>(yy+1,xx-1) = 0xff;
                    boundary.push_back(cv::Point(xx-1,yy+1));
                    start = cv::Point(xx-1,yy+1);
                    startpoint =5;
                    continue;
                }
                else
                {
                    terminate = true;
                    continue;
                }
            }

            else if(startpoint == 3 )
            {

                if(x3 == 0xff)
                {

                    if(((yy-1) == first.y)&& ((xx) == first.x))
                    {
                        terminate = true;
                        continue;
                    }
                    output.at<uchar>(yy-1,xx) = 0xff;
                    boundary.push_back(cv::Point(xx,yy-1));
                    start = cv::Point(xx,yy-1);
                    startpoint = 1;
                    continue;
                }
                else if(x4 == 0xff)
                {

                    if(((yy-1) == first.y)&& ((xx+1) == first.x))
                    {
                        terminate = true;
                        continue;
                    }
                    output.at<uchar>(yy-1,xx+1) = 0xff;
                    boundary.push_back(cv::Point(xx+1,yy-1));
                    start = cv::Point(xx+1,yy-1);
                    startpoint = 1;
                    continue;

                }
                else if(x5 == 0xff)
                {
                    output.at<uchar>(yy,xx+1) = 0xff;
                    boundary.push_back(cv::Point(xx+1,yy));
                    start = cv::Point(xx+1,yy);
                    startpoint = 3;
                    continue;
                }
                else if(x6 == 0xff)
                {
                    output.at<uchar>(yy+1,xx+1) = 0xff;
                    boundary.push_back(cv::Point(xx+1,yy+1));
                    start = cv::Point(xx+1,yy+1);
                    startpoint = 3;
                    continue;
                }
                else if(x7 == 0xff)
                {
                    output.at<uchar>(yy+1,xx) = 0xff;
                    boundary.push_back(cv::Point(xx,yy+1));
                    start = cv::Point(xx,yy+1);
                    startpoint = 5;
                    continue;
                }
                else if(x8 == 0xff)
                {
                    output.at<uchar>(yy+1,xx-1) = 0xff;
                    boundary.push_back(cv::Point(xx-1,yy+1));
                    start = cv::Point(xx-1,yy+1);
                    startpoint =5;
                    continue;
                }
                else if(x1 == 0xff)
                {
                    output.at<uchar>(yy,xx-1) = 0xff;
                    boundary.push_back(cv::Point(xx-1,yy));
                    start = cv::Point(xx-1,yy);
                    startpoint = 7;
                    continue;
                }
                else if(x2 == 0xff)
                {
                    output.at<uchar>(yy-1,xx-1) = 0xff;
                    boundary.push_back(cv::Point(xx-1,yy-1));
                    start = cv::Point(xx-1,yy-1);
                    startpoint = 7;

                    continue;
                }
                else
                {
                    terminate = true;
                    continue;
                }
            }

            else if(startpoint == 5 )
            {

                if(x5 == 0xff)
                {
                    output.at<uchar>(yy,xx+1) = 0xff;
                    boundary.push_back(cv::Point(xx+1,yy));
                    start = cv::Point(xx+1,yy);
                    startpoint = 3;
                    continue;
                }
                else if(x6 == 0xff)
                {
                    output.at<uchar>(yy+1,xx+1) = 0xff;
                    boundary.push_back(cv::Point(xx+1,yy+1));
                    start = cv::Point(xx+1,yy+1);
                    startpoint = 3;
                    continue;
                }
                else if(x7 == 0xff)
                {
                    output.at<uchar>(yy+1,xx) = 0xff;
                    boundary.push_back(cv::Point(xx,yy+1));
                    start = cv::Point(xx,yy+1);
                    startpoint = 5;
                    continue;
                }
                else if(x8 == 0xff)
                {
                    output.at<uchar>(yy+1,xx-1) = 0xff;
                    boundary.push_back(cv::Point(xx-1,yy+1));
                    start = cv::Point(xx-1,yy+1);
                    startpoint =5;
                    continue;
                }
                else if(x1 == 0xff)
                {
                    output.at<uchar>(yy,xx-1) = 0xff;
                    boundary.push_back(cv::Point(xx-1,yy));
                    start = cv::Point(xx-1,yy);
                    startpoint = 7;
                    continue;
                }
                else if(x2 == 0xff)
                {
                    output.at<uchar>(yy-1,xx-1) = 0xff;
                    boundary.push_back(cv::Point(xx-1,yy-1));
                    start = cv::Point(xx-1,yy-1);
                    startpoint = 7;

                    continue;
                }
                else if(x3 == 0xff)
                {

                    if(((yy-1) == first.y)&& ((xx) == first.x))
                    {
                        terminate = true;
                        continue;
                    }
                    output.at<uchar>(yy-1,xx) = 0xff;
                    boundary.push_back(cv::Point(xx,yy-1));
                    start = cv::Point(xx,yy-1);
                    startpoint = 1;
                    continue;

                }
                else if(x4 == 0xff)
                {

                    if(((yy-1) == first.y)&& ((xx+1) == first.x))
                    {
                        terminate = true;
                        continue;
                    }
                    output.at<uchar>(yy-1,xx+1) = 0xff;
                    boundary.push_back(cv::Point(xx+1,yy-1));
                    start = cv::Point(xx+1,yy-1);
                    startpoint = 1;
                    continue;

                }
                else
                {
                    terminate = true;
                    continue;
                }
            }

            else if(startpoint == 7 )
            {

                if(x7 == 0xff)
                {
                    output.at<uchar>(yy+1,xx) = 0xff;
                    boundary.push_back(cv::Point(xx,yy+1));
                    start = cv::Point(xx,yy+1);
                    startpoint = 5;
                    continue;
                }
                else if(x8 == 0xff)
                {
                    output.at<uchar>(yy+1,xx-1) = 0xff;
                    boundary.push_back(cv::Point(xx-1,yy+1));
                    start = cv::Point(xx-1,yy+1);
                    startpoint =5;
                    continue;
                }
                else if(x1 == 0xff)
                {
                    output.at<uchar>(yy,xx-1) = 0xff;
                    boundary.push_back(cv::Point(xx-1,yy));
                    start = cv::Point(xx-1,yy);
                    startpoint = 7;
                    continue;
                }
                else if(x2 == 0xff)
                {
                    if(((yy-1) == first.y)&& ((xx-1) == first.x))
                    {
                        terminate = true;
                        continue;
                    }

                    output.at<uchar>(yy-1,xx-1) = 0xff;
                    boundary.push_back(cv::Point(xx-1,yy-1));
                    start = cv::Point(xx-1,yy-1);
                    startpoint = 7;

                    continue;

                }
                else if(x3 == 0xff)
                {

                    if(((yy-1) == first.y)&& ((xx) == first.x))
                    {
                        terminate = true;
                        continue;
                    }
                    output.at<uchar>(yy-1,xx) = 0xff;
                    boundary.push_back(cv::Point(xx,yy-1));
                    start = cv::Point(xx,yy-1);
                    startpoint = 1;
                    continue;

                }
                else if(x4 == 0xff)
                {

                    if(((yy-1) == first.y)&& ((xx+1) == first.x))
                    {
                        terminate = true;
                        continue;
                    }
                    output.at<uchar>(yy-1,xx+1) = 0xff;
                    boundary.push_back(cv::Point(xx+1,yy-1));
                    start = cv::Point(xx+1,yy-1);
                    startpoint = 1;
                    continue;

                }
                else if(x5 == 0xff)
                {
                    output.at<uchar>(yy,xx+1) = 0xff;
                    boundary.push_back(cv::Point(xx+1,yy));
                    start = cv::Point(xx+1,yy);
                    startpoint = 3;
                    continue;
                }
                else if(x6 == 0xff)
                {
                    output.at<uchar>(yy+1,xx+1) = 0xff;
                    boundary.push_back(cv::Point(xx+1,yy+1));
                    start = cv::Point(xx+1,yy+1);
                    startpoint = 3;
                    continue;
                }
                else
                {
                    terminate = true;
                    continue;
                }
            }

        }
        retVal = NO_ERRORS;
    }
    return retVal;
}
