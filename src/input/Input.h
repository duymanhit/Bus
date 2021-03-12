/**
 * @Created by Manh Vu Duy (manhvdm@gmail.com) on 3/12/2021.
 * @Please contact before using this source code
 */
//

#ifndef BUS_INPUT_H
#define BUS_INPUT_H

#endif //BUS_INPUT_H
#pragma once
void process_input();
void inputName(string path) {
    wifstream fileIn(path);
    for (int i = 0; i <= n_node; i++)
        //fileIn.getline(locations[i].address, 256);
        fileIn.close();
}
void getInput(const string& path) {
    ifstream fileIn(path);
    /// <summary>
    /// setting configuration
    /// </summary>
    /// <param name="path"></param>
    fileIn >> waiting_time;
    fileIn >> max_nodes_per_route;
    fileIn >> max_time_per_route;
    fileIn >> max_percentage_travel_time;
    fileIn >> max_nagative_time_ratio;
    fileIn >> n_node;
    for (int i = 0; i <= n_node; i++) {
        fileIn >> i >>  nodes[i].x >> nodes[i].y >> nodes[i].demand;
    }
    initArray2D(travel_time, n_node + 2, n_node + 2, oo);
    for (int i = 0; i <= n_node; i++)
        for (int j = 0; j <= n_node; j++) {
            fileIn >> travel_time[i][j];
        }

    for (int j = 0; j <= n_node; j++) travel_time[0][j] = 0;
    fileIn >> n_bus_type;
    for (int i = 1; i <= n_bus_type; i++) {
        fileIn >> bus_types[i].capacity >> bus_types[i].fixed_cost >> bus_types[i].travelling_cost;
    }
    /// <summary>
    /// calculate timeTravel
    /// </summary>
    //inputName(path + ".dat");
    process_input();
    current_sol.n_giant_tour = 0;
    int node;
    while (fileIn >> node) current_sol.giant_tour[++current_sol.n_giant_tour] = node;
    current_sol.convertGiantToRoutes();
    for (int i = 1; i <= n_node; i++) {
        nodes[i].current_time = current_sol.time_of_node[i];
    }
    current_sol.outFile();
    //current_sol.check();
    fileIn.close();
}
void process_input() {
    // demand
    total_demand = 0;
    for (int i = 0; i <= n_node; i++) {
        total_demand += nodes[i].demand;
    }
    //
    max_negative_students = total_demand * max_negative_percentage_of_student;
    out(max_negative_students, total_demand);
    // types of buses and demand processing
    initArray(fixed_cost_for_demand, max(100, total_demand + 2), oo);
    initArray(travel_cost_for_demand, max(100, total_demand + 2), oo);
    bus_types[0].capacity = bus_types[0].fixed_cost = bus_types[0].travelling_cost = 0;
    bus_types[n_bus_type + 1].capacity = bus_types[n_bus_type + 1].fixed_cost = oo;
    initArray(bus_for_demand, max(100, total_demand + 2), n_bus_type + 1);
    bus_for_demand[0] = 0;
    for (int i = 1; i <= n_bus_type; i++) {
        for (int demand = bus_types[i].capacity; demand >= 1; demand--) {
            if (bus_types[bus_for_demand[demand]].fixed_cost > bus_types[i].fixed_cost)
                bus_for_demand[demand] = i;
        }
    }
    for (int demand = 0; demand <= total_demand; demand++) {
        fixed_cost_for_demand[demand] = bus_types[bus_for_demand[demand]].fixed_cost;
        travel_cost_for_demand[demand] = bus_types[bus_for_demand[demand]].travelling_cost;
    }
    for (int i = 0; i <= n_node; i++)
        for (int j = 0; j <= n_node; j++) {
            if (j != 0 && i != j) travel_time[i][j] += waiting_time;
        }
    for (int j = 0; j <= n_node; j++) travel_time[0][j] = 0;
    Sol::init();
}