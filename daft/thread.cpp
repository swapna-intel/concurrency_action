#include <iostream>
#include <thread>

void threadFunction()
{
  std::cout << "Hello from thread!\n";

}

int main()
{
  std::thread th(&threadFunction);
  std::cout << "Hello threads!\n";
  th.join();
  return 0;

}
