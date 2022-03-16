#pragma once

#include "SharedBuffer.hxx"

#include <condition_variable>
#include <mutex>
#include <queue>
#include <vector>

// definition of a thread-safe queue of SharedBuffer
class SharedBufferQueue
{
public:

    /**
     * @brief Construct a new Shared Buffer Queue object
     * 
     */
    SharedBufferQueue() = default;

    /**
     * @brief Destroy the Shared Buffer Queue object
     * 
     */
    ~SharedBufferQueue() = default;

    /**
     * @return SharedBuffer at the front of the queue
     */
    SharedBuffer front() 
    {
        std::unique_lock<std::mutex> lck(m_mtx);
        return m_queue.front();
    }
    
    /**
     * @brief erase the first element in the queue
     * 
     */
    void pop()
    {
        std::unique_lock<std::mutex> lck(m_mtx);
        m_queue.erase(m_queue.begin());
    }

    /**
     * @brief append the input buffer to the end of the queue
     * 
     * @param report 
     */
    void push(const SharedBuffer& buffer)
    {
        std::unique_lock<std::mutex> lck(m_mtx);

        if (m_queue.size() < MAX_DEPTH)        
        {
            m_queue.push_back(buffer);
            m_cv.notify_one();
        }
    }

    /**
     * @return true if the queue is empty
     * 
     */
    bool empty()
    {
        std::unique_lock<std::mutex> lck(m_mtx);
        return m_queue.empty();
    }

    /**
     * @brief wait for the queue to have at least 1 entry. otherwise return immediately
     * 
     */
    void wait()
    {
        std::unique_lock<std::mutex> lck(m_mtx);
        while(m_queue.empty())
        {
            m_cv.wait(lck);
        }
    }

    /**
     * @brief clear all elements of the queue
     * 
     */
    void clear()
    {
        std::unique_lock<std::mutex> lck(m_mtx);
        m_queue.clear();
    }

private:
    std::mutex m_mtx;
    std::condition_variable m_cv;
    std::vector<SharedBuffer> m_queue;

    static constexpr size_t MAX_DEPTH = 100000;
};
