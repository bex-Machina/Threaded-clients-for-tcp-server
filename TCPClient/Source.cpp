//#include <iostream>
//#include <thread>
//#include <vector>
//#include <string>
//#include<chrono>
//#include<conio.h>
//#include <future>
//#include <cstdlib>
//#include <random>
//std::string random_read(size_t length);
//std::string random_post(size_t length);
//
//
//#include "TCPClient.h"
//
//#define DEFAULT_PORT 12345
//
//struct threadInfo {
//	std::vector<int>requestCount;
//	std::vector<double>time;
//};
//
//threadInfo PostClient(char** argv);
//void ExitClient(char** argv, int TIME);
//bool Exit = false;
//
//
//
//
//int main(int argc, char** argv)
//{
//	// Validate the parameters
//	if (argc != 5) {
//		printf("usage: %s server-name|IP-address\n", argv[0]);
//		return 1;
//	}
//	int POST = std::stoi(std::string(argv[2]));
//	int READ = std::stoi(std::string(argv[3]));
//	int TIME = std::stoi(std::string(argv[4]));
//
//	int postCount = 0;
//
//	//std::vector<std::thread> PostThreads;
//	std::vector<std::shared_future<threadInfo>> PostThreads;
//	std::vector <std::vector<threadInfo>> PostPool;
//	if (POST > 0)
//	{
//		for (int i = 0; i < POST; i++)
//		{
//			PostThreads.push_back(std::async(std::launch::async, PostClient, argv));
//			//std::future<int>std::async(std::launch::async, PostClient, argv);
//		}
//	}
//
//
//	std::this_thread::sleep_for(std::chrono::seconds(TIME));
//	Exit = true;
//	for (auto& th : PostThreads)
//		PostPool.push_back(th.get());
//
//
//
//
//	std::thread exit((ExitClient), argv, TIME);
//	exit.join();
//	return 0;
//}
//
//
//
//std::string random_post(size_t length)
//{
//	auto randchar = []() -> char
//	{
//		const char charset[] =
//			"0123456789"
//			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//			"abcdefghijklmnopqrstuvwxyz";
//		const size_t max_index = (sizeof(charset) - 1);
//		return charset[rand() % max_index];
//	};
//	std::string request;
//	std::string str(length, 0);
//	std::generate_n(str.begin(), length, randchar);
//	std::string str2(length, 0);
//	std::generate_n(str2.begin(), length, randchar);
//	request = "POST@" + str + "#" + str2;
//	return request;
//}
//
//void ExitClient(char** argv, int TIME)
//{
//	TCPClient client(argv[1], DEFAULT_PORT);
//	client.OpenConnection();
//	client.send("EXIT");
//	client.CloseConnection();
//}
//
//threadInfo PostClient(char** argv)
//{
//	TCPClient client(argv[1], DEFAULT_PORT);
//	auto start = std::chrono::high_resolution_clock::now();
//	double tempTime = 0;
//	threadInfo threadInfo;
//	int tempCount = 0;
//	client.OpenConnection();
//	do {
//		auto end = std::chrono::high_resolution_clock::now();
//		auto dif = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
//		std::string request = random_post(140);
//		std::string reply = client.send(request);
//		tempCount = tempCount + 1;
//		if (dif > tempTime)
//		{
//			tempTime = dif;
//			threadInfo.requestCount.push_back(tempCount);
//			//threadInfo.time.push_back(end);
//		}
//	} while (Exit == false);
//	//std::cout << "Post Count :" << tempCount << std::endl;
//	client.CloseConnection();
//	return threadInfo;
//}
//
//
//
//
