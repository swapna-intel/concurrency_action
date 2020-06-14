#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
// Buggy threads manipulating the same list!! Pass by ref to threads dangling pointers
class List
{
  struct Node
  {
    int x;
    Node* next;

    Node(int y = 0)
      :x(y), next(nullptr) {}
  };

  Node* head;
  
public:
  List():head(nullptr) {}
  
  void insert(int x)
  {
    Node* node = new Node(x);
    node->next = head;
    head = node;

  }
  int size() const
  {
    auto node = head;
    int count = 0;
    while(node)
      {
	count++;
	node = node->next;
      }
    return count;
  }
};

void threadFunc(List &list)
{

  for(int i = 0; i < 100; i++)
    {
      list.insert(i);
    }

}
int main()
{
  List list;
  std::vector<std::thread> workers;
  for(int i = 0; i < 10; i++)
    {
      workers.push_back(std::thread(threadFunc, std::ref(list)));
    }

  std::for_each(workers.begin(), workers.end(), [](std::thread &th)
		{
		  th.join();
		});
  std::cout << list.size() << std::endl;
  return 0;

}
