//
// Created by danilo on 08/11/15.
//
#include "helper.h"
#include <string>
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
        bool failed = false;
        using std::ifstream;
        using std::cerr;
        unsigned char data;
        ifstream      file;
        file.open(fileName);
        if (!file.is_open()) {
            cerr << "File could not be opened!" << endl;
            return;
        }
        unsigned int count = 0;


        for (unsigned int i = 0; i < ct.getNX(); i++) {
            for (unsigned int j = 0; j < ct.getNY(); j++) {
                for (unsigned int k = 0; k < ct.getNZ(); k++) {
                    if (failed || file.fail()) {
                        if (!failed) {
                            cerr << "Error: `" << strerror(errno) << "` !" << endl;
                        }
                        failed = true;
                        break;
                    }

                    file.read((char*) &data, 1);
                    count++;
                    ct.set(i, j, k, data);
//                    cout << data << " ";
                }
//                if (!failed) {
//                    cout << endl;
//                }
            }
//            if (!failed) {
//                cout << endl << "================" << endl;
//            }
        }

        if (file.fail()) {
            cerr << "=>\t Fail during the reading of file `" << fileName << "`!" << endl;
            cerr << "=>\t Count:" << count << endl;
            cerr << "=>\t Misssing:" << (ct.getNX() * ct.getNY()* ct.getNZ()) - count << endl;
        }

        file.close();
        //ct.set()
    }
}

