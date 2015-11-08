#include <tgmath.h>
#include <functional>
#include "CtScan.h"

#include "task.h"

using namespace scan;

namespace task
{
    static const double BYTE_LIMIT = 255.0;
    static double transference(double densityValue)
    {
        if (densityValue < .3) {
            return 0;
        }
        return .05 * (densityValue - .3);
    }

    std::function<double (unsigned int)> createDensity(CtScan &ct, unsigned int i, unsigned int k ) {
        return [i,k,ct] (unsigned int jf) {
            unsigned int j = (unsigned int) floor(jf);

            double value = ((double) ct.get(i, j, k)) / BYTE_LIMIT;
            double value2 = ((double) ct.get(i, j + 1, k)) / BYTE_LIMIT;


            return value / 255.0;
        };
    }

    static double density(double jf) {



        return jf;
    }
}