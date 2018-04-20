#include <iostream>
#include "tinyxml2.h"
#include "BasicFunc.h"
#include "DataProcess.h"

using namespace std;


int main() {
    string dir = "/root/data/TUM/rgbd_dataset_freiburg1_xyz/rgb";
    string base = "/root/data/satellite/tianjin/";
    string xml_path = "/root/data/satellite/tianjin/observation/VBZ1_201801051905_002.time";
    string out_path = "/root/data/satellite/tianjin/rgb.txt";
    string vocab_path = "/root/data/TUM/rgbd_dataset_freiburg1_xyz/";

    vector<string> data = prepareData(dir, xml_path, OVS_1A);
    saveStrVecTUM(data, base, out_path);

//    createVocabulary(dir, vocab_path);

    return 0;
}