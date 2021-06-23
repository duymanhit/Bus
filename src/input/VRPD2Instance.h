/**
 * @Created by Manh Vu Duy (manhvdm@gmail.com) on 6/17/2021.
 * @Please contact before using this source code
 */
//

#ifndef BUS_VRPD2INSTANCE_H
#define BUS_VRPD2INSTANCE_H
#endif //BUS_VRPD2INSTANCE_H
#pragma once

void convertVRPDInstance(const string &path) {
    n_bus_type = 3;
    bus_types[1].capacity = 15, bus_types[1].fixed_cost = 1300, bus_types[1].travelling_cost = 1;
    bus_types[2].capacity = 28, bus_types[2].fixed_cost = 1700, bus_types[2].travelling_cost = 1;
    bus_types[3].capacity = 44, bus_types[3].fixed_cost = 2200, bus_types[3].travelling_cost = 1;
    max_nodes_per_route = 7;
    waiting_time = 2;
    max_percentage_travel_time = 2;
    max_negative_time_ratio = 1.05;
    max_time_per_route = 90;
    ifstream fileIn("../input/Input_vrpd/" + path);
    string str;
    for (int i = 1; i <= 11; i++)
        getline(fileIn, str);

    //srand(time(0));
    //fileIn.ignore();
    n_node = 0;
    double ddd;
    while (fileIn >> nodes[n_node].id >> nodes[n_node].x >> nodes[n_node].y >> ddd) {
        nodes[n_node].pre_demand = rand() % 15 + 1;
        if (rand() % 20 == 1) nodes[n_node].pre_demand = 0;
        nodes[n_node].demand = nodes[n_node].pre_demand + rand() % 4;
        n_node++;
        if (n_node > 16) break;

    }
    n_node--;
    int max_dis = 0;
    initArray2D(travel_time, n_node + 1, n_node + 1);
    for (int i_1 = 0; i_1 <= n_node; i_1++)
        for (int i_2 = 0; i_2 <= n_node; i_2++) {
            travel_time[i_1][i_2] = round(
                    getMHTanDis(nodes[i_1].x, nodes[i_1].y, nodes[i_2].x, nodes[i_2].y) / 30.0 * 60);
            max_dis = max(max_dis, travel_time[i_1][0]);
        }
    for (int i = 0; i <= n_node; i++) travel_time[0][i] = 0;
    for (int i = 0; i <= n_node; i++) {
        if (i != 0 && nodes[i].pre_demand == 0) {
            // new node
            nodes[i].current_time = 0;
        } else
            nodes[i].current_time = round((((rand() % 1000) / 999.0) + 1.0) * travel_time[i][0]);
        if (i == 0) {
            nodes[i].demand = nodes[i].pre_demand = nodes[i].current_time = 0;
        }
    }
    {
        fileOut.open("../input/SBRPNI-" + path);
        fileOut << waiting_time << endl;
        fileOut << max_nodes_per_route << endl;
        fileOut << max_time_per_route << endl;
        fileOut << max_percentage_travel_time << endl;
        fileOut << max_negative_time_ratio << endl;
        //fileOut << max_negative_percentage_of_student << endl;
        fileOut << n_node << endl;
        for (int i = 0; i <= n_node; i++) {
            fileOut << i << " " << nodes[i].x << " " << nodes[i].y << " " << nodes[i].pre_demand << " " << nodes[i].demand << " " << nodes[i].current_time << endl;
        }
        for (int i_1 = 0; i_1 <= n_node; i_1++) {
            for (int i_2 = 0; i_2 <= n_node; i_2++) {
                fileOut << travel_time[i_1][i_2] << " ";
            }
            fileOut << endl;
        }
        fileOut << n_bus_type << endl;
        for (int i = 1; i <= n_bus_type; i++) {
            fileOut << bus_types[i].capacity << " " << bus_types[i].fixed_cost << " " << bus_types[i].travelling_cost
                    << endl;
        }
        fileOut.close();
    }
}
