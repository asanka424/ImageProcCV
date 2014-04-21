#include <ImageProcCV.h>

bool removeFT(cv::Vec2i gl_1,cv::Vec2i gl, cv::Vec2i fi, int hl_1, int hl, int x, int y);
void voronoiFT(cv::Mat &_feat, int i, int undef);
int delta(int p1, int p2);

int ImageProcCV::ssedTransform(cv::Mat &_input, cv::Mat &_feature_transform)
{
    cv::Mat& input = _input;
    int retVal = NO_ERRORS;
    if (input.type() != CV_8UC1)
    {
        retVal = INV_IMG_TYPE;
        return retVal;
    }
    cv::Mat& feat = _feature_transform;
    feat = cv::Mat::zeros(input.rows,input.cols,CV_32SC2);

    //defining undef
    int undef = (input.rows > input.cols)?input.rows:input.cols;
    undef++;

    //creating Fo(X)
    /*for(int i = 0; i < input.rows; i++)
    {
        uchar *_input_ = input.ptr<uchar>(i);
        cv::Vec2i *_feat_out = feat.ptr<cv::Vec2i>(i);

        for(int j = 0; j < input.cols; j++)
        {
            if(_input_[j] == 0xff)
            {
                _feat_out[j][0] = j;
                _feat_out[j][1] = i;
            }
            else
            {
                _feat_out[j][0] = undef;
                _feat_out[j][1] = undef;
            }
        }
    }*/
    //std::cout << feat << std::endl;
    //creating F1(X)

    for(int i = 0; i < input.rows; i++)
    {
        uchar *_input_ = input.ptr<uchar>(i);
        cv::Vec2i *_feat_out = feat.ptr<cv::Vec2i>(i);
        int pos = -1;
        //First pass
        for(int j = 0; j < input.cols; j++)
        {
            //if((_feat_out[j][0] != undef) || (_feat_out[j][1] != undef))
            if(_input_[j] == 0x00)
            {
                pos = j;
                _feat_out[j][0] = j;
                _feat_out[j][1] = i;
                //_value[x] = 0.0f;
            }
            else if( pos >= 0)
            {
                //int tmp = pos -j;
                _feat_out[j][0] = pos;
                _feat_out[j][1] = i;
            }
            else
            {
                _feat_out[j][0] = undef;
                _feat_out[j][1] = undef;
            }
        }

        if(pos == -1) continue;
        else //reverse pass
        {
            pos = -1;
            for(int j = input.cols-1 ; j >=0; j--)
            {

               // if((_feat_out[j][0] != undef) || (_feat_out[j][1] != undef))
                if(_input_[j] == 0x00)
                {
                    pos = j;
                    _feat_out[j][0] = j;
                    _feat_out[j][1] = i;
                    //_value[x] = undef;
                }
                else if (pos != -1)
                {
                    int tmp = pos - j;
                    //int tmp2 = tmp;
                    tmp *= tmp;
                    int ret = (_feat_out[j][0] -j) * (_feat_out[j][0] - j);
                    if((ret > tmp) || (ret == -1))
                    {

                        _feat_out[j][0] = pos;
                        _feat_out[j][1] = i;
                    }
                }
            }
        }
    }
    //std::cout << feat << std::endl;
    //creating F(X)
    for(int i = 0; i < input.cols; i++)
    {
        voronoiFT(feat,i,undef);
    }
    //std::cout << feat << std::endl;
    //getting relative positions and seed point
    //double max_distance = -1;
    for(int i = 0; i < feat.rows; i++)
    {
        cv::Vec2i* _feat_out = feat.ptr<cv::Vec2i>(i);
        for(int j = 0; j < feat.cols; j++)
        {
            int xcor = _feat_out[j][0];
            int ycor = _feat_out[j][1];
            _feat_out[j][0] = xcor - j;
            _feat_out[j][1] = ycor - i;
           /* double dis = cv::norm(_feat_out[j]);
            if(dis > max_distance)
            {
                max_distance = dis;
                seed = cv::Point(j,i);
            }*/
        }
    }
    return retVal;
    //std::cout << feat << std::endl;



}
void voronoiFT(cv::Mat& _feat, int i,int undef)
{
    cv::Mat& feat = _feat;

    int l = -1;
    cv::Vec2i fi;
    std::vector<cv::Vec2i> g(feat.rows);
    std::vector<int> h(feat.rows);
    int x0 = i,x1;
    for(x1 = 0; x1 < feat.rows; ++x1)
    {
        fi = feat.at<cv::Vec2i>(x1,x0);
        if((fi[0] != undef) || (fi[1] != undef))
        {
            if (l < 1)
            {
                l++;
                g[l] = fi;
                h[l] = x1;
            }
            else
            {
                while((l >=1 ) && removeFT(g[l-1],g[l],fi,h[l-1],h[l],x0,x1))
                {
                    l--;
                }
                l++;
                g[l] = fi;
                h[l] = x1;
            }
        }
    }
    if(l == -1) return;

    int ns = l;
    l=0;
    for(x1 = 0; x1 < feat.rows; ++x1)
    {
        //cv::Vec2i xi = feat.at<cv::Vec2i>(x1,x0);
        int c1 = h[l] - x1;
        int c2 = h[l+1] -x1;
        int tmp1 = (g[l][0] - x0)*(g[l][0] - x0) + c1*c1;
        int tmp2 = (g[l+1][0] - x0)*(g[l+1][0] - x0) + c2*c2;
        while ((l < ns) && ( tmp1 > tmp2))
        {
            l++;
            c1 = h[l] - x1;
            c2 = h[l+1] -x1;
            tmp1 = (g[l][0] - x0)*(g[l][0] - x0) + c1*c1;
            tmp2 = (g[l+1][0] - x0)*(g[l+1][0] - x0) + c2*c2;
        }
        feat.at<cv::Vec2i>(x1,x0) = g[l];
    }

}

bool removeFT(cv::Vec2i u, cv::Vec2i v, cv::Vec2i w, int hl_1, int hl, int x, int y)
{
    //d th dimention is y direction
    int du = (u[0] - x)*(u[0] - x);
    int dv = (v[0] - x)*(v[0] - x);
    int dw = (w[0] - x)*(w[0] - x);
    int a = hl - hl_1;
    int b = y - hl;
    int c = y - hl_1;
    return ( (c * dv - b * du - a * dw) > (a * b * c) );


}

int delta(int p1, int p2)
{
    return (p1 - p2)*(p1-p2);
}
