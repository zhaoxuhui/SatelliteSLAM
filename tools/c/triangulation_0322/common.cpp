#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <dirent.h>//遍历系统指定目录下文件要包含的头文件
#include <string>
#include "MatrixCalculation.h"
#include <fstream>
#include <math.h>

# define PI 3.14159265358979323846

using namespace std;
using namespace cv;


string getIndex(string path)
{
  size_t found = path.rfind("/");
  string name = path.substr(found+1,35);
  string index;
  if(name.length()<26)
  {
    index = name;
  }
  else
  {
    index = name.substr(22,4);
  }
  return index;
}

vector<string> findFiles(string path)
{
  vector<string> paths;
  path = path + "/";
  DIR* dir = opendir(path.c_str());//打开指定目录  
  dirent* p = NULL;//定义遍历指针  
  while((p = readdir(dir)) != NULL)//开始逐个遍历  
  {  
    //这里需要注意，linux平台下一个目录中有"."和".."隐藏文件，需要过滤掉  
    if(p->d_name[0] != '.')//d_name是一个char数组，存放当前遍历到的文件名  
    {  
      string name = path + string(p->d_name);
      paths.push_back(name);
    }
  }
  sort(paths.begin(),paths.end());
  closedir(dir);//关闭指定目录
  return paths;
}

void test_orb(vector<vector<string>> results)
{ 
  char save[512];
  vector<string> paths = results[1];
  vector<string> names = results[0];
  for(int i=0;i<paths.size()-1;i++)
  {
    cout<<"第"<<i+1<<"次匹配： "<<names[i]<<" & "<<names[i+1]<<"  ";
    sprintf(save,"/root/out/orb_%s_%s.jpg",names[i].c_str(),names[i+1].c_str());
    orb_match(paths[i],paths[i+1],save);
  }
}

Mat matching(string path_img1,string path_img2)
{
  vector<vector<Point2f>> res;
  res = getMatchPoints(path_img1,path_img2);
  Mat img1 = imread(path_img1);
  Mat img2 = imread(path_img2);
  Mat homo = calcHomoMatrix(res);
  Mat resample_img2;
  warpPerspective(img2, resample_img2, homo, Size(int(img2.cols*1.2),int(img2.rows*1.2)));
  
  int dst_width = resample_img2.cols;
  int dst_height = resample_img2.rows;

  Mat dst(dst_height, dst_width, CV_8UC3);
  dst.setTo(0);

  resample_img2.copyTo(dst(Rect(0, 0, resample_img2.cols, resample_img2.rows)));
  img1.copyTo(dst(Rect(0, 0, img1.cols, img1.rows)));
  
  return dst;
}

Mat matchingIMG(Mat img1,Mat img2)
{
  vector<vector<Point2f>> res;
  res = getMatchPointsIMG(img1,img2);
  Mat homo = calcHomoMatrix(res);
  Mat resample_img2;
  //Size第一个参数是横轴，也即图像的宽，第二个是纵轴，图像的高
  warpPerspective(img2, resample_img2, homo, 
		  Size(int(img2.cols*1.2),int(img2.rows*1.3)),
		  CV_INTER_LINEAR,
		  BORDER_TRANSPARENT);
  
  int dst_width = resample_img2.cols;
  int dst_height = resample_img2.rows;

  Mat dst(dst_height, dst_width, CV_8UC3);
  dst.setTo(0);
  
  //拷贝第一帧图像到dst中（非零像素）
  for(int i=0;i<img1.rows;i++)
  {
    uchar* d = dst.ptr<uchar>(i);
    uchar* p = img1.ptr<uchar>(i);
    for(int j=0;j<img1.cols;j++)
    {
      if(p[j * 3] >= 10 || p[j * 3 + 1] >= 10 || p[j * 3 + 2] >= 10)
	{
	  d[j * 3]=p[j * 3];
	  d[j * 3 + 1]=p[j * 3 + 1];
	  d[j * 3 + 2]=p[j * 3 + 2];
	}
    }
  }
  
  //拷贝重采样后的第二帧图像到dst中（非零像素）
  for(int i=0;i<resample_img2.rows;i++)
  {
    uchar* d = dst.ptr<uchar>(i);
    uchar* p = resample_img2.ptr<uchar>(i);
    for(int j=0;j<resample_img2.cols;j++)
    {
      if(p[j * 3] >= 10 || p[j * 3 + 1] >= 10 || p[j * 3 + 2] >= 10)
	{
	  d[j * 3]=p[j * 3];
	  d[j * 3 + 1]=p[j * 3 + 1];
	  d[j * 3 + 2]=p[j * 3 + 2];
	}
    }
  }
  
  return dst;
}

Mat matchingIMG2(Mat img1,Mat img2)
{
  vector<vector<Point2f>> res;
  res = getMatchPointsIMG(img1,img2);
  Mat homo = calcHomoMatrix(res);
  Mat resample_img2;
  
  int dst_width = int(img2.cols*1.2);
  int dst_height = int(img2.rows*1.2);
  
  Mat dst(dst_height, dst_width, CV_8UC3);
  dst.setTo(0);
  warpPerspective(img2, dst, homo, Size(int(img2.cols*1.2),int(img2.rows*1.2)));
  img1.copyTo(dst(Rect(0, 0, img1.cols, img1.rows)));
  
  
  return dst;
}

void cutBlankBorder(Mat inputIMG)
{
  int top;
  int bottom;
  int left;
  int right;
  
  for(int i = 0;i<inputIMG.rows;i++)
  {
    uchar* img = inputIMG.ptr<uchar>(i);
    for(int j = 0;j<inputIMG.cols;j++)
    {
      if(img[j]!=0)
	top = i;
	break;
    }
  }
  
  for(int i = inputIMG.rows;i>0;i--)
  {
    uchar* img = inputIMG.ptr<uchar>(i);
    for(int j = 0;j<inputIMG.cols;j++)
    {
      if(img[j]!=0)
	bottom = i;
	break;
    }
  }
  
  for(int j = 0;j<inputIMG.cols;j++)
  {
    uchar* img = inputIMG.ptr<uchar>(j);
    for(int i = 0;j<inputIMG.rows;i++)
    {
      if(img[i]!=0)
	left = i;
	break;
    }
  }
  
  for(int j = inputIMG.cols;j>0;j--)
  {
    uchar* img = inputIMG.ptr<uchar>(j);
    for(int i = 0;j<inputIMG.rows;i++)
    {
      if(img[i]!=0)
	right = i;
	break;
    }
  }
  
  cout<<top<<endl;
  cout<<bottom<<endl;
  cout<<left<<endl;
  cout<<right<<endl;
}

Point2d pixel2cam( const Point2d& p, const Mat& K )
{
    //这个地方虽然没有算K逆，但是结果和K逆是相同的。应该是简化算法
    //这和OpenCV源码里由像素坐标转相机坐标的方法是一样的（five-point.cpp line432）
    return Point2d
           (
               ( p.x - K.at<double> ( 0,2 ) ) / K.at<double> ( 0,0 ),
               ( p.y - K.at<double> ( 1,2 ) ) / K.at<double> ( 1,1 )
           );
}

Mat evalAccuarcy(string path1,string path2,double dx,double dy,double f)
{
  Mat R,t;
  Mat ave=(Mat_<double>(1,1)<<0);
  vector<Point2f> points1,points2;
  getRtForEval(path1,path2,dx,dy,f,R,t,points1,points2);
  Mat K = (Mat_<double>(3,3)<<f,0,dx,0,f,dy,0,0,1);
  Mat t_x;
  t_x = (Mat_<double>(3,3)<<
	      0,			-t.at<double>(2,0),	t.at<double>(1,0),
	      t.at<double>(2,0),	0,			-t.at<double>(0,0),
	      -t.at<double>(1.0),	t.at<double>(0,0),	0);
  Mat t_R = t_x*R;
  
  cout<<"accuracy for every matched points"<<endl;
  for(int i=0;i<points1.size();i++)
  {
    Point2d pt1 = pixel2cam(points1[i],K);
    Mat y1 = (Mat_<double>(3,1)<<pt1.x,pt1.y,1);
    Point2d pt2 = pixel2cam(points2[i],K);
    Mat y2 = (Mat_<double>(3,1)<<pt2.x,pt2.y,1);
    Mat d = y2.t()*t_R*y1;
    cout<<d<<endl;
    ave = ave+abs(d);
  }
  ave = ave/points1.size();
  cout<<"average accuracy "<<endl;
  cout<<ave<<endl;
  return ave;
}

Mat evalAccuarcyAndOutput(string path1,string path2,double dx,double dy,double f,string outputPath)
{
  ofstream myout(outputPath);
  Mat R,t;
  Mat ave=(Mat_<double>(1,1)<<0);
  vector<Point2f> points1,points2;
  getRtForEval(path1,path2,dx,dy,f,R,t,points1,points2);
  
  Mat esse = calcEssentialMatrix2(points1,points2,dx,dy,f);
  Mat fun = calcFunMatrix2(points1,points2);
  Mat homo = calcHomoMatrix2(points1,points2);
  myout<<"homo_matrix"<<endl<<homo<<endl<<endl;
  myout<<"fundamental_matrix"<<endl<<fun<<endl<<endl;
  myout<<"essential_matrix"<<endl<<esse<<endl<<endl;
  myout<<"R"<<endl<<R<<endl<<endl;
  myout<<"t"<<endl<<t<<endl<<endl;
  
//   vector<double> res;
//   res = R2RPY(R);
//   double beta = res[0];
//   double alpha = res[1];
//   double sigma = res[2];
  
//   printf("beta %f\n",beta);
//   printf("alpha %f\n",alpha);
//   printf("sigma %f\n",sigma);
  
  Mat K = (Mat_<double>(3,3)<<f,0,dx,0,f,dy,0,0,1);
  Mat t_x;
  t_x = (Mat_<double>(3,3)<<
	      0,			-t.at<double>(2,0),	t.at<double>(1,0),
	      t.at<double>(2,0),	0,			-t.at<double>(0,0),
	      -t.at<double>(1.0),	t.at<double>(0,0),	0);
  Mat t_R = t_x*R;
  myout<<"t_R"<<endl<<t_R<<endl<<endl;
  myout<<"accuracy for every matched points"<<endl;
  
//   cout<<"accuracy for every matched points"<<endl;
  for(int i=0;i<points1.size();i++)
  {
    Point2d pt1 = pixel2cam(points1[i],K);
    Mat y1 = (Mat_<double>(3,1)<<pt1.x,pt1.y,1);
    Point2d pt2 = pixel2cam(points2[i],K);
    Mat y2 = (Mat_<double>(3,1)<<pt2.x,pt2.y,1);
    Mat d = y2.t()*t_R*y1;
//     cout<<y1<<endl;
//     cout<<y2<<endl;
//     cout<<d<<endl;
//     cout<<endl;
    
    myout<<y1<<endl;
    myout<<y2<<endl;
    myout<<d<<endl;
    myout<<endl;
    ave = ave+abs(d);
  }
  ave = ave/points1.size();
//   cout<<"average accuracy "<<endl;
  cout<<ave<<endl;
  myout<<"average accuracy "<<endl;
  myout<<ave<<endl;
  myout.close();
  return ave;
}

Mat eval(Mat t,Mat R)
{
  Mat t_x;
  t_x = (Mat_<double>(3,3)<<
	      0,			-t.at<double>(2,0),	t.at<double>(1,0),
	      t.at<double>(2,0),	0,			-t.at<double>(0,0),
	      -t.at<double>(1.0),	t.at<double>(0,0),	0);
  Mat t_R = t_x*R;
  return t_R;
}

void evalAccuarcyAndOutput2(string path1,string path2,double dx,double dy,double f,string outputPath)
{
  ofstream myout(outputPath);
  Mat R,t;
  Mat ave=(Mat_<double>(1,1)<<0);
  vector<Point2f> points1,points2;
  getRtForEval(path1,path2,dx,dy,f,R,t,points1,points2);
  Mat K = (Mat_<double>(3,3)<<f,0,dx,0,f,dy,0,0,1);
  
  myout<<"camera internal params K"<<endl<<K<<endl<<endl;
  
  Mat esse = calcEssentialMatrix2(points1,points2,dx,dy,f);
  Mat fun = calcFunMatrix2(points1,points2);
  Mat homo = calcHomoMatrix2(points1,points2);
  myout<<"HomographyMat"<<endl<<homo<<endl<<endl;
  myout<<"FundamentalMat"<<endl<<fun<<endl<<endl;
  myout<<"EssentialMat"<<endl<<esse<<endl<<endl;
  myout<<"R from recover essential Mat"<<endl<<R<<endl<<endl;
  myout<<"t from recover essential Mat"<<endl<<t<<endl<<endl;
  
  vector<double> res;
  res = R2RPY(R);
  double beta = res[0];
  double alpha = res[1];
  double sigma = res[2];
  
  myout<<"beta "<<beta<<endl;
  myout<<"alpha "<<alpha<<endl;
  myout<<"sigma "<<sigma<<endl<<endl;
  
  res = R2Q4(R);
  double qx = res[0];
  double qy = res[1];
  double qz = res[2];
  double qw = res[3];
  
  myout<<"qx "<<res[0]<<endl;
  myout<<"qy "<<res[1]<<endl;
  myout<<"qz "<<res[2]<<endl;
  myout<<"qw "<<res[3]<<endl<<endl;
  
  vector<Mat> R2,t2,n2;
  decomposeHomographyMat(homo,K,R2,t2,n2);
  
  for(int i=0;i<R2.size();i++)
  {
    myout<<"Case "<<i<<endl<<endl;
    myout<<"R from decomposeHomographyMat"<<endl<<R2[i]<<endl<<endl;
    myout<<"t from decomposeHomographyMat"<<endl<<t2[i]<<endl<<endl;
  }
  
  Mat t_R = eval(t,R);
  myout<<"t_R from essential"<<endl<<t_R<<endl<<endl;
  
  for(int i=0;i<points1.size();i++)
  {
    Point2d pt1 = pixel2cam(points1[i],K);
    Point2d pt2 = pixel2cam(points2[i],K);
    
    Mat y1 = (Mat_<double>(3,1)<<pt1.x,pt1.y,1);
    Mat y2 = (Mat_<double>(3,1)<<pt2.x,pt2.y,1);
    Mat d = y2.t()*t_R*y1;
    ave = ave+abs(d);
  }
  ave = ave/points1.size();
  myout<<"ave from essential "<<ave<<endl<<endl;
  
  for(int i=0;i<R2.size();i++)
  {
    t_R = eval(t2[i],R2[i]);
    myout<<"t_R from homography"<<endl<<t_R<<endl<<endl;
    ave=(Mat_<double>(1,1)<<0);
    for(int i=0;i<points1.size();i++)
    {
      Point2d pt1 = pixel2cam(points1[i],K);
      Point2d pt2 = pixel2cam(points2[i],K);
    
      Mat y1 = (Mat_<double>(3,1)<<pt1.x,pt1.y,1);
      Mat y2 = (Mat_<double>(3,1)<<pt2.x,pt2.y,1);
      Mat d = y2.t()*t_R*y1;
      ave = ave+abs(d);
    }
    ave = ave/points1.size();
    myout<<"ave from homo "<<i<<ave<<endl<<endl;
  }
  
  myout<<"a=["<<endl;
  for(int i=0;i<points1.size();i++)
  {
    Point2d pt1 = pixel2cam(points1[i],K);
    Point2d pt2 = pixel2cam(points2[i],K);
    
    double x0x1 = pt1.x*pt2.x;
    double x0y1 = pt1.x*pt2.y;
    double x0= pt1.x;
    double y0x1 = pt1.y*pt2.x;
    double y0y1 = pt1.y*pt2.y;
    double y0 = pt1.y;
    double x1 = pt2.x;
    double y1 = pt2.y;

    myout<<x0x1<<" "<<x0y1<<" "<<x0<<" "<<y0x1<<" "<<y0y1<<" "<<y0<<" "<<x1<<" "<<y1<<" 1"<<";"<<endl;
  }
  myout<<"]"<<endl<<endl;
  for(int i=0;i<points1.size();i++)
  {
    Point2d pt1 = pixel2cam(points1[i],K);
    Mat y1 = (Mat_<double>(3,1)<<pt1.x,pt1.y,1);
    Point2d pt2 = pixel2cam(points2[i],K);
    Mat y2 = (Mat_<double>(3,1)<<pt2.x,pt2.y,1);
    
    myout<<y1<<endl;
    myout<<y2<<endl;
    myout<<endl;
  }
  myout.close();
  return;
}

void evalAccuarcyAndOutput3(string path1,string path2,double dx,double dy,double f,string outputPath,double &pitch,double &yaw,double &roll)
{
  ofstream myout(outputPath);
  Mat R,t;
  Mat ave=(Mat_<double>(1,1)<<0);
  vector<Point2f> points1,points2;
  getRtForEval(path1,path2,dx,dy,f,R,t,points1,points2);
  Mat K = (Mat_<double>(3,3)<<f,0,dx,0,f,dy,0,0,1);
  
  myout<<"camera internal params K"<<endl<<K<<endl<<endl;
  
  Mat esse = calcEssentialMatrix2(points1,points2,dx,dy,f);
  Mat fun = calcFunMatrix2(points1,points2);
  Mat homo = calcHomoMatrix2(points1,points2);
  myout<<"HomographyMat"<<endl<<homo<<endl<<endl;
  myout<<"FundamentalMat"<<endl<<fun<<endl<<endl;
  myout<<"EssentialMat"<<endl<<esse<<endl<<endl;
  myout<<"R from recover essential Mat"<<endl<<R<<endl<<endl;
  myout<<"t from recover essential Mat"<<endl<<t<<endl<<endl;
  
  vector<double> res;
  res = R2RPY(R);
  double beta = res[0];
  double alpha = res[1];
  double sigma = res[2];
  
  pitch = pitch + beta;
  yaw = yaw + alpha;
  roll = roll + sigma;
  
  myout<<"beta "<<beta<<endl;
  myout<<"alpha "<<alpha<<endl;
  myout<<"sigma "<<sigma<<endl<<endl;
  
  myout<<"pitch "<<pitch<<endl;
  myout<<"yaw "<<yaw<<endl;
  myout<<"roll "<<roll<<endl<<endl;
  
  res = R2Q4(R);
  double qx = res[0];
  double qy = res[1];
  double qz = res[2];
  double qw = res[3];
  
  myout<<"qx "<<res[0]<<endl;
  myout<<"qy "<<res[1]<<endl;
  myout<<"qz "<<res[2]<<endl;
  myout<<"qw "<<res[3]<<endl<<endl;
  
  vector<Mat> R2,t2,n2;
  decomposeHomographyMat(homo,K,R2,t2,n2);
  
  for(int i=0;i<R2.size();i++)
  {
    myout<<"Case "<<i<<endl<<endl;
    myout<<"R from decomposeHomographyMat"<<endl<<R2[i]<<endl<<endl;
    myout<<"t from decomposeHomographyMat"<<endl<<t2[i]<<endl<<endl;
  }
  
  Mat t_R = eval(t,R);
  myout<<"t_R from essential"<<endl<<t_R<<endl<<endl;
  
  for(int i=0;i<points1.size();i++)
  {
    Point2d pt1 = pixel2cam(points1[i],K);
    Point2d pt2 = pixel2cam(points2[i],K);
    
    Mat y1 = (Mat_<double>(3,1)<<pt1.x,pt1.y,1);
    Mat y2 = (Mat_<double>(3,1)<<pt2.x,pt2.y,1);
    Mat d = y2.t()*t_R*y1;
    ave = ave+abs(d);
  }
  ave = ave/points1.size();
  myout<<"ave from essential "<<ave<<endl<<endl;
  
  for(int i=0;i<R2.size();i++)
  {
    t_R = eval(t2[i],R2[i]);
    myout<<"t_R from homography"<<endl<<t_R<<endl<<endl;
    ave=(Mat_<double>(1,1)<<0);
    for(int i=0;i<points1.size();i++)
    {
      Point2d pt1 = pixel2cam(points1[i],K);
      Point2d pt2 = pixel2cam(points2[i],K);
    
      Mat y1 = (Mat_<double>(3,1)<<pt1.x,pt1.y,1);
      Mat y2 = (Mat_<double>(3,1)<<pt2.x,pt2.y,1);
      Mat d = y2.t()*t_R*y1;
      ave = ave+abs(d);
    }
    ave = ave/points1.size();
    myout<<"ave from homo "<<i<<ave<<endl<<endl;
  }
  
  myout<<"a=["<<endl;
  for(int i=0;i<points1.size();i++)
  {
    Point2d pt1 = pixel2cam(points1[i],K);
    Point2d pt2 = pixel2cam(points2[i],K);
    
    double x0x1 = pt1.x*pt2.x;
    double x0y1 = pt1.x*pt2.y;
    double x0= pt1.x;
    double y0x1 = pt1.y*pt2.x;
    double y0y1 = pt1.y*pt2.y;
    double y0 = pt1.y;
    double x1 = pt2.x;
    double y1 = pt2.y;

    myout<<x0x1<<" "<<x0y1<<" "<<x0<<" "<<y0x1<<" "<<y0y1<<" "<<y0<<" "<<x1<<" "<<y1<<" 1"<<";"<<endl;
  }
  myout<<"]"<<endl<<endl;
  for(int i=0;i<points1.size();i++)
  {
    Point2d pt1 = pixel2cam(points1[i],K);
    Mat y1 = (Mat_<double>(3,1)<<pt1.x,pt1.y,1);
    Point2d pt2 = pixel2cam(points2[i],K);
    Mat y2 = (Mat_<double>(3,1)<<pt2.x,pt2.y,1);
    
    myout<<y1<<endl;
    myout<<y2<<endl;
    myout<<endl;
  }
  myout.close();
  return;
}

double Rad2Deg(double rad)
{
  double deg = (180.0 / PI) * rad;
  return deg;
}

void evalAccuarcyAndOutput4(string path1,string path2,double dx,double dy,double f,string outputPath)
{
  ofstream myout(outputPath);
  Mat R,t,ess,fun,homo;
  Mat ave=(Mat_<double>(1,1)<<0);
  
  //这里points1、points2是指ORB匹配完以后，对应点的像素坐标（u，v）
  vector<Point2f> points1,points2;
  vector<KeyPoint> key1,key2;
  vector<DMatch> matches;
  getRtForEval3(path1,path2,dx,dy,f,R,t,points1,points2,key1,key2,ess,homo,fun,matches);
  Mat K = (Mat_<double>(3,3)<<f,0,dx,0,f,dy,0,0,1);
  Mat K_inv;
  K_inv = K.inv();
  
  myout<<"相机内参矩阵K"<<endl<<K<<endl<<endl;
  myout<<"K逆"<<endl<<K_inv<<endl<<endl;
  myout<<"单应矩阵H"<<endl<<homo<<endl<<endl;
  myout<<"基础矩阵F"<<endl<<fun<<endl<<endl;
  myout<<"本质矩阵E"<<endl<<ess<<endl<<endl;
  myout<<"旋转矩阵R"<<endl<<R<<endl<<endl;
  myout<<"平移向量t"<<endl<<t<<endl<<endl;
  
  vector<double> res = R2RPY2(R);
  myout<<"Phi "<<Rad2Deg(res[0])<<endl;
  myout<<"Kappa "<<Rad2Deg(res[1])<<endl;
  myout<<"Omega "<<Rad2Deg(res[2])<<endl<<endl;
  
  vector<double> qs = R2Q4(R);
  myout<<"q0 "<<qs[0]<<endl;
  myout<<"q1 "<<qs[1]<<endl;
  myout<<"q2 "<<qs[2]<<endl;
  myout<<"q3 "<<qs[3]<<endl<<endl;
  
  
  cout<<"matching "<<path1<<" & "<<path2<<endl;
  cout<<"camera internal params K"<<endl<<K<<endl<<endl;
  cout<<"K-1"<<endl<<K_inv<<endl<<endl;
  cout<<"EssentialMat"<<endl<<ess<<endl<<endl;
  cout<<"FundamentalMat"<<endl<<fun<<endl<<endl;
  cout<<"HomographyMat"<<endl<<homo<<endl<<endl;
  cout<<"R"<<endl<<R<<endl<<endl;
  cout<<"t"<<endl<<t<<endl<<endl;
  
  Mat t_R = eval(t,R);
  
  myout<<"匹配 "<<points1.size()<<" points."<<endl<<endl;
  cout<<"matched "<<points1.size()<<" points."<<endl<<endl;
  
  //-- 三角化
  vector<Point3d> points;
  triangulation( key1, key2, matches, R, t, K, points);
  
  
  for ( int i=0; i<matches.size(); i++ )
  {
    //由像素坐标转成齐次像素坐标
    Mat homo_p1=(Mat_<double>(3,1)<<points1[i].x,points1[i].y,1);
    Mat homo_p2=(Mat_<double>(3,1)<<points2[i].x,points2[i].y,1);
    
    //利用公式P=K-1p1，计算得到归一化的相机坐标系下的坐标
    Mat homo_P1 = K_inv*homo_p1;
    Mat homo_P2 = K_inv*homo_p2;
    
    //对极约束验证。d理论为0。注意输入的坐标是归一化相机坐标而不是像素坐标
    Mat d = homo_P2.t()*t_R*homo_P1;
    
    cout<<"------point "<<(i+1)<<"------"<<endl;
    cout<<"齐次像素坐标p1"<<endl<<homo_p1<<endl;
    cout<<"归一化相机坐标P1"<<endl<<homo_P1<<endl;
    cout<<"齐次像素坐标p2"<<endl<<homo_p2<<endl;
    cout<<"归一化相机坐标P2"<<endl<<homo_P2<<endl;
    cout<<"对极约束 "<<d<<endl<<endl;
    
    myout<<"------point "<<(i+1)<<"------"<<endl;
    myout<<"齐次像素坐标p1（已知）"<<endl<<homo_p1<<endl;
    myout<<"归一化相机坐标P1（已知）"<<endl<<homo_P1<<endl;
    myout<<"齐次像素坐标p2（已知）"<<endl<<homo_p2<<endl;
    myout<<"归一化相机坐标P2（已知）"<<endl<<homo_P2<<endl;
    myout<<"对极约束（计算） "<<d<<endl<<endl;
    
    ave = ave+abs(d);
      
    //-- 验证三角化点与特征点的重投影关系
    //这里的pt1_cam其实就是相面坐标，也可以看成是没有齐次的相机坐标，
    //如果z为1,则变为归一化相机坐标
    Point2d pt1_cam = pixel2cam( key1[matches[i].queryIdx].pt, K );
    
    //这个点是OpenCV三角化输出的坐标，并且x、y同除了z，进行了归一化
    //因此我们要比较的就是这个算出来的归一化坐标和上面的那个坐标
    //理论上而言，他们的x、y应该是一样的
    Point2d pt1_cam_3d(
            points[i].x/points[i].z, 
            points[i].y/points[i].z 
    );
    
    cout<<"第一帧"<<endl;
    cout<<"第一帧中的相面坐标（z=1）（已知）: "<<pt1_cam<<endl;
    cout<<"三角化算出来的点坐标（计算）："<<points[i]<<endl;
    cout<<"由三角化计算出的点的归一化相机坐标(z=1)（计算）："<<pt1_cam_3d<<endl;
    
    myout<<"第一帧"<<endl;
    myout<<"第一帧中的相面坐标（z=1）（已知）: "<<pt1_cam<<endl;
    myout<<"三角化算出来的点坐标（计算）："<<points[i]<<endl;
    myout<<"由三角化计算出的点的归一化相机坐标(z=1)（计算）："<<pt1_cam_3d<<endl;
    Point2d delta1 = pt1_cam_3d-pt1_cam;
    myout<<"计算的归一化坐标与实际归一化坐标差值：["<<abs(delta1.x)<<","<<abs(delta1.y)<<"]"<<endl;
    
    
    
    // 第二个图
    Point2f pt2_cam = pixel2cam( key2[ matches[i].trainIdx ].pt, K );
    //这是把第一帧算出来的相机坐标，通过R、t转到第二帧的相机坐标系中来
    Mat pt2_trans = R*( Mat_<double>(3,1) << points[i].x, points[i].y, points[i].z ) + t;
    
    
    cout<<"第二帧"<<endl;
    myout<<"第二帧"<<endl;
    
    myout<<"由第一帧算出的3D点重投影到第二帧的相机坐标（计算）: "<<pt2_trans.t()<<endl;
    cout<<"由第一帧算出的3D点重投影到第二帧的相机坐标（计算）: "<<pt2_trans.t()<<endl;
    
    //对该点的相机坐标进行归一化，试z=1
    //所以要比较的是由第一帧算出的三维点投影到第二帧上的归一化相机坐标和
    //由第二帧特征点算出来的相面坐标相比
    //理论上他们应该相等
    pt2_trans /= pt2_trans.at<double>(2,0);
    
    myout<<"由第一帧算出的3D点重投影到第二帧的归一化相机坐标（计算）: "<<pt2_trans.t()<<endl;
    myout<<"第二帧中的相面坐标（z=1）（已知）: "<<pt2_cam<<endl;
    myout<<"重投影后计算的归一化坐标与实际归一化坐标差值：["<<abs(pt2_trans.at<double>(0,0)-pt2_cam.x)<<","<<abs(pt2_trans.at<double>(1,0)-pt2_cam.y)<<"]"<<endl;
    myout<<endl;
    
    cout<<"由第一帧算出的3D点重投影到第二帧的归一化相机坐标（计算）: "<<pt2_trans.t()<<endl;
    cout<<"第二帧中的相面坐标（z=1）（已知）: "<<pt2_cam<<endl;
    cout<<endl;
  }
  
  ave = ave/points1.size();
  myout<<"mean epipolar constraint "<<ave<<endl<<endl;
  cout<<"mean epipolar constraint "<<ave<<endl<<endl;
  myout.close();
  return;
}

void evalAccuarcyAndOutput5(string path1,string path2,double dx,double dy,double f,string outputPath)
{
  ofstream myout(outputPath);
  Mat R,t,ess,fun,homo;
  Mat ave=(Mat_<double>(1,1)<<0);
  
  //这里points1、points2是指ORB匹配完以后，对应点的像素坐标（u，v）
  vector<Point2f> points1,points2;
  vector<KeyPoint> key1,key2;
  vector<DMatch> matches;
  getRtForEval3(path1,path2,dx,dy,f,R,t,points1,points2,key1,key2,ess,homo,fun,matches);
  Mat K = (Mat_<double>(3,3)<<f,0,dx,0,f,dy,0,0,1);
  Mat K_inv;
  K_inv = K.inv();
  
  myout<<"相机内参矩阵K"<<endl<<K<<endl<<endl;
  myout<<"K逆"<<endl<<K_inv<<endl<<endl;
  myout<<"单应矩阵H"<<endl<<homo<<endl<<endl;
  myout<<"基础矩阵F"<<endl<<fun<<endl<<endl;
  myout<<"本质矩阵E"<<endl<<ess<<endl<<endl;
  myout<<"旋转矩阵R"<<endl<<R<<endl<<endl;
  myout<<"平移向量t"<<endl<<t<<endl<<endl;
  
  vector<double> res = R2RPY2(R);
  myout<<"Phi "<<Rad2Deg(res[0])<<endl;
  myout<<"Kappa "<<Rad2Deg(res[1])<<endl;
  myout<<"Omega "<<Rad2Deg(res[2])<<endl<<endl;
  
  vector<double> qs = R2Q4(R);
  myout<<"q0 "<<qs[0]<<endl;
  myout<<"q1 "<<qs[1]<<endl;
  myout<<"q2 "<<qs[2]<<endl;
  myout<<"q3 "<<qs[3]<<endl<<endl;
  
  
  cout<<"matching "<<path1<<" & "<<path2<<endl;
  cout<<"camera internal params K"<<endl<<K<<endl<<endl;
  cout<<"K-1"<<endl<<K_inv<<endl<<endl;
  cout<<"EssentialMat"<<endl<<ess<<endl<<endl;
  cout<<"FundamentalMat"<<endl<<fun<<endl<<endl;
  cout<<"HomographyMat"<<endl<<homo<<endl<<endl;
  cout<<"R"<<endl<<R<<endl<<endl;
  cout<<"t"<<endl<<t<<endl<<endl;
  
  Mat t_R = eval(t,R);
  
  myout<<"匹配 "<<points1.size()<<" points."<<endl<<endl;
  cout<<"matched "<<points1.size()<<" points."<<endl<<endl;
  
  //-- 三角化
  vector<Point3d> points;
  triangulation( key1, key2, matches, R, t, K, points);
  
  Mat r,t2;
  solvePnP(points,points2,K,Mat(), r, t2, false);
  Mat R2;
  cv::Rodrigues ( r, R2 ); // r为旋转向量形式，用Rodrigues公式转换为矩阵
  myout<<"旋转矩阵R2"<<endl<<R2<<endl<<endl;
  myout<<"平移向量t2"<<endl<<t2<<endl<<endl;
  
  for ( int i=0; i<matches.size(); i++ )
  {
    //由像素坐标转成齐次像素坐标
    Mat homo_p1=(Mat_<double>(3,1)<<points1[i].x,points1[i].y,1);
    Mat homo_p2=(Mat_<double>(3,1)<<points2[i].x,points2[i].y,1);
    
    //利用公式P=K-1p1，计算得到归一化的相机坐标系下的坐标
    Mat homo_P1 = K_inv*homo_p1;
    Mat homo_P2 = K_inv*homo_p2;
    
    //对极约束验证。d理论为0。注意输入的坐标是归一化相机坐标而不是像素坐标
    Mat d = homo_P2.t()*t_R*homo_P1;
    
    cout<<"------point "<<(i+1)<<"------"<<endl;
    cout<<"齐次像素坐标p1"<<endl<<homo_p1<<endl;
    cout<<"归一化相机坐标P1"<<endl<<homo_P1<<endl;
    cout<<"齐次像素坐标p2"<<endl<<homo_p2<<endl;
    cout<<"归一化相机坐标P2"<<endl<<homo_P2<<endl;
    cout<<"对极约束 "<<d<<endl<<endl;
    
    myout<<"------point "<<(i+1)<<"------"<<endl;
    myout<<"齐次像素坐标p1（已知）"<<endl<<homo_p1<<endl;
    myout<<"归一化相机坐标P1（已知）"<<endl<<homo_P1<<endl;
    myout<<"齐次像素坐标p2（已知）"<<endl<<homo_p2<<endl;
    myout<<"归一化相机坐标P2（已知）"<<endl<<homo_P2<<endl;
    myout<<"对极约束（计算） "<<d<<endl<<endl;
    
    ave = ave+abs(d);
      
    //-- 验证三角化点与特征点的重投影关系
    //这里的pt1_cam其实就是相面坐标，也可以看成是没有齐次的相机坐标，
    //如果z为1,则变为归一化相机坐标
    Point2d pt1_cam = pixel2cam( key1[matches[i].queryIdx].pt, K );
    
    //这个点是OpenCV三角化输出的坐标，并且x、y同除了z，进行了归一化
    //因此我们要比较的就是这个算出来的归一化坐标和上面的那个坐标
    //理论上而言，他们的x、y应该是一样的
    Point2d pt1_cam_3d(
            points[i].x/points[i].z, 
            points[i].y/points[i].z 
    );
    
    cout<<"第一帧"<<endl;
    cout<<"第一帧中的相面坐标（z=1）（已知）: "<<pt1_cam<<endl;
    cout<<"三角化算出来的点坐标（计算）："<<points[i]<<endl;
    cout<<"由三角化计算出的点的归一化相机坐标(z=1)（计算）："<<pt1_cam_3d<<endl;
    
    myout<<"第一帧"<<endl;
    myout<<"第一帧中的相面坐标（z=1）（已知）: "<<pt1_cam<<endl;
    myout<<"三角化算出来的点坐标（计算）："<<points[i]<<endl;
    myout<<"由三角化计算出的点的归一化相机坐标(z=1)（计算）："<<pt1_cam_3d<<endl;
    Point2d delta1 = pt1_cam_3d-pt1_cam;
    myout<<"计算的归一化坐标与实际归一化坐标差值：["<<abs(delta1.x)<<","<<abs(delta1.y)<<"]"<<endl;
    
    
    
    // 第二个图
    Point2f pt2_cam = pixel2cam( key2[ matches[i].trainIdx ].pt, K );
    //这是把第一帧算出来的相机坐标，通过R、t转到第二帧的相机坐标系中来
    Mat pt2_trans = R*( Mat_<double>(3,1) << points[i].x, points[i].y, points[i].z ) + t;
    
    
    cout<<"第二帧"<<endl;
    myout<<"第二帧"<<endl;
    
    myout<<"由第一帧算出的3D点重投影到第二帧的相机坐标（计算）: "<<pt2_trans.t()<<endl;
    cout<<"由第一帧算出的3D点重投影到第二帧的相机坐标（计算）: "<<pt2_trans.t()<<endl;
    
    //对该点的相机坐标进行归一化，试z=1
    //所以要比较的是由第一帧算出的三维点投影到第二帧上的归一化相机坐标和
    //由第二帧特征点算出来的相面坐标相比
    //理论上他们应该相等
    pt2_trans /= pt2_trans.at<double>(2,0);
    
    myout<<"由第一帧算出的3D点重投影到第二帧的归一化相机坐标（计算）: "<<pt2_trans.t()<<endl;
    myout<<"第二帧中的相面坐标（z=1）（已知）: "<<pt2_cam<<endl;
    myout<<"重投影后计算的归一化坐标与实际归一化坐标差值：["<<abs(pt2_trans.at<double>(0,0)-pt2_cam.x)<<","<<abs(pt2_trans.at<double>(1,0)-pt2_cam.y)<<"]"<<endl;
    myout<<endl;
    
    cout<<"由第一帧算出的3D点重投影到第二帧的归一化相机坐标（计算）: "<<pt2_trans.t()<<endl;
    cout<<"第二帧中的相面坐标（z=1）（已知）: "<<pt2_cam<<endl;
    cout<<endl;
  }
  
  ave = ave/points1.size();
  myout<<"mean epipolar constraint "<<ave<<endl<<endl;
  cout<<"mean epipolar constraint "<<ave<<endl<<endl;
  myout.close();
  return;
}

void triangulation ( 
    const vector< KeyPoint >& keypoint_1, 
    const vector< KeyPoint >& keypoint_2, 
    const std::vector< DMatch >& matches,
    const Mat& R, const Mat& t,Mat K,
    vector< Point3d >& points)
{
    Mat T1 = (Mat_<float> (3,4) <<
        1,0,0,0,
        0,1,0,0,
        0,0,1,0);
    Mat T2 = (Mat_<float> (3,4) <<
        R.at<double>(0,0), R.at<double>(0,1), R.at<double>(0,2), t.at<double>(0,0),
        R.at<double>(1,0), R.at<double>(1,1), R.at<double>(1,2), t.at<double>(1,0),
        R.at<double>(2,0), R.at<double>(2,1), R.at<double>(2,2), t.at<double>(2,0)
    );
    
    vector<Point2f> pts_1, pts_2;
    for ( DMatch m:matches )
    {
        // 将像素坐标转换至相机坐标
        pts_1.push_back ( pixel2cam( keypoint_1[m.queryIdx].pt, K) );
        pts_2.push_back ( pixel2cam( keypoint_2[m.trainIdx].pt, K) );
    }
    
    Mat pts_4d;
    cv::triangulatePoints( T1, T2, pts_1, pts_2, pts_4d );
    
    // 转换成非齐次坐标
    for ( int i=0; i<pts_4d.cols; i++ )
    {
        Mat x = pts_4d.col(i);
        x /= x.at<float>(3,0); // 归一化
        Point3d p (
            x.at<float>(0,0), 
            x.at<float>(1,0), 
            x.at<float>(2,0) 
        );
        points.push_back( p );
    }
}


void test()
{
  string dir = "/root/satellite_slam_data/tianjin/jpg/";
  Mat frame2 = imread(dir+"VBZ1_201801051905_002_0002_L1A.jpg");
  Mat frame3 = imread(dir+"VBZ1_201801051905_002_0003_L1A.jpg");
  Mat frame4 = imread(dir+"VBZ1_201801051905_002_0004_L1A.jpg");
  Mat frame5 = imread(dir+"VBZ1_201801051905_002_0005_L1A.jpg");
  Mat img2_3 = matchingIMG(frame2,frame3);
  Mat img3_4 = matchingIMG(frame3,frame4);
  Mat img4_5 = matchingIMG(frame4,frame5);
  imwrite("/root/img2_3.jpg",img2_3);
  imwrite("/root/img3_4.jpg",img3_4);
  imwrite("/root/img4_5.jpg",img4_5);
  Mat img2_3_4 = matchingIMG(img2_3,img3_4);
  Mat img3_4_5 = matchingIMG(img3_4,img4_5);
  imwrite("/root/img2_3_4.jpg",img2_3_4);
  imwrite("/root/img3_4_5.jpg",img3_4_5);
  Mat img2_3_4_5 = matchingIMG(img2_3_4,img3_4_5);
  imwrite("/root/img2_3_4_5.jpg",img2_3_4_5);
}

void readData(string inputPath,vector<double> &UTC,vector<double> & X,vector<double> &Y,vector<double> &Z,vector<double> &Pitch,vector<double> &Yaw,vector<double> &Roll)
{
  int count = 0;
  ifstream input(inputPath);
  double utc;
  double x;
  double y;
  double z;
  double pitch;
  double yaw;
  double roll;
  if(input.is_open())
  {
    string line;
    while(getline(input,line))
    {
      sscanf(line.c_str(),"%lf %lf %lf %lf %lf %lf %lf",&utc,&x,&y,&z,&pitch,&roll,&yaw);
      UTC.push_back(utc);
      X.push_back(x);
      Y.push_back(y);
      Z.push_back(z);
      Pitch.push_back(pitch);
      Roll.push_back(roll);
      Yaw.push_back(yaw);
    }
    input.close();
  }
}


/**
 * 功能： 1. 检查是否是旋转矩阵
 * 作者： Zuo
 * 日期： 2017-10-12
**/bool isRotationMatrix(Mat &R)
{
    Mat Rt;
    transpose(R, Rt);
    Mat shouldBeIdentity = Rt * R;
    Mat I = Mat::eye(3,3, shouldBeIdentity.type());

    return  norm(I, shouldBeIdentity) < 1e-6;    
}

/**
 * 功能： 1. 通过给定的旋转矩阵计算对应的欧拉角
 * 作者： Zuo
 * 日期： 2017-10-12
**/
Vec3f rotationMatrixToEulerAngles(Mat &R)
{
    assert(isRotationMatrix(R));

    float sy = sqrt(R.at<double>(0,0) * R.at<double>(0,0) +  R.at<double>(1,0) * R.at<double>(1,0) );

    bool singular = sy < 1e-6; // If

    float x, y, z;
    if (!singular) {
        x = atan2(R.at<double>(2,1) , R.at<double>(2,2));
        y = atan2(-R.at<double>(2,0), sy);
        z = atan2(R.at<double>(1,0), R.at<double>(0,0));
    } else {
        x = atan2(-R.at<double>(1,2), R.at<double>(1,1));
        y = atan2(-R.at<double>(2,0), sy);
        z = 0;
    }
    return Vec3f(x, y, z);   
}


/**
 * 功能： 1. 通过给定的欧拉角计算对应的旋转矩阵
 * 作者： Zuo
 * 日期： 2017-10-12
**/
Mat eulerAnglesToRotationMatrix(Vec3f &theta)
{
    // 计算旋转矩阵的X分量
    Mat R_x = (Mat_<double>(3,3) <<
               1,       0,              0,
               0,       cos(theta[0]),   -sin(theta[0]),
               0,       sin(theta[0]),   cos(theta[0])
               );

    // 计算旋转矩阵的Y分量
    Mat R_y = (Mat_<double>(3,3) <<
               cos(theta[1]),    0,      sin(theta[1]),
               0,               1,      0,
               -sin(theta[1]),   0,      cos(theta[1])
               );

    // 计算旋转矩阵的Z分量
    Mat R_z = (Mat_<double>(3,3) <<
               cos(theta[2]),    -sin(theta[2]),      0,
               sin(theta[2]),    cos(theta[2]),       0,
               0,               0,                  1);

    // 合并 
    Mat R = R_z * R_y * R_x;

    return R;
}