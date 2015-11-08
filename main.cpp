#include <iostream>
#include <fstream>
#include <string>
#include <string.h>


#include "modules/helper.h"
#include "modules/ImageData.h"
#include "modules/CtScan.h"
#include "tarefa.h"

using namespace scan;
using namespace std;
using namespace image;




int main(void)
{
    const double L = 255;

    auto ct = CtScan(256, 256, 99);
    auto img = ImageData(128,99);
    printf("%d", ct.get(0,0,0));
    helper::LoadFileToCtScan("resources/head-8bit.raw", ct);
    task::task(ct, img);
    img.printToFile("output.pgm");



    cout << endl << "=> Fim!" <<endl;
    //Array<int, ThreeIndexes>* labels = new Array<int>(10,20);

    return 0;
}