#include "../includes/Common.hpp"
#include "../includes/Analytic_Greek.hpp"
#include "../includes/Finite_Differences.hpp"  

static void run_case(const char* title, double S, double K, double r, double q, double sigma, double T)
{
    // --- Analytic ---
    const double price = bs_price_call(S,K,r,q,sigma,T);
    const double d_an  = analytic_delta(S,K,r,q,sigma,T);
    const double g_an  = analytic_gamma(S,K,r,q,sigma,T);

    // --- Finite Differences ---
    const double d_fd = finite_difference_delta(S,K,r,q,sigma,T);
    const double g_fd = finite_difference_gamma(S,K,r,q,sigma,T);

    std::cout << title << " | "
              << "S="<<S<<" K="<<K<<" r="<<r<<" q="<<q<<" sig="<<sigma<<" T="<<T<<" | "
              << "Price="<<price<<" | "
              << "Δ an="<<d_an<<" FD="<<d_fd<<" err="<<std::abs(d_fd-d_an) << " | "
              << "Γ an="<<g_an<<" FD="<<g_fd<<" err="<<std::abs(g_fd-g_an) << "\n";
}

int main() {
    run_case("Scenario 1 (ATM ref)",            100,100,0.0,0.0,0.20,1.0);
    run_case("Scenario 2 (near-expiry, low-vol)",100,100,0.0,0.0,0.01,1.0/365.0);
    std::cout << "Analytic & FD checks passed.\n";
    return 0;
}
