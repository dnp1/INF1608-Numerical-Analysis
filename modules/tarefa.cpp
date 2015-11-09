#include "tarefa.h"

#include <tgmath.h>
#include <functional>
#include <iostream>


using namespace scan;
using namespace image;
using std::function;
namespace tarefa
{
    static const double       BYTE_LIMIT = 255.0;
    static const unsigned int M          = 28;


    /**
    *
    */
    static double Simpson(double leftBound, double rightBound, unsigned int m, function<double(double x)> (f))
    {
        double       h  = (rightBound - leftBound) / (2 * m);
        double       xi = leftBound;
        unsigned int i;

        double soma_pares   = 0;
        double soma_impares = 0;

        for (i = 1; i < 2 * m; i++) {
            xi += h;

            if (i % 2 == 0) {
                soma_pares += f(xi);
            } else {
                soma_impares += f(xi);
            }
        }

        return (h / 3) * (f(leftBound) + f(rightBound) + 4 * soma_impares + 2 * soma_pares);
    }


    // Esta é uma função auxiliar que gera uma função a ser usada em simpson. C++11 requerido!
    function<double(double jf)> createTransference(CtScan* const ct, unsigned int i, unsigned int k)
    {
        const auto result = [i, k, ct](double jf) {
            unsigned int jInx = (unsigned int) floor(jf);

            double j    = (double) jInx;
            double imJ  = ((double) ct->get(i, jInx, k));
            double imJ_ = ((double) ct->get(i, (jInx + 1 < ct->getNY()) ? (jInx + 1) : ct->getNY() - 1, k));

            double value = imJ + (imJ_ - imJ) * (jf - j);

            if (value > BYTE_LIMIT) {
                std::cerr << "Opps, value too great!!!" << std::endl;
            }

            value /= BYTE_LIMIT;

            if (value < .3) {
                return 0.0;
            }

            return .05 * (value - .3);

        };
        return [result](double jf) {
            return result(jf) * exp(-Simpson(0, jf, M, result));
        };
    }

    void PerformTask(CtScan &ct, ImageData &img)
    {

        for (unsigned int i = 0; i < img.getNX() - 1; i++) {
            for (unsigned int k = 0; k < img.getNY(); k++) {
                auto          f1    = createTransference(&ct, 2 * i, k); // cria função para integração.
                double        int1  = Simpson(0, 255.0, M, f1);
                auto          f2    = createTransference(&ct, 2 * i + 1, k); // cria função para integração.
                double        int2  = Simpson(0, 255.0, M, f2);
                unsigned char value = (unsigned char) ((int1 + int2) / 2.0 * 255.0); // falta fazer o ponto médio!!!!

                img.setPixel(i, k, value);
            }
        }
    }
}