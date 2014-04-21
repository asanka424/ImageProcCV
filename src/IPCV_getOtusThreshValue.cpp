#include <ImageProcCV.h>

int ImageProcCV::getOtsuThreshValue(cv::Mat &_src, double &threshold)
{
    int retVal = NO_ERRORS;

    if (_src.type() != CV_8UC1)
    {
        retVal = INV_IMG_TYPE;
        return retVal;
    }
    cv::Size size = _src.size();
    if( _src.isContinuous() )
    {
        size.width *= size.height;
        size.height = 1;
    }
    const int N = 256;
    int i, j, h[N] = {0};
    for( i = 0; i < size.height; i++ )
    {
        //const uchar* src = _src.data + _src.step*i;
        const uchar* psrc = _src.ptr<uchar>(i);
        for( j = 0; j <= size.width - 4; j += 4 )
        {
            int v0 = psrc[j], v1 = psrc[j+1];
            h[v0]++; h[v1]++;
            v0 = psrc[j+2]; v1 = psrc[j+3];
            h[v0]++; h[v1]++;
        }
        for( ; j < size.width; j++ )
            h[psrc[j]]++;
    }

    double mu = 0, scale = 1./(size.width*size.height);
    for( i = 0; i < N; i++ )
        mu += i*(double)h[i];

    mu *= scale;
    double mu1 = 0, q1 = 0;
    double max_sigma = 0, max_val = 0;

    for( i = 0; i < N; i++ )
    {
        double p_i, q2, mu2, sigma;

        p_i = h[i]*scale;
        mu1 *= q1;
        q1 += p_i;
        q2 = 1. - q1;

        if( std::min(q1,q2) < FLT_EPSILON || std::max(q1,q2) > 1. - FLT_EPSILON )
            continue;

        mu1 = (mu1 + i*p_i)/q1;
        mu2 = (mu - q1*mu1)/q2;
        sigma = q1*q2*(mu1 - mu2)*(mu1 - mu2);
        if( sigma > max_sigma )
        {
            max_sigma = sigma;
            max_val = i;
        }
    }
    threshold = max_val;
    return retVal;
}
