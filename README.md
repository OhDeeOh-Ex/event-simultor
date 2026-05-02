# High-Performance Event-Driven System Simulator

## Overview
This project is a high-performance event-driven simulation engine implemented in C++. It is designed to model real-time systems, such as financial exchanges or network routers, under varying workloads. 
The system manages event scheduling using a Binary Heap (Priority Queue) and includes a matching engine logic for processing simulated orders.

## Key Features
- Event-Driven Architecture: Uses a min-heap priority queue to ensure events are processed in strict chronological order.

- Nanosecond Precision: Captures per-event latency at the nanosecond level to identify performance bottlenecks and system jitter.

- Order Matching Engine: Simulates a simplified limit order book (LOB) with buy/sell matching logic.

- Performance Benchmarking: Automated CSV logging of execution times across increasing workloads (10k to 100k events).

- Python Analytics: A visualization suite using pandas and matplotlib to analyze scaling behavior and latency distributions.

## Technologies
- C++
- Python
- STL (priority_queue, vector)
- pandas, matplotlib

## Performance Analysis
The system was evaluated using workloads ranging from 10,000 to 100,000 events.

Results demonstrate increasing execution time consistent with O(n log n) complexity, due to the use of a heap-based priority queue.

This validates theoretical expectations for event-driven systems using priority scheduling.

## Latency Analysis

Per-event latency is visualized using a Log-Scaled Histogram. This analysis reveals a "long-tail" distribution, typical of high-frequency systems. 
While most events process within a tight microsecond window, the outliers (tail latency) represent the overhead of heap rebalancing and cache misses during high-contention periods.

## How to Run

### Compile
cd cpp/src

g++ main.cpp -o sim

### Execute
sim

### Visualise
cd ../../python

python plot.py


## Future Improvements
- Lock-Free Structures: Replace the standard priority queue with a lock-free heap to support multi-threaded event dispatching.

- Price-Time Priority: Upgrade the matching logic to a full L3 Order Book with price-time priority.

- Network Jitter Simulation: Introduce variable network latency models using a Poisson distribution.

## Author
Daniel Oduwole