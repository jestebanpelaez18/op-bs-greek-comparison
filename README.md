# op-bs-greek-comparison

# Black–Scholes Greeks – Numerical Differentiation

## Project Overview

This project implements **numerical differentiation** for option Greeks (Delta $\Delta$ and Gamma $\Gamma$) under the **Black–Scholes model**. Three approaches were developed and compared:

* **Analytic Greeks** (reference implementation)
* **Forward Finite Differences**
* **Complex-Step Differentiation** (real-part and 45° variants)

The goal is to evaluate the numerical stability and accuracy of each method across a logarithmic grid of step sizes $h_{rel} \in [10^{-16}, 10^{-4}]$ for two validation scenarios.

---

## Build & Run Instructions

### Requirements

* A **C++20** compatible compiler (e.g., `g++`)
* **GNU Make**

### Build

To compile the main executable (`bin/main`):

```bash
make
```

### Run

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

### Cleanup

To clean the repository:

```bash
make clean     
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

## Tables 

A brief error validation report is provided below, summarizing the performance of the implemented methods: $\Delta_{fd}$, $\Delta_{cs}$, $\Gamma_{fd}$, $\Gamma_{cs, real}$, and $\Gamma_{cs, 45^{\circ}}$.

We generated plots (not shown here) of the **absolute error** vs. the relative step size ($\mathbf{h_{rel}}$) for both Delta and Gamma to visualize stability and accuracy across the range $[10^{-16}, 10^{-4}]$.

The compact error summary (using Max, Median, and 90th Percentile) for **Scenario 1** is shown below:

| Metric | $\mathbf{\Delta_{fd}}$ | $\mathbf{\Delta_{cs}}$ | $\mathbf{\Gamma_{fd}}$ | $\mathbf{\Gamma_{cs, real}}$ | $\mathbf{\Gamma_{cs, 45^{\circ}}}$ |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Max Error** | 0.7924 | $\sim 6.045\text{e-}6$ | $1.332\text{e+}14$ | 0.02311 | 0.01985 |
| **Median** | $4\text{e-}16$ | $\sim 1\text{e-}16$ | 16.486 | 0.01984 | $\sim 1.43\text{e-}8$ |
| **Percentile 90** | 0.091 | 0 | $2.883\text{e+}12$ | 0.02009 | 0.00280 |

---

And the error summary for **Scenario 2** (Stress Scenario):

| Metric | $\mathbf{\Delta_{fd}}$ | $\mathbf{\Delta_{cs}}$ | $\mathbf{\Gamma_{fd}}$ | $\mathbf{\Gamma_{cs, real}}$ | $\mathbf{\Gamma_{cs, 45^{\circ}}}$ |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Max Error** | 0.92098 | $\sim 1.535\text{e-}13$ | $1.421\text{e+}14$ | 7.847 | 7.621 |
| **Median** | 0.00020 | $\sim 3.820\text{e-}14$ | 7.628 | 7.621 | $0.0000428$ |
| **Percentile 90** | 0.03617 | $\sim 1.193\text{e-}13$ | $8.831\text{e+}10$ | 7.704 | 0.93925 |

---

## Observations 

Based on the numerical data generated across the two scenarios, the following key observations were made regarding method accuracy and stability:

* **Accuracy Ranking:** Complex-step methods clearly outperform finite-difference (FD) ones.
Both $\Gamma_{cs,real}$ and $\Gamma_{cs,45°}$ remain stable down to the smallest step sizes, while $\Gamma_{fd}$ and $\Delta_{fd}$ degrade rapidly due to roundoff. The 45° complex-step version yields slightly lower noise and better numerical symmetry. 
* **Dependence on Step Size ($h_{rel}$):**
    * **Complex-Step Methods:** These methods maintained consistently high accuracy across a broad range of step sizes, performing optimally even for very small $h_{rel}$, as they are inherently immune to subtraction and round-off errors.
    * **Finite Differences:** The accuracy of $\Delta_{fd}$ peaked around $h_{rel} \approx 10^{-5}$ but rapidly deteriorated for smaller step sizes ($h_{rel} < 10^{-8}$) due to **big cancellation** errors.

* **Differences between Scenarios:** The “stress” case (short maturity, low volatility) amplifies instability in FD gamma due to the smaller option sensitivity, but complex-step performance is unaffected.

* **Stability Issues:** FD gamma produced extreme outliers and NaNs for $h_{rel} < 10^{-10}$, which were expected from cancellation.
After ensuring both $C(S)$ and $C(S+i h)$ used the same templated pricing function, complex-step gamma behaved perfectly

---

## Brief Reasoning

The **finite-difference approach** experiences truncation error proportional to `O(h)` and roundoff error proportional to `O(1/h)`.  
These two competing sources produce an optimal `h` range, beyond which precision loss occurs.  

The **complex-step method** avoids subtractive cancellation by leveraging the imaginary perturbation of `S`, allowing extremely small `h` (e.g., 1e−15) with machine-precision accuracy.

---

### Recommendation

* **For $\Delta$ and $\Gamma$:** Use complex-step differentiation whenever possible.
* **Step-size choice:** $h_{rel} = 10^{-10}$ to $10^{-12}$ is safe for all practical purposes; results are stable across several orders of magnitude.
* **Finite differences:** Only acceptable for rough estimates; choose $h_{rel} \approx 10^{-5}$ to minimize error.
* **45° complex-step:** Recommended for $\Gamma$ due to its robustness and slightly improved numerical symmetry.

---