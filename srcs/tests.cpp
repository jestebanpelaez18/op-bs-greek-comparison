#include "../includes/Common.hpp"            
#include "../includes/Analytic_Greek.hpp"   

static void print_case(const char* title, double S, double K, double r, double q, double sigma, double T,double price, double delta, double gamma)
{
    std::cout << "=== " << title << " ===\n"
              << "S=" << S << "  K=" << K
              << "  r=" << r << "  q=" << q
              << "  sigma=" << sigma << "  T=" << T << "\n"
              << "price=" << price
              << "  delta=" << delta
              << "  gamma=" << gamma << "\n\n";
}

int main(void) 
{    // ---------- Scenario 1: ATM reference ----------
    {
        const double S=100.0, K=100.0, r=0.0, q=0.0, sigma=0.20, T=1.0;
        const double price = bs_price_call(S,K,r,q,sigma,T);
        const double delta = analytic_delta(S,K,r,q,sigma,T);
        const double gamma = analytic_gamma(S,K,r,q,sigma,T);

        assert(delta > 0.0 && delta < 1.0);
        assert(gamma > 0.0);

        print_case("Scenario 1 (ATM reference)", S,K,r,q,sigma,T, price, delta, gamma);
    }

    // ---------- Scenario 2: Near-expiry, low-vol, ATM ----------
    {
        const double S=100.0, K=100.0, r=0.0, q=0.0, sigma=0.01, T=(1.0/365.0);
        const double price = bs_price_call(S,K,r,q,sigma,T);
        const double delta = analytic_delta(S,K,r,q,sigma,T);
        const double gamma = analytic_gamma(S,K,r,q,sigma,T);

        // Propiedades generales
        assert(delta > 0.0 && delta < 1.0);
        assert(gamma > 0.0);

        print_case("Scenario 2 (near-expiry, low-vol, ATM)", S,K,r,q,sigma,T, price, delta, gamma);
    }

    std::cout << "Analytic checks passed (basic invariants).\n";
    return 0;
}
