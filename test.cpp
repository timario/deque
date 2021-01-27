#include <deque>
#include "deque_str.hpp"

using namespace nostd;
void test()
{
	std::deque<std::string> deq1(10);
	std::deque<std::string> deq2(5, "123");
	std::deque<std::string> deq3;
	nostd::deque my_deq1(10, "");
	nostd::deque my_deq2(5, "123");
	nostd::deque my_deq3;

	std::deque<std::string>::iterator it_deq1_beg = deq1.begin();
	std::deque<std::string>::iterator it_deq2_beg = deq2.begin();

	nostd::deque::iterator it_my_deq2_beg = my_deq2.begin();
	nostd::deque::iterator it_my_deq1_beg = my_deq1.begin();

	/////////////////////////////////////////////////TESTING FUN ///////////////////////////////////////////////
	assert(deq1.size() == my_deq1.size());
	assert(deq2.at(3) == my_deq2.at(3));
	assert(deq2[0] == my_deq2[0]);
	
	deq1.push_back("321");
	my_deq1.push_back("321");
	assert(deq1.back() == my_deq1.back());
	deq2.pop_back();
	deq2.pop_back();
	my_deq2.pop_back();
	my_deq2.pop_back();
	assert(deq2.back() == my_deq2.back());
	assert(deq2.front() == my_deq2.front());

	deq2.push_back("321");
	deq2.push_back("32");
	deq2.push_back("3");
	my_deq2.push_back("321");
	my_deq2.push_back("32");
	my_deq2.push_back("3");
	for (size_t i = 0; i < (deq2.size() < my_deq2.size() ? my_deq2.size() : deq2.size()); i++)
		assert(deq2[i] == my_deq2[i]);

	assert((deq2.end() - deq2.begin()) == my_deq2.end() - my_deq2.begin());
	
	assert(my_deq1.empty() == deq1.empty());
	assert(my_deq3.empty() == deq3.empty());

	deq2.clear();
	my_deq2.clear();
	assert(my_deq2.empty() == deq2.empty());

	deq2.erase(deq2.begin(), deq2.end());	my_deq2.erase(my_deq2.begin(), my_deq2.end());


	nostd::deque mydeque(10, "4");     
	nostd::deque mydeque1;     

	mydeque1.insert(mydeque1.begin(), mydeque.begin() + 1, mydeque.end() - 1);


	assert(mydeque != mydeque1);

	assert(mydeque >= mydeque1);
		
	mydeque = mydeque1;

	assert(mydeque >= mydeque1);
	assert(mydeque <= mydeque1);
	assert(mydeque == mydeque1);
}