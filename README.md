
# Smart City Navigation System

## Abstract
The Smart City Navigation System is a lightweight, high-performance computational model designed to optimize urban routing. Developed in C, the core engine utilizes a Graph data structure represented via an Adjacency Matrix to mathematically determine the shortest path between critical municipal nodes. To demonstrate system scalability and interoperability, the architecture implements a dual-mode interface, allowing execution as a standalone console application or as a backend microservice queried by a web-based frontend via a Python RESTful bridge.

## Academic Context
This repository contains the source code and documentation for the Semester V Data Structures Self Learning Activity (SLA) completed at **Shah & Anchor Kutchhi Engineering College**.

## System Architecture
The project is built on a decoupled, full-stack architecture to separate the computational engine from the visualization layer:

1. **Algorithmic Engine (C):** A statically typed, statically allocated backend ensuring memory efficiency. It computes shortest paths and network traversals without external dependencies.
2. **Middleware Bridge (Python/Flask):** A lightweight server that executes the compiled C binary via subprocesses, capturing standard output (stdout) and serving it over HTTP via JSON.
3. **Visualization Layer (HTML5/JS):** A client-side web interface utilizing the Canvas API to dynamically render the graph topology and highlight computed paths.

## Data Structures & Algorithmic Complexity
The system enforces strict computational boundaries suitable for embedded navigation systems.

* **Primary Structure:** Graph (Adjacency Matrix)
* **Time Complexity:** 
  * Dijkstra's Algorithm: $O(V^2)$
  * Breadth-First Search (BFS): $O(V^2)$
  * Depth-First Search (DFS): $O(V^2)$
* **Space Complexity:** $O(V^2)$ — Memory is bounded by the static allocation of the $V \times V$ matrix and auxiliary 1D arrays for state tracking.

## Repository Structure
```text
.
├── src/
│   ├── smart_city.c      # Core algorithmic engine and console interface
│   ├── server.py         # Flask middleware bridge
│   └── index.html        # Web-based visualization client
├── docs/
│   ├── Phase_I_Report.pdf
│   └── Phase_II_Report.pdf
├── assets/
│   ├── terminal_execution.png
│   └── web_visualization.png
├── .gitignore
└── README.md

```

## Build and Execution Instructions

### Prerequisites

* GCC Compiler (MinGW environment for Windows)
* Python 3.x
* Flask Framework (`pip install flask flask-cors`)

### Mode A: Standalone Console Execution

For environments with strict memory constraints, the engine can be run natively in the terminal.

1. Compile the source code:
```bash
gcc src/smart_city.c -o smart_city

```


2. Execute the binary:
```bash
./smart_city

```



### Mode B: Full-Stack Web Visualization

To launch the interactive routing interface.

1. Ensure the C binary (`smart_city.exe` or `smart_city`) is compiled.
2. Initialize the middleware server:
```bash
python src/server.py

```


3. Open `src/index.html` in a standard web browser to access the client interface.

## License

Developed for educational purposes as part of the university curriculum.

```

```
