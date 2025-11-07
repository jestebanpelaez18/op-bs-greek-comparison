#ifndef COMPLEX_DIFFERENTIATION_HPP
# define COMPLEX_DIFFERENTIATION_HPP

#include "Common.hpp"

inline double complex_step_delta(double S, double K, double r, double q, double sigma, double T, double h)
{
    const std::complex<double> S_c(S, h);

    const std::complex<double> C_ri = bs_price_call_t<std::complex<double>>(S_c, K, r, q, sigma, T); // C(S + h)

    return std::imag(C_ri) / (h);

}
inline double complex_step_gamma_real(double S, double K, double r, double q, double sigma, double T, double h)
{  
    const std::complex<double> S_c(S, h);
    
    const std::complex<double> C_ri = bs_price_call_t<std::complex<double>>(S_c, K, r, q, sigma, T); // C(S + h)
    const double C_S = bs_price_call(S, K, r, q, sigma, T); // C(S)

    return -2.0 * (std::real(C_ri) - C_S) / (h * h);
}

inline double complex_step_gamma_45(double S, double K, double r, double q, double sigma, double T, double h)
{  
    const std::complex<double> S_1(S + (h / std::sqrt(2)), (h / std::sqrt(2))); // S + hw
    const std::complex<double> S_2(S - (h / std::sqrt(2)), (-h / std::sqrt(2))); // S - hw

    const std::complex<double> C_1 = bs_price_call_t<std::complex<double>>(S_1, K, r, q, sigma, T); // C(S + hw)
    const std::complex<double> C_2 = bs_price_call_t<std::complex<double>>(S_2, K, r, q, sigma, T); // C(S - hw)

    return std::imag(C_1 + C_2) / (h * h);
}
#endif 