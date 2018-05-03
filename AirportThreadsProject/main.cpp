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

void thread_func(std::string label) { // Проверяем занята полоса или не занята
    if (!l1.flag) {
        if (!l2.flag) {
            std::this_thread::sleep_for(std::chrono::milliseconds(3000)); //блокируем на 3000 ms 2 полосы
            l2.flag = true;
            l1.flag = true;
            std::cout << "Lines 1 and 2 are free" << std::endl;
        } else { //полоса свободна => можно посадить самолёт / можно взлететь самолёту
            std::cout << label << std::endl;
            l2.flag = false;
            std::cout << "Line 2 is occuped" << std::endl;
        }
    } else { //полоса свободна => можно посадить самолёт / можно взлететь самолёту
        std::cout << label << std::endl;
        l1.flag = false;
        std::cout << "Line 1 is occuped" << std::endl;
    }
}

void AirbusRequestHandlerUP() { // вектор самолётов на взлет
    std::lock_guard<std::mutex> locked(m); //блокируем доступ к общим переменным
    if (!AirbusUP.empty()) {
        thread_func("Airbus UP");
        AirbusUP.erase(AirbusUP.begin());
    }
}

void AirbusRequestHandlerDOWN() { //вектор самолётов на посадку
    std::lock_guard<std::mutex> locked(m);
    if (!AirbusDown.empty()) {
        thread_func("Airbus--DOWN");
        AirbusDown.erase(AirbusDown.begin());
    }
}

int main()
{

    int i = 0;
    while (i < 7) {  // заполняем массивы (самолеты-взлёт/посадка) значениями
        AirbusUP.push_back(i);
        i++;
    }
    i = 0;
    while (i < 5) {
        AirbusDown.push_back(i);
        i++;
    }

    while (!AirbusUP.empty()) { //Если массив не пустой - входим в цикл
        std::thread th1(AirbusRequestHandlerUP);  // функция обработки самолётов на взлет
        AirbusRequestHandlerDOWN();  // функция обработки самолётов на посадку

        th1.join();
    }
}
