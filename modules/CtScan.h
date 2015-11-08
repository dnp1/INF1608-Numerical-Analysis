//
// Created by danilo on 07/11/15.
//

#include <string>

#ifndef INF1608_NUMERICAL_ANALYSIS_CTSCAN_H
#define INF1608_NUMERICAL_ANALYSIS_CTSCAN_H

namespace scan
{
    class CtScan
    {
    private:
        unsigned char* data = nullptr;
        unsigned int nX       = 0;
        unsigned int nY       = 0;
        unsigned int nZ       = 0;

    public:
        CtScan(unsigned int x, unsigned int y, unsigned int z);
        ~CtScan();
        unsigned char get(unsigned int i, unsigned int j, unsigned int k);
        void set(unsigned int i, unsigned int j, unsigned int k, unsigned char value);
        // CtScan& loadFromFile(std::string fileName);
        unsigned int getNX() const ;
        unsigned int getNY() const ;
        unsigned int getNZ() const ;
        unsigned int getSizeInBytes() const;
        unsigned char* getReferenceToData() const ; //Unsafe!!!!! you can do anything with a pointer!

    };
}


#endif //INF1608_NUMERICAL_ANALYSIS_CTSCAN_H
