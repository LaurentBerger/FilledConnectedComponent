#include <opencv2/opencv.hpp> 
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace cv;
using namespace std;

vector<vector<Point> > contours;
vector<Vec4i> hierarchy;
vector<char> fillCtr;

    Mat c;

void DrawTree( int idx, int level)
{
    int i=idx;
    drawContours(c, contours, i, Scalar(i),CV_FILLED);
    fillCtr[i]=1;
    while (hierarchy[i][0]!=-1)
    {
        int j=hierarchy[i][0];
        if (fillCtr[j] == 0)
        {
            drawContours(c, contours, j, Scalar(j),CV_FILLED);
            fillCtr[j]=1;
            DrawTree(j,level);
        }
        i=hierarchy[i][0];
        
    }
    if (hierarchy[idx][2]!=-1)
        DrawTree(hierarchy[idx][2],level+1);
}

int main (int argc,char **argv)
{
    {
        Mat x = imread("C:/Users/Laurent.PC-LAURENT-VISI/Downloads/14415468805620458.jpg",CV_LOAD_IMAGE_GRAYSCALE);
        //Mat x = imread("f:/IMAGES/pic10.png",CV_LOAD_IMAGE_GRAYSCALE);
    imshow("original",x);
    Mat y;
    threshold(x,y,50,255,THRESH_BINARY);
    imshow("threshold",y);
    Mat yc;
    findContours(y,contours,hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
    c =Mat::zeros(x.size(),CV_16U);
   fillCtr.resize(contours.size());
   for( int i=0;i <contours.size();i++)
    {
       if (hierarchy[i][3] == -1 && fillCtr[i]==0)
       {
           DrawTree(i,0);
       }
    }

    imshow("contour",c);
    imwrite("contour.jpg",c);
    imwrite("contour.tif",c);
    waitKey(0);
    }

}

