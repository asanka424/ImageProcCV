#include <ImageProcCV.h>

int ImageProcCV::bwBoundaries_2(cv::Mat bwImage, std::vector<cv::Point>& contour)
{
    int retVal = NO_ERRORS;

    cv::Mat perim;

    retVal = ImageProcCV::bwPerim(bwImage,perim);
    if (retVal < 0)
    {
        return retVal;
    }

    int sx = -1,sy = -1;
    for(int i = 0; i < bwImage.rows; i++)
    {
        for(int j = 0; j < bwImage.cols; j++)
        {
            int y = j;
            int x = bwImage.rows - i - 1;
            if(perim.at<uchar>(x,y) == 0xff)
            {
                sx = x;
                sy = y;
            }
        }
    }
    if ((sx == -1) || (sy == -1))
    {
        retVal = NO_ENTRY_PNT_FOUND;
        return retVal;
    }
    int dx[] = {-1,-1,-1,0,1,1,1,0};
    int dy[] = {-1,0,1,1,1,0,-1,-1};

    bool findStartPoint = false;
    int temp = 0;

    int cx = sx, cy = sy;
    int maxVal = bwImage.rows*bwImage.cols;
    int count1 = 0;
    while(!findStartPoint)
    {
        count1++;
        if (count1 > maxVal)
        {
            retVal = NOT_CONVERGING;
            return retVal;
        }
        contour.push_back(cv::Point(cy,cx)); //x and y have interchanged

        bool findPoint = false;
        int count2 = 0;
        while(!findPoint)
        {
            count1++;
            int tx = cx+ dx[temp];
            int ty = cy + dy[temp];
            uchar pixel;
            if (((tx < 0) || (ty < 0)) || ((tx == bwImage.rows)||(ty == bwImage.cols)))
                pixel = 0x00;
            else
                pixel = perim.at<uchar>(tx,ty);
            if(pixel == 0xff)
            {
                findPoint = true;
                cx = tx;
                cy = ty;
                if((cx == sx) && (cy == sy))
                    findStartPoint = true;
                temp = temp -1;
                if(temp == -1)
                {
                    temp = 7;
                }
                temp = temp -1;
                if(temp == -1)
                {
                    temp = 7;
                }
            }
            else
            {
                temp = temp +1;
                if(temp == 8)
                {
                    temp = 0;
                }
            }
            if (count2 > 8)
            {
                retVal = NEXT_PNT_NOT_FOUND;
                return retVal;
            }
        }
    }
    return retVal;

}
