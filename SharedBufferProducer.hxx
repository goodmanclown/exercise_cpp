#pragma once

#include "SharedBufferArray.hxx"

#include <atomic>
#include <string>
#include <thread>

/**
 * the shared buffer producer class
 */ 
class SharedBufferProducer 
{

public:

    /** 
     * Constructor
     * @param - number of shared buffer
     * @param - file path name
     */
    SharedBufferProducer(size_t uNumberOfSharedBuffer, const std::string& sFilePathName):
                        m_uNumberOfSharedBuffer(uNumberOfSharedBuffer),
                        m_sFilePathName(sFilePathName)
    {
    };


    /** 
     * Empty Constructor
     */
    SharedBufferProducer() = delete;


    /** 
     * Destructor
     */
    ~SharedBufferProducer() = default;


    /**
     * @brief start the producer
     */
    void Start();


private:


    /**
     * number of shared buffer
     */
    size_t              m_uNumberOfSharedBuffer;

    /**
     * file path name
     */
    std::string         m_sFilePathName;

    /**
     * shared buffer
     */
    SharedBufferArray        m_cSharedBufferArray;

};


