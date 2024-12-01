#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "API.h"

#define MAZE_SIZE 32  // Adjust if maze size differs
bool visited[MAZE_SIZE][MAZE_SIZE];  // Track visited cells
int x = 0, y = 0;  // Current position
int dx = 0, dy = 1;  // Current direction (initially "up")

// Logging helper
void logMessage(const char* message) {
    fprintf(stderr, "%s\n", message);
    fflush(stderr);
}

// Update the position after moving
void updatePosition() {
    x += dx;
    y += dy;
    logMessage("Updated position.");
}

// Turn left and update direction
void turnLeft() {
    int temp = dx;
    dx = -dy;
    dy = temp;
    API_turnLeft();
    logMessage("Turned left.");
}

// Turn right and update direction
void turnRight() {
    int temp = dx;
    dx = dy;
    dy = -temp;
    API_turnRight();
    logMessage("Turned right.");
}

// Mark the current cell as visited
void markVisited() {
    visited[x][y] = true;
    API_setColor(x, y, 'G');  // Optional visualization
    logMessage("Marked cell as visited.");
}

// Check if the goal is reached (example condition, adjust as needed)
bool isGoal() {
    return (x == MAZE_SIZE - 1 && y == MAZE_SIZE - 1);  // Example: bottom-right corner
}

int main() {
    logMessage("Starting maze navigation...");

    // Initialize visited array
    memset(visited, 0, sizeof(visited));
    markVisited();

    // Main navigation loop
    while (1) {
        // Check if the goal is reached
        if (isGoal()) {
            logMessage("Goal reached!");
            API_setColor(x, y, 'R');  // Mark the goal for visualization
            break;
        }

        // Right-hand rule logic:
        if (!API_wallRight()) {
            turnRight();
        } else {
            while (API_wallFront()) {
                turnLeft();
            }
        }

        // Move forward and mark the cell as visited
        if (API_moveForward()) {
            updatePosition();
            if (!visited[x][y]) {
                markVisited();
            }
        } else {
            logMessage("Error: Could not move forward.");
            break;
        }

        // Optional: Check reset condition (if supported by the environment)
        if (API_wasReset()) {
            logMessage("Maze was reset! Exiting.");
            break;
        }
    }

    logMessage("Program terminated.");
    return 0;
}