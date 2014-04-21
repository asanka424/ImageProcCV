/////////////////////////////////////////////////////////////////////
//                                                                 //
//      Provides the thinned output of a black and white blob      //
//                                                                 //
//      File Name: bwThin.cpp                                      //
//      File Type: C++ source                                      //
//      Auther: Asanka Wickramasinghe                              //
//      Project: Image Processing CV               //
//      Module: Image Processing Library (ImageProcCV)            //
//      Date Created: 2012 - Mar                                   //
//                                                                 //
/////////////////////////////////////////////////////////////////////
#include "ImageProcCV.h"


int ImageProcCV::bwThin(cv::Mat& _input, cv::Mat& _output, int itr)
{
    int retVal;
    cv::Mat &input = _input;
    cv::Mat &output = _output;
    output = input.clone();

    //scanning through the image
    uchar x1=0x00;
    uchar x2=0x00;
    uchar x3=0x00;
    uchar x4=0x00;
    uchar x5=0x00;
    uchar x6=0x00;
    uchar x7=0x00;
    uchar x8=0x00;

    bool changes_made = true;
    int runs = 0;


    // prepare two subfields in checkerboard pattern

    while(changes_made )
    {
        runs++;
        changes_made = false;
        std::vector<cv::Point> points_delete;
        for(int i = 0; i < output.rows; i++)
        {

            //get the address of raq i
            uchar *drow = output.ptr<uchar>(i);
            //if (i != 0)
                uchar *drow_above = output.ptr<uchar>(i-1);
           // if(i != (input.rows -1) )
                uchar *drow_below = output.ptr<uchar>(i+1);
            for(int j = 0; j< output.cols; j++)
            {
                if (drow[j] != 0x00)
                {
                    x1 = (j == (output.cols - 1))? 0 : drow[j+1];
                    x3 = (i == 0)? 0 : drow_above[j];
                    x5 = (j == 0)? 0 : drow[j-1];
                    x7 = (i == (output.rows - 1))? 0 : drow_below[j];
                    x2 = ((i == 0) || (j == (output.cols - 1)))? 0 : drow_above[j+1];
                    x4 = ((i == 0) || (j == 0))? 0 :drow_above[j-1];
                    x6 = ((i == (output.rows - 1)) || (j == 0))? 0 : drow_below[j-1];
                    x8 = ((i == (output.rows - 1)) || (j == (output.cols - 1)))? 0 : drow_below[j+1];


                    //check for G1
                    int b1= 0 ,b2 = 0 ,b3 = 0 ,b4 = 0;
                    int sum = 0;
                    bool satisfy = false;
                    if((x1 == 0x00)&((x2==0xff) | (x3 == 0xff)))
                        b1 = 1;
                    if((x3 == 0x00)&((x4==0xff) | (x5 == 0xff)))
                        b2 = 1;
                    if((x5 == 0x00)&((x6==0xff) | (x7 == 0xff)))
                        b3 = 1;
                    if((x7 == 0x00)&((x8==0xff) | (x1 == 0xff)))
                        b4 = 1;
                    sum = b1 + b2 + b3 + b4;
                    //uchar notx = (x6 | x7 | ~x4);
                    if (sum == 1)// G1 satisfied go to check G2
                    {
                        int p1=0, p2=0, p3=0, p4=0 , q1=0, q2=0, q3=0, q4=0;
                        int sum1 = 0, sum2 = 0;
                        if((x1 | x2 )== 0xff)
                            p1 = 1;
                        if((x3 | x4 )== 0xff)
                            p2 = 1;
                        if((x5 | x6 )== 0xff)
                            p3 = 1;
                        if((x7 | x8 )== 0xff)
                            p4 = 1;
                        sum1 = p1 + p2 + p3+ p4;

                        if((x2 | x3 )== 0xff)
                            q1 = 1;
                        if((x4 | x5 )== 0xff)
                            q2 = 1;
                        if((x6 | x7 )== 0xff)
                            q3 = 1;
                        if((x8 | x1 )== 0xff)
                            q4 = 1;
                        sum2 = q1 + q2 + q3+ q4;
                        if( (std::min(sum1,sum2)>= 2) & (std::min(sum1,sum2)<=3))//g2 is also satisfied
                        {
                            if(((x2 | x3 | ~x8) & x1) == 0x00)
                                satisfy = true;
                            if(satisfy)
                            {
                                changes_made=true;
                                if( runs == itr)
                                    changes_made = false;

                                points_delete.push_back(cv::Point(j,i));
                            }
                        }
                        else //G2 not satisfied goto next pixel
                        {
                            continue;
                        }
                    }
                    else // G1 not satisfied go to the next pixel
                    {
                        continue;
                    }
                }
            }

        }

        for(int m =0; m<(int)points_delete.size(); m++)
            output.at<uchar>(points_delete[m].y,points_delete[m].x) = 0x00;
        //clear vector.
        points_delete.clear();
        // second iteration
        for(int i = 0; i < output.rows; i++)
        {

            //get the address of raq i
            uchar *drow = output.ptr<uchar>(i);
            //if (i != 0)
                uchar *drow_above = output.ptr<uchar>(i-1);
           // if(i != (input.rows -1) )
                uchar *drow_below = output.ptr<uchar>(i+1);
            for(int j = 0; j< output.cols; j++)
            {
                if (drow[j] != 0x00)
                {

                    x1 = (j == (output.cols - 1))? 0 : drow[j+1];
                    x3 = (i == 0)? 0 : drow_above[j];
                    x5 = (j == 0)? 0 : drow[j-1];
                    x7 = (i == (output.rows - 1))? 0 : drow_below[j];
                    x2 = ((i == 0) || (j == (output.cols - 1)))? 0 : drow_above[j+1];
                    x4 = ((i == 0) || (j == 0))? 0 :drow_above[j-1];
                    x6 = ((i == (output.rows - 1)) || (j == 0))? 0 : drow_below[j-1];
                    x8 = ((i == (output.rows - 1)) || (j == (output.cols - 1)))? 0 : drow_below[j+1];

                    //check for G1
                    int b1= 0 ,b2 = 0 ,b3 = 0 ,b4 = 0;
                    int sum = 0;
                    bool satisfy = false;
                    if((x1 == 0x00)&((x2==0xff) | (x3 == 0xff)))
                        b1 = 1;
                    if((x3 == 0x00)&((x4==0xff) | (x5 == 0xff)))
                        b2 = 1;
                    if((x5 == 0x00)&((x6==0xff) | (x7 == 0xff)))
                        b3 = 1;
                    if((x7 == 0x00)&((x8==0xff) | (x1 == 0xff)))
                        b4 = 1;
                    sum = b1 + b2 + b3 + b4;

                    if (sum == 1)// G1 satisfied go to check G2
                    {
                        int p1=0, p2=0, p3=0, p4=0 , q1=0, q2=0, q3=0, q4=0;
                        int sum1 = 0, sum2 = 0;
                        if((x1 | x2 )== 0xff)
                            p1 = 1;
                        if((x3 | x4 )== 0xff)
                            p2 = 1;
                        if((x5 | x6 )== 0xff)
                            p3 = 1;
                        if((x7 | x8 )== 0xff)
                            p4 = 1;
                        sum1 = p1 + p2 + p3+ p4;

                        if((x2 | x3 )== 0xff)
                            q1 = 1;
                        if((x4 | x5 )== 0xff)
                            q2 = 1;
                        if((x6 | x7 )== 0xff)
                            q3 = 1;
                        if((x8 | x1 )== 0xff)
                            q4 = 1;
                        sum2 = q1 + q2 + q3+ q4;
                        if( (std::min(sum1,sum2)>= 2) & (std::min(sum1,sum2)<=3))//g2 is also satisfied
                        {
                            //check for checkerboard pattern
                            if(((x6 | x7 | ~x4) & x5) == 0x00)
                                satisfy = true;
                            if(satisfy)
                            {
                                changes_made=true;
                                if( runs == itr)
                                    changes_made = false;
                                points_delete.push_back(cv::Point(j,i));
                                //drow[j] = 0x00;
                            }
                        }
                        else //G2 not satisfied goto next pixel
                        {

                            continue;
                        }
                    }
                    else // G1 not satisfied go to the next pixel
                    {
                        continue;
                    }
                }
            }
        }
        for(int m =0; m<(int)points_delete.size(); m++)
            output.at<uchar>(points_delete[m].y,points_delete[m].x) = 0x00;

        points_delete.clear();

        retVal = NO_ERRORS;
    }
    return 0;
}

