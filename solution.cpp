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

int get_volume(int left_nearest_wall_index, int right_nearest_wall_index, std::vector<int> height) {
    int cur_height = std::abs(height[left_nearest_wall_index] - height[right_nearest_wall_index]);
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
                int sink_volume = get_volume(left_nearest_wall_index, right_nearest_wall_index, height);
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
};

int main(int argc, char *argv[]) {
    Solution *s = new Solution();
    std::vector<int> height{ 0,1,0,2,1,0,1,3,2,1,2,1 };
    printf("output:%d\n", s -> trap(height));
}
