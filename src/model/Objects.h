/**
 * @Created by Manh Vu Duy (manhvdm@gmail.com) on 3/12/2021.
 * @Please contact before using this source code
 */
//

#ifndef BUS_OBJECTS_H
#define BUS_OBJECTS_H

#endif //BUS_OBJECTS_H
#pragma once
struct VehicleType{
    int capacity;
    int fixed_cost;
    int travelling_cost;
};

struct Location {
    int id;
    double x;
    double y;
    int pre_demand = 0;
    int demand;
    string address;
    int current_time;
};
