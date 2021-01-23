#pragma once
#include <vector>

struct threadInfo {
	std::vector<int>requestCount;
	bool ispost = true;
};

std::vector<threadInfo> PostPool;
std::vector<threadInfo> ReadPool;


int getTotalPoster() {
	int total = 0;
	for (int i = 0; i < PostPool.size(); i++)
	{
		for (int j = 0; j < PostPool[i].requestCount.size(); j++)
		{
			total += PostPool[i].requestCount[j];
		}
	}


	return total;
}


std::string random_post(size_t length)
{
	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	std::string request;
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);
	std::string str2(length, 0);
	std::generate_n(str2.begin(), length, randchar);
	request = "POST@" + str + "#" + str2;
	return request;
}

std::string random_read(size_t length)
{
	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	std::string request;
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);
	str = "READ@" + str + "#" + std::to_string(rand() % 100);
	return str;
}

int Avposter() {
	return getTotalPoster() / PostPool.size();
}

int getTotalReader()
{
	int total = 0;
	for (int i = 0; i < ReadPool.size(); i++)
	{
		for (int j = 0; j < ReadPool[i].requestCount.size(); j++)
		{
			total += ReadPool[i].requestCount[j];
		}
	}
	return total;
}

int Avreader()
{
	return getTotalReader() / ReadPool.size();
}

int getTotal()
{
	return getTotalPoster() + getTotalReader();
}

int AvPthread()
{
	int Numthreads = ReadPool.size() + PostPool.size();
	return getTotal() / Numthreads;
}

int AvPthreadPsecond(int time)
{
	return AvPthread() / time;
}