/**
 * @Created by Manh Vu Duy (manhvdm@gmail.com) on 3/12/2021.
 * @Please contact before using this source code
 */

/**
 * @TODO this method always reduces the number of buses
 */

#ifndef BUS_Solution_H
#define BUS_Solution_H

#endif //BUS_Solution_H

struct Solution {
    int nGiantTour;
    int orderNode[maxn];
    int giantTour[maxn];
    static clock_t startRunning;
    static int routeKey;
    static int currentColor;
    static int **lastExtraRoutes;
    static int *lastIntraRoutes;
    static int *timeOfNode;
    static int **routes;
    static int **demandOfRoutes;
    static int **timeOfRoutes;
    static int **reverseTimeOfRoutes;
    static bool *isNegativeNode;
    static int *routeDemand;
    static int *routeTime;
    static int *routeCost;
    static int *routeNegative;
    static int *routeLength;
    static int *cacheRoute;
    static bool *isServed;
    int nRoute;
    int totalCost;
    int nNegative;

    Solution();

    ~Solution();

    static void init();

    static void destroy();

    void split();

    void preprocessRoutes();

    void preprocessRoute(int);

    void convertRoutesToOrder();

    void convertRoutesToGiant();

    bool check();

    static int getNegativeStudents(const int &route, const int &start, const int &end, const int &time);

    static int getNegativeStudentsWithStartTime(const int &route, const int &tend, const int &start, const int &end, int time);

    void cloneToCache(const int &r);

    void pasteFormCache(const int &r);

    inline static int getTimeSubTour(const int *timeOfRoute, const int &start, const int &end);

    inline static int getReverseTimeSubTour(const int *reverseTimeOfRoute, const int &start, const int &end);

    inline static int getDemandSubTour(const int *demandOfRoute, const int &start, const int &end);


    inline static int
    getDiffTimeSwap(const int &r_1, const int &start_1, const int &end_1, const int &r_2, const int &tend, const int &start_2,
                    const int &end_2);

    //int getDiffTimeSwapInRoute(int& start_1, int& end_1, int& start_2, int& end_2);
    inline static int
    getNewDemandSwap(const int &r_1, const int &start_1, const int &end_1, const int &r_2, const int &start_2,
                     const int &end_2);

    int getCostRoute(int &, const int &);

    inline bool localSearchExtraRoutes();

    void localSearch();

    void processFormOrderNode();

    void copy(Solution another_Solution);

    void improve();

    void copyOrderNode(Solution &anotherSolution);

    void copyOrderNode(int *order_node);

    void copyFor(Sol &another_sol);

    void initColor();

    void resetRouteColor(const int &key);

    bool localSearchIntraRoutes();

    inline int getNegativeStudentForm(const int &start, int time);
};

clock_t Solution::startRunning;
int *Solution::timeOfNode;
int Solution::routeKey;
int Solution::currentColor;
int **Solution::lastExtraRoutes;
int *Solution::lastIntraRoutes;
int **Solution::routes;
int **Solution::demandOfRoutes;
int **Solution::timeOfRoutes;
int **Solution::reverseTimeOfRoutes;
bool *Solution::isNegativeNode;
int *Solution::routeDemand;
int *Solution::routeTime;
int *Solution::routeCost;
int *Solution::routeNegative;
int *Solution::routeLength;
int *Solution::cacheRoute;
bool *Solution::isServed;

inline Solution::Solution() {
    totalCost = 0;
}

inline Solution::~Solution() {
    //delete giantTour;
    //delete orderNode;
}

void Solution::init() {
    destroy();
    Solution::routeKey = max_nodes_per_route * 1.5;
    initArray(Solution::timeOfNode, n_node * 3, oo);
    initArray2D(Solution::routes, n_node, max_nodes_per_route * 2, 0);
    for (int route = 0; route < n_node; route++) {
        routes[route][routeKey] = route;
    }

    initArray2D(Solution::lastExtraRoutes, n_node, n_node, 0);
    initArray(Solution::lastIntraRoutes, n_node, 0);

    initArray2D(Solution::demandOfRoutes, n_node, max_nodes_per_route * 2, 0);
    initArray2D(Solution::timeOfRoutes, n_node, max_nodes_per_route * 2, 0);
    initArray2D(Solution::reverseTimeOfRoutes, n_node, max_nodes_per_route * 2, 0);
    initArray(Solution::routeCost, n_node, 0);
    initArray(Solution::routeNegative, n_node, 0);
    initArray(Solution::routeDemand, n_node, 0);
    initArray(Solution::routeTime, n_node, 0);
    initArray(Solution::routeLength, n_node, 0);
    initArray(Solution::isNegativeNode, n_node * 3, false);
    initArray(string_concat_next, n_node * 3);
    initArray(string_concat_cache, n_node * 3);
    initArray(Solution::cacheRoute, n_node * 3);
    initArray(Solution::isServed, n_node * 3, false);
}

void Solution::destroy() {
    /** TODO
     *
     */
}

void Solution::split() {
    ///<summary>
    /// f_split[i][k] is result of splitting to i with k negative locations
    ///f_split[i][nextEnd] =
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
                    time += travel_time[orderNode[end]][start];
                    if (!checkTimeNode(orderNode[end], time)) break;
                    demand += nodes[orderNode[end]].demand;
                    start = orderNode[end];
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
    totalCost = f_split[n_node][current_n_negative];
    nNegative = current_n_negative;

    /** TODO
     * extract routes
     */
    nGiantTour = 0;
    giantTour[0] = 0;
    nRoute = 0;
    int current_end = n_node;
    int nextEnd;
    while (current_end) {
        routeLength[nRoute] = 0;
        routes[nRoute][0] = 0;
        nextEnd = pre_split[current_end][current_n_negative].fs;
        for (i = nextEnd + 1; i <= current_end; i++) {
            routes[nRoute][++routeLength[nRoute]] = orderNode[i];
        }
        routes[nRoute][++routeLength[nRoute]] = 0;
        current_n_negative = pre_split[current_end][current_n_negative].sc;
        current_end = nextEnd;
        nRoute++;
    }
    preprocessRoutes();
    check();
    //convertRoutesToGiant();
    //printArray0N(giantTour, nGiantTour);
    //check();
    //update();
}

void Solution::preprocessRoutes() {
    totalCost = 0;
    nNegative = 0;
    for (int route = 0; route < nRoute; route++) {
        routeCost[route] = 0;
        routeNegative[route] = 0;
        preprocessRoute(route);
    }
    for (int route = 0; route < nRoute; route++) {
        if (routeLength[route] <= 1) {
            // empty route
            swap2Array(routes[route], routes[nRoute - 1], max_nodes_per_route * 2);
            nRoute--;
        }
    }
}

void Solution::preprocessRoute(int r) {
    /**
     * routeLength *
     * demandOfRoutes
     * timeOfRoutes
     * timeOfNode
     * reverseTimeOfRoutes
     * routeCost
     * isNegativeNode
     */
    totalCost -= routeCost[r];
    nNegative -= routeNegative[r];
    routeNegative[r] = 0;
    int *route = routes[r];
    int *demandOfRoute = demandOfRoutes[r];
    int *timeOfRoute = timeOfRoutes[r];
    int *reverseTimeOfRoute = reverseTimeOfRoutes[r];
    int length;
    int node;
    demandOfRoute[0] = 0;
    timeOfRoute[0] = 0;
    for (length = 1; route[length] != 0; length++) {
        node = route[length];
        demandOfRoute[length] = demandOfRoute[length - 1] + nodes[node].demand;
        timeOfRoute[length] = timeOfRoute[length - 1] + travel_time[node][route[length - 1]];
        isNegativeNode[node] = checkNegative(node, timeOfRoute[length]);
        routeNegative[r] += isNegativeNode[node] * nodes[node].demand;
    }
    // reverseTime
    reverseTimeOfRoute[length] = 0;
    for (int i = length - 1; i >= 0; i--) {
        reverseTimeOfRoute[i] = reverseTimeOfRoute[i + 1] + travel_time[route[i]][route[i + 1]];
    }
    routeTime[r] = timeOfRoute[length] = timeOfRoute[length - 1];
    routeDemand[r] = demandOfRoute[length] = demandOfRoute[length - 1];
    routeLength[r] = length;
    routeCost[r] = getCostRoute(demandOfRoute[length], timeOfRoute[length]);
    totalCost += routeCost[r];
    nNegative += routeNegative[r];
    resetRouteColor(route[routeKey]);

}

inline void Solution::convertRoutesToOrder() {
    int n = 0;
    orderNode[0] = 0;
    for (int r = 0; r < nRoute; r++) {
        for (int i = 1; i < routeLength[r]; i++) {
            orderNode[++n] = routes[r][i];
        }
    }
}

inline void Solution::convertRoutesToGiant() {
    nGiantTour = 0;
    giantTour[0] = 0;
    for (int r = 0; r < nRoute; r++) {
        for (int i = 1; i < routeLength[r]; i++) {
            giantTour[++nGiantTour] = routes[r][i];
        }
        giantTour[++nGiantTour] = 0;
    }
    giantTour[++nGiantTour] = 0;
}

int Solution::getNegativeStudents(const int &route, const int &start, const int &end, const int &time) {
    int result = 0;
    int node, newTime;
    for (int i = start; i <= end; i++) {
        node = routes[route][i];
        newTime = timeOfRoutes[route][i] + time;
        if (!checkTimeNode(node, newTime)) return oo;
        result += (checkNegative(node, newTime) - isNegativeNode[node]) * nodes[node].demand;
    }
    return result;
}

inline int Solution::getNegativeStudentsWithStartTime(const int &route, const int &tend, const int &start, const int &end, int time) {
    int result = 0,
            node,
            endLoop = end + tend;
    for (int i = start; i != endLoop; i += tend) {
        node = routes[route][i];
        if (!checkTimeNode(node, time)) return oo;
        result += (checkNegative(node, time) - isNegativeNode[node]) * nodes[node].demand;
        time += travel_time[routes[route][i + tend]][node];
    }
    return result;
}

inline int Solution::getNegativeStudentForm(const int &start, int time) {
    int result = 0, node;
    for (int i = start; true; i++) {
        node = cacheRoute[i];
        if(i != 0 && node == 0) break;
        if (!checkTimeNode(node, time)) return oo;
        result += (checkNegative(node, time) - isNegativeNode[node]) * nodes[node].demand;
        time += travel_time[cacheRoute[i + 1]][node];
    }
    return result;
}

inline void Solution::cloneToCache(const int &r) {
    for (int i = 0; i <= routeLength[r]; i++) cacheRoute[i] = routes[r][i];
}

inline void Solution::pasteFormCache(const int &r) {
    for (int i = 0; i <= routeLength[r]; i++) routes[r][i] = cacheRoute[i];
}

inline int Solution::getTimeSubTour(const int *timeOfRoute, const int &start, const int &end) {
    if (start > end) return 0;
    return timeOfRoute[end] - timeOfRoute[start];
}


inline int Solution::getReverseTimeSubTour(const int *reverseTimeOfRoute, const int &start, const int &end) {
    return reverseTimeOfRoute[end] - reverseTimeOfRoute[start];
}

inline int Solution::getDemandSubTour(const int *demandOfRoute, const int &start, const int &end) {
    return demandOfRoute[end] - demandOfRoute[start - 1];
}


inline int
Solution::getDiffTimeSwap(const int &r_1, const int &start_1, const int &end_1, const int &r_2, const int &tend, const int &start_2,
                          const int &end_2) {
    int current_time, *route_1 = routes[r_1], *route_2 = routes[r_2];
    if (start_1 <= end_1) {
        current_time = travel_time[route_1[start_1]][route_1[start_1 - 1]] +
                       travel_time[route_1[end_1 + 1]][route_1[end_1]]
                       + getTimeSubTour(timeOfRoutes[r_1], start_1, end_1);
    } else {
        current_time = travel_time[route_1[start_1]][route_1[end_1]];
    }
    if (tend >= 0) {
        if (start_2 <= end_2) {
            return travel_time[route_2[start_2]][route_1[start_1 - 1]] +
                   travel_time[route_1[end_1 + 1]][route_2[end_2]]
                   + getTimeSubTour(timeOfRoutes[r_2], start_2, end_2)
                   - current_time;
        }
        return travel_time[route_1[end_1 + 1]][route_1[start_1 - 1]]
               - current_time;
    }
    // reverse route_2
    return travel_time[route_2[start_2]][route_1[start_1 - 1]] +
           travel_time[route_1[end_1 + 1]][route_2[end_2]]
           + getReverseTimeSubTour(reverseTimeOfRoutes[r_2], start_2, end_2)
           - current_time;

    //out(travel_time[giantTour[end_1 + 1]][giantTour[start_1 - 1]], current_time);
}

inline int
Solution::getNewDemandSwap(const int &r_1, const int &start_1, const int &end_1, const int &r_2, const int &start_2,
                           const int &end_2) {
    return routeDemand[r_1] + getDemandSubTour(demandOfRoutes[r_2], start_2, end_2) -
           getDemandSubTour(demandOfRoutes[r_1], start_1, end_1);
}

inline int Solution::getCostRoute(int &demand, const int &riding_time) {
    return fixed_cost_for_demand[demand] + riding_time * travel_cost_for_demand[demand];
}

inline bool Solution::localSearchExtraRoutes() {
    bool checkImprove = true;
    bool result = false;
    int r_1, r_2, start_1, end_1, start_2, end_2, newDemand_1, newDemand_2, newTime_1, newTime_2, negative_1, negative_2, diffTime_1, diffTime_2,
            newReverseTime_1, newReverseTime_2, diffReverseTime_1, diffReverseTime_2, reverseNegative_1, reverseNegative_2, newCost, newNegative, oldNegative;
    while (checkImprove) {
        checkImprove = false;
        for (r_1 = 0; r_1 < nRoute; r_1++) {
            for (r_2 = r_1 + 1; r_2 < nRoute; r_2++)
                if (lastExtraRoutes[routes[r_1][routeKey]][routes[r_2][routeKey]] != currentColor) {
                    lastExtraRoutes[routes[r_1][routeKey]][routes[r_2][routeKey]] = currentColor;
                    // check local search r_1 and r_2
                    if (routeLength[r_1] <= 1 || routeLength[r_2] <= 1) continue;
                    for (start_1 = 1; start_1 <= routeLength[r_1]; start_1++)
                        for (end_1 = start_1 - 1; end_1 < routeLength[r_1]; end_1++)
                            for (start_2 = 1; start_2 <= routeLength[r_2]; start_2++)
                                for (end_2 = start_2 - 1; true; end_2++) {
                                    if (start_1 > routeLength[r_1] || end_1 >= routeLength[r_1] ||
                                        start_2 > routeLength[r_2] || end_2 >= routeLength[r_2])
                                        break;
                                    if (start_1 > end_1 && start_2 > end_2) continue;
                                    // length0
                                    if (routeLength[r_1] - (end_1 - start_1 + 1) + (end_2 - start_2 + 1) - 1 > max_nodes_per_route)
                                        continue;
                                    if (routeLength[r_2] + (end_1 - start_1 + 1) - (end_2 - start_2 + 1) - 1 > max_nodes_per_route)
                                        continue;
                                    newDemand_1 = getNewDemandSwap(r_1, start_1, end_1, r_2, start_2, end_2);
                                    newDemand_2 = getNewDemandSwap(r_2, start_2, end_2, r_1, start_1, end_1);
                                    if (fixed_cost_for_demand[newDemand_1] + fixed_cost_for_demand[newDemand_2] >
                                        fixed_cost_for_demand[routeDemand[r_1]] + fixed_cost_for_demand[routeDemand[r_2]])
                                        continue;
                                    negative_1 = negative_2 = reverseNegative_1 = reverseNegative_2 = -oo;
                                    diffTime_1 = getDiffTimeSwap(r_1, start_1, end_1, r_2, 1, start_2, end_2);
                                    diffTime_2 = getDiffTimeSwap(r_2, start_2, end_2, r_1, 1, start_1, end_1);
                                    newTime_1 = routeTime[r_1] + diffTime_1;
                                    newTime_2 = routeTime[r_2] + diffTime_2;
                                    if (newTime_1 > max_time_per_route)
                                        goto reverse_2;
                                    if (newTime_2 > max_time_per_route)
                                        goto reverse_2;
                                    // dont reverse
                                    if (routeCost[r_1] + routeCost[r_2] <= getCostRoute(newDemand_1, newTime_1) + getCostRoute(newDemand_2, newTime_2))
                                        goto reverse_2;
                                    negative_1 = getNegativeStudents(r_1, end_1 + 1, routeLength[r_1] - 1, diffTime_1) +
                                                 getNegativeStudentsWithStartTime(r_2, 1, start_2, end_2, timeOfRoutes[r_1][start_1 - 1] + travel_time[routes[r_2][start_2]][routes[r_1][start_1 - 1]]);
                                    negative_2 = getNegativeStudents(r_2, end_2 + 1, routeLength[r_2] - 1, diffTime_2) +
                                                 getNegativeStudentsWithStartTime(r_1, 1, start_1, end_1, timeOfRoutes[r_2][start_2 - 1] + travel_time[routes[r_1][start_1]][routes[r_2][start_2 - 1]]);
                                    if (nNegative + negative_1 + negative_2 > max_negative_students)
                                        goto reverse_2;
                                    newCost = totalCost - (routeCost[r_1] + routeCost[r_2])
                                              + (getCostRoute(newDemand_1, newTime_1) +
                                                 getCostRoute(newDemand_2, newTime_2));
                                    newNegative = nNegative + negative_1 + negative_2;
                                    swap2subArray(routes[r_1], 1, start_1, end_1, routes[r_2], 1, start_2, end_2);
                                    goto improve;
                                    reverse_2:
                                    {
                                        if (end_1 == 0 || start_1 >= end_1)
                                            goto reverse_1;
                                        diffReverseTime_2 = getDiffTimeSwap(r_2, start_2, end_2, r_1, -1, end_1, start_1);
                                        newReverseTime_2 = routeTime[r_2] + diffReverseTime_2;
                                        if (newTime_1 > max_time_per_route || newReverseTime_2 > max_time_per_route)
                                            goto reverse_1;
                                        if (routeCost[r_1] + routeCost[r_2] <= getCostRoute(newDemand_1, newTime_1) + getCostRoute(newDemand_2, newReverseTime_2))
                                            goto reverse_1;
                                        reverseNegative_2 = getNegativeStudents(r_2, end_2 + 1, routeLength[r_2] - 1, diffReverseTime_2) +
                                                            getNegativeStudentsWithStartTime(r_1, -1, end_1, start_1,
                                                                                             timeOfRoutes[r_2][start_2 - 1] + travel_time[routes[r_1][end_1]][routes[r_2][start_2 - 1]]);
                                        if (negative_1 == -oo) {
                                            negative_1 = getNegativeStudents(r_1, end_1 + 1, routeLength[r_1] - 1, diffTime_1) +
                                                         getNegativeStudentsWithStartTime(r_2, 1, start_2, end_2,
                                                                                          timeOfRoutes[r_1][start_1 - 1] + travel_time[routes[r_2][start_2]][routes[r_1][start_1 - 1]]);
                                        }
                                        if (nNegative + negative_1 + reverseNegative_2 > max_negative_students)
                                            goto reverse_1;
                                        newCost = totalCost - (routeCost[r_1] + routeCost[r_2])
                                                  + (getCostRoute(newDemand_1, newTime_1) +
                                                     getCostRoute(newDemand_2, newReverseTime_2));
                                        newNegative = nNegative + negative_1 + reverseNegative_2;
                                        swap2subArray(routes[r_1], -1, start_1, end_1, routes[r_2], 1, start_2, end_2);
                                        goto improve;
                                    };

                                    reverse_1:
                                    {
                                        if (end_2 == 0 || start_2 >= end_2)
                                            continue;
                                        diffReverseTime_1 = getDiffTimeSwap(r_1, start_1, end_1, r_2, -1, end_2, start_2);
                                        newReverseTime_1 = routeTime[r_1] + diffReverseTime_1;
                                        if (newReverseTime_1 > max_time_per_route || newTime_2 > max_time_per_route)
                                            goto reverse_both;
                                        if (routeCost[r_1] + routeCost[r_2] <= getCostRoute(newDemand_1, newReverseTime_1) + getCostRoute(newDemand_2, newTime_2))
                                            goto reverse_both;
                                        reverseNegative_1 = getNegativeStudents(r_1, end_1 + 1, routeLength[r_1] - 1, diffReverseTime_1) +
                                                            getNegativeStudentsWithStartTime(r_2, -1, end_2, start_2,
                                                                                             timeOfRoutes[r_1][start_1 - 1] + travel_time[routes[r_2][end_2]][routes[r_1][start_1 - 1]]);
                                        if (negative_2 == -oo) {
                                            negative_2 = getNegativeStudents(r_2, end_2 + 1, routeLength[r_2] - 1, diffTime_2) +
                                                         getNegativeStudentsWithStartTime(r_1, 1, start_1, end_1,
                                                                                          timeOfRoutes[r_2][start_2 - 1] + travel_time[routes[r_1][start_1]][routes[r_2][start_2 - 1]]);
                                        }
                                        if (nNegative + reverseNegative_1 + negative_2 > max_negative_students)
                                            goto reverse_both;
                                        newCost = totalCost - (routeCost[r_1] + routeCost[r_2])
                                                  + (getCostRoute(newDemand_1, newReverseTime_1) +
                                                     getCostRoute(newDemand_2, newTime_2));
                                        newNegative = nNegative + reverseNegative_1 + negative_2;

                                        swap2subArray(routes[r_1], 1, start_1, end_1, routes[r_2], -1, start_2, end_2);
                                        goto improve;
                                    };
                                    reverse_both:
                                    {
                                        if (end_1 == 0 || start_1 >= end_1)
                                            continue;
                                        if (newReverseTime_1 > max_time_per_route || newReverseTime_2 > max_time_per_route)
                                            continue;
                                        if (routeCost[r_1] + routeCost[r_2] <= getCostRoute(newDemand_1, newReverseTime_1) + getCostRoute(newDemand_2, newReverseTime_2))
                                            continue;
                                        if (reverseNegative_1 == -oo) {
                                            reverseNegative_1 = getNegativeStudents(r_1, end_1 + 1, routeLength[r_1] - 1, diffReverseTime_1) +
                                                                getNegativeStudentsWithStartTime(r_2, -1, end_2, start_2,
                                                                                                 timeOfRoutes[r_1][start_1 - 1] + travel_time[routes[r_2][end_2]][routes[r_1][start_1 - 1]]);
                                        }
                                        if (reverseNegative_2 == -oo) {
                                            reverseNegative_2 = getNegativeStudents(r_2, end_2 + 1, routeLength[r_2] - 1, diffReverseTime_2) +
                                                                getNegativeStudentsWithStartTime(r_1, -1, end_1, start_1,
                                                                                                 timeOfRoutes[r_2][start_2 - 1] + travel_time[routes[r_1][end_1]][routes[r_2][start_2 - 1]]);
                                        }
                                        if (nNegative + reverseNegative_1 + reverseNegative_2 > max_negative_students)
                                            continue;
                                        newCost = totalCost - (routeCost[r_1] + routeCost[r_2])
                                                  + (getCostRoute(newDemand_1, newReverseTime_1) +
                                                     getCostRoute(newDemand_2, newReverseTime_2));
                                        newNegative = nNegative + reverseNegative_1 + reverseNegative_2;

                                        swap2subArray(routes[r_1], -1, start_1, end_1, routes[r_2], -1, start_2, end_2);
                                    };
                                    improve:
                                    {
                                        checkImprove = true;
                                        int oldCost = totalCost;
                                        oldNegative = nNegative;
                                        preprocessRoute(r_1);
                                        preprocessRoute(r_2);
                                        if (oldNegative > nNegative) {
                                            currentColor++;
                                        }
                                        check();
                                        //cout <<"***";
                                        if (oldCost <= totalCost || newCost != totalCost || newNegative != nNegative) {
                                            cout << "error";
                                            out(newCost, totalCost);
                                            out(newNegative, nNegative);
                                            while (true);
                                        }
                                        //printArray0N(giantTour, nGiantTour);
                                    };
                                }
                    if (checkImprove) {
                        result = true;
                    }
                }
        }
    }
    return result;
}

inline bool Solution::localSearchIntraRoutes() {
    bool check_improve = true;
    bool result = false;
    int r, start_1, end_1, start_2, end_2, diffTime_1, diffTime_2, diffReverseTime_1, diffReverseTime_2, newCost, negative, newNegative, oldNegative;
    while (check_improve) {
        check_improve = false;
        for (r = 0; r < nRoute; r++)
            if (lastIntraRoutes[routes[r][routeKey]] != currentColor) {
                lastIntraRoutes[routes[r][routeKey]] = currentColor;
                for (start_1 = 1; start_1 <= routeLength[r]; start_1++)
                    for (end_1 = start_1 - 1; end_1 < routeLength[r]; end_1++)
                        for (start_2 = start_1 + 1; start_2 <= routeLength[r]; start_2++)
                            for (end_2 = start_2 - 1; end_2 < routeLength[r]; end_2++) {
                                if (!checkSwapSubArray(start_1, end_1, start_2, end_2)) continue;
                                diffTime_1 = getDiffTimeSwap(r, start_1, end_1, r, 1, start_2, end_2);
                                diffTime_2 = getDiffTimeSwap(r, start_2, end_2, r, 1, start_1, end_1);
                                if (diffTime_1 + diffTime_2 >= 0) continue;
                                newCost = totalCost + (diffTime_1 + diffTime_2) * travel_cost_for_demand[demandOfRoutes[r][routeLength[r]]];
                                // n = end_route[route_1] - start_route[route_1];
                                cloneToCache(r);
                                swapSubArray(cacheRoute, routeLength[r], start_1, end_1, start_2, end_2);
                                negative = getNegativeStudentForm(start_1 - 1, timeOfRoutes[r][start_1 - 1]);
                                if (nNegative + negative > max_negative_students) {
                                    continue;
                                }
                                newNegative = nNegative + negative;
                                check_improve = true;
                                pasteFormCache(r);
                                int oldCost = totalCost;
                                oldNegative = nNegative;
                                preprocessRoute(r);
                                if (oldNegative > nNegative) {
                                    lastIntraRoutes[routes[r][routeKey]] = ++currentColor;
                                }
                                check();
                                //cout <<"***";
                                if (oldCost <= totalCost || newCost != totalCost || newNegative != nNegative) {
                                    cout << "error";
                                    out(newCost, totalCost);
                                    out(newNegative, nNegative);
                                    while (true);
                                }
                            }
            }
        if (check_improve) {
            result = true;
        }
    }
    return result;
}

inline void Solution::processFormOrderNode() {
    initColor();
    split();
    localSearchExtraRoutes();
    localSearchIntraRoutes();
    convertRoutesToGiant();
    convertRoutesToOrder();
}


inline void Solution::improve() {
    int oldCost = INT_MAX;
    do {
        split();
        if (oldCost > totalCost) {
            oldCost = totalCost;
        } else {
            if (oldCost < totalCost) {
                cout << "ERROR";
                while (true);
            }
            break;
        }
        localSearch();
        if (oldCost > totalCost) {
            oldCost = totalCost;
        } else {
            if (oldCost < totalCost) {
                cout << "ERROR";
                while (true);
            }
            break;
        }
        convertRoutesToOrder();
    } while (true);
}

inline void Solution::copy(Solution another_Solution) {
    nGiantTour = another_Solution.nGiantTour;
    nNegative = another_Solution.nNegative;
    totalCost = another_Solution.totalCost;
    for (int i = 0; i <= nGiantTour; i++) giantTour[i] = another_Solution.giantTour[i];
    for (int i = 0; i <= n_node; i++) orderNode[i] = another_Solution.orderNode[i];
}

inline void Solution::copyOrderNode(Solution &anotherSolution) {
    for (int i = 0; i <= n_node; i++) orderNode[i] = anotherSolution.orderNode[i];
}

inline void Solution::copyOrderNode(int *order_node) {
    for (int i = 0; i <= n_node; i++) orderNode[i] = order_node[i];
}

inline void Solution::copyFor(Sol &targetSol) {
    targetSol.n_giant_tour = nGiantTour;
    targetSol.n_negative = nNegative;
    targetSol.total_cost = totalCost;
    for (int i = 0; i <= nGiantTour; i++) targetSol.giant_tour[i] = giantTour[i];
    for (int i = 0; i <= n_node; i++) targetSol.order_node[i] = orderNode[i];
}

bool Solution::check() {
    convertRoutesToGiant();
    Sol check;
    copyFor(check);
    return check.check();
}

void Solution::initColor() {
    for (int r_1 = 0; r_1 < n_node; r_1++) {
        for (int r_2 = 0; r_2 < n_node; r_2++) {
            lastExtraRoutes[r_1][r_2] = 0;
        }
        lastIntraRoutes[r_1] = 0;
    }
    currentColor = 1;
}

void Solution::resetRouteColor(const int &key) {
    for (int r_1 = 0; r_1 <= nRoute; r_1++) {
        lastExtraRoutes[key][r_1] = lastExtraRoutes[r_1][key] = 0;
    }
}
