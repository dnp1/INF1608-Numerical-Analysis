#include <iostream>
#include <fstream>
#include <string>
#include <string.h>


#include "modules/helper.h"

#include "modules/CtScan.h"

using namespace scan;
using namespace std;
using helper::LoadFileToCtScan;



int main(void)
{
    CtScan* ct = new CtScan(256,256,99);
    LoadFileToCtScan("resources/head-8bit.raw", *ct, false);
    //Array<int, ThreeIndexes>* labels = new Array<int>(10,20);
    cout << "Hello, World!" << endl;
    return 0;
}