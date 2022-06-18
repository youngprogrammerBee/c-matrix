#include <opencv2/opencv.hpp>
#include "matrix.cpp"
using namespace std;
// # define _GLIBCXX_USE_CXX11_ABI 0
int main()
{   matrix<int>temp(3,3);
    int cnt=1;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            temp.set(i,j,cnt++);
        }
        
    }
    cv::Mat a1=convert_toCV(temp);
    cout<<"Transfer matrix to CV matrix\n";
    cout<<a1;

cv::Mat me = cv::Mat::eye(cv::Size(5,5),CV_32FC1);;//单通道
 matrix<int>t=convert_FromCV<int>(me);
 cout<<"Transfer CV matrix to matrix\n";
 for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
           cout<<t.get(i,j)<<" ";
        }
        cout<<endl;
    }
return 0;
}
//g++ -o test test.cpp

