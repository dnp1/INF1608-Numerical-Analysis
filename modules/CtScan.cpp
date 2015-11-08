//
// Created by danilo on 07/11/15.
//

#include <malloc.h>
#include <assert.h>
#include <iostream>
#include <fstream>

#include "CtScan.h"

namespace scan
{
    CtScan::CtScan(unsigned int x, unsigned int y, unsigned int z)
    {
        size_t numberOfMembers;
        nX = x;
        nY = y;
        nZ = z;

        numberOfMembers = x * y * z;

        data = (unsigned char*) calloc(numberOfMembers, sizeof(unsigned char));
    }

    CtScan::~CtScan()
    {
        if (data != nullptr) {
            free(data);
        }
    }


#define access_assert(i,j,k) assert(k < nZ &&  j < nY && i < nX)
#define calc_index(i,j,k) k * nX * nY + j * nX + i
    /** **/
    void CtScan::set(unsigned int i, unsigned int j, unsigned int k,  unsigned char value)
    {
        access_assert(i,j,k);
        data[calc_index(i,j,k)] = value;
    }

    unsigned char CtScan::get(unsigned int i, unsigned int j, unsigned int k) const
    {
        access_assert(i,j,k);
        return data[calc_index(i,j,k)];
    }

    unsigned int CtScan::getNX() const
    {
        return nX;
    }

    unsigned int CtScan::getNY() const
    {
        return nY;
    }

    unsigned int CtScan::getNZ() const
    {
        return nZ;
    }

#undef access_assert
#undef calc_index


    unsigned int CtScan::getSizeInBytes() const
    {
        return getNX() * getNZ() * getNY();
    }

    unsigned char* CtScan::getReferenceToData() const
    {
        return data;
    }
}