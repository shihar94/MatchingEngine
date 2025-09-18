#include <stdlib.h>
#include <string.h>
#include <vector>

#define DEFAULT_POOL_SIZE 16

template <class T>
class MemoryPool
{
    //methods
    public:
        MemoryPool(int chunks , int size = DEFAULT_POOL_SIZE )
        {
            m_chunks = chunks;
            m_size   = size;

            m_memoryChunkList.reserve(m_chunks);

            for(int i = 0 ; i < m_chunks ; i++)
            {
                T* chunk = malloc(sizeof(m_size) * 1);
                m_memoryChunkList.push_back(chunk);
            }
        }


        ~MemoryPool()
        {
            for(int i = 0 ; i < m_chunks ; i++)
            {
                delete m_memoryChunkList[i];
            }
        }

        T* allocateMemory()
        {
            
            if(m_pos >= m_chunks)
            {
                throw std::bad_alloc();
            }
            T* block = m_memoryChunkList.back();
            m_memoryChunkList.pop_back();


            return block;
        }


        void deallocateMemory(T* block)
        {
            m_memoryChunkList.push_back(block);
        }
    private:


    //members
    public:
        

    private:
        int m_size;
        std::vector<T*> m_memoryChunkList;
        int m_chunks;
        int m_pos = 0;
};