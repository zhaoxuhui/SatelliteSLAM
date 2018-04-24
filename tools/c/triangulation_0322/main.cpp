#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <dirent.h>//遍历系统指定目录下文件要包含的头文件
#include <string>
#include "ORBMatching.h"
#include "MatrixCalculation.h"
#include "common.h"

# define PI 3.141592653

using namespace std;
using namespace cv;


int main(int argc, char **argv) {

//     //TUM Freiburg2数据集内参
//     double dx =325.1;
//     double dy = 249.7;
//     double f = 520.9;
//     string input_dir = "/root/satellite_slam_data/tum3";
//     string output_dir = "/root/out/tum3/";

//    //欧比特卫星内参
//    double dx = 1535.89;
//    double dy = 2046.97;
//    double f = 1536.2;
//    string input_dir = "/root/data/satellite/Airport/jpg";
//    string output_dir = "/root/out/Airport/";

    //欧比特卫星内参
    double dx = 1535.89;
    double dy = 2046.97;
    double f = 1536.2;
    string input_dir = "/root/test";
    string output_dir = "/root";


    vector<string> files = findFiles(input_dir);
  for(int i=0;i<files.size()-1;i++)
  {
    cout<<(i+1)<<"/"<<(files.size()-1)<<endl;
    //计算与精度评定
    evalAccuarcyAndOutput5(files[i],files[i+1],dx,dy,f,
	      output_dir+"/res_"+getIndex(files[i])+"_"+getIndex(files[i+1])+".txt");
    //输出两两匹配结果
    orb_match(files[i],files[i+1],
	      output_dir+"/res_"+getIndex(files[i])+"_"+getIndex(files[i+1])+".jpg");
  }

    return 0;
}
