/**
 * @Created by Manh Vu Duy (manhvdm@gmail.com) on 3/12/2021.
 * @Please contact before using this source code
 */
//

#ifndef BUS_ILS_H
#define BUS_ILS_H

#endif //BUS_ILS_H
#pragma once
void ILS(int i_max, int i_ils) {
    Sol::start_running = clock();
    best_sol.total_cost = oo;
    //int max_sub_length = 2;
    Sol potential_sol;
    current_sol;
    potential_sol.greedy();
    current_sol.copy(potential_sol);
    int u, v;
    int last_i = i_max;
    while (i_max--) {
        int iter_ils = 0;
        while (iter_ils < i_ils) {
            //printArray0N(current_sol.order_node, n_node);
            current_sol.processFormOrderNode();
            //out(current_sol.total_cost, potential_sol.total_cost);
            if (current_sol.total_cost < potential_sol.total_cost) {
                potential_sol.copy(current_sol);
                //out(potential_sol.total_cost, potential_sol.n_negative);
                iter_ils = 0;
                //cout << "*";
            }

            //
            iter_ils++;
            //	current copy potential
            for (int i = 1; i <= n_node; i++) current_sol.order_node[i] = potential_sol.order_node[i];
            // perturb
            int n_operator = rand() % 2 + 2;
            while (n_operator--) {
                //int start_1 = rand() % n_node + 1;
                //int start_2 = rand() % n_node + 1;
                //int end_1 = min(n_node, start_1 + rand() % max_sub_length - 1);
                //int end_2 = min(n_node, start_2 + rand() % max_sub_length - 1);
                //if (!checkSwapSubArray(start_1, end_1, start_2, end_2)) {
                //	n_operator++;
                //	continue;
                //}
                //swapSubArray(current_sol.order_node, n_node + 1, start_1, end_1, start_2, end_2);
                u = rand() % n_node + 1;
                v = rand() % n_node + 1;
                if (u == v) {
                    n_operator++;
                    continue;
                }
                swap(current_sol.order_node[u], current_sol.order_node[v]);
            }
        }
        if (potential_sol.total_cost < best_sol.total_cost) {
            best_sol.copy(potential_sol);
            //out(best_sol.total_cost, int(round(100 * double(best_sol.n_negative) / total_demand)));
            i_max += last_i - i_max;
            last_i = i_max;
        }
        if (i_max) {
            potential_sol.greedyFormCurrentSol();
            current_sol.copy(potential_sol);

        }
    }
    if (check_instance && cache_sol.total_cost < best_sol.total_cost) {
        best_sol.copy(cache_sol);
        best_sol.processFormOrderNode();
    }
    best_sol.convertGiantToRoutes();
    best_sol.outFile();
    best_sol.check();
    out(best_sol.total_cost, int(round(100 * double(best_sol.n_negative)/total_demand)));
    printArray0N(best_sol.giant_tour, best_sol.n_giant_tour);
    best_sol.statistic();
    cache_sol.copy(best_sol);
}