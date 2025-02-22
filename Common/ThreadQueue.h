#ifndef THREADQUEUE_H
#define THREADQUEUE_H

#include <vector>
#include <atomic>
template <typename T>
class ThreadQueue
{
    public: 
        ThreadQueue(int num_elements):m_store{num_elements,0}{};

        ~ThreadQueue();

        T* getNextWrite()
        {
            return &m_store[m_write_next_index];
        }

        void updateWriteIndex()
        {
            m_write_next_index = (m_write_next_index + 1)%m_store.size();
            m_num_of_elements++;
        }

        T* getNextRead()
        {
            return (m_read_next_index == m_write_next_index) ? nullptr: &m_store[m_read_next_index];
        }

        void updateReadIndex()
        {
            m_read_next_index = (m_read_next_index + 1 )%m_store.size();
            m_num_of_elements--;
        }

        auto size() 
        {
            return m_num_of_elements.load();
        }


    private:
        std::vector<T> m_store;
        std::atomic_int m_read_next_index = {0};
        std::atomic_int m_write_next_index = {0};
        std::atomic_int m_num_of_elements = {0};
};

#endif
