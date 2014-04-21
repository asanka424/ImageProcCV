#include <ImageProcCV.h>

int ImageProcCV::bwBranchPoints(cv::Mat &input, std::vector<cv::Point> &branchPoints)
{
    int retVal = NO_ERRORS;
    if (input.type() != CV_8UC1)
    {
        retVal = INV_IMG_TYPE;
        return retVal;
    }

    cv::Mat initialBranchPoints = cv::Mat::zeros(input.size(),input.type());
    cv::Mat lutBranchPoints;
    getLutBranchPoints(lutBranchPoints);
    bool changed;

   //initial branch points
    applyLUT(input,lutBranchPoints,false,initialBranchPoints,changed);

    //background object count
    cv::Mat backgroundObjectCount = cv::Mat::zeros(input.size(),input.type());
    cv::Mat lutBackgroundObjectCount;
    getLutBackCount4(lutBackgroundObjectCount);
    cv::Mat inputNormalized = input/255;
    for(int i= 0; i< inputNormalized.rows;i++)
    {
        uchar zero,one,two,three,four,five,six,seven,eight;
        //get the address of raq i
        uchar *drow = inputNormalized.ptr<uchar>(i);
        uchar *outputdata = backgroundObjectCount.ptr<uchar>(i);
        //if (i != 0)
            uchar *drow_above = inputNormalized.ptr<uchar>(i-1);
       // if(i != (input.rows -1) )
            uchar *drow_below = inputNormalized.ptr<uchar>(i+1);
        for(int j = 0; j< inputNormalized.cols; j++)
        {
            four = drow[j];
            seven = (j == (inputNormalized.cols - 1))? 0 : drow[j+1];
            three = (i == 0)? 0 : drow_above[j];
            one = (j == 0)? 0 : drow[j-1];
            five = (i == (inputNormalized.rows - 1))? 0 : drow_below[j];
            six = ((i == 0) || (j == (inputNormalized.cols - 1)))? 0 : drow_above[j+1];
            zero = ((i == 0) || (j == 0))? 0 :drow_above[j-1];
            two = ((i == (inputNormalized.rows - 1)) || (j == 0))? 0 : drow_below[j-1];
            eight = ((i == (inputNormalized.rows - 1)) || (j == (inputNormalized.cols - 1)))? 0 : drow_below[j+1];

            int lookupValue = zero + (one << 1) + (two << 2) + (three << 3) + (four << 4) + (five << 5) +
                                     (six << 6) + (seven << 7) + (eight << 8) ;
            //uchar out = lut.at<uchar>(0,lookupValue)*255;
            uchar out = lutBackgroundObjectCount.at<uchar>(0,lookupValue);
            outputdata[j] = out;
        }
    }

    //end points
    cv::Mat endPoints = cv::Mat::zeros(input.size(),input.type());
    for(int i = 0 ; i < backgroundObjectCount.rows; i++)
    {
        uchar* pobjectCount = backgroundObjectCount.ptr<uchar>(i);
        uchar* pendPoints = endPoints.ptr<uchar>(i);

        for(int j = 0; j < backgroundObjectCount.cols; j++)
        {
            if (pobjectCount[j] == 1)
                pendPoints[j] = 0xff;
        }
    }
    //final branch point candidateds
    cv::Mat finalBranchPointCandidates;
    cv::Mat negate_endPoints = 255 - endPoints;
    initialBranchPoints /= 255;
    negate_endPoints /= 255;
    cv::multiply(initialBranchPoints,negate_endPoints,finalBranchPointCandidates);

    //generate masks that where backgournd connected pixels = 2  or more and not an endpoint
    // Vp is =2 maske
    cv::Mat Vp = cv::Mat::zeros(input.size(),input.type());
    for(int i = 0 ; i < backgroundObjectCount.rows; i++)
    {
        uchar* pobjectCount = backgroundObjectCount.ptr<uchar>(i);
        uchar* pVp = Vp.ptr<uchar>(i);
        uchar* pendPoints = endPoints.ptr<uchar>(i);

        for(int j = 0; j < backgroundObjectCount.cols; j++)
        {
            if ((pobjectCount[j] == 2) && (pendPoints[j] == 0) )
                pVp[j] = 0xFF;
        }
    }
    // Vq is > 2 mask
    cv::Mat Vq = cv::Mat::zeros(input.size(),input.type());
    for(int i = 0 ; i < backgroundObjectCount.rows; i++)
    {
        uchar* pobjectCount = backgroundObjectCount.ptr<uchar>(i);
        uchar* pVq = Vq.ptr<uchar>(i);
        uchar* pendPoints = endPoints.ptr<uchar>(i);

        for(int j = 0; j < backgroundObjectCount.cols; j++)
        {
            if ((pobjectCount[j] > 2) && (pendPoints[j] == 0) )
                pVq[j] = 0xFF;
        }
    }

    //dialate Vq
    cv::Mat dilatedVq = cv::Mat::zeros(input.size(),input.type());
    cv::Mat lutDilate;
    getLutDilate(lutDilate);
    applyLUT(Vq,lutDilate,true,dilatedVq,changed);

    //intersection between dilated Vq final branch point candidates and Vp
    cv::Mat interSections;
    finalBranchPointCandidates *= 255;
    cv::Mat temp;
    cv::bitwise_and(finalBranchPointCandidates,Vp,temp);
    cv::bitwise_and(temp,dilatedVq,interSections);

    //final branch points
    cv::Mat finalBranchPoints;
    cv::Mat negate_interSections;
    interSections *= 255;
    cv::bitwise_not(interSections,negate_interSections);
    cv::bitwise_and(finalBranchPointCandidates,negate_interSections,finalBranchPoints);

    for (int i = 0; i < finalBranchPoints.rows; i++)
    {
        uchar *pdata = finalBranchPoints.ptr<uchar>(i);
        for (int j = 0; j < finalBranchPoints.cols; j++)
        {
            if (pdata[j] == 0xFF)
                branchPoints.push_back(cv::Point(j,i));
        }
    }
    return retVal;
}
