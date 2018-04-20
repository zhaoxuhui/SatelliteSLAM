//
// Created by zhao xuhui on 18-4-15.
// 一些常用、基础函数
//

#include <fstream>
#include <cstring>
#include "BasicFunc.h"

vector<string> findFiles(const string &dictionary) {
    vector<string> paths;
    DIR *dir = opendir(dictionary.c_str());//打开指定目录
    dirent *p = NULL;//定义遍历指针
    string seprator = "/";
#ifdef __linux
    seprator = "/";
#elif WINVER
    seprator = "\\";
#endif
    while ((p = readdir(dir)) != NULL)//开始逐个遍历
    {
        //这里需要注意，linux平台下一个目录中有"."和".."隐藏文件，需要过滤掉
        if (p->d_name[0] != '.')//d_name是一个char数组，存放当前遍历到的文件名
        {
            string name = dictionary + seprator + string(p->d_name);
            paths.push_back(name);
        }
    }
    sort(paths.begin(), paths.end());
    closedir(dir);//关闭指定目录
    return paths;
}

void findFiles(const string &dictionary, vector<string> &paths) {
    DIR *dir = opendir(dictionary.c_str());//打开指定目录
    dirent *p = NULL;//定义遍历指针
    string seprator = "/";
#ifdef __linux
    seprator = "/";
#elif WINVER
    seprator = "\\";
#endif
    while ((p = readdir(dir)) != NULL)//开始逐个遍历
    {
        //这里需要注意，linux平台下一个目录中有"."和".."隐藏文件，需要过滤掉
        if (p->d_name[0] != '.')//d_name是一个char数组，存放当前遍历到的文件名
        {
            string name = dictionary + seprator + string(p->d_name);
            paths.push_back(name);
        }
    }
    sort(paths.begin(), paths.end());
    closedir(dir);//关闭指定目录
}

void saveStrVectorToTXT(const vector<string> &vec, const string &out_path) {
    ofstream out(out_path);
    for (auto item:vec) {
        out << item << endl;
    }
    out.close();
}

void saveStrVecTUM(const vector<string> &vec, const string &base, const string &out_path) {
    ofstream out(out_path);
    out << "# color images" << endl;
    out << "# file: 'satellite video frames'" << endl;
    out << "# timestamp filename" << endl;
    for (int i = 0; i < vec.size(); i++) {
        string time = vec[i].substr(0, vec[i].find(" "));
        string path = vec[i].substr(vec[i].find(" "), vec[i].length() - vec[i].find(" "));
        string res = path.substr(base.length() + 1, path.length() - base.length());
        out << time + " " + res << endl;
    }
    out.close();
}