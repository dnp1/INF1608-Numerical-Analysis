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
    void LoadFileToCtScan(std::string fileName, CtScan &ct, bool print)
    {
        bool failed = false;
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
        if (print) {
            unsigned char     data;
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

                        ct.set(i, j, k, data);
                        data = ct.get(i, j, k);
                        cout << data << " ";
                    }

                    cout << endl;

                }

                cout << endl << "================" << endl;

            }
        }

        file.close();
        //ct.set()
    }
}

