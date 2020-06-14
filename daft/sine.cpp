#include <cmath>
#include <thread>
#include <list>
#include <iostream>
#include <algorithm>

void toSin(std::list<double> &&l)
{
  std::for_each(l.begin(), l.end(), [](double &x)
		{
		  x = sin(x);
		});

  std::for_each(l.begin(), l.end(), [](double &x)
		{
		  int count = static_cast<int>(10*x + 10.5);
		  for(int i = 0; i < count; i++)
		    std::cout.put('*');
		  std::cout << std::endl;

		});

}


int main()
{
  std::list<double> list;
  //access list from main thread
  const double pi = 3.141592;
  const double epsilon = 0.0000001;
  for(double x = 0.0; x < 2*pi+epsilon; x+=pi/16) list.push_back(x);
  //start thread
  std::thread th(&toSin, std::move(list));
  //join thread
  th.join();
  //access list from main thread
  std::cout << "From main:" << std::endl;
  std::for_each(list.begin(), list.end(), [](double &x)
		{
		  int count = static_cast<int>(10*x + 10.5);
		  for(int i = 0; i < count; i++)
		    std::cout.put('*');
		  std::cout << std::endl;

		});

  return 0;
}
