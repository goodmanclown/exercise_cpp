#pragma once

#include "SharedBuffer.hxx"

#include <semaphore.h>

#include <atomic>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

/**
 * @brief enum of result of Wait
 * 
 */
enum class SharedBufferArrayEvent 
{
    Stopped = 0,
    BufferReady,
    SlotReady
};
    

/**
 * @brief role of caller of this SharedBufferArray
 * 
 */
enum class SharedBufferRole 
{
    Producer = 0,
    Consumer
};
    

//
// SharedBufferSegment
//
// struct SharedBufferArraySegment
// {
//     uint16_t      m_uRead;
//     uint16_t      m_uWrite;
//     SharedBuffer m_pSharedBufferArray[0];
// };
    

/**
 * @brief definition of a Shared Buffer Circular Array, using named sempahores for IPC
 * 
 */
class SharedBufferArray
{
public:

    /**
     * @brief Construct a new Shared Buffer Array object
     * 
     */
    SharedBufferArray() = default;

    /**
     * @brief Destroy the Shared Buffer Array object
     * 
     */
    ~SharedBufferArray()  { Close(); };

    /**
     * @brief Create named sync objects, start the thread
     * 
     * @param uNumberOfBuffer - number of Shared Buffer
     * @param enRole - role of the caller
     * 
     * @return true if Open is successful
     */
    bool Open(size_t uNumberOfBuffer, SharedBufferRole   enRole);
        

    /**
     * @brief close named semaphores and the shared memory, stop the thread and clear handles
     */
    void Close();

    /**
     * @param buffer - shared buffer to send 
     * 
     * @return true if send is ok
     */
    bool Send(const SharedBuffer& buffer);

    /**
     * @return buffer - shared buffer received the content
     */
    SharedBuffer Receive();

    /**
     * @brief wait for IPC events
     * 
     * @return SharedBufferEvent 
     */
    SharedBufferArrayEvent      Wait();
        
protected:

    /**
     * @brief signal another party
     * 
     * @return true if signal is ok
     */
    bool      Post();
        
    /**
     * @brief role of caller of this object
     * 
     */
    SharedBufferRole   m_enRole = SharedBufferRole::Producer;

    /**
     * @brief key and handle of the array in use binary semaphore
     * 
     */
    static const int ARRAY_IN_USE_KEY = 0x64321;
    sem_t*             m_pSemArrayInUse = nullptr;

    /**
     * @brief key and handle of the slot count counting semaphore
     * 
     */
    static const int SLOT_COUNT_KEY   = 0x64322;
    sem_t*             m_pSemSlotCount = nullptr;

    /**
     * @brief key and handle of the buffer count counting semaphore
     * 
     */
    static const int BUFFER_COUNT_KEY = 0x64323;
    sem_t*             m_pSemBufferCount = nullptr;


    /**
     * @brief shared buffer array segment in shared memory
     * 
     */
    uint8_t*           m_pSharedBufferArraySeg = nullptr;

    /**
     * @brief number of shared buffer configured
     * 
     */
    uint16_t           m_uNumberOfSharedBuffer = 0;


    /**
     * @brief shared buffer array read pointer
     * 
     */
    uint16_t           m_uReadPointer = 0;  
    

    /**
     * @brief shared buffer array write pointer
     * 
     */
    uint16_t           m_uWritePointer = 0;  
};