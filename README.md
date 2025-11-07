# op-bs-greek-comparison

# 🧮 Black–Scholes Greeks – Numerical Differentiation

## 📘 Project Overview

This project implements **numerical differentiation** for option Greeks (Delta $\Delta$ and Gamma $\Gamma$) under the **Black–Scholes model**. Three approaches were developed and compared:

* **Analytic Greeks** (reference implementation)
* **Forward Finite Differences**
* **Complex-Step Differentiation** (real-part and 45° variants)

The goal is to evaluate the numerical stability and accuracy of each method across a logarithmic grid of step sizes $h_{rel} \in [10^{-16}, 10^{-4}]$ for two validation scenarios.

---

## ⚙️ Build & Run Instructions

### 🧩 Requirements

* A **C++20** compatible compiler (e.g., `g++`)
* **GNU Make**

### 🔧 Build

To compile the main executable (`bin/main`):

```bash
make
```

### ▶️ Run

To compile and run the project directly:

```bash
make run
```
This command will:

1.  Compile the program (`bin/main`).
2.  Execute it automatically.
3.  Generate two **CSV files** with the results:
    * `bs_fd_vs_complex_scenario1.csv`
    * `bs_fd_vs_complex_scenario2.csv`

### 🧹 Cleanup

To clean the repository:

```bash
make clean       # removes executables and CSVs
```
To perform a full clean:

```bash
make fclean
```

## Validation Scenarios

| Scenario | Description | Parameters |
|-----------|--------------|------------|
| **1** | ATM reference | S = 100, K = 100, r = q = 0, σ = 0.20, T = 1 |
| **2** | Near-expiry, low-vol ATM | S = 100, K = 100, r = q = 0, σ = 0.01, T = 1/365 |

For each `h_rel`, the absolute step size is computed as `h = h_rel * S`.

---

## Implementation Summary

The codebase includes the following components:

| File | Description |
|------|--------------|
| **bs_call_price.h** | Core Black–Scholes call pricing function (Φ and φ helpers). |
| **AnalyticGreek.hpp** | Closed-form Δ and Γ formulas. |
| **FiniteDifferences.hpp** | Forward-difference Δ and Γ estimators. |
| **ComplexDifferentiation.hpp** | Complex-step Δ and Γ (real-part and 45° variants). |
| **main.cpp** | Sweep driver, generates CSV outputs for both scenarios. |
| **Makefile** | Simplified build system with `make`, `make run`, `make clean`. |

All functions were written in **C++20**, with `<complex>` for complex arithmetic.

## Plots / Small Tables

Each CSV was analyzed to summarize errors across all step sizes.  
Plots (created in Excel) include:

- `|Δ_error|` vs. `h_rel`
- `|Γ_error|` vs. `h_rel`

A compact summary is shown below (indicative values):

| Method | Δ Error (min) | Γ Error (min) | Stability |
|---------|---------------|---------------|------------|
| Finite Difference | ~1e-6 | ~1e-4 | Sensitive to h |
| Complex-Step (Real) | ~1e-12 | ~1e-10 | Very stable |
| Complex-Step (45°) | ~1e-12 | ~1e-10 | Very stable |

---

## Observations

- **Complex-step methods** maintained high accuracy for very small `h_rel`, avoiding cancellation.  
- **Finite differences** suffered from roundoff errors for `h_rel < 1e-8`.  
- Accuracy peaks around `h_rel ≈ 1e-5` for forward-difference.  
- Complex methods remained stable across all step sizes.  
- In low-volatility near-expiry scenarios, all errors increase slightly due to lower option curvature.

No NaNs or unstable results were encountered during sweeps.

---

## Brief Reasoning

The **finite-difference approach** experiences truncation error proportional to `O(h)` and roundoff error proportional to `O(1/h)`.  
These two competing sources produce an optimal `h` range, beyond which precision loss occurs.  

The **complex-step method** avoids subtractive cancellation by leveraging the imaginary perturbation of `S`, allowing extremely small `h` (e.g., 1e−15) with machine-precision accuracy.

---

## Recommendation

| Method | Suggested Use | Recommended Step Size |
|---------|----------------|------------------------|
| Finite Difference | Basic implementation; acceptable for moderate `h`. | `h_rel ≈ 1e−5` |
| Complex-Step (Real) | Highly stable; best general method. | Any small `h_rel` |
| Complex-Step (45°) | Same accuracy; slightly higher computational cost. | Any small `h_rel` |

---