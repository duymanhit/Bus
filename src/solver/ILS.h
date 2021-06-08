/**
 * @Created by Manh Vu Duy (manhvdm@gmail.com) on 3/12/2021.
 * @Please contact before using this source code
 */
//

#ifndef BUS_ILS_H
#define BUS_ILS_H

void perturb(Solution &potential_sol);

#endif //BUS_ILS_H
#pragma once

void ILS(int i_max, int i_ils) {
    int nPerturb;
    Sol::start_running = clock();
    Sol greedySol;
    Solution currentSol;
    Solution newSol;
    bestSol.total_cost = oo;
    int totalILS = i_ils * n_node;
    int iter_ils;
    int lastTurn = 1;
    for (int iterStart = 1; iterStart <= i_max; iterStart++) {
        greedySol.greedy();
        currentSol.copyOrderNode(greedySol.order_node);
        currentSol.improve();
        iter_ils = 0;
        while (iter_ils < totalILS) {
            iter_ils++;
            newSol.copyOrderNode(currentSol.orderNode);
            //perturb
            nPerturb = random(1, 3);
            for (int t = 1; t <= nPerturb; t++) perturb(newSol);
            // improve
            newSol.processFormOrderNode();
            if (newSol.totalCost < currentSol.totalCost) {
                newSol.improve();
//                out(newSol.totalCost, currentSol.totalCost);
                iter_ils = 0;
                currentSol.copy(newSol);
            }
        }
        if(currentSol.totalCost < bestSol.total_cost) {
//            out(currentSol.totalCost, bestSol.total_cost);
            currentSol.copyFor(bestSol);
            lastTurn = iterStart;
        }
    }
    bestSol.processGiantToRoutes();
    bestSol.outFile(lastTurn);
    bestSol.check();
    out(bestSol.total_cost, int(round(100 * double(bestSol.n_negative) / total_demand)));
    printArray0N(bestSol.giant_tour, bestSol.n_giant_tour);
    bestSol.statistic();
//    cache_sol.copy(bestSol);
}

void perturb(Solution &potential_sol) {
    int u, v;
    do {
        u = rand() % n_node + 1;
        v = rand() % n_node + 1;
    } while (u == v);
    swap(potential_sol.orderNode[u], potential_sol.orderNode[v]);
}
