#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NODES 10
#define INF 9999

char locations[MAX_NODES][50];
int adjMatrix[MAX_NODES][MAX_NODES];
int nodeCount = 0;

// --- Network Initialization ---
void initializeGraph() {
    for (int i = 0; i < MAX_NODES; i++)
        for (int j = 0; j < MAX_NODES; j++)
            adjMatrix[i][j] = 0;
}

void addLocation(const char* name) {
    if (nodeCount < MAX_NODES) {
        strcpy(locations[nodeCount], name);
        nodeCount++;
    }
}

void addRoad(int src, int dest, int distance) {
    adjMatrix[src][dest] = distance;
    adjMatrix[dest][src] = distance;
}

void loadSmartCityData() {
    addLocation("Hospital");          // 0
    addLocation("City Center");       // 1
    addLocation("Railway Station");   // 2
    addLocation("Residential Area");  // 3
    addLocation("Airport");           // 4
    addLocation("Shopping Mall");     // 5
    addLocation("Police Station");    // 6

    addRoad(0, 1, 5);
    addRoad(0, 3, 8);
    addRoad(1, 2, 4);
    addRoad(1, 3, 2);
    addRoad(1, 5, 3);
    addRoad(2, 4, 6);
    addRoad(3, 6, 4);
    addRoad(5, 4, 7);
    addRoad(6, 0, 10);
}

void displayLocations() {
    printf("\n--- Smart City Locations ---\n");
    for (int i = 0; i < nodeCount; i++) {
        printf("[%d] %s\n", i, locations[i]);
    }
    printf("----------------------------\n");
}

// --- Pathfinding & Traversals ---
void printPathConsole(int parent[], int j) {
    if (parent[j] == -1) return;
    printPathConsole(parent, parent[j]);
    printf(" -> %s", locations[j]);
}

void printPathWeb(int parent[], int j) {
    if (parent[j] == -1) {
        printf("%d", j);
        return;
    }
    printPathWeb(parent, parent[j]);
    printf(",%d", j);
}

void dijkstra(int src, int dest, bool isWebMode) {
    int distance[MAX_NODES];
    bool visited[MAX_NODES];
    int parent[MAX_NODES];

    for (int i = 0; i < nodeCount; i++) {
        distance[i] = INF;
        visited[i] = false;
        parent[i] = -1;
    }
    distance[src] = 0;

    for (int count = 0; count < nodeCount - 1; count++) {
        int min = INF, u = -1;
        for (int v = 0; v < nodeCount; v++) {
            if (!visited[v] && distance[v] <= min) {
                min = distance[v];
                u = v;
            }
        }
        visited[u] = true;
        for (int v = 0; v < nodeCount; v++) {
            if (!visited[v] && adjMatrix[u][v] && distance[u] != INF 
                && distance[u] + adjMatrix[u][v] < distance[v]) {
                parent[v] = u;
                distance[v] = distance[u] + adjMatrix[u][v];
            }
        }
    }

    if (isWebMode) {
        // Output clean data for Python to read
        if (distance[dest] == INF) {
            printf("ERROR:No path");
        } else {
            printf("PATH:");
            printPathWeb(parent, dest);
            printf("|DIST:%d", distance[dest]);
        }
    } else {
        // Normal Console Output for Stage 2
        if (distance[dest] == INF) {
            printf("\nNo path exists between %s and %s.\n", locations[src], locations[dest]);
        } else {
            printf("\n=== SHORTEST PATH FOUND ===\n");
            printf("Route: %s", locations[src]);
            printPathConsole(parent, dest);
            printf("\nTotal Distance: %d km\n===========================\n", distance[dest]);
        }
    }
}

void bfs(int startNode) {
    bool visited[MAX_NODES] = {false};
    int queue[MAX_NODES], front = 0, rear = 0;
    printf("\nBFS Traversal:\n");
    visited[startNode] = true;
    queue[rear++] = startNode;
    while (front < rear) {
        int current = queue[front++];
        printf("%s --> ", locations[current]);
        for (int i = 0; i < nodeCount; i++) {
            if (adjMatrix[current][i] != 0 && !visited[i]) {
                visited[i] = true;
                queue[rear++] = i;
            }
        }
    }
    printf("END\n");
}

void dfsUtil(int v, bool visited[]) {
    visited[v] = true;
    printf("%s --> ", locations[v]);
    for (int i = 0; i < nodeCount; i++) {
        if (adjMatrix[v][i] != 0 && !visited[i]) dfsUtil(i, visited);
    }
}

void dfs(int startNode) {
    bool visited[MAX_NODES] = {false};
    printf("\nDFS Traversal:\n");
    dfsUtil(startNode, visited);
    printf("END\n");
}

// --- DUAL-MODE MAIN FUNCTION ---
int main(int argc, char *argv[]) {
    initializeGraph();
    loadSmartCityData();

    // MODE 1: Web API Mode (Triggered by Python)
    if (argc == 4 && strcmp(argv[1], "route") == 0) {
        int src = atoi(argv[2]);
        int dest = atoi(argv[3]);
        dijkstra(src, dest, true); // true = Web Mode
        return 0;
    }

    // MODE 2: Interactive Console Mode (For Stage 2 Screenshots)
    int choice, src, dest, startNode;
    while (1) {
        printf("\n========================================");
        printf("\n  SMART CITY NAVIGATION SYSTEM");
        printf("\n========================================");
        printf("\n1. View City Locations\n2. Find Shortest Path\n3. BFS Traversal\n4. DFS Traversal\n5. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) displayLocations();
        else if (choice == 2) {
            printf("Enter Source ID: "); scanf("%d", &src);
            printf("Enter Dest ID: "); scanf("%d", &dest);
            dijkstra(src, dest, false);
        }
        else if (choice == 3) {
            printf("Enter Start ID: "); scanf("%d", &startNode);
            bfs(startNode);
        }
        else if (choice == 4) {
            printf("Enter Start ID: "); scanf("%d", &startNode);
            dfs(startNode);
        }
        else if (choice == 5) exit(0);
    }
    return 0;
}