#include <ImageProcCV.h>

int ImageProcCV::applyLUT(cv::Mat input1,cv::Mat lut,bool processZero, cv::Mat &output, bool& changed )
{
    //std::cout << lut << std::endl;
    int retVal = NO_ERRORS;
    changed = false;
    if (!output.data)
    {
        retVal = OUTPUT_IMG_EMPTY;
        return retVal;
    }
    if (!input1.data)
    {
        retVal = INPUT_IMG_EMPTY;
        return retVal;
    }
    //check lut it should be a single row matrix
    if (lut.rows != 1)
    {
        retVal = LUT_IS_INVALID;
        return retVal;
    }
    //preparing input.
    cv::Mat input = input1.clone();
    input /= 255;

    for(int i= 0; i< output.rows;i++)
    {
        uchar zero,one,two,three,four,five,six,seven,eight;
        //get the address of raq i
        uchar *drow = input.ptr<uchar>(i);
        uchar *outputdata = output.ptr<uchar>(i);
        //if (i != 0)
            uchar *drow_above = input.ptr<uchar>(i-1);
       // if(i != (input.rows -1) )
            uchar *drow_below = input.ptr<uchar>(i+1);
        for(int j = 0; j< input.cols; j++)
        {
            four = drow[j];
            if((four == 0) && !processZero)
                continue;
            seven = (j == (input.cols - 1))? 0 : drow[j+1];
            three = (i == 0)? 0 : drow_above[j];
            one = (j == 0)? 0 : drow[j-1];
            five = (i == (input.rows - 1))? 0 : drow_below[j];
            six = ((i == 0) || (j == (input.cols - 1)))? 0 : drow_above[j+1];
            zero = ((i == 0) || (j == 0))? 0 :drow_above[j-1];
            two = ((i == (input.rows - 1)) || (j == 0))? 0 : drow_below[j-1];
            eight = ((i == (input.rows - 1)) || (j == (input.cols - 1)))? 0 : drow_below[j+1];

            int lookupValue = zero + (one << 1) + (two << 2) + (three << 3) + (four << 4) + (five << 5) +
                                     (six << 6) + (seven << 7) + (eight << 8) ;
            //uchar out = lut.at<uchar>(0,lookupValue)*255;
            uchar out = lut.at<uchar>(0,lookupValue);
            if (four != out)
                changed = true;
            outputdata[j] = out;

        }

    }
    output *= 255;
    return retVal;

}
