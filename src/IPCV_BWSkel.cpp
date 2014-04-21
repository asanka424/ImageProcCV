/////////////////////////////////////////////////////////////////////
//                                                                 //
//      This function will use  hit-or-miss  morphology  to        //
//      thin a given  binary image. Function  will continue        //
//      until there is no change in input and output images        //
//                                                                 //
//                                                                 //
//      File Name: calculateGVF.cpp                                //
//      File Type: C++ source                                      //
//      Auther: Asanka Wickramasinghe                              //
//      Project: Image Processing CV                                //
//      Module: Image Processing Library (ImageProcCV)            //
//      Date Created: 2012 - Mar                                   //
//                                                                 //
/////////////////////////////////////////////////////////////////////
#include "ImageProcCV.h"

void ImageProcCV::bwSkel(const cv::Mat _input, cv::Mat& _output)
{
    //Process input arrays into matrices with required parameters
    //src and dst had to have same dimensions an same datatypes.
    cv::Mat src = _input;
    cv::Mat& dst = _output;

    dst = src.clone();
    cv::Mat intermediate = src.clone();

    bool changesMade = true;

    while(changesMade)
    {
        changesMade = false;
        for(int i= 0; i< intermediate.rows;i++)
        {
            uchar north,south,east,west,northeast,southeast,southwest,northwest;
            //get the address of raq i
            uchar *drow = intermediate.ptr<uchar>(i);
            uchar *output = dst.ptr<uchar>(i);
            //if (i != 0)
            uchar *drow_above = intermediate.ptr<uchar>(i-1);
           // if(i != (input.rows -1) )
            uchar *drow_below = intermediate.ptr<uchar>(i+1);
            for(int j = 0; j< dst.cols; j++)
            {
                if (drow[j] != 0x00)
                {
                    east = (j == (dst.cols - 1))? 0 : drow[j+1];
                    north = (i == 0)? 0 : drow_above[j];
                    west = (j == 0)? 0 : drow[j-1];
                    south = (i == (dst.rows - 1))? 0 : drow_below[j];
                    northeast = ((i == 0) || (j == (dst.cols - 1)))? 0 : drow_above[j+1];
                    northwest = ((i == 0) || (j == 0))? 0 :drow_above[j-1];
                    southwest = ((i == (dst.rows - 1)) || (j == 0))? 0 : drow_below[j-1];
                    southeast = ((i == (dst.rows - 1)) || (j == (dst.cols - 1)))? 0 : drow_below[j+1];

                    /* check for kernel

                      0 0 0
                      _ 1 _
                      1 1 1

                      */
                    if(((north | northeast | northwest) == 0x00)&&((south & southeast & southwest) == 0xff ) )
                    {
                        output[j]=0x00;
                        changesMade = true;
                        continue;
                    }

                    /* check for kernel

                        1 _ 0
                        1 1 0
                        1 _ 0
                    */
                    else if(((west & southwest & northwest) == 0xff)&&((east | southeast | northeast) == 0x00 ) )
                    {
                        output[j]=0x00;
                        changesMade = true;
                        continue;
                    }

                    /* check for kernel

                        1 1 1
                        _ 1 _
                        0 0 0
                    */
                    else if(((north & northeast & northwest) == 0xff)&&((south | southeast | southwest) == 0x00 ) )
                    {
                        output[j]=0x00;
                        changesMade = true;
                        continue;
                    }

                    /* check for kernel

                        0 _ 1
                        0 1 1
                        0 _ 1
                    */
                    else if(((west | southwest | northwest) == 0x00)&&((east & southeast & northeast) == 0xff ) )
                    {
                        output[j]=0x00;
                        changesMade = true;
                        continue;
                    }

                    /* check for kernel

                        _ 0 0
                        1 1 0
                        _ 1 _
                    */
                    //else if(((west & south & southwest) == 0xff)&&((east | north | northeast ) == 0x00 ) )
                    else if(((west & south) == 0xff)&&((east | north | northeast ) == 0x00 ) )
                    {
                        output[j]=0x00;
                        changesMade = true;
                        continue;
                    }

                    /* check for kernel

                        _ 1 _
                        1 1 0
                        _ 0 0
                    */
                    //else if(((west & north & northwest) == 0xff)&&((east | south | southeast) == 0x00 ) )
                    else if(((west & north) == 0xff)&&((east | south | southeast) == 0x00 ) )
                    {
                        output[j]=0x00;
                        changesMade = true;
                        continue;
                    }

                    /* check for kernel

                        _ 1 _
                        0 1 1
                        0 0 _
                    */
                    //else if(((west | south | southwest) == 0x00 )&&((east & north & northeast) == 0xff ) )
                    else if(((west | south | southwest) == 0x00 )&&((east & north) == 0xff ) )
                    {
                        output[j]=0x00;
                        changesMade = true;
                        continue;
                    }

                    /* check for kernel

                        0 0 _
                        0 1 1
                        _ 1 _
                    */
                    //else if(((west | north | northwest ) == 0x00 )&&((east & south & southeast) == 0xff ) )
                    else if(((west | north | northwest ) == 0x00 )&&((east & south) == 0xff ) )
                    {
                        output[j]=0x00;
                        changesMade = true;
                        continue;
                    }
                }
            }
        }
        intermediate = dst;

    }

    //removing spurs
   /* before_count = (int)valuesVector.size();
    after_count = 0 ;

        for(int i= 0; i<(int)valuesVector.size();i++)
        {
             uchar north,south,east,west,northeast,southeast,southwest,northwest;
            int x,y;
            x = valuesVector[i].x;
            y = valuesVector[i].y;

            if(x==0 && y!=0)//boundry condition
            {
                north = dst.at<uchar>(y-1,x);
                east = dst.at<uchar>(y,x+1);
                west = 0xff;
                south = dst.at<uchar>(y+1,x);
                northeast = dst.at<uchar>(y-1,x+1);
                southeast = dst.at<uchar>(y+1,x+1);
                southwest = 0xff;
                northwest = 0xff;

            }
            if(x==0 && y!=0)//boundry condition
            {
                north = 0xff;
                east = dst.at<uchar>(y,x+1);
                west = dst.at<uchar>(y,x-1);
                south = dst.at<uchar>(y+1,x);
                northeast = 0xff;
                southeast = dst.at<uchar>(y+1,x+1);
                southwest = dst.at<uchar>(y+1,x-1);
                northwest = 0xff;

            }
            if(x!=0 && y!=0)
            {
                north = dst.at<uchar>(y-1,x);
                east = dst.at<uchar>(y,x+1);
                west = dst.at<uchar>(y,x-1);
                south = dst.at<uchar>(y+1,x);
                northeast = dst.at<uchar>(y-1,x+1);
                southeast = dst.at<uchar>(y+1,x+1);
                southwest = dst.at<uchar>(y+1,x-1);
                northwest = dst.at<uchar>(y-1,x-1);
            }



        }
        cv::imshow("My Image",dst);
        cv::waitKey(0);



    //cv::imshow("My Image",dst);
    //cv::waitKey(0);*/
}

