#include <iostream>
#include <cmath>
using namespace std;

class FunctionA {
public:
    double calculate(double x, double y, double z, double b) {
        double t1 = z / (x * x) + pow(sin(b), 2),
            t2 = t1 / (x + y),
            t3 = t2 / (z + pow(x, 3) / 3.0);
        return y * y + t3 - log(fabs(x * x + z));
    }
};

class FunctionB {
public:
    double calculate(double x, double y, double z) {
        double t1 = fabs((x + y) / pow(fabs(z), 0.6)),
            inner = fabs((x + z * z) / (2 * x + y)),
            t2 = pow(sin(pow(inner, 1.0 / 3.0)), 2),
            t3 = z * exp((x * x - y) / (1 + z));
        return t1 + t2 - t3;
    }
};

int main() {
    int v = 4;
    double x = 0.48 * v, y = 0.47 * v, z = -1.32 * v, b = 1.0;

    FunctionA fa;
    FunctionB fb;

    cout << "x=" << x << " y=" << y << " z=" << z << " b=" << b << endl;
    cout << "a[x,y,z,b] = " << fa.calculate(x, y, z, b) << endl;
    cout << "b[x,y,z] = " << fb.calculate(x, y, z) << endl;

    return 0;
}