#include <iostream>
#include <iomanip>
using namespace std;

int main () {
    double altura, pesoIdeal;
    char sexo;
    bool fag = false;
    
    cin >> altura;
    getchar();
    cin >> sexo;
    
    if((sexo=='m' || sexo=='f') && altura>0) {
        fag = true;
    }
    
    if(fag) {
        if(sexo=='m') {
            pesoIdeal = (altura*72.7)-58;
        } else {
            pesoIdeal = (altura*62.1)-44.7;
        }
        
        cout << setprecision(1) << fixed << pesoIdeal << "kg" << endl;
    
    } else {
        cout << "Entrada inválida!\n" << endl;
    }

    return 0;
}
