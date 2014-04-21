/////////////////////////////////////////////////////////////////////
//                                                                 //
//      File Name: cannyEdgeDetector.cpp                           //
//      File Type: C++ source                                      //
//      Auther: Asanka Wickramasinghe                              //
//      Project: Image Processing CV               //
//      Module: Image Processing Library (ImageProcCV)            //
//      Date Created: 2012 - Mar                                   //
//                                                                 //
/////////////////////////////////////////////////////////////////////
#include "ImageProcCV.h"


int ImageProcCV::cannyEdgeDetector(cv::Mat &_input, cv::Mat &_output, double sigma)
{   
    //in this function input verifications are not done. user should make sure to
    //send valid input parameters.

    //setting parameters
    int retVal = NO_ERRORS;
    double nonEdgePixelsRatio = 0.7;
    double thresholdRatio = 0.4;

    //preparing input and output
    cv::Mat& input = _input, &output = _output;

    output = cv::Mat::zeros(input.size(),CV_8UC1);

    //making input [0 1]
    cv::Mat Input;
    retVal = imageNormalize(input,Input);
    if ( retVal < 0)
    {
        return retVal;
    }

    //step 1: getting gaussian filterd image
        //preparing gaussian kernal w.r.t the sigma value
    int width = 0;
    double ssq = sigma*sigma;
    for(int i = 1; i<31; i++)
    {
        double temp = std::exp(-0.5*(i*i)/ssq);
        if(temp > 0.0001)
        {
            width = i;
        }
        else
        {
            break;
        }
    }
    if(width == 0)//too small sigma value
        width = 1;

    width = width*2 +1;
    double gausData[width];
    for(int i = 0; i < width; i++ )
    {
        //double x = i - (8)*0.5;
        double x = i-((width - 1)/2);
        double t = std::exp(-0.5*(x*x)/(ssq));
         t /= (2*ssq*M_PI);
         gausData[i] = t ;
    }

    cv::Mat kernel(1,width,CV_64F,gausData);
    cv::Mat kernelTr; // transpose
    cv::transpose(kernel,kernelTr);

    //making gaussian smothing
    cv::Mat gaussOutput;
    try
    {
        cv::sepFilter2D(Input,gaussOutput,CV_64FC1,kernel,kernelTr,cv::Point(-1,-1),0,
                        cv::BORDER_REPLICATE);
    }
    catch (cv::Exception& e)
    {
        retVal = EXCEPTION_OCCURED;
        return retVal;
    }

    //std::cout << gaussOutput << std::endl;

    //step 2: getting derivatives along x and y axis and their magnitudes
        //preparing gaussian 2D kernels. we use a derivative of gaussian kernal
    double dataGauss2D[width][width];
    for(int i = 0; i< 9; i++)
    {
        double x = i-((width - 1)/2);
        for(int j = 0; j<width; j++)
        {
            double y = j-((width - 1)/2);
            double t =  x*(std::exp(-0.5*(x*x + y*y)/(ssq)));
            t /= (M_PI*ssq);
            dataGauss2D[j][i] = t;
        }
    }
    cv::Mat gauss2D(width,width,CV_64F,&dataGauss2D);

    cv::Mat gauss2DTr;
    cv::transpose(gauss2D,gauss2DTr);
    //std::cout << gauss2D << std::endl;
    cv::Mat ax(gaussOutput.size(),gaussOutput.type()),ay(gaussOutput.size(),gaussOutput.type());
    try
    {
    cv::Ptr<cv::FilterEngine> horizontal = cv::createLinearFilter(CV_64FC1,CV_64FC1,gauss2D,cv::Point(-1,-1),
                                                                  0,cv::BORDER_REPLICATE,-1,cv::Scalar(0));
    cv::Ptr<cv::FilterEngine> vertical = cv::createLinearFilter(CV_64FC1,CV_64FC1,gauss2DTr,cv::Point(-1,-1),
                                                                  0,cv::BORDER_REPLICATE,-1,cv::Scalar(0));
    horizontal->apply(gaussOutput,ax);
    vertical->apply(gaussOutput,ay);
    }
    catch (cv::Exception& e)
    {
        retVal = EXCEPTION_OCCURED;
        return retVal;
    }
    /*cv::filter2D(gaussOutput,ax,CV_64FC1,gauss2D,cv::Point(-1,-1),0,cv::BORDER_REPLICATE);
    cv::filter2D(gaussOutput,ay,CV_64FC1,gauss2DTr,cv::Point(-1,-1),0,cv::BORDER_REPLICATE);*/
    //std::cout << ax << std::endl;

    //step 3: calculating gradient magnitudes and sorting edge angles;
        //this implementation is from Matlab edge(canny) function. In newer Matlab versions, the
        //function is called as edge(canny_old)

    cv::Mat mag = cv::Mat::zeros(ax.size(),CV_64F);
    cv::Mat angles = cv::Mat::zeros(ax.size(), CV_32S);

    for(int i = 0; i < ax.rows; i++)
    {
        double *_ax = ax.ptr<double>(i),
                *_ay = ay.ptr<double>(i),
                *_mag = mag.ptr<double>(i);
        int *_angles = angles.ptr<int>(i);
        for(int j = 0; j < ax.cols; j++)
        {

            _mag[j] = std::sqrt(_ax[j]*_ax[j] + _ay[j]*_ay[j]);
            if(((_ay[j] <=0) && (_ax[j]>-1*_ay[j]))  || ((_ay[j]>=0) && (_ax[j]<-1*_ay[j])))
                _angles[j] = 1;
            else if(((_ax[j]>0) && (-1*_ay[j]>=_ax[j]))  || ((_ax[j]<0) && (-1*_ay[j]<=_ax[j])))
                _angles[j] = 2;
            else if(((_ax[j]<=0) && (_ax[j]>_ay[j])) || ((_ax[j]>=0) && (_ax[j]<_ay[j])))
                _angles[j] = 3;
            else if(((_ay[j]<0) && (_ax[j]<=_ay[j])) || ((_ay[j]>0) && (_ax[j]>=_ay[j])))
                _angles[j] = 4;
        }
    }

    double max_mag = *std::max_element(mag.begin<double>(),mag.end<double>());
    if(max_mag > 0)
        for(cv::MatIterator_<double> itt = mag.begin<double>(); itt != mag.end<double>(); itt++)
            *itt = *itt / max_mag;

    //std::cout << mag << std::endl;
    int hist[64];
    memset(hist,0,sizeof(hist));
    for(cv::MatIterator_<double> itt = mag.begin<double>(); itt != mag.end<double>(); itt++)
    {

        int pos = std::floor((*itt) * 64  + 0.5);//matlab always do round up
        hist[pos]++;
    }

    int value = std::floor(mag.rows*mag.cols*nonEdgePixelsRatio + 0.5);
    int count = 0;
    double highThreshold = -1;
    for(size_t t = 0 ; t < 64; t++)
    {
        count += hist[t];
        if(count > value)
        {
            highThreshold = (t+1)/(float)64;
            break;
        }
    }

    double lowThreshold = highThreshold*thresholdRatio;

    //ste 4: non maxima suppression
    std::vector<cv::Point> strongPoints;
    for(int i = 0; i < angles.rows; i++)
    {
        int *_angles = angles.ptr<int>(i);
        double *_mag = mag.ptr<double>(i),
                *_mag_up = mag.ptr<double>(i-1),
                *_mag_down = mag.ptr<double>(i+1);
         double  *_ax = ax.ptr<double>(i),
                *_ay = ay.ptr<double>(i);
        uchar *_output = output.ptr<uchar>(i);

        for(int j =0; j < angles.cols; j++)
        {
            if (!((i==0) || (j == 0) || (i == (angles.rows -1)) || (j == (angles.cols -1)))) //excluding exterior pixels
            {
                double grad1, grad2,grad;
                double d;
                switch (_angles[j])
                {
                case 1:
                    //grad1 = _mag[j+1];
                    //grad2 = _mag[j-1];
                    d = std::abs(_ay[j]/_ax[j]);
                    grad1 = _mag[j+1]*(1-d)+_mag_up[j+1]*d  ;
                    grad2 = _mag[j-1]*(1-d)+_mag_down[j-1]*d;
                    grad = _mag[j];
                    if((grad >= grad1) && (grad >= grad2) && (grad > lowThreshold))
                    {
                        _output[j] = 0xff;
                        if(grad > highThreshold)
                            strongPoints.push_back(cv::Point(j,i));
                    }
                    break;
                case 2:
                    //grad1 = _mag_up[j-1];
                    //grad2 = _mag_down[j+1];
                    d = std::abs(_ax[j]/_ay[j]);
                    grad1 = _mag_up[j]*(1-d)+_mag_up[j+1]*d;
                    grad2 = _mag_down[j]*(1-d) + _mag_down[j-1]*d;
                    grad = _mag[j];
                    if((grad >= grad1) && (grad >= grad2) && (grad > lowThreshold))
                    {
                        _output[j] = 0xff;
                        if(grad > highThreshold)
                            strongPoints.push_back(cv::Point(j,i));
                    }
                    break;
                case 3:
                    //grad1 = _mag_up[j];
                    //grad2 = _mag_down[j];
                    d = std::abs(_ax[j]/_ay[j]);
                    grad1 = _mag_up[j]*(1-d) + _mag_up[j-1]*d;
                    grad2 = _mag_down[j]*(1-d) + _mag_down[j+1]*d;
                    grad = _mag[j];
                    if((grad >= grad1) && (grad >= grad2) && (grad > lowThreshold))
                    {
                        _output[j] = 0xff;
                        if(grad > highThreshold)
                            strongPoints.push_back(cv::Point(j,i));
                    }
                    break;
                case 4:
                    //grad1 = _mag_up[j+1];
                    //grad2 = _mag_down[j-1];
                    d = std::abs(_ay[j]/_ax[j]);
                    grad1 = _mag[j-1]*(1-d) + _mag_up[j-1]*d;
                    grad2 = _mag[j+1]*(1-d) + _mag_down[j+1]*d;
                    grad = _mag[j];
                    if((grad >= grad1) && (grad >= grad2) && (grad > lowThreshold))
                    {
                        _output[j] = 0xff;
                        if(grad > highThreshold)
                            strongPoints.push_back(cv::Point(j,i));
                    }
                    break;

                }
            }

        }

    }

    //step 5: trace edges as per matlab implementation
    std::vector<std::vector<cv::Point> > labels;
    cv::Mat label_out;
    bwLabel(output,label_out,labels,0,true);

    //loop via all labels to check if they include at least one point in strongPoints.
    std::vector<std::vector<cv::Point> > strongLabel;

    /*for(std::vector<cv::Point>::iterator points_itr = strongPoints.begin();
        points_itr != strongPoints.end(); points_itr++)
    {
        cv::Point pp = *points_itr;
        std::vector<cv::Point> selectedLabel;

        bwSelect(labels,pp,selectedLabel);

        if(selectedLabel.size() != 0)
        {
            strongLabel.push_back(selectedLabel);
        }
    }*/

    for(std::vector<std::vector<cv::Point> >::iterator it = labels.begin(); it != labels.end(); it++)
    {
        for(std::vector<cv::Point>::iterator inner = (*it).begin(); inner != (*it).end(); inner++)
        {
            bool found = false;
            for(std::vector<cv::Point>::iterator points_itr = strongPoints.begin()
                ;points_itr != strongPoints.end(); points_itr++)
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
    }


    cv::Mat output1 = cv::Mat::zeros(output.size(),output.type());

    for(std::vector<std::vector<cv::Point> >::iterator it = strongLabel.begin(); it != strongLabel.end(); it++)
    {
        for(std::vector<cv::Point>::iterator inner = (*it).begin(); inner != (*it).end(); inner++)
        {

            output1.at<uchar>(*inner) = 0xff;
        }
    }
     bwThin(output1,output,1);
     retVal = NO_ERRORS;
     return retVal;

}
