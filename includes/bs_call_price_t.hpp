#ifndef BS_CALL_PRICE_T_HPP
# define BS_CALL_PRICE_T_HPP

#include "Common.hpp"

inline double Phi_t(double z) 
{                
    return Phi_real(z);
}

inline std::complex<double> Phi_t(const std::complex<double>& z) 
{                
    const double z_r = z.real();
    const double z_i = z.imag();

    return std::complex<double>(Phi_t(z_r), phi(z_r) * z_i);
}

template <typename T>
T bs_price_call_t(T S, T K, T r, T q, T sigma, T T_mat)
{
    const T DF    = std::exp(-r * T_mat);
    const T F     = S * std::exp((r - q) * T_mat);
    const T sigmaT = sigma * std::sqrt(T_mat);

    const T d1 = (std::log(F / K) + T(0.5) * sigma * sigma * T_mat) / sigmaT;
    const T d2 = d1 - sigmaT;

    return DF * (F * Phi_t(d1) - K * Phi_t(d2));
}

#endif 