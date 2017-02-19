#pragma once

class LinearFunction {
public:
    LinearFunction(float m, float q);
    float f(float x) const;
private:
    float m;
    float q;
};
