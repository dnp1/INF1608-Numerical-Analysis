//
// Created by danilo on 08/11/15.
//
#include "helper.h"
#include <fstream>
#include <iostream>
#include <string.h>
#include "CtScan.h"

using namespace std;
using scan::CtScan;

namespace helper
{
    void LoadFileToCtScan(std::string fileName, CtScan &ct)
    {
        using std::ifstream;
        using std::cerr;
        ifstream file;
        file.open(fileName);
        if (!file.is_open()) {
            cerr << "File could not be opened!" << endl;
            return;
        }

        file.read((char*) ct.getReferenceToData(), ct.getSizeInBytes());

        if (file.fail()) {
            cerr << "=>\t Fail during the reading of file `" << fileName << "`!" << endl;
            return;
        }

        file.close();
    }
}

