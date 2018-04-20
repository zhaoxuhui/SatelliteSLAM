//
// Created by root on 18-4-15.
//

#include <iostream>
#include <vector>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/features2d.hpp>
#include "BasicFunc.h"
#include "tinyxml2.h"
#include "DataProcess.h"

using namespace std;
using namespace tinyxml2;
using namespace cv;

vector<string> prepareData(const string &img_dir, const string &xml_path, const SATE_NAME &name) {
    vector<string> data;
    vector<string> imgs = findFiles(img_dir);
    vector<string> times = readTimeXML(xml_path, name);
    if (imgs.size() != times.size()) {
        cout << "Error" << endl;
    } else {
        for (int i = 0; i < imgs.size(); i++) {
            data.push_back(times[i] + " " + imgs[i]);
        }
    }
    return data;
}

vector<string> readTimeXML(const string &xml_path, const SATE_NAME &name) {
    vector<string> times;
    switch (name)
        case OVS_1A: {

            //新建一个XMLDocument对象
            tinyxml2::XMLDocument docXml;
            //调用对象的LoadFile函数加载文件，并将结果返回给errXML
            tinyxml2::XMLError errXml = docXml.LoadFile(xml_path.c_str());
            if (errXml == tinyxml2::XML_SUCCESS) {

                //获取XML的root节点
                tinyxml2::XMLElement *elmtRoot = docXml.RootElement();

                //获取root节点下第一个名为“TimeParams”的子节点
                tinyxml2::XMLElement *elmtTimeParams = elmtRoot->FirstChildElement("TimeParams");

                //获取TimeParams节点下第一个名为“LineParam”的子节点
                tinyxml2::XMLElement *elmtLineParam = NULL;

                for (elmtLineParam = elmtTimeParams->FirstChildElement("LineParam");
                     elmtLineParam != NULL;
                     elmtLineParam = elmtLineParam->NextSiblingElement()) {
                    //获取LineParam节点下第一个名为“LineTime”的子节点
                    tinyxml2::XMLElement *elmtLineTime = elmtLineParam->FirstChildElement("LineTime");
                    tinyxml2::XMLElement *UTC = elmtLineTime->FirstChildElement("UTC");
                    times.push_back(UTC->GetText());
                }
            } else {
                cout << "Error" << endl;
            }
        }
    return times;
}

void createVocabulary(const string &img_dir, const string &out_path) {
    vector<string> img_paths = findFiles(img_dir);
    Ptr<Feature2D> detector = ORB::create();
    vector<Mat> descriptors;

    cout << "Reading and detecting ORB features..." << endl;

    //read and detect ORB features...
    for (int i = 0; i < img_paths.size(); i++) {
        Mat img = imread(img_paths[i]);
        vector<KeyPoint> keypoints;
        Mat descriptor;
        detector->detectAndCompute(img, Mat(), keypoints, descriptor);
        descriptors.push_back(descriptor);
        cout << (i + 1) << "/" << img_paths.size() << endl;
    }

    //create vocabulary
    cout << "creating vocabulary ... " << endl;
    DBoW3::Vocabulary vocab;
    vocab.create(descriptors);
    cout << "vocabulary info: " << vocab << endl;
    vocab.save(out_path + "vocabulary.txt.gz");
    cout << "done" << endl;
}