// Problem: Max Area of Island
// Difficulty: Medium
// Description: 
//You are given an m x n binary matrix grid.
// An island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.)
// You may assume all four edges of the grid are surrounded by water.
//The area of an island is the number of cells with a value 1 in the island.
//Return the maximum area of an island in grid. If there is no island, return 0.
//Examples:
//Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],
//               [0,0,0,0,0,0,0,1,1,1,0,0,0],
//               [0,1,1,0,1,0,0,0,0,0,0,0,0],
//               [0,1,0,0,1,1,0,0,1,0,1,0,0],
//               [0,1,0,0,1,1,0,0,1,1,1,0,0],
//               [0,0,0,0,0,0,0,0,0,0,1,0,0],
//               [0,0,0,0,0,0,0,1,1,1,0,0,0],
//               [0,0,0,0,0,0,0,1,1,0,0,0,0]]
//Output: 6
//Explanation: The answer is not 11, because the island must be connected 4-directionally.
//Input: grid = [[0,0,0,0,0,0,0,0]]
//Output: 0
// Constraints:
// m == grid.length, 1 <= m, n <= 50
// grid[i][j] is either 0 or 1.

#include <vector>
#include <queue>
#include <algorithm>

class Solution {
public:
    int maxAreaOfIsland(std::vector<std::vector<int>>& grid){

        std::vector<int> Areas;
        auto visited{grid};
        for(auto &row : visited){
            for(auto &num: row){
                num = 0;
            }
        }

        std::vector<std::pair<int, int>> ds{{0,1},{1,0},{-1, 0},{0,-1}};
        std::queue<std::pair<int,int>> plan;

        for(int i = 0; i < grid.size(); ++i){
            for(int j = 0; j < grid[i].size(); ++j){

                if(grid[i][j] == 1 && visited[i][j] == 0){
                    Areas.push_back(1);
                    plan.push({i,j});
                    visited[i][j] = 1;

                    while(!plan.empty()){
                        auto [i,j] = plan.front();

                        for(auto [di, dj] : ds){
                            if(i + di < grid.size() && j + dj < grid[i].size() && i + di >= 0 && j + dj >= 0){
                                if(visited[i + di][j + dj] != 1 && grid[i + di][j + dj] != 0){
                                    visited[i + di][j + dj] = 1;
                                    ++Areas.back();
                                    plan.push({i + di, j + dj});
                                }        
                            }                    
                        }
                        plan.pop();
                    }
                }
            }
        }
        if(Areas.empty()) return 0;
        std::sort(Areas.begin(), Areas.end());
        return Areas.back(); 
    }
};