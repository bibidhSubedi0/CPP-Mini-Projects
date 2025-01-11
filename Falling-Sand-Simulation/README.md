# Sand Simulation

This project is a basic sand simulation built using **C++** and the **Raylib** library. It demonstrates particle-based physics where "sand" particles interact with a 2D grid and obey simple rules for movement. The simulation features user interaction, enabling the creation of sand particles via mouse input.

## Features
- **Particle Movement**: Sand particles move downward due to simulated gravity, interacting with surrounding particles based on defined rules.
- **Interactive Input**: Left mouse click to create sand particles.
- **Simple Grid-Based Physics**:
  - Particles fall straight down if space is available.
  - If obstructed, they attempt to fall diagonally.
  - If both diagonal paths are open, priority is given to the left.

