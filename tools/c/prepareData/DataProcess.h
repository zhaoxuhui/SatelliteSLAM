//
// Created by root on 18-4-15.
//
#include <iostream>
#include <vector>
#include "BasicFunc.h"
#include "tinyxml2.h"
#include "DBoW3/DBoW3.h"

using namespace std;

#ifndef DATAPROCESS_H
#define DATAPROCESS_H

enum SATE_NAME {
    OVS_1A
};

vector<string> prepareData(const string &img_dir, const string &xml_path, const SATE_NAME &name);

vector<string> readTimeXML(const string &xml_path, const SATE_NAME &name);

void createVocabulary(const string &img_dir, const string &out_path);

#endif //DATAPROCESS_H
