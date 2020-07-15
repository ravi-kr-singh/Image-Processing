
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

void filter(Mat& input_img,Mat& output_img){
    for(int i=0;i<output_img.rows;i++){
        for(int j=0;j<output_img.cols;j++){

            if(i>=1 && i<output_img.rows-1 && j>=1 && j<output_img.cols-1){
                int temp=0;
                for(int a=0;a<3;a++){
                    for(int b=0;b<3;b++){
                        temp+=int(input_img.at<uchar>(i-1+a,j-1+b));
                    }
                }
                temp/=9;
                output_img.at<uchar>(i,j)=temp;
            }
            else
                output_img.at<uchar>(i,j)=input_img.at<uchar>(i,j);

        }
    }
}

int main(){
    Mat noisy_img= imread("input_img.png",IMREAD_GRAYSCALE);
    Mat clear_img(noisy_img.size(),CV_8UC1);
    filter(noisy_img,clear_img);
    imshow("Noisy Image : ",noisy_img);
    imshow("Arithmetic mean filtered image : ",clear_img);
    waitKey(0);

}
