#include <iostream>
#include <fstream>
#include <string>
#include <string.h>


#include "modules/helper.h"

#include "modules/CtScan.h"

using namespace scan;
using namespace std;





int main(void)
{
    const double L = 255;

    CtScan* ct = new CtScan(256, 256, 99);
    helper::LoadFileToCtScan("resources/head-8bit.raw", *ct);

    //Array<int, ThreeIndexes>* labels = new Array<int>(10,20);

    return 0;
}