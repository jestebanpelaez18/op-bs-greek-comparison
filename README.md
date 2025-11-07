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

