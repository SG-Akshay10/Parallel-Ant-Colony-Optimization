import matplotlib.pyplot as plt
import numpy as np

# Read the serial and parallel data
serial_times = []
parallel_times = []

with open('serial.txt', 'r') as f:
    for line in f:
        if 'Time consumed' in line:
            time_str = line.split(':')[1].strip()
            serial_times.append(float(time_str.split(' ')[0]))

with open('parallel.txt', 'r') as f:
    for line in f:
        if 'Time consumed' in line:
            time_str = line.split(':')[1].strip()
            parallel_times.append(float(time_str.split(' ')[0]))

# Calculate the speedup and parallel efficiency
speedup = [st / pt for st, pt in zip(serial_times, parallel_times)]
parallel_efficiency = [s / len(parallel_times) for s in speedup]

# Plot the graphs
x = np.arange(len(serial_times))

fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 8))

ax1.plot(x, speedup)
ax1.set_xlabel('Number of Processing Elements')
ax1.set_ylabel('Speedup')
ax1.set_title('Graph 1: N vs Speed Up')

ax2.plot(x, parallel_efficiency)
ax2.set_xlabel('Number of Processing Elements')
ax2.set_ylabel('Parallel Efficiency')
ax2.set_title('Graph 2: N vs Parallel Efficiency')

plt.tight_layout()
plt.show()