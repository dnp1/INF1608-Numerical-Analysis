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


    int ImageData::discoverMaxValue()
    {
        int               max = -1;
        for (unsigned int i   = 0; i < nX * nY; i++) {
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
        file << "P2" << endl;
        file << nX << " " << nY << endl;
        file << getMaxValue();


        for (unsigned int i = 0; i < nX * nY; i++) {
            if (i % nX == 0) {
                file << endl;
            }
            file << (unsigned int) data[i] << " ";
        }

        file.close();
    }

    unsigned int ImageData::getNX() const
    {
        return nX;
    }

    unsigned int ImageData::getNY() const
    {
        return nY;
    }
}


