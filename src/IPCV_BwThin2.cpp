#include <ImageProcCV.h>
//#include <LookupTables.h>



int ImageProcCV::bwThin2(cv::Mat input, cv::Mat &output, int itr)
{
    int retVal = NO_ERRORS;
    bool changesMade = true;
    cv::Mat intermediate = input.clone();

    int runs = 0;
    while (changesMade)
    {
        runs++;
        //use 2 luts
        for(int i = 0; i < 2; i++)
        {
            cv::Mat lut;
            getLutThin(i,lut);
            //previous = intermediate;
            retVal = applyLUT(intermediate,lut,false,intermediate,changesMade);
            if (retVal != 0)
            {
                changesMade = false;
                break;
            }
            //std::cout << input - intermediate << std::cout;
            /*cv::namedWindow("out");
            cv::imshow("out",intermediate);
            cv::waitKey();
            cv::destroyWindow("out");*/
        }
        //changesMade = !std::equal(previous.begin<uchar>(),previous.end<uchar>(),intermediate.begin<uchar>());
        if (runs == itr)
            changesMade = false;
    }
    output = intermediate;

    return retVal;
}



