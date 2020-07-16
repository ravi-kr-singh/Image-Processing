
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(){

    Mat main_image=imread("input.jpg",IMREAD_GRAYSCALE);
    Mat watermark=imread("watermark.png",IMREAD_GRAYSCALE);
    Mat watermarked_image(main_image.size(),CV_8UC1);

    double alpha = 0.1;
    double beta = 1 - alpha;

    for(int i=0;i<main_image.rows;i++){
        for(int j=0;j<main_image.cols;j++){
            watermarked_image.at<uchar>(i,j)=alpha*int(watermark.at<uchar>(i,j))+beta*int(main_image.at<uchar>(i,j));
        }
    }

    imshow("Input Image : ",main_image);
    imshow("Watermark : ",watermark);
    imshow("Input image after watermarking : ",watermarked_image);
    waitKey(0);

    return 0;
}
