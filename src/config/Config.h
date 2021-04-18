/**
 * @Created by Manh Vu Duy (manhvdm@gmail.com) on 3/12/2021.
 * @Please contact before using this source code
 */
//

#ifndef BUS_CONFIG_H
#define BUS_CONFIG_H

#endif //BUS_CONFIG_H
#pragma once

#define maxn 205
#define maxm 1005
#define oo 50000000
int n_bus_type; // number of Truck's types
int n_node; // number of locations
int total_demand;
VehicleType bus_types[maxn]; // list of Truck's type
Location nodes[maxn]; // list of location
int** travel_time; // the distance between two locations
int waiting_time; // waiting time at each location
int max_nodes_per_route; // maximum of locations per routes
double max_time_per_route; // maximum of riding time per routes
double max_percentage_travel_time; // maximum of negative percentage
double max_negative_percentage_of_student; // maximum of negative locations
int max_negative_students; // corresponding maximum of negative locations
double max_negative_time_ratio; // minimal ratio for negative impact
int* bus_for_demand; // return the optimal type of vehicle for given demand
int* fixed_cost_for_demand; // return correspond fixed cost for given demand
int* travel_cost_for_demand; // return correspond travelling cost for given demand
int f_split[maxn][maxm]; // split
II pre_split[maxn][maxm]; // split
int f[1 << 8][8][100];
int pre[1 << 8][8][100];
III deque[10000005];
ofstream fileOut;
ifstream fileIn;
string instance_name;

