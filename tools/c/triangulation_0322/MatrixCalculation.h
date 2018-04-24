#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <dirent.h>//遍历系统指定目录下文件要包含的头文件
#include <string>
#include "ORBMatching.h"
#include "common.h"

using namespace std;
using namespace cv;

Mat calcFunMatrix(vector<vector<Point2f>> res);
Mat calcHomoMatrix(vector<vector<Point2f>> res);
Mat calcEssentialMatrix(vector<vector<Point2f>> res,double dx,double dy,double f);
void get_homos(vector<vector<string>> results);
vector<Mat> get_essens(vector<vector<string>> results,double dx,double dy,double f);
vector<vector<Mat>> getRt(vector<string> results,double dx,double dy,double f);
void getRtForEval(string path1,string path2,double dx,double dy,double f,Mat &R,Mat &t,vector<Point2f> &points1,vector<Point2f> &points2);
void getRtForEval2(string path1,string path2,double dx,double dy,double f,Mat &R,Mat &t,vector<Point2f> &points1,vector<Point2f> &points2,Mat &ess,Mat &homo,Mat &fun);
void getRtForEval3(string path1,string path2,double dx,double dy,double f,Mat &R,Mat &t,vector<Point2f> &points1,vector<Point2f> &points2,vector<KeyPoint> &keys1,vector<KeyPoint> &keys2,Mat &ess,Mat &homo,Mat &fun,vector<DMatch> &matches);
void getRtForEvalOutput(string path1,string path2,double dx,double dy,double f,Mat &R,Mat &t,vector<Point2f> &points1,vector<Point2f> &points2);
void get_funs(vector<vector<string>> results);
Mat calcFunMatrix2(vector<Point2f> points1,vector<Point2f> points2);
Mat calcHomoMatrix2(vector<Point2f> points1,vector<Point2f> points2);
Mat calcEssentialMatrix2(vector<Point2f> points1,vector<Point2f> points2,double dx,double dy,double f);
void reconstruct(Mat& K, Mat& R, Mat& T, vector<Point2f>& p1, vector<Point2f>& p2, Mat& structure);
vector<double> R2RPY(Mat R);
vector<double> R2RPY2(Mat R);
vector<double> R2Q4(Mat R);