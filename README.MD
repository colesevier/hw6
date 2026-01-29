# HW6 — Boggle & Hash Table Utilities

This directory contains the homework 6 implementation and tests for:
- a Boggle solver/driver ([boggle-driver.cpp](boggle-driver.cpp), [boggle.cpp](boggle.cpp), [boggle.h](boggle.h))
- hashing / hash-table utilities and tests ([hash.h](hash.h), [ht.h](ht.h), [hash-check.cpp](hash-check.cpp), [ht-test.cpp](ht-test.cpp), [str-hash-test.cpp](str-hash-test.cpp))
- a small dictionary file used by the Boggle solver ([dict.txt](dict.txt))

Prerequisites
- A C++ compiler (e.g., g++ / clang++)
- make

Build
1. From this folder:
```sh
cd hw6
make
```
The [Makefile](Makefile) will build the provided targets. If your environment differs, you can compile manually, for example:
```sh
g++ -std=c++17 -O2 boggle.cpp boggle-driver.cpp -o boggle
g++ -std=c++17 -O2 hash-check.cpp -o hash-check
g++ -std=c++17 -O2 ht-test.cpp -o ht-test
g++ -std=c++17 -O2 str-hash-test.cpp -o str-hash-test
```

Running
- Boggle driver (example):
```sh
./boggle              # if built as 'boggle' by the Makefile
# or
./boggle-driver       # depending on Makefile target name
```
The driver reads board/input as implemented in [boggle-driver.cpp](boggle-driver.cpp) and uses [dict.txt](dict.txt) for word checks.

- Hash & hash-table tests:
```sh
./hash-check
./ht-test
./str-hash-test
```

Tests
- A test archive is included: [hw6_tests.tar.gz](hw6_tests.tar.gz). Inspect or extract it to see formal test cases:
```sh
tar -xzf hw6_tests.tar.gz
# run any provided test scripts inside the extracted folder
```

Notes and tips
- Inspect header files for API expectations:
  - Hash helpers: [hash.h](hash.h)
  - Hash-table interface: [ht.h](ht.h)
- If benchmarks or debugging are needed, use the test drivers:
  - [hash-check.cpp](hash-check.cpp) validates individual hash functions.
  - [ht-test.cpp](ht-test.cpp) and [str-hash-test.cpp](str-hash-test.cpp) exercise the hash table implementation.
- Dictionary file format: [dict.txt](dict.txt) — one word per line; ensure path is correct when running the boggle executable.

Troubleshooting
- If compilation fails, check your compiler flags and C++ standard (C++17 recommended).
- If the Makefile doesn’t expose test targets, build the individual sources as shown above.

Contact / Credit
- Author(s): see project root README for full project credits.
