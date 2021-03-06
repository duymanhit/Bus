/**
 * @Created by Manh Vu Duy (manhvdm@gmail.com) on 3/12/2021.
 * @Please contact before using this source code
 */
//

#include <ilcplex/ilocplex.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <string>
#include <iomanip>

using namespace std;
#define fs first
#define sc second
typedef pair<int, int> II;
typedef pair<II, int> III;
typedef pair<double, int> DI;
string inputDictionary = "../input/";
string outputDictionary = "../output/out-";
int seed = 100000007;
void testStringConcat();
void testPermutation();
#include "model/objects.h"
#include "config/Config.h"
#include "business/StringConcat.h"
#include "business/Function.h"
#include "model/Route.h"
#include "solver/Sol.h"
#include "solver/Solution.h"
#include "solver/Mip.h"
#include "config/GlobalVariables.h"
#include "Input/Input.h"
#include "solver/ILS.h"
#include "solver/GRASP.h"
#include "input/VRP2Instance.h"
#include "input/VRPD2instance.h"
int main() {
//    testStringConcat();
    cout << "BUS-NI" << endl;
    cin >> seed;
    int i_max, i_ils;
    cin >> i_max  >> i_ils;
    ifstream name_file("../input/test.txt");
    while (name_file >> instance_name) {
        string name = instance_name;
//        check_instance = false;
        cout << instance_name << endl;
        for (double ratio = 0.1; ratio <= 1; ratio += 0.1) {
            if (ratio > 0.5) ratio = 1;
            max_negative_percentage_of_student = ratio;
//            convertVRPDInstance(instance_name);
            srand(seed);
            instance_name = "SBRPNI-current-" + name;
            getInput2(inputDictionary + "SBRPNI-" + name);
//            getInput2(inputDictionary + "SBRPNI-" + name);

//            instance_name = "SBRPNI-" + to_string(int(round(max_negative_percentage_of_student * 100))) + "-" + name;
//            ILS(i_max, i_ils);

            // uncomment to run mip
            instance_name = "mip-SBRPNI-" + to_string(int(round(max_negative_percentage_of_student * 100))) + "-" + name;
            mip();
        }
    }
    system("pause");
}

void testStringConcat() {
    int *a, *b;
    int start_1, end_1, start_2, end_2, tend_1, tend_2;
    int n = 7;
    initArray(a, n* 2, 0);
    initArray(b, n*2, 0);
    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = i + n;
    }
    a[n-1] = b[n-1] = 0;
    while (cin >> tend_1 >>  start_1 >> end_1 >> tend_2 >>  start_2 >> end_2) {
        swap2subArray(a, tend_1, start_1, end_1, b, tend_2, start_2, end_2);
        printArray(a, n * 2);
        printArray(b, n * 2);
    }

//for (int start_1 = 1; start_1 <= 3; start_1++)
//	for (int end_1 = start_1 - 1; end_1 <= 3; end_1++)
//		for (int start_2 = start_1 + 1; start_2 <= 3; start_2++)
//			for (int end_2 = start_2 - 1; end_2 <= 3; end_2++) {
//				if (checkSwapSubArray(start_1, end_1, start_2, end_2)) {
//					out(start_1, end_1, start_2, end_2);
//				}
//			}

}
void testPermutation() {
    int myints[] = {1,2,3,5,6,7};

    std::sort (myints,myints+7);

    do {
        for(int i = 1; i < 7; i++) {
            myints[i];
        }
    } while ( std::next_permutation(myints,myints+7) );


}
