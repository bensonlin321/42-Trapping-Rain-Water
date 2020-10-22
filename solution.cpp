#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <queue>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <limits>
#include <utility> // pair
#include <tuple>
#include <algorithm>
#include <iterator>     // std::distance
#include <list>         // std::list

#define MINUS_INT_MAX INT_MAX * (-1)

std::vector<int> is_sink(int index, std::vector<int> height){
    bool left_has_wall = false;
    bool right_has_wall = false;
    int left_nearest_wall_index = -1;
    int right_nearest_wall_index = -1;
    std::vector<int> output;
    output.push_back(0);
    output.push_back(left_nearest_wall_index);
    output.push_back(right_nearest_wall_index);
    if(index == 0) {    
        return output;
    } else {
        // center to left
        for(int i = index - 1 ; i >= 0; i--) {
            if(height[i] > height[index]) {
                left_has_wall = true;
                left_nearest_wall_index = i;
                break;
            }
        }

        for(int i = index + 1 ; i < height.size(); i++) {
            if(height[index] < height[i]) {
                right_has_wall = true;
                right_nearest_wall_index = i;
                break;
            }
        }
        if(right_has_wall && left_has_wall){
            output.clear();
            output.push_back(1);
            output.push_back(left_nearest_wall_index);
            output.push_back(right_nearest_wall_index);
        }
        return output; // return {is_sink, the nearest index of left wall, the nearest index of right wall}
    }
}

int get_volume(int cur_index, int left_nearest_wall_index, int right_nearest_wall_index, std::vector<int> height) {
    int min_height_bwt_left_right = std::min(height[left_nearest_wall_index], height[right_nearest_wall_index]);
    int cur_height = min_height_bwt_left_right - height[cur_index];
    cur_height = cur_height > 0 ? cur_height : 1; // if the left wall height == right wall height, cur_height = 1
    int volume = cur_height * (right_nearest_wall_index-1 - left_nearest_wall_index);
    return volume;
}

class Solution {
public:
    int trap(std::vector<int>& height) {
        if(height.size() == 0) {
            return 0;
        }
        int output = 0;
        std::vector< std::pair<int, int> > wall_array;
        for(int i = 1 ; i < height.size() ; i++) {
            std::vector<int> res = is_sink(i, height);
            int left_nearest_wall_index = res[1];
            int right_nearest_wall_index = res[2];
            std::pair<int, int> wall_pair{left_nearest_wall_index, right_nearest_wall_index};

            
            if(res[0] == 1) {
                printf("=======================\n");
                // is sink
                printf("wall:  |       |\n");
                printf("index: %d       %d\n", left_nearest_wall_index, right_nearest_wall_index);
                int sink_volume = get_volume(i, left_nearest_wall_index, right_nearest_wall_index, height);
                printf("sink_volume: %d\n", sink_volume);
                
                if (std::find(wall_array.begin(), wall_array.end(), wall_pair) == wall_array.end()) {
                    wall_array.push_back(wall_pair);
                    output += sink_volume;
                } else {
                    printf("already exist in wall_array\n");
                }
                printf("accumulated volume: %d\n", output);
                printf("=======================\n");
            }
        }
        return output;
    }

    int trap_method2(std::vector<int>& height) { 
        int water = 0;

        // left[i] contains height of tallest wall to the 
        // left of ith wall including itself 
        std::vector<int> left(height.size(), 0); 

        // Right [i] contains height of tallest wall to 
        // the right of ith wall including itself 
        std::vector<int> right(height.size(), 0);  

        // Traverse the input heights and find the highest left wall for each term
        left[0] = height[0];
        for (int i = 1; i < height.size(); i++) 
            left[i] = std::max(left[i - 1], height[i]); 

        // Traverse the input heights and find the highest right wall for each term
        right[height.size() - 1] = height[height.size() - 1]; 
        for (int i = height.size() - 2; i >= 0; i--) 
            right[i] = std::max(right[i + 1], height[i]); 

        // Calculate the accumulated water element by element 
        // ith water will be equal to min(left[i], right[i]) - arr[i] . 
        for (int i = 0; i < height.size(); i++) 
            water += std::min(left[i], right[i]) - height[i]; 

        /*
               if i = 1, height[i] = 0, left[i] = 3, right[i] = 4
               min(left[i], right[i]) = 3, water = 3 - 0 = 3

               ^
               |
               |       water        __ 
               |    __   3         ||||
             3 |   ||||//// __     ||||
             2 |   ||||////||||    ||||
             1 |   ||||////||||    ||||
              -|------------------------------------------>
                    */

        return water; 
    } 

};

int main(int argc, char *argv[]) {
    Solution *s = new Solution();
    std::vector<int> height{ 3, 0, 2, 0, 4 };
    printf("output:%d\n", s -> trap(height));
}
