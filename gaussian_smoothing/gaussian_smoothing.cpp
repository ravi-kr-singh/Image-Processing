#include <iostream>
#include <cmath>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

#define pi     3.14159265358979323846

int normalisation_factor;

void mask_generator(vector<vector<double>>& mask,double& sigma){

    double t_sum = 0.0;

    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            double temp = sqrt((i-2)*(i-2)+(j-2)*(j-2));
            mask[i][j]=(exp(-(temp*temp)/(2.0*sigma*sigma)))/(pi*sigma*sigma*2.0);
            t_sum+=mask[i][j];
        }
    }

    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            mask[i][j]/=t_sum;

    double factor=mask[0][0];

    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++){
            mask[i][j]/=factor;
            mask[i][j]=floor(mask[i][j]);
            normalisation_factor+=mask[i][j];
        }
}

void gaussian_smoothing(Mat& input_img, Mat& output_img, vector<vector<double>>& mask){
    for(int i=0;i<output_img.rows;i++){
        for(int j=0;j<output_img.cols;j++){

            if(i>=2 && i<output_img.rows-2 && j>=2 && j<=output_img.cols-2){
                int temp=0;
                for(int a=0;a<5;a++){
                    for(int b=0;b<5;b++){
                        temp+=int(input_img.at<uchar>(i-2+a,j-2+b))*mask[a][b];
                    }
                }
                temp/=normalisation_factor;
                temp=min(max(0,temp),255);

                output_img.at<uchar>(i,j)=temp;
            }
            else
               output_img.at<uchar>(i,j)=input_img.at<uchar>(i,j);

        }
    }
}

int main(){

    Mat input_img = imread("input_img.jfif",IMREAD_GRAYSCALE);
    double sigma;
    cout<<"Enter sigma : ";
    cin>>sigma;

    vector<vector<double>> mask(5,vector<double>(5));
	mask_generator(mask,sigma);

    cout<<"5*5 Gaussian mask with sigma="<<sigma<<" :-"<<endl;
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            cout<<mask[i][j]<<"\t";
        }
        cout<<endl;
    }

    Mat output_img(input_img.size(),CV_8UC1);
    gaussian_smoothing(input_img,output_img,mask);
    imshow("Original : ",input_img);
    imshow("After Gaussian Smoothing : ",output_img);
    waitKey(0);
}




