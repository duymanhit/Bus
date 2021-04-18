/**
 * @Created by Manh Vu Duy (manhvdm@gmail.com) on 4/10/2021.
 * @Please contact before using this source code
 */
//

#ifndef BUS_GRASP_H
#define BUS_GRASP_H

#endif //BUS_GRASP_H

void GRASP(int nGrasp) {
    Sol::start_running = clock();
    bestSol.total_cost = oo;
    int iter_grasp = 0;
    int totalGrasp = nGrasp * n_node;
    Sol greedySol;
    Solution currentSol;
    while (iter_grasp < totalGrasp) {
        iter_grasp++;
        greedySol.greedy();
        currentSol.copyOrderNode(greedySol.order_node);
        currentSol.processFormOrderNode();

        if (currentSol.totalCost < bestSol.total_cost) {
            iter_grasp = 0;
            out(currentSol.totalCost, bestSol.total_cost);
            //out(bestSol.total_cost, currentSol.total_cost);
            currentSol.copyFor(bestSol);
        }
    }
    bestSol.processGiantToRoutes();
    bestSol.outFile();
    bestSol.check();
    out(bestSol.total_cost, int(round(100 * double(bestSol.n_negative) / total_demand)));
    printArray0N(bestSol.giant_tour, bestSol.n_giant_tour);
    bestSol.statistic();
}
