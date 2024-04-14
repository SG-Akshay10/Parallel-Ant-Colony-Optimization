import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Load the CSV files into pandas dataframes
parallel_df = pd.read_csv('parallel.csv')
serial_df = pd.read_csv('serial.csv')

# Calculate the speedup and parallel efficiency
parallel_df['Speedup'] = serial_df['TimeConsumed'] / parallel_df['TimeConsumed']
parallel_df['Parallel_Efficiency'] = parallel_df['Speedup'] / parallel_df['Iteration']

# Create a figure with three subplots
fig, (ax1, ax2, ax3) = plt.subplots(3, 1, figsize=(12, 12))

# Graph 1: Speedup vs Number of Processing Elements
ax1.plot(parallel_df['Iteration'], parallel_df['Speedup'])
ax1.set_xlabel('Number of Processing Elements')
ax1.set_ylabel('Speedup')
ax1.set_title('Speedup vs Number of Processing Elements')
ax1.grid(True)

# Graph 2: Speedup vs N
ax2.plot(parallel_df['Iteration'], parallel_df['Speedup'])
ax2.set_xlabel('N')
ax2.set_ylabel('Speedup')
ax2.set_title('Speedup vs N')
ax2.grid(True)

# Graph 3: Parallel Efficiency vs Number of Processing Elements
ax3.plot(parallel_df['Iteration'], parallel_df['Parallel_Efficiency'])
ax3.set_xlabel('Number of Processing Elements')
ax3.set_ylabel('Parallel Efficiency')
ax3.set_title('Parallel Efficiency vs Number of Processing Elements')
ax3.grid(True)

plt.tight_layout()
plt.show()