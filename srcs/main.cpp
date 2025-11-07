#include "../includes/Common.hpp"
#include "../includes/AnalyticGreek.hpp"
#include "../includes/FiniteDifferences.hpp"  
#include "../includes/ComplexDifferentiation.hpp"
#include <fstream>


static void write_csv(const char* title, double S, double K, double r, double q, double sigma, double T)
{
    std::ofstream file(title);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << title << std::endl;
        return;
    }

    file << "h_rel,h,Delta_analytic,Delta_fd,Delta_cs,err_D_fd,err_D_cs,Gamma_analytic,Gamma_fd,Gamma_cs_real,Gamma_cs_45,err_G_fd,err_G_cs_real,err_G_cs_45\n";

    const int points = 24;
    const double log_start = -16.0; // From 10^-16
    const double log_end = -4.0; // To 10^-4
    const double log_step = (log_end - log_start) / (points - 1); // Uniform step in log10 space

    for (int i = 0; i < points; ++i) 
    {
        const double exponent = log_start + i * log_step; // Exponent for h_rel
        const double h_rel = std::pow(10.0, exponent); // Convert exponent to h_rel
        const double h = h_rel * S;

        // Analytic
        const double d_an  = analytic_delta(S,K,r,q,sigma,T);
        const double g_an  = analytic_gamma(S,K,r,q,sigma,T);

        // Finite Differences   
        const double d_fd = finite_difference_delta(S,K,r,q,sigma,T,h);
        const double g_fd = finite_difference_gamma(S,K,r,q,sigma,T,h);

        // Complex-Step Differentiation
        const double d_cs = complex_step_delta(S,K,r,q,sigma,T,h);
        const double g_cs_r = complex_step_gamma_real(S,K,r,q,sigma,T,h);
        const double g_cs_45 = complex_step_gamma_45(S,K,r,q,sigma,T,h);

        // Absolute Errors
        const double err_D_fd = std::abs(d_fd - d_an);
        const double err_D_cs = std::abs(d_cs - d_an);
        const double err_G_fd = std::abs(g_fd - g_an);
        const double err_G_cs_r = std::abs(g_cs_r - g_an);
        const double err_G_cs_45 = std::abs(g_cs_45 - g_an);
        
        // Created CSV line
        file << h_rel << "," << h << "," << d_an << "," << d_fd << "," << d_cs << ","
            << err_D_fd << "," << err_D_cs << "," << g_an << "," << g_fd << ","
            << g_cs_r << "," << g_cs_45 << "," << err_G_fd << "," << err_G_cs_r << ","
            << err_G_cs_45 << "\n";
    }

    file.close();
    std::cout << "CSV file created successfully: " << title << std::endl;

}
int main(void)
{
    write_csv("bs_fd_vs_complex_scenario1.csv",100,100,0.0,0.0,0.20,1.0);
    write_csv("bs_fd_vs_complex_scenario2.csv",100,100,0.0,0.0,0.01,1.0/365.0);

    return 0;
}