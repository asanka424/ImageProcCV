/////////////////////////////////////////////////////////////////////
//                                                                 //
//      Selects the image blob corresponding to the                //
//      given input pixel                                          //
//                                                                 //
//      File Name: bwSelect.cpp                                    //
//      File Type: C++ source                                      //
//      Auther: Asanka Wickramasinghe                              //
//      Project: Image Processing CV               //
//      Module: Image Processing Library (ImageProcCV)            //
//      Date Created: 2012 - Mar                                   //
//                                                                 //
/////////////////////////////////////////////////////////////////////



#include <ImageProcCV.h>

int ImageProcCV::bwSelect(std::vector<std::vector<cv::Point> > &labels, cv::Point point,
                           std::vector<cv::Point>& _selected)
{
    bool found = false;
    int retVal;
    std::vector<cv::Point>& retval = _selected;
    for(std::vector<std::vector<cv::Point> >::iterator outer = labels.begin(); outer != labels.end(); outer++)
    {
        for(std::vector<cv::Point>::iterator inner = (*outer).begin(); inner != (*outer).end(); inner++)
        {
            if((*inner) == point)
            {
                found = true;
                break;
            }
        }
        if(found)
        {
            retval = *outer;
            retVal = NO_ERRORS;
            break;
        }
        else
        {
            retVal = NO_LABELS_SELECTED;
        }
    }

    return retVal;


    /*std::vector<std::vector<cv::Point> > strongLabel;
        for(std::vector<std::vector<cv::Point> >::iterator it = labels.begin(); it != labels.end(); it++)
        {

            for(std::vector<cv::Point>::iterator inner = (*it).begin(); inner != (*it).end(); inner++)
            {
                bool found = false;
                for(std::vector<cv::Point>::iterator points_itr = strongPoints.begin();
                    points_itr != strongPoints.end(); points_itr++)
                {

                    if(*inner == *points_itr)
                    {
                        strongLabel.push_back((*it));
                        found = true;
                        break;
                    }

                }
                if(found)
                {
                    break;
                }
            }
        }*/

}
