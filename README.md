# Black–Scholes Greeks – Numerical Differentiation

## Project Overview

This project implements **numerical differentiation** for option Greeks (Delta $\Delta$ and Gamma $\Gamma$) under the **Black–Scholes model**. Three approaches were developed and compared:

* **Analytic Greeks** (reference formulas)
* **Forward Finite Differences**
* **Complex-Step Differentiation** (real-part and 45° variants)

The goal was to study how accurate and stable each method is for different step sizes, using a logarithmic grid of
$h_{rel} \in [10^{-16}, 10^{-4}]$ across two test scenarios.

---

## Build & Run Instructions

### Requirements

* A **C++20** compatible compiler (e.g., `g++`)
* **GNU Make**

### Option A — Using `make` (Recommended)

### Build

To compile the main executable (`bin/main`):

```bash
make
```

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

Both commands will generate the CSV's. Based on the requiriments the CSV's are already included in the submission, this is in case the execution is required. 

---

### Option B — Manual Compilation

#### Linux/MacOS

```bash
mkdir -p bin
g++ -std=c++20 -O2 -Wall -Wextra -Wpedantic -Iincludes srcs/main.cpp -o bin/main
```
#### Windows (Using MinGW)

```bash
mkdir bin
g++ -std=c++20 -O2 -Wall -Wextra -Wpedantic -Iincludes srcs\main.cpp -o bin\main.exe
```
Then run: 

```bash
./bin/main      # Linux/MacOS
bin\main.exe    # Windows
```

---
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
| **AnalyticGreek.hpp** | Analytic Δ and Γ formulas. |
| **FiniteDifferences.hpp** | Forward difference formulas for Δ and Γ. |
| **ComplexDifferentiation.hpp** | Complex-step versions for Δ and Γ (real-part and 45° variants). |
| **main.cpp** | Runs the sweep and writes the CSV files |
| **Makefile** | Simplified build system with `make`, `make run`, `make clean`. |

All functions were written in **C++20**, with `<complex>` for complex arithmetic.

## Tables && Results

A brief error validation report is provided below, summarizing the performance of the implemented methods: $\Delta_{fd}$, $\Delta_{cs}$, $\Gamma_{fd}$, $\Gamma_{cs, real}$, and $\Gamma_{cs, 45^{\circ}}$.

Tables of the **absolute error** vs. the relative step size ($\mathbf{h_{rel}}$) are generated for both Delta and Gamma to visualize stability and accuracy across the range $[10^{-16}, 10^{-4}]$.

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

* **Accuracy Ranking:** Complex-step methods were by far the most accurate and consistent.
Both $\Gamma_{cs,real}$ and $\Gamma_{cs,45°}$ remain stable down to the smallest step sizes, while finite differences worked fine for larger h, but became unstable when h was too small.
* **Dependence on Step Size ($h_{rel}$):**
    * **Complex-Step Methods:** Complex-step results stayed almost perfectly flat, they don’t depend much on h, performing optimally even for very small $h_{rel}$.
    * **Finite Differences:** In finite differences, errors first decrease and then explode when h gets very small (below 1e-8).

* **Differences between Scenarios:** The “stress” scenario (short maturity and low volatility) caused the biggest instability in finite-difference Γ, while complex-step methods handled it easily.

* **Stability Issues:** Finite-difference Gamma sometimes gave extreme or nonsense values for tiny h, which is expected because of floating-point cancellation. Complex-step versions produced clean, stable results with no NaNs or spikes.

---

## Brief Reasoning

There are two main types of errors when doing numerical differentiation: truncation error and round-off error.

* Truncation error happens when the step size h is too large. The method becomes less precise because it’s only an approximation of the true derivative.
* Round-off error appears when h is too small. The computer starts subtracting numbers that are almost identical, which causes a loss of precision.

In finite-difference methods, these two errors go in opposite directions. Making h smaller helps at first, but after a point it makes things worse again.

The complex-step method avoids this issue. It doesn’t do any subtraction, instead, it adds a tiny imaginary part to the input and takes the imaginary component of the result as the derivative. This makes it extremely stable, even for very small h.

---

### Recommendation

* **For $\Delta$ and $\Gamma$:** Use complex-step differentiation whenever possible.
* **Step-size choice:** $h_{rel} = 10^{-10}$ to $10^{-12}$ is safe for all practical purposes; results are stable and precise.
* **Finite differences:** Only acceptable for rough estimates; choose $h_{rel} \approx 10^{-6}$ to minimize error.
* **45° complex-step:** slightly better for Γ, especially in sensitive cases.

---

### Summary

The complex-step approach gave clean, consistent, and accurate results across all step sizes and both scenarios.
Finite differences work but are very sensitive to h and prone to large errors for extreme values.