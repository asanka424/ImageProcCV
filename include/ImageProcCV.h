/////////////////////////////////////////////////////////////////////
//                                                                 //
//      File Name: imageprocv.h                                   //
//      File Type: C++ header                                      //
//      Auther: Asanka Wickramasinghe                              //
//      Project: Image Processing CV               //
//      Module: Image Processing Library (ImageProcCV)            //
//      Date Created: 2012 - Mar                                   //
//                                                                 //
/////////////////////////////////////////////////////////////////////
#ifndef IMAGEPROCCV_H
#define IMAGEPROCCV_H

#include "ImageProcCV_global.h"
#include "ErrorNumbers.h"
#define NORM_GLOBAL 1
#define NORM_STD 2

void getLutSkel(int i, cv::Mat& lut);
void getLutThin(int i, cv::Mat& lut);
void getLutBridge(cv::Mat& lut);
void getLutEndPoints(cv::Mat& lut);
void getLutSpur(cv::Mat& lut);
void getLutBranchPoints(cv::Mat& lut);
void getLutBackCount4(cv::Mat& lut);
void getLutDilate(cv::Mat& lut);


namespace ImageProcCV {


    int bwSpur(cv::Mat& _input,int op = 1, int itr = 0);
    int bwClean(cv::Mat& _input);
    void bwHitMiss(cv::Mat &_input, cv::Mat &_hit, cv::Mat &_miss,
                   cv::Mat &_output,  bool _middleElement = true);
    int bwBoundaries( cv::Mat& _input, cv::Mat& _output,std::vector<cv::Point>& _boundary);
    int bwspurremove_mod(cv::Mat &_input, int itr = 0);
    int findJunctions(cv::Mat& _input,std::vector<cv::Point>& _juncPoints);
    int bwLabel(cv::Mat &_input, cv::Mat& _output, std::vector<std::vector<cv::Point> >& _labels, int min_size, bool eight_con);
    int bwCorner(cv::Mat& _image);
    int bwThin(cv::Mat& _input, cv::Mat& _output, int itr = -1);
    int bwThin2(cv::Mat _input, cv::Mat &_output, int itr = -1);
    std::vector<int> bwHist(cv::Mat _image);
    int bwMajority(cv::Mat &_input, cv::Mat &_output);
    int bwRemove(cv::Mat& _input);
    void bwSkel(const cv::Mat _input, cv::Mat& _output);
    void bwSkel2(cv::Mat _input, cv::Mat& _output);
    void bwSkel3(cv::Mat _input, cv::Mat& _output);
    void imageInvert(cv::Mat& _input, cv::Mat& _output);
    int imageAdjust(cv::Mat &_input, cv::Mat& _output);
    int imageNormalize(cv::Mat& _input, cv::Mat& _output, int method = NORM_GLOBAL);
    int cannyEdgeDetector(cv::Mat &_input, cv::Mat& _output, double sigma = 1);
    int bwPerim(cv::Mat& _input, cv::Mat& _output, int conn = 4);
    int skelEndPoints(cv::Mat &_input, std::vector<cv::Point>& _endPoints);
    int bwSelect(std::vector<std::vector<cv::Point> >& labels,cv::Point point,std::vector<cv::Point>& _selected);
    void bwBridge(cv::Mat& _input, cv::Mat& _output, bool eight_con = true);
    int bwBoundaries_2(cv::Mat bwImage, std::vector<cv::Point>& contour);
    int ssedTransform(cv::Mat& input, cv::Mat& ftransform);
    int applyLUT(cv::Mat input,  cv::Mat lut, bool processZero,cv::Mat &output,bool& changed);
    void bwSkel4(const cv::Mat _input, cv::Mat& _output);
    int getOtsuThreshValue(cv::Mat& _src, double& threshold );
    int bwEndPoints(cv::Mat& bw, std::vector<cv::Point>& endPoints);
    int bwSpur2(cv::Mat& input, cv::Mat& output, int itr);
    int bwBranchPoints(cv::Mat& input, std::vector<cv::Point>& branchPoints);
    void spurOnce(cv::Mat& output);
    }


inline int checkMatrix(cv::Mat& _input)
{
    cv::Mat& input = _input;
    //check for the input matrix
    if(input.empty())
    {
        return -1; //no elements or data
    }
    else
    {
        return 0;
    }
}


#endif // IMAGEPROCCV_H
