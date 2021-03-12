/**
 * @Created by Manh Vu Duy (manhvdm@gmail.com) on 3/12/2021.
 * @Please contact before using this source code
 */
//

#ifndef BUS_FUNCTION_H
#define BUS_FUNCTION_H

#endif //BUS_FUNCTION_H
#pragma once

int getMaxTravelTime(int node) {
    return  travel_time[node][0] * max_percentage_travel_time;
}
bool checkTimeNode(int node, int riding_time) {
    return (riding_time <= travel_time[node][0] * max_percentage_travel_time) & (riding_time <= max_time_per_route);
}
bool checkNegative(int node, int riding_time) {
    return (riding_time > nodes[node].current_time * max_nagative_time_ratio);
}
int getNegative(int node, int riding_time) {
    return nodes[node].demand * ((riding_time > nodes[node].current_time * max_nagative_time_ratio));
}
int getEUCdis(int x_1, int y_1, int x_2, int y_2) {
    return round(sqrt(pow(x_1 - x_2, 2) + pow(y_1 - y_2, 2)));
}
