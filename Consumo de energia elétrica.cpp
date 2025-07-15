#include <iostream>
#include <iomanip>
using namespace std;

int main () {
    double consumo, custoConsumo, dinheiro;
    
    cin >> consumo;
    
    if(consumo<=500) {
        dinheiro = (consumo*0.02)+5;
    } else if(consumo<=1000) {
        dinheiro = 55+((consumo-500)*0.05);
    } else {
        dinheiro = 355+((consumo-1000)*0.1);
    }
    
    custoConsumo = dinheiro-5;
    
    cout << setprecision(2) << fixed << custoConsumo << " 5.00 " << setprecision(2) << fixed << dinheiro << endl;
    
    return 0;
}
