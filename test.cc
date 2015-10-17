#include "BlockedQueue.h"
#include <thread>
#include <iostream>

BlockedQueue<int> bq(3);
void func1(){
    while(true){
        bq.push(1);    
        std::cout << "push 1" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
void func2(){
    while(true){
        int tmp = bq.pop();
        std::cout << "pop 1" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int main(){
    std::thread t1(func1);
    std::thread t2(func2);

    t1.join();
    t2.join();
    return 0;
}
