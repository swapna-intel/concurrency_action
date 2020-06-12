#include <iostream>
#include <thread>

void threadFunction()
{
  std::cout << "Hello from thread!\n";

}

int main()
{
  //  std::thread th(&threadFunction);
  std::thread th([]()
  {
    std::cout << "Hi from thread\n";
  });
  std::cout << "Hello threads!\n";
  th.join();
  return 0;

}
