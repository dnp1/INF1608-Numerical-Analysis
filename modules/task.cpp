#include <tgmath.h>
#include "task.h"


namespace task
{
    static double transference(double densityValue)
    {
        if (densityValue < .3) {
            return 0;
        }
        return .05 * (densityValue - .3);
    }
    static double density(double jf) {
        unsigned int j = (unsigned int) floor(jf);

    }
}