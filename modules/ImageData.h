//
// Created by danilo on 07/11/15.
//
#include <string>

using std::string;

#ifndef INF1608_NUMERICAL_ANALYSIS_IMAGEDATA_H
#define INF1608_NUMERICAL_ANALYSIS_IMAGEDATA_H

namespace image
{
    class ImageData
    {
    private:
        int          maxValue = -1;
        unsigned int nX;
        unsigned int nY;
        unsigned char* data = nullptr;

        int discoverMaxValue();


    public:
        ImageData(unsigned int x, unsigned int y);

        ~ImageData();

        unsigned int getNX() const;

        unsigned int getNY() const;

        unsigned char getPixel(unsigned int i, unsigned int j);

        void setPixel(unsigned int i, unsigned int j, unsigned char value);

        int getMaxValue();

        void printToFile(string fileName);
    };


}


#endif //INF1608_NUMERICAL_ANALYSIS_IMAGEDATA_H
