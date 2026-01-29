## Overview — systems-focused summary

This repository contains a concise, single-threaded C++ implementation that demonstrates core systems and data-structure fundamentals: a small Boggle solver and a templated open-addressing hash table with multiple probing strategies and a custom string hash. It was developed as a homework exercise, but the code intentionally surfaces design trade-offs and low-level implementation details that are directly relevant to systems engineering roles (performance, memory, algorithmic complexity, and correctness).

What to look for
- Hash table: `ht.h` implements a templated hash table using open addressing. It supports pluggable probing (linear and double hashing), uses a table of prime capacities, and dynamically resizes when a load factor threshold is exceeded.
- Hash function: `hash.h` provides `MyStringHash` — a base-36 style string hash using pre-seeded R-values. The implementation shows how string partitioning, base conversion, and mixing constants influence distribution and collisions.
- Boggle solver: `boggle.cpp` is a compact demonstration of recursive search and prefix pruning using `std::set` for dictionary and prefix lookup. It illustrates algorithmic pruning and correctness checks.

Design and systems takeaways
- Performance vs. simplicity: linear probing is simple and cache-friendly but suffers primary clustering; double hashing reduces clustering at the cost of more complex step computation. Both are implemented so you can compare probe counts and behavior under load.
- Dynamic resizing: the table rehashes into larger prime capacities when the load factor exceeds a configurable threshold (default 0.4). Resizing is O(m) for the new table size and is a predictable, infrequent cost that trades CPU for sustained O(1) average lookups.
- Hash quality matters: `MyStringHash` demonstrates deterministic mixing using R-values and base-36 word chunks. Small changes to the mixing constants or chunking strategy can change collision rates dramatically — a practical lesson for latency-sensitive systems.
- Implementation-level details: manual allocation (`new`/`delete` for bucket entries), templated APIs, exception handling (`std::logic_error`, `std::out_of_range`), and probe-count instrumentation (the table tracks `totalProbes`) expose lower-level resource and correctness concerns you'd manage in production code.

How to build and run (macOS / Linux)
```bash
cd hw6
make
```

If you prefer to compile manually:
```bash
g++ -std=c++17 -O2 boggle.cpp boggle-driver.cpp -o boggle
g++ -std=c++17 -O2 hash-check.cpp -o hash-check
g++ -std=c++17 -O2 ht-test.cpp -o ht-test
g++ -std=c++17 -O2 str-hash-test.cpp -o str-hash-test
```

Typical runs
- Run the Boggle driver to see the solver run against `dict.txt` (board generation and drivers are in `boggle-driver.cpp`/`boggle.cpp`).

```bash
./boggle
```

- Run the hash and hash-table tests to observe probe statistics and verify correctness:

```bash
./hash-check
./ht-test
./str-hash-test
```

Interpreting results
- `ht-test` / `str-hash-test` exercises insertion/find/remove and prints probe-related diagnostics. Compare total probe counts between `LinearProber` and `DoubleHashProber` to see practical effects of clustering and probe sequences.
- `hash-check` validates the string hash behavior and is useful to experiment with alternate R-values or chunking for real words.

Known limitations (honest appraisal)
- Single-threaded and not hardened for production concurrency or persistence.
- Uses manual heap allocation per occupied bucket; a production implementation would likely avoid per-bucket `new`/`delete` and prefer contiguous storage/placement new for cache friendliness and lower allocation overhead.
- Testing is minimal (homework-level). For production readiness, add deterministic micro-benchmarks, property tests, and fuzzing for edge cases.

Suggested follow-ups (short list)
- Add a lightweight benchmarking harness to measure average probe counts and latency across realistic workloads.
- Replace the `std::set` dictionary with a trie or hash-backed dictionary to measure real differences in prefix lookup performance for the Boggle solver.
- Make the hash table generic over an allocator and swap manual allocations for storage in a contiguous vector to reduce fragmentation and improve cache behavior.

Files of interest
- `ht.h` — hash table implementation, probing strategies, resizing logic.
- `hash.h` — `MyStringHash` and helpers.
- `boggle.cpp`, `boggle-driver.cpp` — solver and driver.
- `hash-check.cpp`, `ht-test.cpp`, `str-hash-test.cpp` — small test drivers and verification.

If you'd like, I can:
- Add a short benchmark script that runs the hash table over `dict.txt` and emits probe/QPS numbers.
- Add a one-page summary you can include in your Citadel application describing the specific systems challenges you solved and citations to measurements.

---
Honest note: this started as a homework project, but the code is intentionally written to expose real systems trade-offs you’d discuss in an interview: algorithmic complexity, memory-management decisions, hash quality, and how to instrument and reason about performance.
