#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>
#include "ThreadManager.h"

// 소수 구하기
bool isPrime(int32 number)
{
	if (number <= 1)
		return false;
	if (number == 2 || number == 3)
		return true;

	for (int32 i = 2; i < number; i++)
	{
		if ((number % i) == 0)
			return false;
	}

	return true;
}

//[start - end]
int32 CountPrime(int32 start, int32 end)
{
	int32 count = 0;

	for (int32 number = start; number < end; number++)
	{
		if (isPrime(number))
			count++;
	}

	return count;
}

// 1과 자기 자신으로만 나뉘는 숫자가 소수

int main()
{
	const int32 MAX_NUMBER = 100'0000;

	int32 coreCount = thread::hardware_concurrency();
	int32 jobCount = (MAX_NUMBER / coreCount) + 1;

	Atomic<int32> primeCount = 0;

	for (int32 i = 0; i < coreCount; i++)
	{
		int32 start = (i * jobCount) + 1;
		int32 end = min(MAX_NUMBER, (i + 1) * jobCount);

		GThreadManager->Launch([start, end, &primeCount]()
			{
				primeCount += CountPrime(start, end);
			});
	}

	GThreadManager->Join();

	cout << primeCount << endl;
}