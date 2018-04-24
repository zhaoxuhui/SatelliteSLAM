#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <dirent.h>//遍历系统指定目录下文件要包含的头文件
#include <string>

using namespace std;
using namespace cv;

string getIndex(string path);
vector<string> findFiles(string path);
Mat evalAccuarcy(string path1,string path2,double dx,double dy,double f);
Mat evalAccuarcyAndOutput(string path1,string path2,double dx,double dy,double f,string outputPath);
void evalAccuarcyAndOutput2(string path1,string path2,double dx,double dy,double f,string outputPath);
void evalAccuarcyAndOutput4(string path1,string path2,double dx,double dy,double f,string outputPath);
void evalAccuarcyAndOutput3(string path1,string path2,double dx,double dy,double f,string outputPath,double &pitch,double &yaw,double &roll);
Point2d pixel2cam( const Point2d& p, const Mat& K );
void cutBlankBorder(Mat inputIMG);
Mat matchingIMG2(Mat img1,Mat img2);
Mat matchingIMG(Mat img1,Mat img2);
Mat matching(string path_img1,string path_img2);
void test_orb(vector<vector<string>> results);
void test();
Mat eval(Mat t,Mat R);
void triangulation ( 
    const vector< KeyPoint >& keypoint_1, 
    const vector< KeyPoint >& keypoint_2, 
    const std::vector< DMatch >& matches,
    const Mat& R, const Mat& t, Mat K,
    vector< Point3d >& points);
void readData(string inputPath,vector<double> &UTC,vector<double> & X,vector<double> &Y,vector<double> &Z,vector<double> &Pitch,vector<double> &Yaw,vector<double> &Roll);
double Rad2Deg(double rad);
void evalAccuarcyAndOutput5(string path1,string path2,double dx,double dy,double f,string outputPath);