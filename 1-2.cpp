#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double y = 0.47 * 4;
    double z = -1.32 * 4;
    double b = 1.0;

    double x = -1.0;

    while (x <= 1.0) {

        double a, bb;

        if (x == 0) {
            cout << "x = " << x << "  a = ne vyznachena";
        }
        else {
            a = y * y + (z / (x * x) + sin(b) * sin(b)) / (x + y) / (z + x * x * x / 3.0) - log(fabs(x * x + z));
            cout << "x = " << x << "  a = " << a;
        }

        bb = fabs(x + y) / pow(fabs(z), 0.6) + pow(sin(pow(fabs((x + z * z) / (2 * x + y)), 1.0 / 3.0)), 2) - z * exp((x * x - y) / (1 + z));
        cout << "  b = " << bb << endl;

        x = x + 0.2;
    }

    return 0;
}