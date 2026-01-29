#include "ht.h"
#include "hash.h"

#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;
using clk = std::chrono::high_resolution_clock;

static vector<string> load_dict(const string& fname) {
    ifstream fs(fname);
    if(!fs) { cerr << "unable to open dictionary: " << fname << "\n"; exit(1); }
    vector<string> words;
    string w;
    while(fs >> w) words.push_back(w);
    return words;
}

template<typename ProberT>
void run_benchmark(const vector<string>& words, const string& label) {
    typedef HashTable<string,int,ProberT, MyStringHash> HT;

    HT ht; // use default resize alpha and hash
    ht.clearTotalProbes();

    auto t0 = clk::now();
    for(size_t i = 0; i < words.size(); ++i) {
        ht.insert(typename HT::ItemType(words[i], static_cast<int>(i)));
    }
    auto t1 = clk::now();

    auto insert_us = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
    size_t inserts = words.size();
    size_t probes = ht.totalProbes();
    double avg_probes = inserts ? (double)probes / (double)inserts : 0.0;

    cout << "[" << label << "] inserts=" << inserts
         << " time_us=" << insert_us
         << " avg_probe=" << avg_probes
         << " total_probes=" << probes << "\n";

    // Find throughput (repeat a few rounds)
    const int rounds = 10;
    ht.clearTotalProbes();
    auto f0 = clk::now();
    for(int r = 0; r < rounds; ++r) {
        for(const auto &s : words) {
            auto p = ht.find(s);
            if(p == nullptr) {
                cerr << "ERROR: missing key during find: " << s << "\n";
                exit(2);
            }
        }
    }
    auto f1 = clk::now();
    auto find_us = chrono::duration_cast<chrono::microseconds>(f1 - f0).count();
    double qps = (double)words.size() * rounds / (find_us / 1e6);

    cout << "[" << label << "] find_time_us=" << find_us
         << " qps=" << static_cast<long long>(qps)
         << " probes=" << ht.totalProbes() << "\n";
}

int main(int argc, char** argv) {
    string dict = "dict.txt";
    if(argc > 1) dict = argv[1];

    auto words = load_dict(dict);
    cout << "Loaded " << words.size() << " words from " << dict << "\n";

    run_benchmark< LinearProber<string> >(words, "LinearProber");
    run_benchmark< DoubleHashProber<string, MyStringHash> >(words, "DoubleHashProber");

    return 0;
}
