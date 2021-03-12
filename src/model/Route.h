/**
 * @Created by Manh Vu Duy (manhvdm@gmail.com) on 3/12/2021.
 * @Please contact before using this source code
 */
//

#ifndef BUS_ROUTE_H
#define BUS_ROUTE_H

#endif //BUS_ROUTE_H
#pragma once
//struct Route {
//	int n_node;
//	int* order_node;
//	int max_negative;
//	int* cost;
//	int** route;
//	Route(int*, int);
//	void hamilton();
//};
//Route::Route(int* index_giant, int n) {
//	order_node = index_giant;
//	n_node = n;
//	max_negative = 0;
//	int min_demand = total_demand;
//	for (int i = 0; i < n_node; i++) {
//		min_demand = min(min_demand, nodes[order_node[i]].demand);
//		max_negative += nodes[order_node[i]].demand;
//	}
//	max_negative -= min_demand;
//}
//void Route::hamilton() {
//	int max_state = (1 << n_node) - 1;
//	for (int state = max_state; state >= 0; state--)
//		for (int last = 0; last < n_node; last++)
//			for (int negative = 0; negative <= max_negative; negative++) f[state][last][negative] = oo;
//	// init
//	for (int last = 0; last < n_node; last++) {
//		f[1 << last][last][0] = travel_time[order_node[last]][0];
//	}
//	// calculate
//	for (int state = 1; state < max_state; state++)
//		for (int last = 0; last < n_node; last++)
//			for (int negative = 0; negative <= max_negative; negative++) if (f[state][last][negative] != oo) {
//				for (int next = 0; next < n_node; next++) if (!(state & (1 << next))) {
//					int riding_time = f[state][last][negative] + travel_time[order_node[next]][order_node[last]];
//					if (!checkTimeNode(order_node[next], riding_time)) continue;
//					int new_state = state | (1 << next);
//					int new_negative = negative + getNegative(order_node[next], riding_time);
//					if (f[new_state][next][new_negative] > riding_time) {
//						f[new_state][next][new_negative] = riding_time;
//						pre[new_state][next][new_negative] = last;
//					}
//				}
//			}
//	//
//	initArray(cost, max_negative);
//	route = new int* [max_negative];
//	int d = 0;
//	for (int negative = 0; negative <= max_negative; negative++) {
//		int res_last = 0;
//		for (int last = 0; last < n_node; last++)
//			if (f[max_state][last][negative] < f[max_state][res_last][negative]) {
//				res_last = last;
//			}
//		cost[negative] = f[max_state][res_last][negative];
//		if (cost[negative] == oo) continue;
//		// find route
//		int n = n_node;
//		int current_state = max_state;
//		int current_negative = negative;
//		int pre_last = 0;
//		do {
//			route[negative][--n] = order_node[res_last];
//			pre_last = pre[current_state][res_last][current_negative];
//			current_negative -= getNegative(order_node[res_last], f[current_state][res_last][current_negative]);
//			current_state -= 1 << res_last;
//			res_last = pre_last;
//		} while (n);
//	}
//}
