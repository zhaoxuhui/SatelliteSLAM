//
// Created by zhao xuhui on 18-4-15.
// 一些常用、基础函数
//

#include <iostream>
#include <vector>
#include <dirent.h>
#include <algorithm>

using namespace std;

#ifndef BASICFUNC_H
#define BASICFUNC_H

vector<string> findFiles(const string &dir);

void findFiles(const string &dictionary, vector<string> &paths);

void saveStrVectorToTXT(const vector<string> &vec, const string &out_path);

void saveStrVecTUM(const vector<string> &vec, const string &base, const string &out_path);


#endif //BASICFUNC_H
