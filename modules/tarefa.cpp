#include "tarefa.h"

#include <tgmath.h>
#include <functional>
#include <iostream>


using namespace scan;
using namespace image;
using std::function;
namespace task
{
    static const double BYTE_LIMIT = 255.0;

    /**
    *
    */
    static double Simpson(double leftBound, double rightBound, double h, function<double(double x)> (f))
    {
        int    i;
        double jf           = leftBound;
        double soma_pares   = 0;
        double soma_impares = 0;


        for (i = 1, jf = leftBound; jf <= (rightBound - 1.0 - 2*h); jf += h, i++) {
            if (i % 2 == 0) {
                soma_pares +=  f(jf);
            } else {
                soma_impares += f(jf);
            }
        }

        return h / 3 * (f(leftBound) + f(rightBound) + 4 * soma_impares + 2 * soma_pares);
    }

    // Esta é uma função auxiliar que gera uma função a ser usada em simpson. C++11 requerido!
    function<double(double jf)> createTransference(CtScan const *ct, unsigned int i, unsigned int k)
    {
        return [i, k, ct](double jf) {
            unsigned int jInx = (unsigned int) floor(jf);
//            if (jInx >= 255) {
//                std::cout << jInx << std::endl;
//            }

            double j = (double) jInx;
            double imJ  = ((double) ct->get(i, jInx, k));
            double imJ_ = ((double) ct->get(i, (jInx+1 < ct->getNY()) ? (jInx + 1) : ct->getNY() - 1 , k));

            double value = imJ + (imJ_ - imJ) * (jf - j);

            if (value > BYTE_LIMIT ) {
                std::cerr << "Opps, value too great!!!" << std::endl;
            }

            value /= BYTE_LIMIT;

            if (value < .3) {
                return 0.0;
            }
            return .05 * (value - .3);

        };
    }


    void task(CtScan &ct, ImageData &img) {

        for(unsigned int i = 0; i < img.getNX() -1 ; i++) {
            for(unsigned int k = 0; k < img.getNY(); k++) {
                auto f = createTransference(&ct, 2 * i, k); // cria função para integração.
                double int1 = Simpson(0, 255.0, 4.5, f);
                auto f2 = createTransference(&ct, 2 * i + 1, k); // cria função para integração.
                double int2 = Simpson(0, 255.0, 4.5, f2);

                unsigned char value = (unsigned char) ((int1 + int2 / 2) * 255); // falta fazer o ponto médio!!!!

                img.setPixel(i,k, value);
            }
        }
    }
}