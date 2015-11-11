//
// Created by danilo on 11/11/15.
//

#include <tgmath.h>

#include "simpson.h"


namespace numerical_integration
{

    using std::function;

    static void swap(double &a, double &b)
    {
        double aux = b;
        b = a;
        a = aux;
    }

    double CompositeSimpson(double leftBound, double rightBound, unsigned int numberOfSteps,
                            function<double(double x)> (f))
    {
        if (leftBound > rightBound) {
            swap(leftBound, rightBound);
        }

        double       h  = (rightBound - leftBound) / (2 * numberOfSteps);
        double       xi = leftBound;
        unsigned int i;

        double soma_pares   = 0;
        double soma_impares = 0;

        for (i = 1; i < 2 * numberOfSteps; i++) {
            xi += h;

            if (i % 2 == 0) {
                soma_pares += f(xi);
            } else {
                soma_impares += f(xi);
            }
        }

        return (h / 3) * (f(leftBound) + f(rightBound) + 4 * soma_impares + 2 * soma_pares);
    }

    double Simpson(double leftBound, double rightBound, function<double(double x)> (f))
    {
        if (leftBound > rightBound) {
            swap(leftBound, rightBound);
        }
        double h = (rightBound - leftBound);
        return (h / 6) * (f(leftBound) + f(rightBound) + 4 * f((leftBound + rightBound) / 2));
    }

    double DoubleSimpson(double leftBound, double rightBound, function<double(double x)> (f))
    {
        if (leftBound > rightBound) {
            swap(leftBound, rightBound);
        }

        double c = (leftBound + rightBound) / 2;
        return Simpson(leftBound, c, f) + Simpson(c, rightBound, f);

    }

    double AdaptativeSimpson(double a, double b, function<double(double x)> (f), double tol)
    {
        double ab    = Simpson(a, b, f);
        double ac_cb = DoubleSimpson(a, b, f);
        if (fabs(ab - ac_cb) < 15 * tol) {
            return ac_cb;
        }
        double c = (a + b) / 2;
        return AdaptativeSimpson(a, c, f, tol / 2) + AdaptativeSimpson(c, b, f, tol / 2);
    }
}