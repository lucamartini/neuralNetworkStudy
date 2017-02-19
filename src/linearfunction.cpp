#include "linearfunction.h"

LinearFunction::LinearFunction(float m, float q) :
    m(m),
    q(q) {
}

float LinearFunction::f(float x) const {
    return m*x + q;
}
