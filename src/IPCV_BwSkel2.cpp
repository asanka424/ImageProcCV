#include <ImageProcCV.h>
#include <stack>
int skeletonGrow(cv::Point seed, cv::Mat distTransform,cv::Mat bwImage,cv::Mat& skel);
bool checkSkeleton(cv::Point candidate, cv::Mat dt,cv::Mat bwImage);
void ImageProcCV::bwSkel2(cv::Mat input, cv::Mat& output)
{
    cv::Mat distMap;
    ssedTransform(input,distMap);
    std::cout << distMap << std::endl;
    //finding seed point
    cv::Point seed;
    double max_distance = -1;
    for(int i = 0; i < distMap.rows; i++)
    {
        cv::Vec2i* _distMap_out = distMap.ptr<cv::Vec2i>(i);
        for(int j = 0; j < distMap.cols; j++)
        {
            int xcor = _distMap_out[j][0];
            int ycor = _distMap_out[j][1];
            _distMap_out[j][0] = xcor;
            _distMap_out[j][1] = ycor;
            double dis = cv::norm(_distMap_out[j]);
            if(dis > max_distance)
            {
                max_distance = dis;
                seed = cv::Point(j,i);
            }
        }
    }
    output = cv::Mat::zeros(input.size(),CV_8UC1);
    skeletonGrow(seed,distMap,input,output);

}
int skeletonGrow(cv::Point seed, cv::Mat distTransform, cv::Mat bwImage,cv::Mat &skel)
{
    int retVal = NO_ERRORS;
    skel = cv::Mat::zeros(distTransform.size(),CV_8UC1);
    std::stack<cv::Point> pointStack;
    pointStack.push(seed);
    skel.at<uchar>(seed) = 0xff;
    int count = 0;
    while(pointStack.size() > 0)
    {
        //get the top element;
        cv::Point skelPoint = pointStack.top();
        int x = skelPoint.x, y = skelPoint.y;
        pointStack.pop();

        //get all 8 neighbors. if they are not already a skeleton point check
        //whether they are skeleton points. this function requirs at least 3 pixel gap
        //between object boundary and the image edge. Otherwise it will give segmentation
        //failures.
        //uchar value = bwImage.at<uchar>(y,x+1);
        if((skel.at<uchar>(y,x+1) == 0x00) && (bwImage.at<uchar>(y,x+1) != 0x00) )
            if(checkSkeleton(cv::Point(x+1,y),distTransform,bwImage))
            {
                skel.at<uchar>(y,x+1) = 0xff;
                pointStack.push(cv::Point(x+1,y));

                count++;
            }

        if((skel.at<uchar>(y-1,x+1) == 0x00) && (bwImage.at<uchar>(y-1,x+1) != 0x00) )
            if(checkSkeleton(cv::Point(x+1,y-1),distTransform,bwImage))
            {
                skel.at<uchar>(y-1,x+1) = 0xff;
                pointStack.push(cv::Point(x+1,y-1));

                count++;
            }

        if((skel.at<uchar>(y-1,x) == 0x00) && (bwImage.at<uchar>(y-1,x) != 0x00))
            if(checkSkeleton(cv::Point(x,y-1),distTransform,bwImage))
            {
                skel.at<uchar>(y-1,x) = 0xff;
                pointStack.push(cv::Point(x,y-1));

                count++;
            }

        if((skel.at<uchar>(y-1,x-1) == 0x00)&& (bwImage.at<uchar>(y-1,x-1) != 0x00))
            if(checkSkeleton(cv::Point(x-1,y-1),distTransform,bwImage))
            {
                skel.at<uchar>(y-1,x-1) = 0xff;
                pointStack.push(cv::Point(x-1,y-1));

                count++;
            }

        if((skel.at<uchar>(y,x-1) == 0x00)&& (bwImage.at<uchar>(y,x-1) != 0x00))
            if(checkSkeleton(cv::Point(x-1,y),distTransform,bwImage))
            {
                skel.at<uchar>(y,x-1) = 0xff;
                pointStack.push(cv::Point(x-1,y));

                count++;
            }
        if((skel.at<uchar>(y+1,x-1) == 0x00) && (bwImage.at<uchar>(y+1,x-1) != 0x00))
            if(checkSkeleton(cv::Point(x-1,y+1),distTransform,bwImage))
            {
                skel.at<uchar>(y+1,x-1) = 0xff;
                pointStack.push(cv::Point(x-1,y+1));

                count++;
            }

        if((skel.at<uchar>(y+1,x) == 0x00) && (bwImage.at<uchar>(y+1,x) != 0x00))
            if(checkSkeleton(cv::Point(x,y+1),distTransform,bwImage))
            {
                skel.at<uchar>(y+1,x) = 0xff;
                pointStack.push(cv::Point(x,y+1));

                count++;
            }

        if((skel.at<uchar>(y+1,x+1) == 0x00) && (bwImage.at<uchar>(y+1,x+1) != 0x00))
            if(checkSkeleton(cv::Point(x+1,y+1),distTransform,bwImage))
            {
                skel.at<uchar>(y+1,x+1) = 0xff;
                pointStack.push(cv::Point(x+1,y+1));

                count++;
            }

        //check if we have found skeleton points
        if (count == 0)
        {
            retVal = NO_SKEL_POINTS_FOUND;
            return retVal;
        }
    }
    return retVal;
}
bool checkSkeleton(cv::Point candidate, cv::Mat dt, cv::Mat bw)
{
    bool returnValue = false;
    int i = candidate.y, j = candidate.x;
    cv::Vec2i Q = dt.at<cv::Vec2i>(candidate);
    double pro = (Q[0]*Q[0] + Q[1]*Q[1])*2;
    pro = std::min(4.0,pro);
    std::vector<cv::Point> nNeighbors;
    //get neighbors at edges

    for(int m = i-1; m <= i+1; m++)
    {
        for(int n = j -1; n<= j+1; n++)
        {

            bool alreadyIn = false;
            if(((i != m)|| (j != n)) && (bw.at<uchar>(m,n) == 0xff))
            {
                cv::Vec2i qi = dt.at<cv::Vec2i>(m,n);
                cv::Point posRelatedtoCandidate = cv::Point(qi[0]+n-j,qi[1]+m-i);
                //cv::Point genPoint = cv::Point(qi[0]+n,qi[1]+m);
                for(std::vector<cv::Point>::iterator it = nNeighbors.begin();
                    it != nNeighbors.end(); it++)
                {
                    if(*it == posRelatedtoCandidate)
                    {
                        alreadyIn = true;
                        break;
                    }
                }
                if(!alreadyIn)
                {
                    nNeighbors.push_back(posRelatedtoCandidate);
                    double dsquare = (Q[0]- posRelatedtoCandidate.x)*(Q[0]- posRelatedtoCandidate.x) +
                            (Q[1] - posRelatedtoCandidate.y)*(Q[1] - posRelatedtoCandidate.y);
                    //if (dsquare >= std::min(4.0,pro))
                    if (dsquare >= 4.0)
                    {
                        double width = std::abs((posRelatedtoCandidate.x * posRelatedtoCandidate.x + posRelatedtoCandidate.y * posRelatedtoCandidate.y)
                                    - (Q[0]*Q[0] + Q[1]*Q[1]))/(float)(std::max(std::abs(posRelatedtoCandidate.x - Q[0]),std::abs(posRelatedtoCandidate.y - Q[1])));

                        if(width <= 1 )
                        {
                            returnValue = true;
                            break;

                        }
                    }
                }
            }
        }
        if(returnValue)
            break;
    }
    return returnValue;
}
