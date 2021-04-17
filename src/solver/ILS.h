/**
 * @Created by Manh Vu Duy (manhvdm@gmail.com) on 3/12/2021.
 * @Please contact before using this source code
 */
//

#ifndef BUS_ILS_H
#define BUS_ILS_H

void perturb(Sol &potential_sol);

#endif //BUS_ILS_H
#pragma once

void ILS(int i_max, int i_ils) {
    int nPerturb;
    Sol::start_running = clock();
    Sol currentSol;
    Sol newSol;
    bestSol.total_cost = oo;
    int totalILS = i_ils * n_node;
    int iter_ils;
    int last_i = i_max;
    while (i_max--) {
        currentSol.greedy();
        currentSol.improve();
        iter_ils = 0;
        while (iter_ils < totalILS) {
            iter_ils++;
            newSol.copyOrderNode(currentSol);
            //perturb
            nPerturb = random(1, 3);
            for (int t = 1; t <= nPerturb; t++) perturb(newSol);
            // improve
            newSol.improve();
            if (newSol.total_cost <  currentSol.total_cost) {
                newSol.improve();
                iter_ils = 0;
                currentSol.copy(newSol);
            }
        }
        if(currentSol.total_cost < bestSol.total_cost) {
            bestSol.copy(currentSol);
            i_max += last_i - i_max;
            last_i = i_max;
        }
    }
    bestSol.processGiantToRoutes();
    bestSol.outFile();
    bestSol.check();
    out(bestSol.total_cost, int(round(100 * double(bestSol.n_negative) / total_demand)));
    printArray0N(bestSol.giant_tour, bestSol.n_giant_tour);
    bestSol.statistic();
//    cache_sol.copy(bestSol);
}

void perturb(Sol &potential_sol) {
    int u, v;
    do {
        u = rand() % n_node + 1;
        v = rand() % n_node + 1;
    } while (u == v);
    swap(potential_sol.order_node[u], potential_sol.order_node[v]);
}
