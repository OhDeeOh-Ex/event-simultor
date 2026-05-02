import pandas as pd
import matplotlib.pyplot as plt
import os

# Ensure we are looking in the right spot
output_path = "../results/output.csv"
latency_path = "../results/latency.csv"

if os.path.exists(output_path):
    df = pd.read_csv(output_path)
    plt.figure(figsize=(10, 5))
    plt.plot(df["events"], df["time"], marker='o', color='royalblue')
    plt.xlabel("Number of Events")
    plt.ylabel("Execution Time (ms)")
    plt.title("Performance Scaling (O(N log N))")
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.show()

if os.path.exists(latency_path):
    lat = pd.read_csv(latency_path)
    plt.figure(figsize=(10, 5))
    # iloc[:, 0] selects the first column regardless of the header name
    plt.hist(lat.iloc[:, 0], bins=100, color='seagreen', edgecolor='black', alpha=0.7)
    plt.yscale('log') # Log scale helps visualize outliers
    plt.xlabel("Latency (nanoseconds)")
    plt.ylabel("Frequency (Log Scale)")
    plt.title("Event Processing Latency Distribution")
    plt.grid(axis='y', linestyle='--', alpha=0.5)
    plt.show()
else:
    print("Error: latency.csv not found. Run the C++ simulation first.")