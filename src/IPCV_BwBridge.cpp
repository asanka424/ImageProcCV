/////////////////////////////////////////////////////////////////////
//                                                                 //
//      Bridge unconnected pixels                                  //
//      Set 0 values to 1, if they have two nonzero neighbours     //
//      which are not connected                                    //
//                                                                 //
//      File Name: bwBridge.cpp                                    //
//      File Type: C++ source                                      //
//      Auther: Yanxin Li                                          //
//      Project: Image Processing CV               //
//      Module: Image Processing Library ( ImageProcCV )          //
//      Date Created: 2012 - Oct                                   //
//                                                                 //
/////////////////////////////////////////////////////////////////////

#include <ImageProcCV.h>

//  Matlab Version
void ImageProcCV::bwBridge(cv::Mat& input, cv::Mat& output, bool eight_con)
{
    output = input.clone();
    if(!eight_con)	
    {
        std::cout<<"ImageProcCV bwBridge: four_con not implemented yet"<<std::endl;
	return;
    }
    //	Get lutbridge
    cv::Mat lut; 
    getLutBridge(lut);

    bool changed;
    applyLUT(output, lut, true, output, changed);
}

/*
bool checkGap(uchar roi[3][3]);

void ImageProcCV::bwBridge(cv::Mat& _input, cv::Mat& _output, bool eight_con)
{
    if(!eight_con)
    {
        std::cout<<"ImageProcCV bwBridge: four_con not implemented yet"<<std::endl;
        return;
    }

    cv::Mat& input = _input;
    cv::Mat& output = _output;
    output = input.clone();
    std::cout << "bridge "<<output.rows<<" "<<output.cols<<std::endl;

    for(int i=0; i<input.rows; i++)
    {
        uchar* entry = input.ptr<uchar>(i);
    uchar* out_entry = output.ptr<uchar>(i);
        uchar* entryabove = (i>0)?input.ptr<uchar>(i-1):NULL;
        uchar* entrybelow = (i<(input.rows-1))?input.ptr<uchar>(i+1):NULL;
        for(int j=0; j<input.cols; j++)
        {
            if(entry[j]==0x00)
            {
                uchar roi[3][3] = {0x00};
                roi[0][0] = ((i==0)||(j==0))?0x00:entryabove[j-1];
                roi[0][1] = (i==0)?0x00:entryabove[j];
                roi[0][2] = ((i==0)||(j==input.cols-1))?0x00:entryabove[j+1];
                roi[1][0] = (j==0)?0x00:entry[j-1];
                roi[1][1] = entry[j];
                roi[1][2] = (j==input.cols-1)?0x00:entry[j-1];
                roi[2][0] = ((i==input.rows-1)||j==0)?0x00:entrybelow[j-1];
                roi[2][1] = (i==input.rows-1)?0x00:entrybelow[j];
                roi[2][2] = ((i==input.rows-1)||(j==input.cols-1))?0x00:entrybelow[j+1];

                if(checkGap(roi))
                    out_entry[j] = 0xff;
            }
        }
    }
    std::cout<< "output "<<output.rows<<" "<<output.cols<<std::endl;
}

bool checkGap(uchar roi[3][3])
{
    bool gap_exist = false;

    if(roi[1][1]!=0x00)
        return gap_exist;

    int map_row[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int map_col[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    std::vector<cv::Point> neighbours;

    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
            if((i!=1 || j!=1) && roi[i][j]!=0X00)
            {
                cv::Point point(j, i);
                neighbours.push_back(point);
            }
        }

    if(neighbours.size()<2)
        return gap_exist;
    for(int i=0; i<neighbours.size(); i++)
    {
        bool connected = false;
        for(int j=0; j<8; j++)
        {
            int row = neighbours[i].y + map_row[j];
            int col = neighbours[i].x + map_col[j];

            if(row>=0 && row<3 && col>=0 && col<3)
                if(roi[row][col]!=0x00)
                    connected = true;
        }
        if(!connected)
        {
            gap_exist = true;
            return gap_exist;
        }
    }

    return gap_exist;
}
*/
