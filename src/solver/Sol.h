/**
 * @Created by Manh Vu Duy (manhvdm@gmail.com) on 3/12/2021.
 * @Please contact before using this source code
 */
//

#ifndef BUS_SOL_H
#define BUS_SOL_H

#endif //BUS_SOL_H

struct Sol {
    int n_giant_tour;
    int order_node[maxn];
    int giant_tour[maxn];
    static clock_t start_running;
    static int *time_of_node;
    static int *start_route;
    static int *end_route;
    static int *route_of_index;
    static int *time_giant;
    static int *demand_giant;
    static int *demand_of_route;
    //static int* fixed_cost_of_route;
    //static int* travel_cost_of_route;
    static bool *is_negative_node;
    static int *time_of_route;
    static int *cost_of_route;
    static int *cache_route;
    static bool *is_served;
    int n_route;
    int total_cost;
    int n_negative;

    Sol();

    ~Sol();

    static void init();

    static void destroy();

    void split();

    void processGiantToRoutes();

    void convertGiantToOrder();

    int check();

    int getNegativeStudents(const int &start, const int &end, const int &time);

    int getNegativeStudentsWithStartTime(const int &start, const int &end, int time);

    int getNegativeStudentForm(const int &start, int time);

    void cloneToCache(const int &start, const int &end);

    void pasteFormCache(const int &start, const int &end);

    int getTimeSubTour(int, int);

    int getDemandSubTour(int, int);

    int getDiffTimeSwap(int &, int &, int &, int &);

    //int getDiffTimeSwapInRoute(int& start_1, int& end_1, int& start_2, int& end_2);
    int getDiffDemandSwap(int &, int &, int &, int &);

    int getCostRoute(int &, const int &);

    void localSearch();

    void greedy();

    void greedyFormCurrentSol();

    II getCostInsert(const int &node);

    void processFormOrderNode();

    void copy(Sol another_sol);

    void statistic();

    void outFile();

    void outFile(double);

    void printf();

    void improve();

    II getCostInsert(const int &node, bool remainingSpot);

    void copyOrderNode(Sol anotherSol);
};

clock_t Sol::start_running;
int *Sol::time_of_node;
int *Sol::start_route;
int *Sol::end_route;
int *Sol::route_of_index;
int *Sol::time_giant;
int *Sol::demand_giant;
int *Sol::demand_of_route;
//int* Sol::fixed_cost_of_route;
//int* Sol::travel_cost_of_route;
bool *Sol::is_negative_node;
int *Sol::time_of_route;
int *Sol::cost_of_route;
int *Sol::cache_route;
bool *Sol::is_served;

inline Sol::Sol() {
    //cout << "manh ";
    total_cost = 0;
    //initArray(this->orderNode, n_node + 1, 0);
    //initArray(this->giantTour, n_node * 2, 0);

}

inline Sol::~Sol() {
    //delete giantTour;
    //delete orderNode;
}

void Sol::init() {
    destroy();
    initArray(Sol::time_of_node, n_node * 3, oo);
    initArray(Sol::start_route, n_node * 3, 0);
    initArray(Sol::end_route, n_node * 3, 0);
    initArray(Sol::route_of_index, n_node * 3, 0);
    initArray(Sol::time_giant, n_node * 3, 0);
    initArray(Sol::demand_giant, n_node * 3, 0);
    initArray(Sol::demand_of_route, n_node * 3, 0);
    //initArray(Sol::fixed_cost_of_route, n_node + 1, 0);
    //initArray(Sol::travel_cost_of_route, n_node + 1, 0);
    initArray(Sol::is_negative_node, n_node * 3, false);
    initArray(Sol::time_of_route, n_node * 3, 0);
    initArray(Sol::cost_of_route, n_node * 3, 0);
    initArray(string_concat_next, n_node * 3);
    initArray(string_concat_cache, n_node * 3);
    initArray(Sol::cache_route, n_node * 3);
    initArray(Sol::is_served, n_node * 3, false);
}

void Sol::destroy() {
    delete Sol::time_of_node;
    delete Sol::start_route;
    delete Sol::end_route;
    delete Sol::route_of_index;
    delete Sol::time_giant;
    delete Sol::demand_giant;
    delete Sol::demand_of_route;
    //delete Sol::fixed_cost_of_route;
    //delete Sol::travel_cost_of_route;
    delete Sol::is_negative_node;
    delete Sol::time_of_route;
    delete Sol::cost_of_route;
    delete string_concat_cache;
    delete string_concat_next;
    delete Sol::cache_route;
    delete Sol::is_served;
}

void Sol::split() {
    ///<summary>
    /// f_split[i][k] is result of splitting to i with k negative locations
    ///f_split[i][j] =
    ///</summary>
    for (int i = 0; i <= n_node; i++) for (int k = 0; k <= max_negative_students; k++) f_split[i][k] = oo;
    f_split[0][0] = 0;
    int demand, time, start, current_n_negative, cost, i, end, k, max_end;
    for (i = 0; i < n_node; i++) {
        for (k = 0; k <= max_negative_students; k++)
            if (f_split[i][k] != oo) {
                demand = 0;
                time = 0;
                start = 0;
                current_n_negative = k;
                int max_end = min(n_node, i + max_nodes_per_route);
                for (end = i + 1; end <= max_end; end++) {
                    time += travel_time[order_node[end]][start];
                    if (!checkTimeNode(order_node[end], time)) break;
                    demand += nodes[order_node[end]].demand;
                    start = order_node[end];
                    if (checkNegative(start, time)) current_n_negative += nodes[start].demand;
                    if (current_n_negative > max_negative_students) break;
                    cost = f_split[i][k] + time * travel_cost_for_demand[demand] + fixed_cost_for_demand[demand];
                    //out(i + 1, end, cost, fixed_cost_for_demand[demand]);
                    //out(demand, time);
                    if (f_split[end][current_n_negative] > cost) {
                        f_split[end][current_n_negative] = cost;
                        pre_split[end][current_n_negative] = II(i, k);
                    }
                }
            }
    }
    current_n_negative = 0;
    for (k = 0; k <= max_negative_students; k++)
        if (f_split[n_node][k] < f_split[n_node][current_n_negative]) {
            current_n_negative = k;
        }
    total_cost = f_split[n_node][current_n_negative];
    n_negative = current_n_negative;
    n_giant_tour = 0;
    giant_tour[0] = 0;
    int current_end = n_node;
    while (current_end) {
        for (i = current_end; i > pre_split[current_end][current_n_negative].fs; i--)
            giant_tour[++n_giant_tour] = order_node[i];
        giant_tour[++n_giant_tour] = 0;
        current_n_negative = pre_split[current_end][current_n_negative].sc;
        current_end = i;
    }
    reverse(giant_tour + 1, giant_tour + n_giant_tour);
    giant_tour[++n_giant_tour] = 0;
    processGiantToRoutes();
    //check();
    //update();
}

void Sol::processGiantToRoutes() {
    // remove double depots
    int n = 0;
    for (int i = 1; i <= n_giant_tour; i++)
        if (giant_tour[i - 1] != 0 || giant_tour[i] != 0)
            giant_tour[++n] = giant_tour[i];
    giant_tour[++n] = 0;
    n_giant_tour = n;
    // time, demand following giant tour
    demand_giant[0] = 0;
    time_giant[0] = 0;
    n_route = 1;
    route_of_index[0] = 1;
    start_route[n_route] = 0;
    end_route[n_route] = 0;
    n_negative = 0;
    total_cost = 0;
    for (int i = 1; i <= n_giant_tour; i++) {
        if (giant_tour[i] == 0) {
            // end of one tour
            demand_of_route[n_route] = demand_giant[i - 1];
            time_of_route[n_route] = time_giant[i - 1];
            //fixed_cost_of_route[nRoute] = fixed_cost_for_demand[demand_of_route[nRoute]];
            //travel_cost_of_route[nRoute] = time_giant[i - 1] * travel_cost_for_demand[demand_of_route[nRoute]];
            cost_of_route[n_route] = fixed_cost_for_demand[demand_of_route[n_route]]
                                     + time_of_route[n_route] * travel_cost_for_demand[demand_of_route[n_route]];
            total_cost += cost_of_route[n_route];
            // new tour
            route_of_index[i] = ++n_route;
            start_route[n_route] = i;
            end_route[n_route] = i;
            time_giant[i] = 0;
            demand_giant[i] = 0;
            demand_of_route[n_route] = 0;
        } else {
            time_giant[i] = time_giant[i - 1] + travel_time[giant_tour[i]][giant_tour[i - 1]];
            demand_giant[i] = demand_giant[i - 1] + nodes[giant_tour[i]].demand;
            time_of_node[giant_tour[i]] = time_giant[i];
            is_negative_node[giant_tour[i]] = checkNegative(giant_tour[i], time_giant[i]);
            n_negative += is_negative_node[giant_tour[i]] * nodes[giant_tour[i]].demand;
            route_of_index[i] = n_route;
            end_route[n_route] = i;
        }
    }

}

inline void Sol::convertGiantToOrder() {
    int n = 0;
    order_node[0] = 0;
    for (int i = 1; i < n_giant_tour; i++) if (giant_tour[i] != 0) order_node[++n] = giant_tour[i];
}

int Sol::check() {
    // check cost
    int check_cost = 0;
    int time = 0;
    int demand = 0;
    int node = 0;
    int check_n_negative = 0;
    for (int i = 1; i <= n_giant_tour; i++) {
        if (giant_tour[i] == 0) {
            // end of one routes
            int route = route_of_index[i - 1];
            //if (fixed_cost_of_route[routes] != fixed_cost_for_demand[demand]) {
            //	cout << "Error: fixed cost of one routes" << endl;
            //}
            //if (travel_cost_of_route[routes] != time * travel_cost_for_demand[demand]) {
            //	cout << "Error: travelling cost of one routes" << endl;
            //}
            check_cost += fixed_cost_for_demand[demand] + time * travel_cost_for_demand[demand];
            // number of node
            if (node > max_nodes_per_route) {
                cout << "Error: max node per routes" << endl;
                return 1;
            }
            if (time > max_time_per_route) {
                cout << "Error: max time per routes" << endl;
                return 2;
            }
            // new routes
            time = 0;
            demand = 0;
            node = 0;
        } else {
            if (!checkTimeNode(giant_tour[i], time)) {
                cout << "Error: max time per node" << giant_tour[i] << endl;
                return 3;
            }
            time += travel_time[giant_tour[i]][giant_tour[i - 1]];
            demand += nodes[giant_tour[i]].demand;
            check_n_negative += checkNegative(giant_tour[i], time) * nodes[giant_tour[i]].demand;
            node++;
        }
    }
    if (check_cost != total_cost) {
        cout << "Error: total cost" << endl;
        return 4;
    }
    if (check_n_negative > max_negative_students || check_n_negative != n_negative) {
        cout << "Error: negative impact" << endl;
        return 5;
    }
    //
    for (int node = 1; node <= n_node; node++) {
        int count = appearanceTime(giant_tour, 1, n_giant_tour, node);
        if (count != 1) {
            cout << "Error: Appearance of one node " << node << " " << count << endl;
            //return 6;
        }
    }
    //
    return 0;
}

int Sol::getNegativeStudents(const int &start, const int &end, const int &time) {
    int result = 0;
    for (int i = start; i <= end; i++) {
        if (giant_tour[i] == 0) break;
        if (!checkTimeNode(giant_tour[i], time_giant[i] + time)) return oo;
        result += (checkNegative(giant_tour[i], time_giant[i] + time) - is_negative_node[giant_tour[i]]) *
                  nodes[giant_tour[i]].demand;
    }
    return result;
}

inline int Sol::getNegativeStudentsWithStartTime(const int &start, const int &end, int time) {
    int result = 0;
    for (int i = start; i <= end; i++) {
        if (giant_tour[i] == 0) break;
        if (!checkTimeNode(giant_tour[i], time)) return oo;
        result += (checkNegative(giant_tour[i], time) - is_negative_node[giant_tour[i]]) * nodes[giant_tour[i]].demand;
        time += travel_time[giant_tour[i + 1]][giant_tour[i]];
    }
    return result;
}

inline int Sol::getNegativeStudentForm(const int &start, int time) {
    int result = 0;
    for (int i = start; true; i++) {
        if (!checkTimeNode(cache_route[i], time)) return oo;
        result +=
                (checkNegative(cache_route[i], time) - is_negative_node[cache_route[i]]) * nodes[cache_route[i]].demand;
        if (route_of_index[i + 1] == route_of_index[start]) {
            time += travel_time[cache_route[i + 1]][cache_route[i]];
        } else {
            break;
        }
    }
    return result;
    return 0;
}

inline void Sol::cloneToCache(const int &start, const int &end) {
    for (int i = start; i <= end; i++) cache_route[i] = giant_tour[i];
}

inline void Sol::pasteFormCache(const int &start, const int &end) {
    for (int i = start; i <= end; i++) giant_tour[i] = cache_route[i];

}

inline int Sol::getTimeSubTour(int start, int end) {
    if (start > end) return 0;
    return time_giant[end] - time_giant[start];
}

inline int Sol::getDemandSubTour(int start, int end) {
    return demand_giant[end] - demand_giant[start - 1];
}

inline int Sol::getDiffTimeSwap(int &start_1, int &end_1, int &start_2, int &end_2) {
    int current_time;
    if (start_1 <= end_1) {
        current_time = travel_time[giant_tour[start_1]][giant_tour[start_1 - 1]] +
                       travel_time[giant_tour[end_1 + 1]][giant_tour[end_1]]
                       + getTimeSubTour(start_1, end_1);
    } else {
        current_time = travel_time[giant_tour[start_1]][giant_tour[end_1]];
    }
    if (start_2 <= end_2) {
        return travel_time[giant_tour[start_2]][giant_tour[start_1 - 1]] +
               travel_time[giant_tour[end_1 + 1]][giant_tour[end_2]]
               + getTimeSubTour(start_2, end_2)
               - current_time;
    }
    //out(travel_time[giantTour[end_1 + 1]][giantTour[start_1 - 1]], current_time);
    return travel_time[giant_tour[end_1 + 1]][giant_tour[start_1 - 1]]
           - current_time;
}
//
//inline int Sol::getDiffTimeSwapInRoute(int& start_1, int& end_1, int& start_2, int& end_2)
//{
//	if (start_1 + 1 == start_2) {
//		return
//	}
//	return getNewDemandSwap(start_1, end_1, start_2, end_2);
//}

inline int Sol::getDiffDemandSwap(int &start_1, int &end_1, int &start_2, int &end_2) {
    return getDemandSubTour(start_2, end_2) - getDemandSubTour(start_1, end_1);
}

inline int Sol::getCostRoute(int &demand, const int &riding_time) {
    return fixed_cost_for_demand[demand] + riding_time * travel_cost_for_demand[demand];
}

void Sol::localSearch() {
    int max_k = 5; /*(max_nodes_per_route - 1) / 2 + 1; //TODO*/
    bool check_improve = true;
    int route_1, route_2, new_demand_1, new_demand_2, diff_time_1, diff_time_2, new_time_1, new_time_2, negative_1, negative_2;
    while (check_improve) {
        check_improve = false;
        for (int start_1 = 1; start_1 < n_giant_tour; start_1++)
            for (int end_1 = start_1 - 1; end_1 < min(start_1 + max_k, n_giant_tour); end_1++)
                for (int start_2 = start_1 + 1; start_2 < n_giant_tour; start_2++)
                    for (int end_2 = start_2 - 1; end_2 < min(start_2 + max_k, n_giant_tour); end_2++) {
                        if (!checkSwapSubArray(start_1, end_1, start_2, end_2)) continue;
                        route_1 = route_of_index[end_1];
                        route_2 = route_of_index[end_2];
                        if ((route_1 != route_of_index[start_1] || giant_tour[start_1] == 0) &&
                            start_1 <= end_1)
                            continue;
                        if ((route_2 != route_of_index[start_2] || giant_tour[start_2] == 0) &&
                            start_2 <= end_2)
                            continue;
                        if (route_1 != route_2) {
                            // number node
                            if (end_route[route_1] - start_route[route_1] - (end_1 - start_1 + 1) +
                                (end_2 - start_2 + 1) > max_nodes_per_route)
                                continue;
                            if (end_route[route_2] - start_route[route_2] + (end_1 - start_1 + 1) -
                                (end_2 - start_2 + 1) > max_nodes_per_route)
                                continue;
                            //
                            new_demand_1 = demand_of_route[route_1] + getDiffDemandSwap(start_1, end_1, start_2, end_2);
                            new_demand_2 = demand_of_route[route_2] + getDiffDemandSwap(start_2, end_2, start_1, end_1);
                            diff_time_1 = getDiffTimeSwap(start_1, end_1, start_2, end_2);
                            diff_time_2 = getDiffTimeSwap(start_2, end_2, start_1, end_1);
                            new_time_1 = time_of_route[route_1] + diff_time_1;
                            new_time_2 = time_of_route[route_2] + diff_time_2;
                            //cout << totalCost << endl;
                            if (new_time_1 > max_time_per_route || new_time_2 > max_time_per_route)
                                continue;
                            if (cost_of_route[route_1] + cost_of_route[route_2] <=
                                getCostRoute(new_demand_1, new_time_1) + getCostRoute(new_demand_2, new_time_2))
                                continue;
                            negative_1 = getNegativeStudents(end_1 + 1, n_giant_tour, diff_time_1)
                                         + getNegativeStudentsWithStartTime(start_2, end_2, time_giant[start_1 - 1] +
                                                                                            travel_time[giant_tour[start_2]][giant_tour[
                                                                                                    start_1 - 1]]);
                            negative_2 = getNegativeStudents(end_2 + 1, n_giant_tour, diff_time_2)
                                         + getNegativeStudentsWithStartTime(start_1, end_1, time_giant[start_2 - 1] +
                                                                                            travel_time[giant_tour[start_1]][giant_tour[
                                                                                                    start_2 - 1]]);

                            if (n_negative + negative_1 + negative_2 > max_negative_students)
                                continue;
                            int new_negative = n_negative + negative_1 + negative_2;
                            int new_cost = total_cost - (cost_of_route[route_1] + cost_of_route[route_2])
                            	+ (getCostRoute(new_demand_1, new_time_1) + getCostRoute(new_demand_2, new_time_2));

                            // swap subtours
                            check_improve = true;
                            //printArray0N(giantTour, nGiantTour);
                            swapSubArray(giant_tour, n_giant_tour, 1,start_1, end_1,1, start_2, end_2);
                            processGiantToRoutes();
                            if (check() != 0 || new_cost != total_cost || new_negative != n_negative) {
                            	out(new_cost, total_cost);
                            	printArray0N(giant_tour, n_giant_tour);
                            	break;
                            }

                        } else {
                            //continue;
                            diff_time_1 = getDiffTimeSwap(start_1, end_1, start_2, end_2);
                            diff_time_2 = getDiffTimeSwap(start_2, end_2, start_1, end_1);
                            if (diff_time_1 + diff_time_2 >= 0) continue;
                            int new_cost = total_cost + (diff_time_1 + diff_time_2) * travel_cost_for_demand[demand_of_route[route_1]];
                            // n = end_route[route_1] - start_route[route_1];
                            cloneToCache(start_route[route_1], end_route[route_1]);
                            swapSubArray(cache_route + start_route[route_1],
                                         end_route[route_1] - start_route[route_1] + 1,
                                         1,
                                         start_1 - start_route[route_1], end_1 - start_route[route_1],1,
                                         start_2 - start_route[route_1], end_2 - start_route[route_1]);
                            negative_1 = getNegativeStudentForm(start_1 - 1, time_giant[start_1 - 1]);
                            if (n_negative + negative_1 > max_negative_students) {
                                continue;
                            }
                            check_improve = true;
                            pasteFormCache(start_route[route_1], end_route[route_1]);
                            processGiantToRoutes();

                            if (check() || new_cost != total_cost) {
                            	printArray0N(giant_tour, n_giant_tour);
                            	while (true);
                            }
                        }
                    }
    }
}

inline void Sol::greedy() {
    for (int i = 0; i <= 2 * n_node; i++) giant_tour[i] = 0;
    for (int i = 1; i <= n_node; i++) is_served[i] = false;
    n_giant_tour = 2;
    n_negative = 0;
    total_cost = 0;
    processGiantToRoutes();
    for (int t = 1; t <= n_node; t++) {
        // choice served node
        int res_node = 0, res_cost = oo, res_index = -1;
        for (int node = 1; node <= n_node; node++)
            if (!is_served[node]) {
                II cost_index = getCostInsert(node, rand() % 2);
                if (res_cost > cost_index.fs) {
                    res_cost = cost_index.fs;
                    res_node = node;
                    res_index = cost_index.sc;
                }
            }
        //

        int old_cost = total_cost;
        insertAfter(giant_tour, n_giant_tour, res_index, res_node);
        is_served[res_node] = true;
        //
        processGiantToRoutes();
    }
    //printArray0N(giantTour, nGiantTour);
    convertGiantToOrder();
    //check();
    //split();
}

inline void Sol::greedyFormCurrentSol() {
    random_shuffle(order_node + 1, order_node + n_node + 1);
    int n_remove = random(max_nodes_per_route, n_node / 2);
    for (int i = 1; i <= n_remove; i++) is_served[order_node[i]] = false;
    int n = 0;
    for (int i = 1; i <= n_giant_tour; i++)
        if (giant_tour[i] == 0 || is_served[giant_tour[i]]) {
            giant_tour[++n] = giant_tour[i];
        }
    n_giant_tour = n;
    processGiantToRoutes();
    for (int i = n_giant_tour; i <= 2 * n_node; i++) giant_tour[i] = 0;
    for (int t = 1; t <= n_node / 2; t++) {
        // choice served node
        int res_node = 0, res_cost = oo, res_index = -1;
        for (int node = 1; node <= n_node; node++)
            if (!is_served[node]) {
                II cost_index = getCostInsert(node);
                if (res_cost > cost_index.fs) {
                    res_cost = cost_index.fs;
                    res_node = node;
                    res_index = cost_index.sc;
                }
                if (res_cost == oo) {
                    while (true);
                }
            }
        //

        int old_cost = total_cost;
        insertAfter(giant_tour, n_giant_tour, res_index, res_node);
        is_served[res_node] = true;
        //
        processGiantToRoutes();
    }
    //printArray0N(giantTour, nGiantTour);
    convertGiantToOrder();
    //if (check() != 0) while(true);
    //split();
}

inline II Sol::getCostInsert(const int &node, bool remainingSpot) {
    int res_cost = oo, res_index = 0;
    for (int index = 0; index < n_giant_tour; index++) {
        // number node of this routes
        int route = route_of_index[index];
        if (end_route[route] - start_route[route] >= max_nodes_per_route) {
            index = end_route[route];
            continue;
        }
        //  served_time = time_giant[index] + travel_time[node][giantTour[index]];
        // adjust_time = served_time + travel_time[giantTour[index + 1]][node] - travel_time[giantTour[index + 1]][giantTour[index]]
        int served_time = time_giant[index] + travel_time[node][giant_tour[index]];
        if (!checkTimeNode(node, served_time)) continue;
        int adjust_time = travel_time[node][giant_tour[index]] + travel_time[giant_tour[index + 1]][node] -
                          travel_time[giant_tour[index + 1]][giant_tour[index]];
        int new_demand = demand_of_route[route] + nodes[node].demand;
        int adjust_cost = getCostRoute(new_demand, time_of_route[route] + adjust_time) - cost_of_route[route];
        if (remainingSpot) {
            int capacity = bus_types[bus_for_demand[new_demand]].capacity;
            adjust_cost += (double) (capacity - new_demand) * fixed_cost_for_demand[new_demand] / capacity;
        }
        if (adjust_cost > res_cost) continue;
        if (n_negative + getNegativeStudentsWithStartTime(index + 1, n_giant_tour,
                                                          served_time + travel_time[giant_tour[index + 1]][node]) +
            getNegative(node, served_time) > max_negative_students)
            continue;
        res_cost = adjust_cost;
        res_index = index;
    }
    return II(res_cost, res_index);
}

inline void Sol::processFormOrderNode() {
    split();
    localSearch();
    convertGiantToOrder();
}

inline void Sol::improve() {
    int oldCost = INT_MAX;
    do {
        split();
        if (oldCost > total_cost) {
            oldCost = total_cost;
        } else {
            if (oldCost < total_cost) {
                cout << "ERROR";
                while (true);
            }
            break;
        }
        localSearch();
        if (oldCost > total_cost) {
            oldCost = total_cost;
        } else {
            if (oldCost < total_cost) {
                cout << "ERROR";
                while (true);
            }
            break;
        }
        convertGiantToOrder();
    } while (true);
}


inline void Sol::copy(Sol another_sol) {
    n_giant_tour = another_sol.n_giant_tour;
    n_negative = another_sol.n_negative;
    total_cost = another_sol.total_cost;
    for (int i = 0; i <= n_giant_tour; i++) giant_tour[i] = another_sol.giant_tour[i];
    for (int i = 0; i <= n_node; i++) order_node[i] = another_sol.order_node[i];
}

inline void Sol::copyOrderNode(Sol anotherSol) {
    for (int i = 0; i <= n_node; i++) order_node[i] = anotherSol.order_node[i];
}

inline void Sol::statistic() {
    int res_route = 0, res_1 = 0, res_2 = 0, res_3 = 0;
    for (int route = 1; route <= n_route; route++) {
        if (demand_of_route[route] == 0) continue;
        res_route++;
        if (demand_of_route[route] <= bus_types[1].capacity) {
            res_1++;
            continue;
        }
        if (demand_of_route[route] <= bus_types[2].capacity) {
            res_2++;
            continue;
        }
        if (demand_of_route[route] <= bus_types[3].capacity) {
            res_3++;
            continue;
        }
    }
    out(res_route, res_1, res_2, res_3);
}

inline void Sol::outFile() {
    // routes
    int res_route = 0, res_1 = 0, res_2 = 0, res_3 = 0;
    for (int route = 1; route <= n_route; route++) {
        if (demand_of_route[route] == 0) continue;
        res_route++;
        if (demand_of_route[route] <= bus_types[1].capacity) {
            res_1++;
            continue;
        }
        if (demand_of_route[route] <= bus_types[2].capacity) {
            res_2++;
            continue;
        }
        if (demand_of_route[route] <= bus_types[3].capacity) {
            res_3++;
            continue;
        }
    }
    // runtime
    double runtime = ((double) (clock() - start_running) / CLOCKS_PER_SEC);
    fileOut.open(outputDictionary + instance_name);
    fileOut << instance_name << "\t" << n_node << "\t" << res_route << "\t" << res_1 << "\t" << res_2 << "\t" << res_3
            << "\t"
            << ((double) n_negative / total_demand) * 100 << "\t" << total_cost << "\t" << runtime << "\t" << endl;
    for (int i = 0; i < n_giant_tour; i++)
        fileOut << giant_tour[i] << " ";
    fileOut.close();
}

inline void Sol::outFile(double gap) {
    // routes
    int res_route = 0, res_1 = 0, res_2 = 0, res_3 = 0;
    for (int route = 1; route <= n_route; route++) {
        if (demand_of_route[route] == 0) continue;
        res_route++;
        if (demand_of_route[route] <= bus_types[1].capacity) {
            res_1++;
            continue;
        }
        if (demand_of_route[route] <= bus_types[2].capacity) {
            res_2++;
            continue;
        }
        if (demand_of_route[route] <= bus_types[3].capacity) {
            res_3++;
            continue;
        }
    }
    // runtime
    double runtime = ((double) (clock() - start_running) / CLOCKS_PER_SEC);
    fileOut.open(outputDictionary + instance_name);
    fileOut << instance_name << "\t" << n_node << "\t" << res_route << "\t" << res_1 << "\t" << res_2 << "\t" << res_3
            << "\t"
            << ((double) n_negative / total_demand) * 100 << "\t" << total_cost << "\t" << runtime << "\t" << gap
            << endl;
    for (int i = 0; i < n_giant_tour; i++)
        fileOut << giant_tour[i] << " ";
    fileOut.close();
}

inline void Sol::printf() {
    processGiantToRoutes();
    check();
    out(total_cost, int(round(100 * double(n_negative) / total_demand)));
    printArray0N(giant_tour, n_giant_tour);
}
