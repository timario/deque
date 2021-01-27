#include "deque_str.hpp"
#include <exception>

using std::string;
using namespace nostd;


    //Common member functions
deque::deque() :
    m_str(aloc_mem()),
    m_ptr(change_type()),
    st_deq(m_ptr),
    beg_it(m_ptr + 20 / 2),
    end_it(beg_it),
    end_deq(st_deq + 20)
{
}
deque::deque(size_type n) :    //will initialize n variables
    m_str(aloc_mem(n * 2)),
    m_ptr(change_type()),
    st_deq(m_ptr),
    beg_it(m_ptr + n/2),
    end_it(beg_it+n),
    end_deq(st_deq + n * 2)
{
    for (iterator it = beg_it; it < end_it; it++)
    {
        deque::iterator sptr = new(it) std::string("");
    }
}
deque::deque(size_type n, const std::string& value) :
    m_str(aloc_mem(n * 2)),
    m_ptr(change_type()),
    st_deq(m_ptr),
    beg_it(m_ptr + n/2),
    end_it(beg_it+n),
    end_deq(st_deq + 2 * n)
{
    for (iterator it = beg_it; it < beg_it + n; it++)
    {
        deque::iterator sptr = new(it) std::string(value);
    }
}
deque::deque(const_iterator b, const_iterator e) :
    m_str(aloc_mem((e-b)*2)),
    m_ptr(change_type()),
    st_deq(m_ptr),
    beg_it(m_ptr + (e-b) / 2),
    end_it(beg_it+(e-b)),
    end_deq(st_deq + (e-b)*2)
{
    //check_iter(b, e);
    iterator tmp_it = (iterator)b;
    for (iterator it = beg_it; it < end_it; it++, tmp_it++)
    {
        deque::iterator sptr = new(it) std::string(*tmp_it);
    }
}

deque::deque(const deque& other) :
    m_str(aloc_mem(other.size() * 2)),
    m_ptr(change_type()),
    st_deq(m_ptr),
    beg_it(m_ptr + other.size() / 2),
    end_it(beg_it + other.size()),
    end_deq(st_deq + other.size() * 2)
{
    iterator tmp_it = (iterator)other.begin();
    for (iterator it = beg_it; it < end_it; it++, tmp_it++)
    {
        deque::iterator sptr = new(it) std::string(*tmp_it);
    }
}

deque& deque::operator=(const deque& other)
{
    uint8_t* m_str_ = aloc_mem(other.size() * 2);
    iterator m_ptr_ = (iterator)m_str_;
    iterator st_deq_ = m_ptr_;
    iterator beg_it_ = m_ptr_ + (other.size()/2);
    iterator end_it_ = beg_it_ + other.size();

    iterator end_deq_ = st_deq_ + other.size()*2;
    iterator tmp_it = beg_it_; 
    for (iterator it = other.beg_it; it < other.end_it; it++, tmp_it++)
    {
        iterator sptr = new (tmp_it) std::string(*it);

    }
    st_deq = st_deq_;
    beg_it = beg_it_;
    end_it = end_it_;
    end_deq = end_deq_;
    m_ptr = data();

    return *this;
}

deque::~deque()
{
    if (size() > 0)
    {
        for (int i = size() - 1; i >= 0; i--)
        {
            (beg_it + i)->~string();
            // std::cout << "i = " << i << "\n";
        }
    }
    delete[] m_str;
}

void deque::assign(deque::size_type count, const std::string& value)
{
    clear();
    for (size_t i = 0; i < count; i++)
    {
        push_back(value);
    }
}
void deque::assign(const_iterator b, const_iterator e)
{
    check_iter(b, e);
    clear();
    assign_fun(b, e);
}

//// Element access
deque::reference deque::at(size_type idx)
{
    try
    {
        check_index(idx);
    }
    catch (std::string a)
    {
        std::cout << a;
        return *(m_ptr + 0);
    }
    return *(beg_it+idx);
}
deque::const_reference deque::at(size_type idx) const
{
    try
    {
        check_index(idx);
    }
    catch (std::string a)
    {
        std::cout << a;
        return *(m_ptr + 0);
    }
    return *(beg_it + idx);
}

deque::reference deque::operator[](size_type idx)
{
    return *(beg_it + idx);
}
deque::const_reference deque::operator[](size_type idx) const
{
    return *(beg_it + idx);
}

deque::reference deque::front()
{
    return *beg_it;
}
deque::const_reference deque::front() const
{
    return *beg_it;
}

deque::reference deque::back()
{
    iterator tmp = end_it - 1;
    return *(tmp);
}
deque::const_reference deque::back() const
{
    const_iterator tmp = end_it;
    return *(--tmp);
}

string* deque::data()
{
    return beg_it;
}
const string* deque::data() const
{
    return beg_it;
}

//// Iterators
deque::const_iterator deque::cbegin() const
{
    return beg_it;
}
deque::iterator deque::begin()
{
    return beg_it;
}
deque::const_iterator deque::begin() const
{
    return beg_it;
}

deque::const_iterator deque::cend() const
{
    return end_it;
}
deque::iterator deque::end()
{
    return end_it;
}
deque::const_iterator deque::end() const
{
    return end_it;
}
//// Capacity
bool deque::empty() const
{
    return  ((end_it - beg_it) == 0) ? true : false;
}
deque::size_type deque::size() const
{
    return (end_it - beg_it);
}
deque::size_type deque::max_size() const
{
    return 1024000;
}

//// Reserve front and back capacity, in one operation.
void deque::reserve(deque::size_type front, deque::size_type back)
{
    uint8_t* m_str_ = aloc_mem(size() + (front+back) * 2);
    iterator m_ptr_ = (iterator)m_str_;
    iterator st_deq_ = m_ptr_;
    iterator beg_it_ = m_ptr_ + (front + (beg_it-st_deq) ) ;
    iterator end_it_ = beg_it_ + size();
    iterator end_deq_ = st_deq_ + (size() + (front + back) * 2);
    iterator tmp_it = beg_it_;
    for (iterator it = beg_it; it < end_it; it++, tmp_it++)
    {
        iterator sptr = new (tmp_it) std::string(*it);
    }


    st_deq = st_deq_;
    beg_it = beg_it_;
    end_it = end_it_;
    end_deq = end_deq_;
    m_ptr = data();
}
        

void deque::reserve(size_type count)
{
    uint8_t * m_str_ = aloc_mem(count*2);
    iterator m_ptr_ = (iterator)m_str_;
    iterator st_deq_ = m_ptr_;
    iterator beg_it_ = m_ptr_ + count / 2;
    iterator end_it_ = beg_it_+size();
    iterator end_deq_=st_deq_ + count*2;
    iterator tmp_it = beg_it_;
    for (iterator it = beg_it; it < end_it; it++ , tmp_it++)
    {
        iterator sptr = new (tmp_it) std::string(*it);
    }


    st_deq = st_deq_;
    beg_it = beg_it_;
    end_it = end_it_;
    end_deq= end_deq_;
    m_ptr = data();
}


//// Returns current size + unused allocated storage before front()
deque::size_type deque::capacity_front() const
{
    return end_it - st_deq;
}

//// Returns current size + unused allocated storage after back()
deque::size_type deque::capacity_back() const
{
    return end_deq - beg_it;
}

//// Returns current size + all unused allocated storage
deque::size_type deque::capacity_full() const
{
    return end_deq - st_deq;
}

//// To achieve interface parity with std::vector, capacity() returns capacity_back();
deque::size_type deque::capacity() const
{
    return end_deq - st_deq;
}

void deque::shrink_to_fit()
{
    st_deq = beg_it;
    end_deq = end_it;
}

//// Modifiers
void deque::clear()
{
    for (int i = size() - 1; i >= 0; i--)
    {
        // if ((beg_it+i)->size() >0)
        (beg_it + i)->~string();
    }
    end_it = beg_it;
}

deque::iterator deque::insert(deque::const_iterator it, const string& value)
{
    if (it >= beg_it && it < end_it)
    {
        iterator tmp = (iterator)it;
        iterator sptr = new (end_it++) std::string(); ///
        for (tmp=tmp+1; tmp < end_it; tmp++)
        {
            *(tmp) = *(tmp-1);
        }
        return tmp;
    }
    else if (it == end_it)
        this->push_back(value);
    else (assert(false));
}
deque::iterator deque::insert(const_iterator it, size_type count, const string& value)
{
    check_mem(1, end_it - it + count );
    for (iterator tmp = (iterator)it; tmp < it + count; tmp++)
    {
        insert(tmp, value);
    }
    iterator a = (iterator)it;
    return a;
}
deque::iterator deque::insert(const_iterator it, const_iterator b, const_iterator e)
{
    iterator tmp_it = (iterator)it;
    for (b; b < e; b++, tmp_it++)
    {
        insert(tmp_it, *b);
    }
    return (iterator)it;
}

deque::iterator deque::erase(const_iterator it)
{
    check_iter(it, end());
    for (iterator tmp = (iterator)it + 1; tmp < end_it; tmp++)
        *(tmp - 1) = *tmp;
    end_it--;
    (end_it + 1)->~string();
    return iterator(it);
}
deque::iterator deque::erase(const_iterator b, const_iterator e)
{
    check_iter(b, e);
    iterator it = (iterator)b;
    for (it; it < e--; it)
    {
        it =erase(it);
    }
    return it;
}

void deque::push_back(const string& value)
{
    deque::iterator sptr = new(end_it) std::string(value);
    check_mem(1, 1);
}
void deque::push_front(const string& value)
{
    check_mem(-1, 1);
    iterator sptr = new((beg_it)) std::string(value);
}

void deque::pop_back()
{
    assert(end_it >= beg_it);
    (--end_it)->~string();
}
void deque::pop_front()
{
    assert(beg_it < end_it);
    (beg_it++)->~string();
}

//// To achieve interface parity with std::vector, resize() performs resize_back();
void deque::resize(size_type count)
{
    if (count < size())
    {
        for (iterator it = end() - 1; it >= begin()+count; it--)
        {
            erase(it);

        }
    }
    else if (st_deq == nullptr)
    {
        m_str = aloc_mem(count*2);
        m_ptr =change_type();
        st_deq= m_ptr;
        beg_it = m_ptr + count;
        end_it =beg_it;
        end_deq = st_deq + count*2;
        for (iterator it = end_it; it < beg_it + count; it++)
        {
            push_back("");
        }
    }
    else
    {
        for (iterator it = end_it; it < beg_it + count; it++)
        {
            push_back("");
        }
    }
}
void deque::resize(size_type count, const string& value)
{
    if (count < size())
    {
        for (iterator it = end() - 1; it >= begin() + count; it--)
        {
            erase(it);

        }
    }
    else
    {
        reserve(count);
        for (iterator it = end_it; end_it < beg_it + count; it++)
        {
            iterator sptr = new(it) std::string(value);
            end_it++;
        }
    }
}

void deque::swap(deque& other)
{
    deque tmp;
    tmp = other;
    other = *this;
    *this = tmp;

}

    
bool nostd::operator==(const deque& lhs, const deque& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	string * rhs_tmp =(string *)rhs.begin();
	for (string * tmp = (string *)lhs.begin(); tmp < (string *)lhs.end(); tmp++)
	{
		if (*tmp != *rhs_tmp++)
			return false;
	}
	return true;
}
bool nostd::operator!=(const deque& lhs, const deque& rhs)
{
	if (lhs.size() != rhs.size())
		return true;
	string * rhs_tmp =(string *)rhs.begin();
	for (string * tmp = (string *)lhs.begin(); tmp < (string *)lhs.end(); tmp++)
	{
		if (*tmp != *rhs_tmp++)
			return true;
	}
	return false;
}

bool nostd::operator<(const deque& lhs, const deque& rhs)
{
	string * tmp = (string *)lhs.begin();
	for (string * rhs_tmp =(string *)rhs.begin(); rhs_tmp < rhs.end(); rhs_tmp++)
	{
		if (*tmp < *rhs_tmp)
			return true;
		else if (*tmp > * rhs_tmp)
			return false;
	}
	if (lhs.size() >= rhs.size())
		return false;
	return true;
}
bool nostd::operator<=(const deque& lhs, const deque& rhs)
{
	string * tmp = (string *)lhs.begin();
	for (string * rhs_tmp =(string *)rhs.begin(); rhs_tmp < rhs.end(); rhs_tmp++)
	{
		if (*tmp < *rhs_tmp)
			return true;
		else if (*tmp > * rhs_tmp)
			return false;
	}
	if (lhs.size() > rhs.size())
		return false;
	return true;
}

bool nostd::operator>(const deque& lhs, const deque& rhs)
{
	string * tmp = (string *)lhs.begin();
	for (string * rhs_tmp =(string *)rhs.begin(); rhs_tmp < rhs.end(); rhs_tmp++)
	{
		if (*tmp > * rhs_tmp)
			return true;
		else if (*tmp < *rhs_tmp)
			return false;
	}
	if (lhs.size() <= rhs.size())
		return false;
	return true;
}
bool nostd::operator>=(const deque& lhs, const deque& rhs)
{
	string* tmp = (string *)lhs.begin();
	for (string * rhs_tmp =(string *)rhs.begin(); rhs_tmp < rhs.end(); rhs_tmp++)
	{
		if (*tmp > * rhs_tmp)
			return true;
		else if (*tmp < *rhs_tmp)
			return false;
	}
	if (lhs.size() < rhs.size())
		return false;
	return true;
}

   







int main()
{
    test();

 //   std::cout << mydeque.capacity_full() << "\n";
 //  // std::cout << mydeque.capacity_front();
 // //  std::cout << mydeque.front() << "back =" << mydeque.back() << "\n";

 //   

 ////   std::cout << " \n" << mydeque.capacity_back();

 //   mydeque.reserve(10);
 //  // std::cout << " \n\n\nsize =" << mydeque.size();

 //   mydeque1.assign(8, "100");

 //  // std::cout << "\nelem#3 =" << mydeque1[3] << "\nsize = " << mydeque1.size() << "\n ";
 //   

 //   mydeque.assign(mydeque1.begin() + 3, mydeque1.end() - 2);

 //   
 //   std::cout << "cap1 =" << mydeque.capacity_full() << "\n";
 //   std::cout << "sz1 =" << mydeque.size() << "\n";


 //   mydeque1 = mydeque;

 //   std::cout << "cap2 =" << mydeque1.capacity_full() << "\n";



 //   mydeque1.reserve(120);
 //   std::cout << "cap4 =" << mydeque1.capacity_full() << "\n";

 //   mydeque1.reserve(10);

 //   std::cout << "cap3 =" << mydeque1.capacity_full() << "\n";

    //nostd::deque mydeque1(mydeque);      ///////////// beg_deq  |1|2|3|+|+|+|+|+|4|5| end_deq

    //std::cout<<mydeque1.front() << "back =" << mydeque1.back() << "\n";


    //std::string* A = mydeque.data();

    //for (size_t i = 0; i < 5; i++)
    //{
    //    std::cout << A[i];
    //}

    //nostd::deque qwe;
    //if (qwe.empty())
    //{
    //    std::cout << "123";
    //}

    //mydeque.clear();

    //mydeque.push_back("123");
    //mydeque.push_back("123");
    //mydeque.push_back("123");

    //std::cout << "\n" << mydeque.size() << "\n";

    //mydeque.erase(mydeque.begin(), mydeque.end());
    //mydeque.push_back("123");

    //std::cout << mydeque.size() << "\n";
    //mydeque.push_back("123");
    //mydeque.shrink_to_fit();
    //std::cout << mydeque.size() << "  " << mydeque.capacity()<< "\n";

    return 0;
}









