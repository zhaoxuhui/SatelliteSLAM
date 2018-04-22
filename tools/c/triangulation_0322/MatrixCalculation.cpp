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
#include <math.h>

using namespace std;
using namespace cv;

vector<double> R2RPY(Mat R)
{
  double r11 = R.at<double>(0,0);
  double r12 = R.at<double>(0,1);
  double r13 = R.at<double>(0,2);
  double r21 = R.at<double>(1,0);
  double r22 = R.at<double>(1,1);
  double r23 = R.at<double>(1,2);
  double r31 = R.at<double>(2,0);
  double r32 = R.at<double>(2,1);
  double r33 = R.at<double>(2,2);
  
  double beta = atan2(-r31,sqrt(pow(r11,2)+pow(r21,2)));
  double alpha;
  double sigma;
  if(beta>=-90 && beta <=90)
  {
    alpha = atan2(r21,r11);
    sigma = atan2(r32,r33);
  }
  else if(beta>=90 && beta <=270)
  {
    alpha = atan2(-r21,-r11);
    sigma = atan2(-r32,-r33);
  }
  
  vector<double> res;
  res.push_back(beta);
  res.push_back(alpha);
  res.push_back(sigma);
  return res;
}


vector<double> R2RPY2(Mat R)
{
  double r11 = R.at<double>(0,0);
  double r12 = R.at<double>(0,1);
  double r13 = R.at<double>(0,2);
  double r21 = R.at<double>(1,0);
  double r22 = R.at<double>(1,1);
  double r23 = R.at<double>(1,2);
  double r31 = R.at<double>(2,0);
  double r32 = R.at<double>(2,1);
  double r33 = R.at<double>(2,2);
  
  double Omega = asin(-r23);
  double cosOmega = cos(Omega);
  double Phi = atan2(r13*cosOmega,r33*cosOmega);
  double Kappa = atan2(r21*cosOmega,r22*cosOmega);
  
  vector<double> res;
  res.push_back(Phi);
  res.push_back(Kappa);
  res.push_back(Omega);
  return res;
}

vector<double> R2Q4(Mat R)
{
  double r11 = R.at<double>(0,0);
  double r12 = R.at<double>(0,1);
  double r13 = R.at<double>(0,2);
  double r21 = R.at<double>(1,0);
  double r22 = R.at<double>(1,1);
  double r23 = R.at<double>(1,2);
  double r31 = R.at<double>(2,0);
  double r32 = R.at<double>(2,1);
  double r33 = R.at<double>(2,2);
  
  double qw = 0.5*sqrt(1+r11+r22+r33);
  double qx = (r32-r23)/(4*qw);
  double qy = (r13-r31)/(4*qw);
  double qz = (r21-r12)/(4*qw);
  
  vector<double> res;
  res.push_back(qx);
  res.push_back(qy);
  res.push_back(qz);
  res.push_back(qw);
  
  return res;
  
}

Mat calcFunMatrix(vector<vector<Point2f>> res)
{
  vector<Point2f> points1;
  vector<Point2f> points2;
  points1 = res[0];
  points2 = res[1];
  Mat fundamental_matrix;
  fundamental_matrix = findFundamentalMat(points1,points2,CV_FM_8POINT);
  return fundamental_matrix;
}

Mat calcFunMatrix2(vector<Point2f> points1,vector<Point2f> points2)
{
  Mat fundamental_matrix;
  fundamental_matrix = findFundamentalMat(points1,points2,CV_FM_8POINT);
  return fundamental_matrix;
}

Mat calcHomoMatrix(vector<vector<Point2f>> res)
{
  vector<Point2f> points1;
  vector<Point2f> points2;
  points1 = res[0];
  points2 = res[1];
  Mat homography_matrix;
  homography_matrix = findHomography(points2,points1,RANSAC,3,noArray(),2000,0.99);
  return homography_matrix;
}

Mat calcHomoMatrix2(vector<Point2f> points1,vector<Point2f> points2)
{
  Mat homography_matrix;
  homography_matrix = findHomography(points2,points1,RANSAC,3,noArray(),2000,0.99);
  return homography_matrix;
}

Mat calcEssentialMatrix(vector<vector<Point2f>> res,double dx,double dy,double f)
{
  Point2d principal_point(dx,dy);
  Mat essential_matrix;
  vector<Point2f> points1;
  vector<Point2f> points2;
  points1 = res[0];
  points2 = res[1];
  essential_matrix = findEssentialMat(points1,points2,f,principal_point,RANSAC);
  return essential_matrix;
}

Mat calcEssentialMatrix2(vector<Point2f> points1,vector<Point2f> points2,double dx,double dy,double f)
{
  Point2d principal_point(dx,dy);
  Mat essential_matrix;
  essential_matrix = findEssentialMat(points1,points2,f,principal_point,RANSAC);
  return essential_matrix;
}

void get_homos(vector<vector<string>> results)
{ 
  char save[512];
  vector<string> paths = results[1];
  vector<string> names = results[0];
  for(int i=0;i<paths.size()-1;i++)
  {
    Mat homo;
    homo = calcHomoMatrix(getMatchPoints(paths[i],paths[i+1]));
    cout<<"第"<<i+1<<"次匹配： "<<names[i]<<" & "<<names[i+1];
    cout<<endl;
    cout<<homo<<endl;
  }
}

vector<Mat> get_essens(vector<vector<string>> results,double dx,double dy,double f)
{ 
  char save[512];
  vector<string> paths = results[1];
  vector<string> names = results[0];
  vector<Mat> essentials;
  for(int i=0;i<paths.size()-1;i++)
  {
    Mat essential_matrix;
    essential_matrix = calcEssentialMatrix(getMatchPoints(paths[i],paths[i+1]),dx,dy,f);
    cout<<"第"<<i+1<<"次匹配： "<<names[i]<<" & "<<names[i+1];
    cout<<endl;
    cout<<essential_matrix<<endl;
    essentials.push_back(essential_matrix);
  }
  return essentials;
}

vector<vector<Mat>> getRt(vector<string> paths,double dx,double dy,double f)
{
  vector<vector<Point2f>> points;
  Point2f point(dx,dy);
  vector<vector<Mat>> res;
  vector<Mat> Rs;
  vector<Mat> ts;
  Mat essential_matrix;
  Mat fun_matrix;
  Mat homo_matrix;
  for(int i=0;i<paths.size()-1;i++)
  {
    cout<<endl<<"第"<<i+1<<"次匹配： "<<getIndex(paths[i])<<" & "<<getIndex(paths[i+1])<<"  "<<endl;
    points = getMatchPoints(paths[i],paths[i+1]);
    essential_matrix = calcEssentialMatrix(points,dx,dy,f);
    fun_matrix = calcFunMatrix(points);
    homo_matrix = calcHomoMatrix(points);
    Mat R,t;
    recoverPose(essential_matrix,points[0],points[1],R,t,f,point);
    cout<<"essential_matrix"<<endl<<essential_matrix<<endl;
    cout<<"fundamental_matrix"<<endl<<fun_matrix<<endl;
    cout<<"homography_matrix"<<endl<<homo_matrix<<endl;
    cout<<"R"<<endl<<R<<endl;
    cout<<"t"<<endl<<t<<endl;
    Rs.push_back(R);
    ts.push_back(t);
  }
  res.push_back(Rs);
  res.push_back(ts);
  return res;
}

void getRtForEval2(string path1,string path2,double dx,double dy,double f,Mat &R,Mat &t,vector<Point2f> &points1,vector<Point2f> &points2,Mat &ess,Mat &homo,Mat &fun)
{
  Point2f point(dx,dy);

  vector<vector<Point2f>> points = getMatchPoints(path1,path2);
  points1 = points[0];
  points2 = points[1];
  ess = calcEssentialMatrix(points,dx,dy,f);
  fun = calcFunMatrix(points);
  homo = calcHomoMatrix(points);
  recoverPose(ess,points[0],points[1],R,t,f,point);
  return;
}

void getRtForEval3(string path1,string path2,double dx,double dy,double f,Mat &R,Mat &t,vector<Point2f> &points1,vector<Point2f> &points2,vector<KeyPoint> &keys1,vector<KeyPoint> &keys2,Mat &ess,Mat &homo,Mat &fun,vector<DMatch> &matches)
{
  Point2f point(dx,dy);

  getMatch2(path1,path2,points1,points2,keys1,keys2,matches);
  ess = calcEssentialMatrix2(points1,points2,dx,dy,f);
  
  fun = calcFunMatrix2(points1,points2);
  homo = calcHomoMatrix2(points1,points2);
  recoverPose(ess,points1,points2,R,t,f,point);
  return;
}

void getRtForEval(string path1,string path2,double dx,double dy,double f,Mat &R,Mat &t,vector<Point2f> &points1,vector<Point2f> &points2)
{
  Point2f point(dx,dy);
  Mat essential_matrix;
  Mat fun_matrix;
  Mat homo_matrix;
//   cout<<endl<<"匹配： "<<getIndex(path1)<<" & "<<getIndex(path2)<<"  "<<endl;
  vector<vector<Point2f>> points = getMatchPoints(path1,path2);
  points1 = points[0];
  points2 = points[1];
  essential_matrix = calcEssentialMatrix(points,dx,dy,f);
  fun_matrix = calcFunMatrix(points);
  homo_matrix = calcHomoMatrix(points);
  recoverPose(essential_matrix,points[0],points[1],R,t,f,point);
//   cout<<"essential_matrix"<<endl<<essential_matrix<<endl;
//   cout<<"fundamental_matrix"<<endl<<fun_matrix<<endl;
//   cout<<"homography_matrix"<<endl<<homo_matrix<<endl;
//   cout<<"R"<<endl<<R<<endl;
//   cout<<"t"<<endl<<t<<endl;
  return;
}

void get_funs(vector<vector<string>> results)
{ 
  char save[512];
  vector<string> paths = results[1];
  vector<string> names = results[0];
  for(int i=0;i<paths.size()-1;i++)
  {
    Mat fun;
    fun = calcFunMatrix(getMatchPoints(paths[i],paths[i+1]));
    cout<<"第"<<i+1<<"次匹配： "<<names[i]<<" & "<<names[i+1];
    cout<<endl;
    cout<<fun<<endl;
  }
}

void reconstruct(Mat& K, Mat& R, Mat& T, vector<Point2f>& p1, vector<Point2f>& p2, Mat& structure)
{
    //两个相机的投影矩阵[R T]，triangulatePoints只支持float型
    Mat proj1(3, 4, CV_32FC1);
    Mat proj2(3, 4, CV_32FC1);

    proj1(Range(0, 3), Range(0, 3)) = Mat::eye(3, 3, CV_32FC1);
    proj1.col(3) = Mat::zeros(3, 1, CV_32FC1);

    R.convertTo(proj2(Range(0, 3), Range(0, 3)), CV_32FC1);
    T.convertTo(proj2.col(3), CV_32FC1);

    Mat fK;
    K.convertTo(fK, CV_32FC1);
    proj1 = fK*proj1;
    proj2 = fK*proj2;

    //三角化重建
    triangulatePoints(proj1, proj2, p1, p2, structure);
}