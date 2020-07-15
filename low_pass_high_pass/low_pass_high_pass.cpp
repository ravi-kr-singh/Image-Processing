#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

void filter(Mat& input_img,Mat& output_img,vector<vector<double>>&mask){
    for(int i=0;i<output_img.rows;i++){
        for(int j=0;j<output_img.cols;j++){

            if(i>=1 && i<output_img.rows-1 && j>=1 && j<output_img.cols-1){
                int temp=0;
                for(int a=0;a<3;a++){
                    for(int b=0;b<3;b++){
                        temp+=int(input_img.at<uchar>(i-1+a,j-1+b))*mask[a][b];
                    }
                }
                temp/=9;
                temp=min(max(0,temp),255);
                output_img.at<uchar>(i,j)=temp;
            }
            else
                output_img.at<uchar>(i,j)=input_img.at<uchar>(i,j);

        }
    }
}

int main(){
    Mat input_img= imread("input_img.jfif",IMREAD_GRAYSCALE);

    vector<vector<double>>low_pass_mask = {{1,1,1},
                                           {1,1,1},
                                           {1,1,1}};
    vector<vector<double>>high_pass_mask = {{-1,-1,-1},
                                           {-1,8,-1},
                                           {-1,-1,-1}};

    Mat output_low_pass(input_img.size(),CV_8UC1);
    Mat output_high_pass(input_img.size(),CV_8UC1);
    filter(input_img,output_low_pass,low_pass_mask);
    filter(input_img,output_high_pass,high_pass_mask);
    imshow("Original : ",input_img);
    imshow("Low pass filter : ",output_low_pass);
    imshow("High pass filter : ",output_high_pass);
    waitKey(0);

}
