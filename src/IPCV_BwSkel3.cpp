#include <ImageProcCV.h>
//#include <LookupTables.h>


void ImageProcCV::bwSkel3(cv::Mat input, cv::Mat &output)
{
    bool changesMade = true;
    bool changesMade_global = true;
    cv::Mat intermediate = input.clone();
    while (changesMade_global)
    {
        //use all 8 luts
        changesMade_global = false;
        for(int i = 0; i < 8; i++)
        {
            cv::Mat lut;
            getLutSkel(i,lut);
            //std::cout << intermediate << std::endl;
            applyLUT(intermediate,lut,false,intermediate,changesMade);

            if (changesMade)
                changesMade_global = true;

            /*cv::namedWindow("out");
            cv::imshow("out",intermediate);
            cv::waitKey();
            cv::destroyWindow("out");*/
            //cv::imwrite("c:/images/skel3result.tif",intermediate);
        }
        //changesMade = !std::equal(previous.begin<uchar>(),previous.end<uchar>(),intermediate.begin<uchar>());

    }
    output = intermediate;
}

