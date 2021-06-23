/**
 * @Created by Manh Vu Duy (manhvdm@gmail.com) on 3/12/2021.
 * @Please contact before using this source code
 */
//

#ifndef BUS_MIP_H
#define BUS_MIP_H

#endif //BUS_MIP_H
#pragma once

void mip() {
    IloEnv env;
    IloModel model(env);
    IloCplex cplex(model);
    cplex.setParam(IloCplex::TiLim, 60 * 60);
    cplex.setParam(IloCplex::WorkMem, 16 * 1024);
    cplex.setParam(IloCplex::TreLim, 16 * 1024);
    fileOut.open(outputDictionary + instance_name);
    cplex.setOut(fileOut);
    IloNumVarArray l(env, n_node + 1, 0, max_nodes_per_route); // constraint(9)
    IloNumVarArray d(env, n_node + 1, 0, bus_types[n_bus_type].capacity);
    IloNumVarArray time(env, n_node + 1, 0, max_time_per_route); // constraint (10)
    IloBoolVarArray r(env, n_node + 1);
    IloArray<IloBoolVarArray> x(env, n_node + 1);
    IloArray<IloBoolVarArray> y(env, n_node + 1);
    IloArray<IloNumVarArray> cost(env, n_node + 1);
    for (int i = 0; i <= n_node; i++) {
        x[i] = IloBoolVarArray(env, n_node + 1);
        y[i] = IloBoolVarArray(env, n_bus_type + 1);
        cost[i] = IloNumVarArray(env, n_bus_type + 1, 0, max_time_per_route * bus_types[n_bus_type].travelling_cost + bus_types[n_bus_type].fixed_cost + 1);
    }
    // constraint (2)
    for (int i = 1; i <= n_node; i++) {
        IloExpr con(env);
        for (int j = 1; j <= n_node; j++)
            if (i != j)
                con += x[i][j];
        for (int j = 1; j <= n_bus_type; j++)
            con += y[i][j];
        model.add(con == 1);
        con.end();
    }
    // constraint (3)
    for (int j = 1; j <= n_node; j++) {
        IloExpr con(env);
        for (int i = 0; i <= n_node; i++)
            if (i != j) {
                con += x[i][j];
            }
        model.add(con == 1);
        con.end();
    }
    // time location capacity
    // caculate time
    int max_time = 0;
    for (int i = 0; i <= n_node; i++)
        for (int j = 1; j <= n_node; j++)
            max_time = max(max_time, travel_time[j][i]);
    max_time += max_time_per_route;
    int max_demand = 0;
    for (int i = 1; i <= n_node; i++) max_demand = max(max_demand, nodes[i].demand);
    max_demand += bus_types[n_bus_type].capacity;
    for (int i = 0; i <= n_node; i++) {
        for (int j = 1; j <= n_node; j++)
            if (i != j) {
                // constraint (4)
                model.add(l[i] + 1 + (max_nodes_per_route) * x[i][j] <= l[j] + (max_nodes_per_route));
                // constraint (5)
                model.add(d[i] + nodes[j].demand + (max_demand) * x[i][j] <= d[j] + (max_demand));
                // constraint (6)
                model.add(time[i] + travel_time[j][i] + max_time * x[i][j] <= time[j] + max_time);

            }
    }
    // constraint (7)
    for (int i = 1; i <= n_node; i++) {
        for (int j = 1; j <= n_bus_type; j++) {
            model.add(d[i] + y[i][j] * (bus_types[n_bus_type].capacity) <= bus_types[j].capacity + (bus_types[n_bus_type].capacity));
        }
    }
    // constraint (11)
    for (int i = 1; i <= n_node; i++) {
        model.add(time[i] <= getMaxTravelTime(i));
    }
    // constraint (12)
    {
        IloExpr con(env);
        for (int i = 1; i <= n_node; i++) if (nodes[i].pre_demand > 0) {
            model.add(time[i] - r[i] * max_time_per_route <= max_negative_time_ratio * nodes[i].current_time);
            con += r[i] * nodes[i].pre_demand;
        }
        model.add(con <= max_negative_students);
        con.end();
    }
    //contraint(13)
    {
        for (int i = 1; i <= n_node; i++) {
            for (int j = 1; j <= n_bus_type; j++) {
                int M = bus_types[j].travelling_cost * max_time_per_route;
                model.add(cost[i][j] - bus_types[j].travelling_cost * time[i] - (M + bus_types[j].fixed_cost) * y[i][j] >= -M);
            }
        }
    }
    /// <summary>
    /// obj
    /// </summary>
    IloExpr obj(env);
    for (int i = 1; i <= n_node; i++) {
        for (int j = 1; j <= n_bus_type; j++) {
            obj += cost[i][j];
        }
    }
    model.add(IloMinimize(env, obj));
    Sol::start_running = clock();
    cplex.solve();
    cout << cplex.getStatus() << endl;
    cout << cplex.getValue(obj) << endl;
    int x_value[50][50];
    for (int i = 0; i <= n_node; i++) {
        for (int j = 1; j <= n_node; j++) {
            if (i != j) {
                x_value[i][j] = (cplex.getValue(x[i][j]) > 0.5);
                //cout << round(cplex.getValue(x[i][j])) << " ";

            } else x_value[i][j] = 0;
            //cout << 0 << " ";
        }
        //if (i > 0) cout << (cplex.getValue(y[i][1]) > 0.5) + (cplex.getValue(y[i][2]) > 0.5) + (cplex.getValue(y[i][3]) > 0.5) << endl;
        //else cout << endl;
    }

    Sol sol;
    sol.n_giant_tour = 0;
    sol.giant_tour[0] = 0;
    int start = 0;
    while (true) {
        int start_node = -1;
        for (int i = start + 1; i <= n_node; i++) {
            bool check_start = true;
            for (int j = 1; j <= n_node; j++)
                if (i != j && x_value[i][j] > 0) {
                    check_start = false;
                    break;
                }
            if (check_start) {
                start_node = i;
                start = i;
                break;
            }
        }
        if (start_node == -1) break;
        while (start_node != 0) {
            int node = 0, count = 0;
            for (int next_node = 0; next_node <= n_node; next_node++)
                if (start_node != next_node && x_value[next_node][start_node] == 1) {
                    count++;
                    node = next_node;
                    x_value[next_node][start_node] = 2;
                }
            if (count != 1) cout << "error " << count << endl;;
            sol.giant_tour[++sol.n_giant_tour] = start_node;
            start_node = node;
        }
        sol.giant_tour[++sol.n_giant_tour] = 0;
    }
    reverse(sol.giant_tour, sol.giant_tour + sol.n_giant_tour + 1);
    sol.processGiantToRoutes();
    sol.outFile(cplex.getMIPRelativeGap(), false);
    out(sol.total_cost, int(round(100 * double(sol.n_negative) / total_demand)));
    printArray0N(sol.giant_tour, sol.n_giant_tour);
    //for (int i = 1; i <= n_node; i++) {
    //	cout << cplex.getValue(time[i]) << " ";
    //}
    //cout << endl;
    //for (int i = 1; i <= n_node; i++) {
    //	cout << sol.timeOfNode[i] << " ";
    //}
    //cout << endl;
    //printArray0N(sol.demand_giant, sol.nGiantTour);
    //for (int i = 0; i <= sol.nGiantTour; i++) {
    //	cout << cplex.getValue(d[sol.giantTour[i]]) << " ";
    //}
    if (int(round(cplex.getValue(obj))) != sol.total_cost) while (true);
    sol.check();
    env.end();
}