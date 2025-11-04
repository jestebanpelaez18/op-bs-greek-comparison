#ifndef ANALYTIC_GREEK_HPP
# define ANALYTIC_GREEK_HPP

#include "bs_call_price.h"
#include "Common.hpp"

inline double analytic_delta(double S, double K, double r, double q, double sigma, double T)
{
    const double F = S * std::exp((r - q) * T);
    const double vol =  sigma * std::sqrt(T); // denominator : sigma * sqrt(T)

    if (vol == 0.0) 
        return (F > K) ? std::exp(-q*T) : 0.0;
    const double d1 = (std::log(F / K) + 0.5 * sigma * sigma * T) / vol;

    return std::exp(-q*T) * Phi_real(d1);
}
inline double analytic_gamma(double S, double K, double r, double q, double sigma, double T)
{  
    const double F = S * std::exp((r - q) * T);
    const double vol =  sigma * std::sqrt(T); // denominator : sigma * sqrt(T)

    if (vol == 0.0) 
        return 0.0;

    const double d1 = (std::log(F / K) + 0.5 * sigma * sigma * T) / vol;

    return std::exp(-q*T) * phi(d1) / (S * sigma * std::sqrt(T));
}

#endif 
