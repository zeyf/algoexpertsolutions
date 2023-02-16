#include <bits/stdc++.h>
using namespace std;

/*

Problem: Remove Islands
Problem Link: https://www.algoexpert.io/questions/remove-islands

Intuition:

We can differentiate "good" islands from "bad" (non-edge-connected islands) by iterating over all edges of the matrix and incrementing all connected components of these edge-connected islands

Edge-connected islands go from a value of 1 to 2

From there, those that are non-edge-connected are never touched, hence they remain as 1 (0 is never considered)

Now we can simply iterate over the matrix and decrement all matrix[x][y] that are 2 to 1 and all matrix[x][y] that are 1 to 0 in order to produce the solution

Time Complexity: O(n*m) - Due to having to traverse up to n*m cells recursively and iteratively twice
Space Complexity: O(n*m) - Due to recursive call space on call stack

*/

vector<vector<int>> removeIslands(vector<vector<int>> matrix) {

  // Initialize the directional adjustments and set for badIslands (on the edges of the matrix)
  vector<vector<int>> directions{{ 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 }};
  int n = matrix.size(), m = matrix[0].size();

  // Lambda function to check if a location is inbounds after an applied directional
  auto inbounds = [&] (int x, int y) -> bool {
    return x >= 0 && y >= 0 && x < n && y < m;
  };

  // Lambda function to recursively traverse any good (edge-connected) islands
  auto dfs = [&] (int x, int y, auto &&dfs) -> void {

    // Mark the current location as 2 (non 1 value, and non-zero)
    matrix[x][y]++;

    // Iterate through all possible directionals
    for (vector<int> dir: directions) {
      // Apply the current directional
      int nx = x + dir[0], ny = y + dir[1];

      // If the next location is inbounds and is a valid island (value of 1), traverse
      if (inbounds(nx, ny) && matrix[nx][ny] == 1) {
        dfs(nx, ny, dfs);
      }
      
    }
    
  };

  // Iterate over the x axis of the matrix
  for (int x = 0; x < n; ++x) {

    // Check for a 1, aka land (x, leftMostCoordinate) 
    if (matrix[x][0] == 1)
      dfs(x, 0, dfs);

    // Check for a 1, aka land (x, rightMostCoordinate) 
    if (matrix[x][m - 1] == 1)
      dfs(x, m - 1, dfs);

  }

  // Iterate over the y axis of the matrix
  for (int y = 0; y < m; ++y) {
    
    // Check for a 1, aka land (topMostCoordinate, y) 
    if (matrix[0][y] == 1)
      dfs(0, y, dfs);
    
    // Check for a 1, aka land (bottomMostCoordinate, y) 
    if (matrix[n - 1][y] == 1)
      dfs(n - 1, y, dfs);

  }

  // Now all of the edge-sided islands are 2'd out and the non edged islands are all 1's

  // Iterate over the entire board again and 1-out all 2'd coordinates (preserve edge-connected islands)
  // Also 0-out all non-2'd locations, removing non-edge islands from the matrix
  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < m; ++y) {
      if (matrix[x][y] == 2)
        matrix[x][y] = 1;
      else if (matrix[x][y] == 1)
        matrix[x][y] = 0;
    }
  }

  // Return solution
  return matrix;
}
