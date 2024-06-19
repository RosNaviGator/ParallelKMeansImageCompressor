import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV file into a DataFrame
df = pd.read_csv('performanceData.csv')

# Get unique combinations of n_points and starting colors
combinations = df[['n_points', 'starting colors']].drop_duplicates()

# Iterate over each combination
for _, row in combinations.iterrows():
    n_points = row['n_points']
    starting_colors = row['starting colors']
    
    # Filter the DataFrame for the current combination
    filtered_df = df[(df['n_points'] == n_points) & (df['starting colors'] == starting_colors)]
    
    # Create a new figure for each combination (all methods)
    plt.figure(figsize=(10, 6))
    
    # Plot Sequential line
    seq_df = filtered_df[filtered_df['method'] == 'Sequential']
    seq_mean_time = seq_df.groupby('k')['time'].mean()
    plt.plot(seq_mean_time.index, seq_mean_time.values, marker='o', label='Sequential')
    
    # Plot OMP line
    omp_df = filtered_df[filtered_df['method'] == 'OMP']
    omp_mean_time = omp_df.groupby('k')['time'].mean()
    plt.plot(omp_mean_time.index, omp_mean_time.values, marker='o', label='OMP')
    
    # Plot MPI lines for each world size
    mpi_df = filtered_df[filtered_df['method'] == 'MPI']
    world_sizes = mpi_df['world_size'].unique()
    for world_size in world_sizes:
        ws_df = mpi_df[mpi_df['world_size'] == world_size]
        ws_mean_time = ws_df.groupby('k')['time'].mean()
        plt.plot(ws_mean_time.index, ws_mean_time.values, marker='o', label=f'MPI (World Size: {world_size})')
    
    # Set labels and title
    plt.xlabel('k')
    plt.ylabel('Mean Time')
    plt.title(f'Performance (n_points: {n_points}, starting colors: {starting_colors})')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    
    # Display the plot
    plt.show()
    
    # Create a new figure for each combination (parallel methods only)
    plt.figure(figsize=(10, 6))
    
    # Plot OMP line
    plt.plot(omp_mean_time.index, omp_mean_time.values, marker='o', label='OMP')
    
    # Plot MPI lines for each world size
    for world_size in world_sizes:
        ws_df = mpi_df[mpi_df['world_size'] == world_size]
        ws_mean_time = ws_df.groupby('k')['time'].mean()
        plt.plot(ws_mean_time.index, ws_mean_time.values, marker='o', label=f'MPI (World Size: {world_size})')
    
    # Set labels and title
    plt.xlabel('k')
    plt.ylabel('Mean Time')
    plt.title(f'Parallel Performance (n_points: {n_points}, starting colors: {starting_colors})')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    
    # Display the plot
    plt.show()