#ifndef FINITE_DIFFERENCES_HPP
# define FINITE_DIFFERENCES_HPP

#include "Common.hpp"

inline double finite_difference_delta(double S, double K, double r, double q, double sigma, double T, double h)
{
    const double C_0 = bs_price_call(S, K, r, q, sigma, T); // C(S)
    const double C_1 = bs_price_call(S + h, K, r, q, sigma, T); // C(S + h)

    return (C_1 - C_0) / (h);
}
inline double finite_difference_gamma(double S, double K, double r, double q, double sigma, double T, double h)
{  
    const double C_0 = bs_price_call(S, K, r, q, sigma, T); // C(S)
    const double C_1 = bs_price_call(S + h, K, r, q, sigma, T); // C(S + h)
    const double C_2 = bs_price_call(S + 2 * h, K, r, q, sigma, T); // C(S + 2h)

    return (C_2 - 2 * C_1 + C_0) / (h * h);
}

#endif 
