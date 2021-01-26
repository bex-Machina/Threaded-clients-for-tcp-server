#include <iostream>
#include <thread>
#include <string>
#include<chrono>
#include<conio.h>
#include <future>
#include <cstdlib>
#include <random>
#include <shared_mutex>

#include "TCPClient.h"
#include "helperFunc.h"




#define DEFAULT_PORT 12345


threadInfo PostClient(char** argv);
threadInfo RequestClient(char** argv);

void ExitClient(char** argv, int TIME);
bool Exit = false;


int main(int argc, char** argv)
{
	// Validate the parameters
	if (argc != 5) {
		printf("usage: %s server-name|IP-address\n", argv[0]);
		return 1;
	}
	int POST = std::stoi(std::string(argv[2]));
	int READ = std::stoi(std::string(argv[3]));
	int TIME = std::stoi(std::string(argv[4]));

	int postCount = 0;


	std::vector<std::shared_future<threadInfo>> ClientThreads;
	

	if (POST > 0)
	{
		for (int i = 0; i < POST; i++)
		{
			ClientThreads.push_back(std::async(std::launch::async, PostClient, argv));
		}
	}

	if (READ > 0)
	{
		for (int i = 0; i < READ; i++)
		{
			ClientThreads.push_back(std::async(std::launch::async, RequestClient, argv));
		}
	}



	std::this_thread::sleep_for(std::chrono::seconds(TIME));
	Exit = true;
	
	for (auto& th : ClientThreads)
	{
		threadInfo temp = th.get();
		if (temp.ispost)
		{
			PostPool.push_back(temp);
		}
		else
		{
			ReadPool.push_back(temp);
		}
	}
		

	std::thread exit((ExitClient), argv, TIME); 
	exit.join();



	for (int i = 0; i < PostPool.size(); i++)
	{
		std::cout << "POST thread " << i << " sent:" <<std::endl;
		for (int j = 0; j < PostPool[i].requestCount.size(); j++)
		{
			std::cout << '\t' << "second " << j << " "<< PostPool[i].requestCount[j] << ": requests." << std::endl;
		}
		std::cout << '\t' << "Runtime: " << TIME << " seconds." << std::endl;
	}



	for (int i = 0; i < ReadPool.size(); i++)
	{
		std::cout << "Read THREAD: " << i << std::endl;
		for (int j = 0; j < ReadPool[i].requestCount.size(); j++)
		{
			std::cout << '\t' << "second " << j << " " << ReadPool[i].requestCount[j] << ": requests." << std::endl;
		}
		std::cout << '\t' << "Runtime: " << TIME << " seconds." << std::endl;
	}

	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Total poster requests: " << getTotalPoster() << "." << std::endl;
	std::cout << "Average request per poster thread: " << Avposter() << "." << std::endl;
	std::cout << "Total reader requests: " << getTotalReader() << "." << std::endl;
	std::cout << "Average request per reader thread: " << Avreader() << "." << std::endl;
	std::cout << "Total requests: " << getTotal() << "." << std::endl;
	std::cout << "Average request per thread: " << AvPthread() << "." << std::endl;
	std::cout << "Average request per thread per second: " << AvPthreadPsecond(TIME) << "." << std::endl;
	return 0;
}





void ExitClient(char** argv, int TIME)
{
	TCPClient client(argv[1], DEFAULT_PORT);
	client.OpenConnection();
	client.send("EXIT");
	client.CloseConnection();
}

threadInfo PostClient(char** argv)
{
	TCPClient client(argv[1], DEFAULT_PORT);
	int count = 0;
	threadInfo temp;
	auto start = std::chrono::high_resolution_clock::now();
	client.OpenConnection();
	do {
		std::string request = random_post(140);
		std::string reply = client.send(request);
		count += 1;
		auto end = std::chrono::high_resolution_clock::now();
		auto dif = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
		
		if (dif >= 1.0)
		{
			temp.requestCount.push_back(count);
			start = std::chrono::high_resolution_clock::now();
			count = 0;
		}	
	} while (Exit == false);

	if (count)
	{
		temp.requestCount.push_back(count);
	}
	
	client.CloseConnection();
	return temp;
}


threadInfo RequestClient(char** argv)
{
	TCPClient client(argv[1], DEFAULT_PORT);
	int count = 0;
	threadInfo temp;
	temp.ispost = false;
	auto start = std::chrono::high_resolution_clock::now();
	client.OpenConnection();
	do {
		std::string request = random_read(140);
		std::string reply = client.send(request);
		count += 1;
		auto end = std::chrono::high_resolution_clock::now();
		auto dif = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

		if (dif >= 1.0)
		{
			temp.requestCount.push_back(count);
			start = std::chrono::high_resolution_clock::now();
			count = 0;
		}
	} while (Exit == false);

	if (count)
	{
		temp.requestCount.push_back(count);
	}

	client.CloseConnection();
	return temp;
}



