#include <tgmath.h>
#include <functional>
#include <iostream>

#include "tarefa.h"
#include "simpson.h"


namespace tarefa
{
    using namespace scan;
    using namespace image;
    using namespace numerical_integration;

    using std::function;
    static const double       BYTE_LIMIT = 255.0;
    static const unsigned int M          = 28;

    double transference(double density)
    {
        if (density < .3) {
            return 0.0;
        }

        return .05 * (density - .3);
    }

    static inline double linearInterpolation(double x, double a, double b, double fa, double fb)
    {
        return fa + (fb - fa) * (x - a) / (b - a);
    }

    function<double(double jf)> createTransference(CtScan* const ct, unsigned int i, unsigned int k)
    {
        const auto result = [i, k, ct](double jf) {
            unsigned int jInx = (unsigned int) floor(jf);

            double j    = (double) jInx;
            double j_   = (double) jInx + 1;
            double imJ  = ((double) ct->get(i, jInx, k));
            double imJ_ = ((double) ct->get(i, (jInx + 1 < ct->getNY()) ? (jInx + 1) : ct->getNY() - 1, k));

            double value = linearInterpolation(jf, j, j_, imJ, imJ_);

            if (value > BYTE_LIMIT) {
                std::cerr << "Opps, value too great!!!" << std::endl;
            }

            value /= BYTE_LIMIT;

            return transference(value);
        };
        return [result](double jf) {
            return result(jf) * exp(-CompositeSimpson(0, jf, M, result));
        };
    }

    void PerformTask(CtScan &ct, ImageData &img)
    {

        for (unsigned int i = 0; i < img.getNX() - 1; i++) {
            for (unsigned int k = 0; k < img.getNY(); k++) {
                auto          f1    = createTransference(&ct, 2 * i, k); // cria função para integração.
                double        int1  = CompositeSimpson(0, 255.0, M, f1);
                auto          f2    = createTransference(&ct, 2 * i + 1, k); // cria função para integração.
                double        int2  = CompositeSimpson(0, 255.0, M, f2);
                unsigned char value = (unsigned char) ((int1 + int2) / 2.0 * 255.0); // falta fazer o ponto médio!!!!

                img.setPixel(i, k, value);
            }
        }
    }
}