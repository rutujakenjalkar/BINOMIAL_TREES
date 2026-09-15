# Binomial Trees (C++)

C++ implementation of European and American option pricing models using the Cox-Ross-Rubinstein (CRR) binomial model.

## Mathematical Derivation & Core Logic
> Full mathematical proofs, GBM discretization assumptions, and $u/d/p$ martingale derivations are detailed in [docs/CRR_Mathematical_Derivation.pdf](docs/CRR_Mathematical_Derivation.pdf).

## What Are Options?
Financial derivatives that give the buyer the right to buy or sell an underlying asset at a specific strike price:
* **European Options**: Can be exercised **only on** the maturity date.
* **American Options**: Can be exercised at **any time up to** maturity.

## Valuation Methodology
Both models discretize the time horizon into $N$ steps of length $\Delta t = T/N$ to build a multi-step price lattice:

* **European Options**: Evaluates terminal payoffs and discounts the probability-weighted expectation back to present value.
* **American Options**: Applies backward induction from maturity to today, comparing intrinsic early-exercise value against discounted continuation value at each node.

## Core Technical Concepts
* **Lattice Geometry**: Multi-step up/down stock price paths driven by volatility and time steps ($u, d$).
* **Risk-Neutral Pricing**: Probability weighting adjusted by the risk-free rate.
* **State Management**: Dynamic 2D grids (`std::vector<std::vector<node>>`) tracking node-level stock prices, transition probabilities, and payoffs.
* **Complexity Profile**: $O(N^2)$ time and $O(N^2)$ space for an $N$-step recombinant lattice.

## Sample Output 
```
--- TERMINAL NODES VERIFICATION ---
Node (UP =0, DOWN =2) -> Price: 67.032 | Payoff: 0 | Prob: 0.178512
Node (UP =1, DOWN =1) -> Price: 100.00 | Payoff: 0 | Prob: 0.487990
Node (UP =2, DOWN =0) -> Price: 149.182 | Payoff: 49.1825 | Prob: 0.333498

Root (S0: 100.00) -> Option Valuation Result: 14.8414
```

## Build and Run
```
g++ -O3 binomial_tree.cpp -o binomial_tree_euro
./binomial_tree_euro

g++ -O3 american_tree.cpp -o binomial_tree_amer
./binomial_tree_amer

```

---
> **Design Note**: I/O visualization logic has been stripped from core valuation loops to maximize execution speed and benchmark accuracy.


