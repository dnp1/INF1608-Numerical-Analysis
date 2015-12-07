//
// Created by danilo on 11/11/15.
//

#include <functional>

#ifndef INF1608_NUMERICAL_ANALYSIS_SIMPSON_H
#define INF1608_NUMERICAL_ANALYSIS_SIMPSON_H

namespace numerical_integration {
    using std::function;

    double CompositeSimpson(double leftBound, double rightBound, unsigned int numberOfSteps,
                            function<double(double x)> (f));

    double Simpson(double leftBound, double rightBound, function<double(double x)> (f));

    double DoubleSimpson(double leftBound, double rightBound, function<double(double x)> (f));

    double AdaptativeSimpson(double a, double b, function<double(double x)> (f), double tol);
}
#endif //INF1608_NUMERICAL_ANALYSIS_SIMPSON_H
