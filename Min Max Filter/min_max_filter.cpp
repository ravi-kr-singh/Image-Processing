#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<climits>
#include<algorithm>

using namespace std;
using namespace cv;

void filter(Mat& input_img,Mat& output_img){

    for(int i=0;i<input_img.rows;i++){
        for(int j=0;j<input_img.cols;j++){
            if(i>0 && i<input_img.rows-1 && j>0 && j<input_img.cols-1){
                unsigned long long min_item=INT_MAX;
                unsigned long long max_item=INT_MIN;
                int t1=-1,t2=-1;
               for(int a=0;a<9;a++){
                    int value=int(input_img.at<uchar>(i+t2,j+t1));
                    if(value<min_item)
                        min_item=value;
                    if(value>max_item)
                        max_item=value;

                    t1++;
                    if(t1==2){
                        t1=-1;
                        t2++;
                    }

                }



                output_img.at<uchar>(i,j)=(min_item+max_item)/2;;
            }
            else{
                output_img.at<uchar>(i,j)=127;
                input_img.at<uchar>(i,j)=127;
            }
        }
    }
}

int main(){
    Mat noisy_img= imread("input_img.png",IMREAD_GRAYSCALE);
    Mat clear_img(noisy_img.size(),CV_8UC1);
    filter(noisy_img,clear_img);
    imshow("Noisy image : ",noisy_img);
    imshow("After Min - Max filter : ",clear_img);
    waitKey(0);

}
