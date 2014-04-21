/////////////////////////////////////////////////////////////////////
//                                                                 //
//      Connected  components  labeling  in  a  binary  image.     //
//      Uses two pass algorithm with disjointsets (find-union)     //
//      data structure.                                            //
//                                                                 //
//      File Name: bwLabel.cpp                                     //
//      File Type: C++ source                                      //
//      Auther: Asanka Wickramasinghe                              //
//      Project: Image Processing CV               //
//      Module: Image Processing Library (ImageProcCV)            //
//      Date Created: 2012 - Mar                                   //
//                                                                 //
/////////////////////////////////////////////////////////////////////
#include <ImageProcCV.h>
#include <DisjointSets.h>

int ImageProcCV::bwLabel( cv::Mat &_input, cv::Mat &_output,
                           std::vector<std::vector<cv::Point> > &_labels,
                           int min_size, bool eight_con)
{
    int retVal = NO_ERRORS;
    cv::Mat& input = _input;
    if(!input.data)
    {
        retVal = EMPTY_IMAGE_MTRX;
        std::cout << "input image for imageLabel is invalid" << std::endl;
        return retVal;
    }
    if (input.type()!= CV_8UC1)
    {
        retVal = INV_IMG_TYPE;
        return retVal;
    }
    else
    {
        cv::Mat& output = _output;
        std::vector<std::vector<cv::Point> >& labels = _labels;
        labels.clear();
        output = cv::Mat::zeros(input.size(),CV_32SC1); //  int matrix to hold labels
        DisjointSets  equivelent(0);
        int label = 1;
        for(int i =0; i<input.rows; i++)
        {
            uchar *data_input = input.ptr<uchar>(i);
            int *data_output = output.ptr<int>(i);
            //uchar *top_input = input.ptr<uchar>(i-1);
            int *top_output = output.ptr<int>(i-1);

            for(int j = 0; j< input.cols; j++)
            {
                //uchar pixel = 0x00;
                int north_output=0, northeast_output =0, northwest_output=0, west_output = 0;
                //pixel = data_input[j];
                if (data_input[j] != 0x00)
                {
                    north_output = (i == 0)? 0 : top_output[j];
                    west_output = (j == 0)? 0 : data_output[j-1];
                    if(eight_con)
                    {
                        northeast_output = ((i == 0) || (j == (output.cols - 1)))? 0 : top_output[j+1];
                        northwest_output = ((i == 0) || (j == 0))? 0 : top_output[j-1];
                    }



                    // get neighbours into a vector
                    std::vector<int> neighbours;
                    neighbours.clear();
                    if(north_output != 0)
                        neighbours.push_back(north_output);
                    if(west_output != 0)
                        neighbours.push_back(west_output);
                    if(eight_con)
                    {
                        if(northeast_output != 0)
                            neighbours.push_back(northeast_output);
                        if(northwest_output != 0)
                            neighbours.push_back(northwest_output);
                    }

                    //check whether neibours are empty or not
                    if(neighbours.size() > 0 )
                    {
                        int min_val = *std::min_element(neighbours.begin(),neighbours.end());

                        data_output[j] = min_val;

                        for(std::vector<int>::iterator it = neighbours.begin();
                            it<neighbours.end();it++)
                        {
                            //int key_val = *it;

                            equivelent.Union(equivelent.FindSet((int)(*it)),equivelent.FindSet((int)min_val));

                        }

                    }
                    else
                    {
                        data_output[j] = label;
                        label++;
                        if(label > equivelent.m_numElements)
                        {
                            equivelent.AddElements(label - equivelent.m_numElements+1);
                        }
                    }

                }
            }

        }

        //sorting out uniq labels
        std::map<int,int> uniq_labels;
        int count = 0;
        for(int a = 1; a < equivelent.m_numElements;a++)
        {

            if(a == equivelent.FindSet(a))
            {
                count++;

                uniq_labels.insert(std::pair<int,int>(a,count));
            }
            else
            {

            }
        }

        //inserting labels to label points vector

        std::map<int,std::vector<cv::Point> > temp_map;


        //second iteration to resolve label equivelences
        for(int i=0; i< output.rows; i++)
        {
            int* data_output = output.ptr<int>(i);
            for(int j=0; j<output.cols; j++)
            {
               // int value_out = data_output[j];
                if(data_output[j] != 0)
                {
                    int temp_val,temp_val2,temp_val3;
                    temp_val3 = (int)data_output[j];
                    temp_val = equivelent.FindSet(temp_val3);
                    temp_val2 = (int)uniq_labels.find(temp_val)->second;
                    data_output[j] = (int)temp_val2;

                    std::map<int,std::vector<cv::Point> >::iterator ret = temp_map.lower_bound((int)temp_val2);

                    if(ret != temp_map.end() && !(temp_map.key_comp()(temp_val2,ret->first))) //key already exist
                    {
                         std::vector<cv::Point>& temp_vector = ret->second;
                         temp_vector.push_back(cv::Point(j,i));
                    }
                    else
                    {
                        std::vector<cv::Point> temp_vector;
                        temp_vector.push_back(cv::Point(j,i));
                        temp_map.insert(std::pair<int,std::vector<cv::Point> >((int)temp_val2,temp_vector));
                    }
                }
            }
        }

        for(std::map<int,std::vector<cv::Point> >::iterator itr = temp_map.begin(); itr != temp_map.end(); itr++)
        {
            if((int)itr->second.size() > min_size)
            {
                labels.push_back(itr->second);
            }
        }
        retVal = NO_ERRORS;
    }
    return retVal;
}
