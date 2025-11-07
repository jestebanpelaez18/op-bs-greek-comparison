#include "../includes/Common.hpp"
#include "../includes/AnalyticGreek.hpp"
#include "../includes/FiniteDifferences.hpp"  
#include "../includes/ComplexDifferentiation.hpp"

static void run_case(const char* title, double S, double K, double r, double q, double sigma, double T)
{
    const double h = std::sqrt(std::numeric_limits<double>::epsilon()) * S; // Machine epsilon (precision limit)
    // --- Analytic ---
    const double price = bs_price_call(S,K,r,q,sigma,T);
    const double d_an  = analytic_delta(S,K,r,q,sigma,T);
    const double g_an  = analytic_gamma(S,K,r,q,sigma,T);

    // --- Finite Differences ---
    const double d_fd = finite_difference_delta(S,K,r,q,sigma,T,h);
    const double g_fd = finite_difference_gamma(S,K,r,q,sigma,T,h);

    //-- Complex-Step Differentiation ---
    const double d_cs = complex_step_delta(S,K,r,q,sigma,T,h);
    const double g_cs_r = complex_step_gamma_real(S,K,r,q,sigma,T,h);
    const double g_cs_45 = complex_step_gamma_45(S,K,r,q,sigma,T,h);

  std::cout << "=== " << title << " ===\n"
              << "S="<<S<<" K="<<K<<" r="<<r<<" q="<<q<<" sig="<<sigma<<" T="<<T<<"\n"
              << "Price="<<price<<"\n"
              << "Delta  an="<<d_an
              << "  FD="<<d_fd  << "  |errFD|="<< std::abs(d_fd  - d_an)
              << "  CS="<<d_cs  << "  |errCS|="<< std::abs(d_cs  - d_an) << "\n"
              << "Gamma  an="<<g_an
              << "  FD="<<g_fd  << "  |errFD|="<< std::abs(g_fd  - g_an)
              << "  CSr="<<g_cs_r << "  |errCSr|="<< std::abs(g_cs_r - g_an)
              << "  CS45="<<g_cs_45<< "  |err45|="<< std::abs(g_cs_45- g_an) << "\n\n";
}

int main() {
    run_case("Scenario 1 (ATM ref)",            100,100,0.0,0.0,0.20,1.0);
    run_case("Scenario 2 (near-expiry, low-vol)",100,100,0.0,0.0,0.01,1.0/365.0);
    return 0;
}
