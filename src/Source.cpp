///**********************************************
/// @Author: Duy Manh Vu
/// @Gmail: manhvdm@gmail.com
/// @Please contact before using the source code
/// 
///**********************************************

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

void testStringConcat();

#include "business/StringConcat.h"
#include "model/objects.h"
#include "config/Config.h"
#include "business/Function.h"
#include "model/Route.h"
#include "solver/Sol.h"
#include "solver/Mip.h"
#include "config/GlobalVariables.h"
#include "Input/Input.h"
#include "solver/ILS.h"
#include "input/VRP2Instance.h"

int main() {
    testStringConcat();
    ifstream name_file("../input/test.txt");
    srand(time(NULL));
    while (name_file >> instance_name) {
        string name = instance_name;
        check_instance = false;
        cout << instance_name << endl;
        for (double ratio = 0.1; ratio <= 1; ratio += 0.1) {
            if (ratio == 0.6) ratio = 1;
            max_negative_percentage_of_student = ratio;
            cout << ratio << " " << name << endl;
            //convertvrpinstance(instance_name);
            instance_name = "SBRPNI-current-" + name;
            getInput("../input/SBRPNI-" + name);
            instance_name = "SBRPNI-" + to_string(int(round(max_negative_percentage_of_student * 100))) + "-" + name;
            mip();
            //ILS(100, 500);
            check_instance = true;
            //instance_name = "mip-SBRPNI-" + to_string(int(round(max_negative_percentage_of_student * 100))) + "-" + name;
            //mip();
        }
    }
    system("pause");
}

void testStringConcat() {
//for (int start_1 = 1; start_1 <= 3; start_1++)
//	for (int end_1 = start_1 - 1; end_1 <= 3; end_1++)
//		for (int start_2 = start_1 + 1; start_2 <= 3; start_2++)
//			for (int end_2 = start_2 - 1; end_2 <= 3; end_2++) {
//				if (checkSwapSubArray(start_1, end_1, start_2, end_2)) {
//					out(start_1, end_1, start_2, end_2);
//				}
//			}

}
