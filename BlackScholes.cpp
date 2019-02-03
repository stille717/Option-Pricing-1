//
//  BlackScholes.cpp
//  OptionsPricing
//


// =================================================================================================== //

//         Utilisation de la formule de Black-Scholes pour pricer un call vanille européen

// ================================================================================================== //



// imports ------------------------------------------------------ //

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>


// Fonctions ---------------------------------------------------- //

// Densité de probabilité d'une loi normale N(0, 1)
double densite_norm(const double &x) {
    return (1.0/(pow(2*M_PI,0.5)))*exp(-0.5*x*x);
}

// La fonction suivante est une approximation de la f.d.r de la loi normale N(0, 1)
double fdr_norm(const double &x) {
    double k = 1.0/(1.0 + 0.2316419*x);
    double k_sum = k*(0.319381530 + k*(-0.356563782 + k*(1.781477937 + k*(-1.821255978 + 1.330274429*k))));
    
    if (x >= 0.0) {
        return (1.0 - (1.0/(pow(2*M_PI,0.5)))*exp(-0.5*x*x) * k_sum);
    } else {
        return 1.0 - fdr_norm(-x);
    }
}

// La fonction suivante calcule le terme d_j (pour j=0 ou 1) de la formule de Black-Scholes
// Les arguments sont les suivants
//             - S est le cours de l'action sous jacente à t=0
//             - K le strike du call
//             - T la maturité
//             - r le taux d'interet
//             - v la volatilité de l'action
double d_j(const int &j, const double &S, const double &K, const double &r, const double &v, const double &T) {
    return (log(S/K) + (r + (pow(-1,j-1))*0.5*v*v)*T)/(v*(pow(T,0.5)));
}

// La fonction suivante permet de pricer un call via la formule de Black-Scholes.
// Les arguments sont les suivants
//             - S est le cours de l'action sous jacente à t=0
//             - K le strike du call
//             - T la maturité
//             - r le taux d'interet
//             - v la volatilité de l'action
double call_price(const double& S, const double& K, const double& r, const double& v, const double& T) {
    return S * fdr_norm(d_j(1, S, K, r, v, T))-K*exp(-r*T) * fdr_norm(d_j(2, S, K, r, v, T));
}



// Programme ---------------------------------------------------- //

int main(int argc, char **argv) {
    // On initialise nos paramètre (strike, aturité, taux d'interet...)
    double S = 100.0;  // Prix de l'action sous-jacente à t=0
    double K = 100.0;  // Strike
    double r = 0.05;   // Taux d'interet (5%)
    double v = 0.2;    // Volatilité du sous-jacent (ie du cours de l'action) (20%)
    double T = 1.0;    // Maturité
    
    // On calcule la valeur du call grace à la fonction définie précédemment
    double call = call_price(S, K, r, v, T);
    
    // On affiche nos paramètres ainsi que le résultat du calcul de la valeur du Call
    std::cout << "Sous-jacent:           " << S << "\n";
    std::cout << "Strike:                " << K << "\n";
    std::cout << "Taux d'interet:        " << r << "\n";
    std::cout << "Volatilité:            " << v << "\n";
    std::cout << "Maturité:              " << T << "\n";
    
    std::cout << "Prix du Call :         " << call << "\n";
    
    return 0;
}


// Résultats ------------------------------------------------ //
// On obtient: Prix du Call = 10.4506
