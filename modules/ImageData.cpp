//
// Created by danilo on 07/11/15.
//
#include <fstream>
#include <iostream>
#include <assert.h>
#include "ImageData.h"

namespace image
{

    image::ImageData::ImageData(unsigned int x, unsigned int y)
    {
        size_t numberOfMembers;
        nX              = x;
        nY              = y;
        numberOfMembers = x * y;

        data = (unsigned char*) calloc(numberOfMembers, sizeof(unsigned char));
    }

    image::ImageData::~ImageData()
    {
        if (data != nullptr) {
            free(data);
        }
    }

#define access_assert() assert(j < nY && i < nX)
#define calc_index() j * nX + i

    unsigned char image::ImageData::getPixel(unsigned int i, unsigned int j)
    {
        access_assert();
        return data[calc_index()];
    }

    void image::ImageData::setPixel(unsigned int i, unsigned int j, unsigned char value)
    {
        access_assert();
        data[calc_index()] = value;

    }

#undef access_assert
#undef calc_index

    void image::ImageData::setMaxValue(int maxValue)
    {
        this->maxValue = maxValue;
    }


    int ImageData::discoverMaxValue()
    {
        int               max;
        for (unsigned int i = 0; i < nX * nY; i++) {
            if (data[i] > max) {
                max = data[i];
            }
        }
        return max;
    }

    int image::ImageData::getMaxValue()
    {
        if (maxValue >= 0) {
            return maxValue;
        }

        return discoverMaxValue();
    }

    void image::ImageData::printToFile(string fileName)
    {
        using std::ofstream;
        using std::endl;
        using std::cerr;

        ofstream file;
        file.open(fileName, std::ofstream::out | std::ofstream::trunc);
        if (!file.is_open()) {
            cerr << "File could not be opened!" << endl;
            return;
        }

        file << nY << " " << nX << endl;
        file << getMaxValue() << endl;


        for (unsigned int i = 0; i < nX * nY; i++) {
            if (i % nY == 0) {
                file << endl;
            }
            file << data[i];
        }

        file.close();
    }
}


