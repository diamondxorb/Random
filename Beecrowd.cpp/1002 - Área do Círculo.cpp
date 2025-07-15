#include <iostream>
#include <iomanip>
using namespace std;

int main () {
    double area, raio;
    cin >> raio;
    area = raio*raio*3.14159;
    cout << "A=" << setprecision(4) << fixed << area << endl;
    return 0;
}
