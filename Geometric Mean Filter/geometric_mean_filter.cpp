#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<cmath>
#include<algorithm>

using namespace std;
using namespace cv;

void filter(Mat& input_img,Mat& output_img){

    for(int i=0;i<input_img.rows;i++){
        for(int j=0;j<input_img.cols;j++){
            if(i>0 && i<input_img.rows-1 && j>0 && j<input_img.cols-1){
                unsigned long long temp=1;
                int t1=-1,t2=-1;
                for(int a=0;a<9;a++){
                    temp*=int(input_img.at<uchar>(i+t2,j+t1));
                    t1++;
                    if(t1==2){
                        t1=-1;
                        t2++;
                    }
                }

                temp=pow(temp,(1.0/9.0));

                output_img.at<uchar>(i,j)=temp;
            }
            else{
                output_img.at<uchar>(i,j)=127;
                input_img.at<uchar>(i,j)=127;
            }
        }
    }
}

int main(){
    Mat noisy_img= imread("input_img.jpg",IMREAD_GRAYSCALE);
    Mat clear_img(noisy_img.size(),CV_8UC1);
    filter(noisy_img,clear_img);
    imshow("Noisy image : ",noisy_img);
    imshow("After Geometric mean filtering : ",clear_img);
    waitKey(0);

}
