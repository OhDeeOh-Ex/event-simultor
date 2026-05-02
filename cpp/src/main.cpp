#include <iostream>
#include <queue>
#include <vector>
#include <chrono>
#include <fstream>
#include <random>
#include <cmath> // For std::sqrt

#include "../include/event.h"
#include "../include/order.h"

struct Compare {
    bool operator()(Event a, Event b) {
        return a.timestamp > b.timestamp;
    }
};

void run_simulation(int num_events, std::vector<long>& latencies) {
    std::priority_queue<Event, std::vector<Event>, Compare> pq;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.0, 100.0);

    for (int i = 0; i < num_events; i++) {
        pq.push({dist(gen), i});
    }

    std::vector<Order> buy_orders;
    std::vector<Order> sell_orders;

    while (!pq.empty()) {
        auto start = std::chrono::high_resolution_clock::now();

        Event e = pq.top();
        pq.pop();

        // Workload to ensure time passes
        double dummy = 0.0;
        for(int j=0; j<50; j++) dummy += std::sqrt(dist(gen));

        if (e.id % 2 == 0) {
            buy_orders.push_back({e.id, dist(gen) + dummy, 10, true});
        } else {
            sell_orders.push_back({e.id, dist(gen) + dummy, 10, false});
        }

        if (!buy_orders.empty() && !sell_orders.empty()) {
            if (buy_orders.back().price >= sell_orders.back().price) {
                buy_orders.pop_back();
                sell_orders.pop_back();
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        long diff = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        latencies.push_back(diff > 0 ? diff : 1);
    }
}

int main() {
    // 1. Open the files
    std::ofstream file("../../results/output.csv");
    std::ofstream latency_file("../../results/latency.csv");

    if (!file.is_open() || !latency_file.is_open()) {
        std::cerr << "Error: Could not open CSV files. Check if 'results' folder exists." << std::endl;
        return 1;
    }

    file << "events,time\n";
    latency_file << "latency_ns\n";

    // 2. Run the loop
    for (int n = 10000; n <= 100000; n += 10000) { 
        std::vector<long> current_latencies;
        
        auto start = std::chrono::high_resolution_clock::now();
        run_simulation(n, current_latencies);
        auto end = std::chrono::high_resolution_clock::now();

        long duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        file << n << "," << duration << "\n";
        
        // 3. Write latencies immediately every loop
        for (long l : current_latencies) {
            latency_file << l << "\n";
        }
        latency_file.flush(); // Force write to disk

        std::cout << "Finished " << n << " events. Recorded " << current_latencies.size() << " latencies." << std::endl;
    }

    file.close();
    latency_file.close();
    return 0;
}