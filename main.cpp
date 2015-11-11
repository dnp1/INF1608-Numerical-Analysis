#include <iostream>


#include "modules/helper.h"
#include "modules/ImageData.h"
#include "modules/tarefa.h"

using namespace scan;
using namespace std;
using namespace image;


int main(void)
{

    auto ct  = CtScan(256, 256, 99);
    auto img = ImageData(128, 99);

    helper::LoadFileToCtScan("resources/head-8bit.raw", ct);
    tarefa::PerformTask(ct, img);
    img.printToFile("output.pgm");

    cout << endl << "=> Terminou!" << endl;
    //Array<int, ThreeIndexes>* labels = new Array<int>(10,20);

    return 0;
}