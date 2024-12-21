#include <iostream>
#include "hipnuc_imu.hpp"
#include "Rate.hpp"
#include "debug_tools.hpp"

using namespace std;

int main() {
    hipnuc_imu imu;
    debug_tools::Timer t;
    Rate loop_rate(100);
    int count = 0;
    while (1) {
        imu.read_imu();
        cout << "/******* loop " << count++ << " ********/" << endl;
        loop_rate.sleep();
    }
    return 0;
}