/**
 * @Created by Manh Vu Duy (manhvdm@gmail.com) on 3/12/2021.
 * @Please contact before using this source code
 */
//

#ifndef BUS_VRP2INSTANCE_H
#define BUS_VRP2INSTANCE_H

#endif //BUS_VRP2INSTANCE_H
#pragma once
int* generateRouteWithDemand(const int& n, int total_demand, int min_demand, int max_demand) {
    poisson_distribution<int> distribution((double)(total_demand) / n);
    int* demand = new int[n + 1];
    int total_demand_1 = total_demand;
    //cout << "********" << total_demand << endl;
    for (int i = 0; i < n; i++) {
        do {
            demand[i] = distribution(generator);
        } while (demand[i] > total_demand || demand[i] < min_demand || demand[i] > max_demand);
        total_demand -= demand[i];
        if (i + 1 < n && total_demand < min_demand * (n - i - 1)) {
            return generateRouteWithDemand(n, total_demand_1, min_demand, max_demand);
        }
    }
    int index;
    while (total_demand > 1) {
        do {
            index = rand() % n;
        } while (demand[index] >= max_demand);
        ++demand[index];
        total_demand--;
    }
    //cout << total_demand << endl;
    //printArray(demand, n);
    return demand;
}
void convertVRPinstance(const string& path) {
    n_bus_type = 3;
    bus_types[1].capacity = 15, bus_types[1].fixed_cost = 1300, bus_types[1].travelling_cost = 1;
    bus_types[2].capacity = 28, bus_types[2].fixed_cost = 1700, bus_types[2].travelling_cost = 1;
    bus_types[3].capacity = 44, bus_types[3].fixed_cost = 2200, bus_types[3].travelling_cost = 1;
    max_nodes_per_route = 7;
    waiting_time = 2;
    max_percentage_travel_time = 2;
    max_nagative_time_ratio = 1.05;
    ifstream fileIn("Input_vrp/" + path);
    string str;
    getline(fileIn, str);
    getline(fileIn, str);
    getline(fileIn, str);
    fileIn >> str >> str;
    fileIn >> n_node;
    fileIn.ignore();
    n_node--;
    getline(fileIn, str);
    getline(fileIn, str);
    getline(fileIn, str);
    poisson_distribution<int> distribution_15(1.5 * bus_types[1].capacity / max_nodes_per_route);
    poisson_distribution<int> distribution_28(1.5 * bus_types[2].capacity / max_nodes_per_route);
    poisson_distribution<int> distribution_44(2 * bus_types[3].capacity / max_nodes_per_route);
    //srand(time(0));
    for (int i = 0; i <= n_node; i++) {
        fileIn >> nodes[i].id >> nodes[i].x >> nodes[i].y;
        if (i == 0) {
            nodes[i].demand = 0;
            //out(double(i), nodes[i].x, nodes[i].y, double(nodes[i].demand));
            continue;
        }
        nodes[i].demand = 1;
        //out(double(i), nodes[i].x, nodes[i].y, double(nodes[i].demand));
    }
    int max_dis = 0;
    initArray2D(travel_time, n_node+1, n_node+1);
    for (int i_1 = 0; i_1 <= n_node ; i_1++)
        for (int i_2 = 0; i_2 <= n_node; i_2++) {
            travel_time[i_1][i_2] = getEUCdis(nodes[i_1].x, nodes[i_1].y, nodes[i_2].x, nodes[i_2].y);
            max_dis = max(max_dis, travel_time[i_1][0]);
        }
    for (int i = 0; i <= n_node; i++) travel_time[0][i] = 0;
    max_time_per_route = round(max_dis * 1.5) + waiting_time * max_nodes_per_route;
    max_negative_percentage_of_student = 1.0;
    process_input();
    for (int i = 0; i <= n_node; i++) nodes[i].current_time = oo;
    ILS(1, 2000);
    Sol sol_1;
    sol_1.copy(best_sol);
    for (int i = 0; i < best_sol.n_giant_tour - 1; i++) {
        if (best_sol.giant_tour[i] == 0 && best_sol.giant_tour[i + 1] != 0) {
            int start = i + 1;
            int n = 0;
            for (int i = start; best_sol.giant_tour[i] != 0; i++) n++;
            int capacities[] = { 15, 28, 44, 44};
            int capacity;
            do {
                capacity = capacities[rand() % 4];
            } while ((double)(capacity) / n > 15);
            int* demand = generateRouteWithDemand(n, capacity - rand() % 2, 2, 15);
            for (int i = 0; i < n; i++) nodes[best_sol.giant_tour[start + i]].demand = demand[i];
        }
    }
    //for (int i = 0; i < n_node; i++)
    //	out(int(nodes[i].x), int(nodes[i].y), nodes[i].demand);
    {
        for (int i_1 = 0; i_1 <= n_node; i_1++)
            for (int i_2 = 0; i_2 <= n_node; i_2++) {
                travel_time[i_1][i_2] = getEUCdis(nodes[i_1].x, nodes[i_1].y, nodes[i_2].x, nodes[i_2].y);
                //if (i_2 != 0 && i_1 != i_2) travel_time[i_1][i_2] += waiting_time;
            }
        for (int i = 0; i <= n_node; i++) travel_time[0][i] = 0;

        //
        max_negative_percentage_of_student = 1.0;
        fileOut.open("SBRPNI-" + path);
        fileOut << waiting_time << endl;
        fileOut << max_nodes_per_route << endl;
        fileOut << max_time_per_route << endl;
        fileOut << max_percentage_travel_time << endl;
        fileOut << max_nagative_time_ratio << endl;
        //fileOut << max_negative_percentage_of_student << endl;
        fileOut << n_node << endl;
        for (int i = 0; i <= n_node; i++) {
            fileOut << i << " " << nodes[i].x << " " << nodes[i].y << " " << nodes[i].demand << endl;
        }
        for (int i_1 = 0; i_1 <= n_node; i_1++) {
            for (int i_2 = 0; i_2 <= n_node; i_2++) {
                fileOut << travel_time[i_1][i_2] << " ";
            }
            fileOut << endl;
        }
        fileOut << n_bus_type << endl;
        for (int i = 1; i <= n_bus_type; i++) {
            fileOut << bus_types[i].capacity << " " << bus_types[i].fixed_cost << " " << bus_types[i].travelling_cost << endl;
        }
        process_input();
        for (int i = 0; i <= n_node; i++) nodes[i].current_time = oo;
        Sol sol;
        sol.greedy();
        for (int i = 0; i <= n_node; i++) nodes[i].current_time = sol.time_of_node[i];
        for (int i = 0; i <= sol.n_giant_tour; i++) fileOut << sol.giant_tour[i] << endl;
        sol.check();
        cout << sol.total_cost << endl;
        sol.statistic();
        fileOut.close();
        //cout << sol.total_cost << endl;
    }
    //sol_1.convertGiantToRoutes();
    //sol_1.printf();
}

