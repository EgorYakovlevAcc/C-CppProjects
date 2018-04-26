#include <vector>
#include <iostream>
#include "mingw.mutex.h"
#include "mingw.thread.h"
#include "AirportLine.h"
#include <string>

std::vector<int> AirbusUP;
std::vector<int> AirbusDown;
std::mutex m;
AirportLine l1 = AirportLine();
AirportLine l2 = AirportLine();

void thread_func(std::string label) {
        if (!l1.flag) {
            if (!l2.flag) {
                std::this_thread::sleep_for(std::chrono::milliseconds(3000));
                l2.flag = true;
                l1.flag = true;
                std::cout << "Lines 1 and 2 are free" << std::endl;
            } else {
                std::cout << label << std::endl;
                l2.flag = false;
                std::cout << "Line 2 is occuped" << std::endl;
            }
        } else {
            std::cout << label << std::endl;
            l1.flag = false;
            std::cout << "Line 1 is occuped" << std::endl;
        }
}

void AirbusRequestHandlerUP() {
        std::lock_guard<std::mutex> locked(m);
        for (int i: AirbusUP) {
            thread_func("Airbus UP");
            AirbusUP.erase(AirbusUP.begin());
    }
}

void AirbusRequestHandlerDOWN() {
        std::lock_guard<std::mutex> locked(m);
        for (int i: AirbusDown) {
            thread_func("Airbus--DOWN");
            AirbusUP.push_back(i);
            AirbusDown.erase(AirbusDown.begin());
        }
}

int main()
{

    int i = 0;
    while (i < 5) {
        AirbusUP.push_back(i);
        AirbusDown.push_back(i);
        i++;
    }

    while (!AirbusUP.empty()) {
        std::thread th1(AirbusRequestHandlerUP);
        AirbusRequestHandlerDOWN();

        th1.join();
    }
}