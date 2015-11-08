//
// Created by danilo on 08/11/15.
//

#include "simpson.h"
#include <math.h>
#include <stdio.h>

namespace numerical_methods {


    double Simpson(double a, double b, double m, double (* f)(double x))
    {
        double h  = (b - a) / (2 * m);
        double xi = a;
        int    i;

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

        return h / 3 * (f(a) + f(b) + 4 * soma_impares + 2 * soma_pares);
    }


}