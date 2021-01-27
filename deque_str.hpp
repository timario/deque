/*
 * deque.hpp
 *
 * Efficient generic C++ container combining useful features of std::vector and std::deque
 *
 */

#ifndef DEQUE_HEADER_GUARD
#define DEQUE_HEADER_GUARD



#include <iostream>
#include <cassert>
#include <exception>
#include <stdexcept>

namespace nostd
{
    using std::string;
    using std::overflow_error;
    class deque
    {
    public:
        
        using value_type = int;
        using reference = string&;
        using const_reference = const string&;
        using pointer = string*;
        using const_pointer = const string*;
        using iterator = string*;
        using const_iterator = const string*;
        using difference_type = std::ptrdiff_t;
        using size_type = std::size_t;

        // Common member functions
        deque();  //
        deque(size_type n);//
        deque(size_type n, const string& value); //
        deque(const_iterator b, const_iterator e); //

        deque(const deque& other); //
        deque& operator=(const deque& other); //

        ~deque(); //

        void assign(size_type count, const std::string& value);  //
        void assign(const_iterator b, const_iterator e);  //

        // Element access
        reference at(size_type idx);  //
        const_reference at(size_type idx) const;  //

        reference operator[](size_type idx); //
        const_reference operator[](size_type idx) const; //

        reference front(); //
        const_reference front() const; //

        reference back(); //
        const_reference back() const;//

        string* data(); //
        const string* data() const; //

        // Iterators
        const_iterator cbegin() const;//
        iterator begin(); // 
        const_iterator begin() const; //

        const_iterator cend() const; // 
        iterator end(); //
        const_iterator end() const; // 

        // Capacity
        bool empty() const; //
        size_type size() const; //
        size_type max_size() const; //?

        // Reserve front and back capacity, in one operation.
        void reserve(size_type front, size_type back); //
        void reserve(size_type count); ///

        // Returns current size + unused allocated storage before front()
        size_type capacity_front() const; //

        // Returns current size + unused allocated storage after back()
        size_type capacity_back() const; //

        // Returns current size + all unused allocated storage
        size_type capacity_full() const; //

        // To achieve interface parity with std::vector, capacity() returns capacity_back();
        size_type capacity() const;  //

        void shrink_to_fit();//

        // Modifiers
        void clear(); //

        iterator insert(const_iterator it, const string& value);  ///
        iterator insert(const_iterator it, size_type count, const string& value); ///
        iterator insert(const_iterator it, const_iterator b, const_iterator e); ///

        iterator erase(const_iterator it);  //
        iterator erase(const_iterator b, const_iterator e);   //

        void push_back(const string& value); //
        void push_front(const string& value); //

        void pop_back(); //
        void pop_front(); //


        // To achieve interface parity with std::vector, resize() performs resize_back();
        void resize(size_type count); //
        void resize(size_type count, const string& value); //

        void swap(deque& other); ////////////////////////////////////




            private:
                uint8_t* m_str;
                std::string* m_ptr;
                iterator st_deq = nullptr;
                iterator beg_it = nullptr;
                iterator end_it = nullptr;
                iterator end_deq = nullptr;

                static uint8_t* aloc_mem(size_t m_size = 20)
                {
                    return new uint8_t[sizeof(std::string) * m_size];
                }
                std::string* change_type()
                {
                    return (iterator)m_str;
                }
                void assign_fun(const std::string*& b, const std::string*& e)
                {
                    if ((e - b) > (end_deq - beg_it))
                    {
                        this->~deque();
                        m_str = aloc_mem((e - b) * 2);
                        m_ptr = change_type();
                        st_deq = m_ptr;
                        beg_it = st_deq + (e - b) / 2;
                        end_it = beg_it;
                        end_deq = st_deq + 2 * (e - b);

                    }
                    for (std::string* it = (std::string*)b; it < e; it++)
                    {
                        this->push_back(*it);
                    }
                }
                void check_iter(const std::string* b, const std::string* e)
                {
                    assert(e > b || empty() );
                }
                void check_mem(short side, short size)  ///
                {
                    if (side == -1)
                    {
                        if ((--beg_it) == st_deq && size < beg_it - st_deq)
                        {
                            this->reserve(this->size());
                        }
                    }
                    else
                    {
                        if (++end_it == end_deq || size > end_deq - end_it)
                        {
                            this->reserve(this->size());
                        }
                    }
                }
                void check_index(size_type& idx)
                {
                    if (idx > end_it - beg_it)
                    {
                        throw std::string("Invalid index\n");
                    }
                }
                void check_index(size_type& idx) const
                {
                    if (idx > end_it - beg_it)
                    {
                        throw std::string("Invalid index\n");
                    }
                }



    };


    bool operator==(const deque& lhs, const deque& rhs);
    bool operator!=(const deque& lhs,const deque& rhs);
    bool operator<(const deque& lhs, const deque& rhs);
    bool operator<=(const deque& lhs, const deque& rhs);
    
    bool operator>(const deque& lhs, const deque& rhs);
    bool operator>=(const deque& lhs,const deque& rhs);
    
    //void swap(deque& rhs);
}

void test();

#endif  // DEQUE_HEADER_GUARD
