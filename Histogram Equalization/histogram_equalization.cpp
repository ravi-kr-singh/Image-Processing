#include<iostream>
#include<string>
#include<opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

void draw_histogram(int* histogram,string winName){
    double max_val=histogram[0];
    for(int i=1;i<256;i++){
        if(histogram[i]>max_val)
            max_val=histogram[i];
    }
    Mat hist(512,512,CV_8U); //Each line will be 2pixel wide .Therefore 256*2=512

    hist.setTo(255);
    double factor=512.0/max_val;

    for(int i=0;i<256;i++){
        double temp=histogram[i];
        temp*=factor;
        Point pt1,pt2;
        pt1=Point(i*2,512);
        pt2=Point(i*2,512-int(temp));
        const Scalar col=Scalar(0,0,0);
        line(hist,pt1,pt2,col,2,CV_8S);
    }
    imshow(winName,hist);

}

int main(){

    Mat input_img=imread("input_img.jpg",IMREAD_GRAYSCALE);

    int freq[256]={0};
    int freq_final_img[256]={0};
    int total=input_img.rows*input_img.cols;

    for(int i=0;i<input_img.rows;i++){
        for(int j=0;j<input_img.cols;j++)
            freq[int(input_img.at<uchar>(i,j))]++;
    }

    draw_histogram(freq,"Histogram of Image 1 :");

    double temp[256];

    for(int i=0;i<256;i++)
        temp[i]=(double(freq[i]))/(double(total));  //PDF

    for(int i=1;i<256;i++)
        temp[i]+=temp[i-1];       //CDF

    for(int i=1;i<256;i++)
        temp[i]*=255.0;


    Mat output_img(input_img.size(),CV_8UC1);
    for(int i=0;i<input_img.rows;i++){
        for(int j=0;j<input_img.cols;j++){
            output_img.at<uchar>(i,j)=int(temp[int(input_img.at<uchar>(i,j))]);
        }
    }

    for(int i=0;i<output_img.rows;i++){
        for(int j=0;j<output_img.cols;j++)
            freq_final_img[int(output_img.at<uchar>(i,j))]++;
    }
    draw_histogram(freq_final_img,"Histogram of Final image : ");

    imshow("Before Histogram Equalization : ",input_img);
    imshow("After Histogram Equalization : ",output_img);
    waitKey(0);
}




