#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>

vector<int32> v;
mutex m;



void Push()
{
	for (int32 i = 0; i < 1'0000; i++)
	{
		//RAII 패턴(생성자에서 lock 소멸자에서 unlock)
		//std::lock_guard<std::mutex> lockGuard(m);//생성하면 잠기고 소멸시 해제
		std::unique_lock<std::mutex> uniqueLock(m, std::defer_lock); //만들자마자 잠그는게 아니라 실제로 lock시 잠금, 락가드보다 조금 무거움

		uniqueLock.lock();
		//m.lock();

		v.push_back(i);

		//m.unlock();
	}
}

int main()
{
	std::thread t1(Push);
	std::thread t2(Push);

	t1.join();
	t2.join();

	cout << v.size()<< endl;
}