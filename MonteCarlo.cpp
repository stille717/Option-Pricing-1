//
//  MonteCarlo.cpp
//  OptionsPricing
//

// =================================================================================================== //

//         Utilisation de la méthode de Monte Carlo pour pricer un call vanille européen

// ================================================================================================== //



// imports ------------------------------------------------------ //

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>


// Fonctions ---------------------------------------------------- //

// La fonction suivante permet de pricer un call via Monte Carlo.
// Les arguments sont les suivants
//             - S est le cours de l'action sous jacente à t=0
//             - K le strike du call
//             - T la maturité
//             - r le taux d'interet
//             - v la volatilité de l'action
double monte_carlo_call_pricer(const int &num_sims, const double &S, const double &K, const double &r, const double &v, const double &T) {
    double S_t_base = S * exp(T*(r-0.5*v*v));
    double S_t = 0.0;
    double payoff_sum = 0.0;
    
    // Les 3 lignes ci-dessous vont permettre de générer des valeurs à partir d'une normale N(0, 1)
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<> d{0,1};
    
    for (int i=0; i<num_sims; i++) {
        double x = d(gen);
        S_t = S_t_base * exp(sqrt(v*v*T)*x);
        payoff_sum += std::max(S_t - K, 0.0);
    }
    
    return (payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
}


// Programme ---------------------------------------------------- //

int main(int argc, char **argv) {
    // On initialise nos paramètre (strike, aturité, taux d'interet...)
    int num_sims = 10000000;   // Nombre de simulations
    double S = 100.0;  // Prix de l'action sous-jacente à t=0
    double K = 100.0;  // Strike
    double r = 0.05;   // Taux d'interet (5%)
    double v = 0.2;    // Volatilité du sous-jacent (ie du cours de l'action) (20%)
    double T = 1.0;    // Maturité
    
    // On calcule la valeur du call grace à la fonction définie précédemment
    double call = monte_carlo_call_pricer(num_sims, S, K, r, v, T);
    
    // On affiche nos paramètres ainsi que le résultat du calcul de la valeur du Call
    std::cout << "Nombre de simulations: " << num_sims << "\n";
    std::cout << "Sous-jacent:           " << S << "\n";
    std::cout << "Strike:                " << K << "\n";
    std::cout << "Taux d'interet:        " << r << "\n";
    std::cout << "Volatilité:            " << v << "\n";
    std::cout << "Maturité:              " << T << "\n";
    
    std::cout << "Prix du Call:          " << call << "\n";
    
    return 0;
}

// Résultats ------------------------------------------------ //
// On obtient: Prix du Call = 10.4525
