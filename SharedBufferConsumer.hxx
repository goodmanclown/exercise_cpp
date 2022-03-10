#pragma once

#include "SharedBufferArray.hxx"
#include "SharedBufferQueue.hxx"

#include <atomic>
#include <string>
#include <thread>

/**
 * the shared buffer consumer class
 */ 
class SharedBufferConsumer 
{

public:

    /** 
     * Constructor
     * @param - number of shared buffer
     * @param - string to search in a sentence
     */
    SharedBufferConsumer(size_t uNumberOfSharedBuffer, const std::string& sStringToSearch):
                        m_uNumberOfSharedBuffer(uNumberOfSharedBuffer),
                        m_sStringToSearch(sStringToSearch)
    {
    };


    /** 
     * Empty Constructor
     */
    SharedBufferConsumer() = delete;


    /** 
     * Destructor
     */
    ~SharedBufferConsumer() = default;


    /**
     * @brief start this consumer
     */
    void Start();


private:

    /**
     * @brief run the read thread
     */
    void Run();

    /**
     * number of shared buffers
     */
    size_t              m_uNumberOfSharedBuffer;

    /**
     * file path name
     */
    std::string         m_sStringToSearch;

    /**
     * shared buffer
     */
    SharedBufferArray        m_cSharedBufferArray;

    /**
     * Shared Buffer Reader thread
     */
    std::thread         m_tSharedBufferReaderThread;

    /**
     * Shared Buffer Content Queue
     */
    SharedBufferQueue      m_qSharedBufferQueue;
};


