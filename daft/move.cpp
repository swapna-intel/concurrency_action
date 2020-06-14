#include <iostream>
#include <thread>
#include <algorithm>
#include <cassert>
#include <vector>

// WRONG example of passing reference vars local to main thread to worker threads
void threadFunc(int& i)
{
  std::cout << "From worker: " << i << std::endl;

}

// CORRECT usage of pass by val
void threadFunc2(int i)
{
  std::cout << "From worker: " << i << std::endl;

}

void run(std::vector<std::thread> &workers)
{
  int i;
  for(i = 0; i < 8; i++)
    {
      // create the threads
      //      auto th = std::thread(threadFunc, std::ref(i));
      auto th = std::thread(threadFunc2, i);
      workers.push_back(std::move(th));
    }
}

int main()
{
  std::vector<std::thread> workers;
  run(workers);
  std::cout << "Hi from main!" << std::endl;
  // pass a lambda function with th as arg and wait for join
  std::for_each(workers.begin(), workers.end(), [](std::thread& th)
		{
		  th.join();
		});
  return 0;
}
