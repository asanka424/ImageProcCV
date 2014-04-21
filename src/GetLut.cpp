#include <LookupTables.h>
#include <ImageProcCV.h>

void getLutSkel(int i,cv::Mat& lut)
{

    switch (i)
    {
        case 0:
        lut = cv::Mat(1,512,CV_8UC1,lutSkel1);
        break;
        case 1:
        lut = cv::Mat(1,512,CV_8UC1,lutSkel2);
        break;
        case 2:
        lut = cv::Mat(1,512,CV_8UC1,lutSkel3);
        break;
        case 3:
        lut = cv::Mat(1,512,CV_8UC1,lutSkel4);
        break;
        case 4:
        lut = cv::Mat(1,512,CV_8UC1,lutSkel5);
        break;
        case 5:
        lut = cv::Mat(1,512,CV_8UC1,lutSkel6);
        break;
        case 6:
        lut = cv::Mat(1,512,CV_8UC1,lutSkel7);
        break;
        case 7:
        lut = cv::Mat(1,512,CV_8UC1,lutSkel8);
        break;
    }
}

void getLutThin(int i, cv::Mat& lut)
{
    switch (i)
    {
    case 0:
        lut = cv::Mat(1,512,CV_8UC1,lutThin1);
        break;
    case 1:
        lut = cv::Mat(1,512,CV_8UC1,lutThin2);
        break;
    }
}

void getLutBridge(cv::Mat& lut)
{
    lut = cv::Mat(1, 512, CV_8UC1, lutBridge);
}

void getLutEndPoints(cv::Mat &lut)
{
    lut = cv::Mat(1,512,CV_8UC1,lutEndPoints);
}

void getLutSpur(cv::Mat& lut)
{
    lut = cv::Mat(1,512,CV_8UC1,lutSpur);
}

void getLutBranchPoints(cv::Mat& lut)
{
    lut = cv::Mat(1,512,CV_8UC1,lutBranchPoints);
}
void getLutBackCount4(cv::Mat& lut)
{
    lut = cv::Mat(1,512,CV_8UC1,lutBackCount4);
}

void getLutDilate(cv::Mat& lut)
{
    lut = cv::Mat(1,512,CV_8UC1,lutDilate);
}
