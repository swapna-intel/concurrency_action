#include <iostream>
#include <thread>
#include <algorithm>
#include <cassert>
#include <vector>

void threadFunc(int i)
{
  std::cout << "From worker: " << i << std::endl;

}


int main()
{
  std::vector<std::thread> workers;
  for (int i = 0; i < 8; ++i)
    {
      auto th = std::thread(&threadFunc, i);
      std::cout << "th joinable:" << th.joinable() << std::endl;
      // unique object th belongs to workers DS
      workers.push_back(std::move(th));
      std::cout << "After move, th joinable:" << th.joinable() << std::endl;
    }
  std::cout << "Hi from main!" << std::endl;
  // pass a lambda function with th as arg and wait for join
  std::for_each(workers.begin(), workers.end(), [](std::thread &th)
		{
		  std::cout << "worker th joinable:" << std::endl;
		  th.join();
		});
  return 0;
}
