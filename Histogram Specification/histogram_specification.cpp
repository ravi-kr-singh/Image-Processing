#include<iostream>
#include<string>
#include<opencv2/core/core.hpp>
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

    Mat img_a=imread("input_img1.jpg",IMREAD_GRAYSCALE);
    Mat img_b=imread("input_img2.jpg",IMREAD_GRAYSCALE);

    int freq_a[256]={0};
    int freq_b[256]={0};
    int freq_final_img[256]={0};

    for(int i=0;i<img_a.rows;i++){
        for(int j=0;j<img_a.cols;j++)
            freq_a[int(img_a.at<uchar>(i,j))]++;
    }
    draw_histogram(freq_a,"Histogram of Image 1 :");

    for(int i=0;i<img_b.rows;i++){
        for(int j=0;j<img_b.cols;j++)
            freq_b[int(img_b.at<uchar>(i,j))]++;
    }
    draw_histogram(freq_b,"Histogram of Image 2 : ");

    for(int i=1;i<256;i++){
        freq_a[i]+=freq_a[i-1];
        freq_b[i]+=freq_b[i-1];
    }
    int level_map[255];

    int t=0;
    for(int i=0;i<256;i++){
        while(t<256 && freq_b[t]<freq_a[i]){
            t++;
        }
        level_map[i]=t;
    }


    Mat output_img(img_a.size(),CV_8UC1);
    for(int i=0;i<img_a.rows;i++){
        for(int j=0;j<img_a.cols;j++){
            output_img.at<uchar>(i,j)=level_map[int(img_a.at<uchar>(i,j))];
        }
    }

    for(int i=0;i<output_img.rows;i++){
        for(int j=0;j<output_img.cols;j++)
            freq_final_img[int(output_img.at<uchar>(i,j))]++;
    }
    draw_histogram(freq_final_img,"Histogram of final image : ");

    imshow("Img 1 : ",img_a);
    imshow("Img 2 : ",img_b);
    imshow("Img 1 after histogram matching to img 2: ",output_img);
    waitKey(0);
}




