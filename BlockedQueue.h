#ifndef BLOCKEDQUEUE_H_
#define BLOCKEDQUEUE_H_
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

template <class T>
class BlockedQueue {
    public:
        explicit BlockedQueue(int c):capacity(c){};
        void push(const T& t){
            std::unique_lock<std::mutex> lk(mtx);
            while(que.size() == capacity) notFull.wait(lk);
            que.push(t);
            notEmpty.notify_one();
        }

        T pop(){
            std::unique_lock<std::mutex> lk(mtx);
            while(que.size() == 0) notEmpty.wait(lk);
            T res = que.front();
            que.pop();
            notFull.notify_one();
            return res;
        }

    private:
        std::queue<T> que;
        int capacity;

        std::mutex mtx;
        std::condition_variable notFull;
        std::condition_variable notEmpty;
};
#endif
