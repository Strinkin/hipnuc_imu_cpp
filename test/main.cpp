#include <iostream>
#include "hipnuc_imu.hpp"

using namespace std;

int main() {
    hipnuc_imu imu;
    while (1)
    {
        imu.read_imu();
    }
    
    return 0;
}