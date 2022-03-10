#include "SharedBufferArray.hxx"

#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/sem.h>
#include <sys/stat.h> 

using namespace std;

bool 
SharedBufferArray::Open(size_t uNumberOfBuffer, SharedBufferRole enRole)
{
    m_uNumberOfSharedBuffer = uNumberOfBuffer;
    m_enRole = enRole;

    // set up the shared memory file name
    string sMMapName = "/ShareBufferArray";

    // producer will create the segment to write
    auto flags = (m_enRole == SharedBufferRole::Producer) ? O_CREAT : 0;

    if (m_enRole == SharedBufferRole::Producer)
    {
        flags |= O_RDWR;
    }
    else
    {
        flags |= O_RDONLY;
    }

    // open the shared memory segment
    auto hMMF = ::shm_open(sMMapName.c_str(), flags, S_IRUSR | S_IWUSR);
    if (hMMF == -1)
    {
        return false;
    }

    size_t uSharedMemorySize = m_uNumberOfSharedBuffer * SharedBuffer::SHARED_BUFFER_SIZE_MAX;

    // now set the correct size for the segment
    if ((m_enRole == SharedBufferRole::Producer) &&
        (::ftruncate(hMMF, uSharedMemorySize) == -1)) // Each Shared Buffer is of size 1024 bytes
    {
        ::close(hMMF);
        ::shm_unlink(sMMapName.c_str());

        return false;
    }

    int oflags = 0;

    // map the shared memory
    if (m_enRole == SharedBufferRole::Producer)
    {
        m_pSharedBufferArraySeg = reinterpret_cast<uint8_t*>(::mmap(nullptr, 
                                                uSharedMemorySize,
                                                PROT_READ | PROT_WRITE,
                                                MAP_SHARED, hMMF, 0));

        if (m_pSharedBufferArraySeg == MAP_FAILED)
        {
            goto Cleanup;
        }

        // Clear the whole buffer once
        memset(m_pSharedBufferArraySeg, 0, uSharedMemorySize);
    }
    else
    {
       m_pSharedBufferArraySeg = reinterpret_cast<uint8_t*>(::mmap(nullptr, 
                                                uSharedMemorySize,
                                                PROT_READ,
                                                MAP_SHARED, hMMF, 0));

        if (m_pSharedBufferArraySeg == MAP_FAILED)
        {
            goto Cleanup;
        }
    }

    oflags = (m_enRole == SharedBufferRole::Producer) ? O_CREAT : 0;

    // IPC mutex for array in use
    m_pSemArrayInUse = sem_open("/SemArrayInUse", oflags, S_IRUSR | S_IWUSR, 1);
    if (m_pSemArrayInUse == SEM_FAILED)
    {
        goto Cleanup;
    }

    // IPC mutex for slot available
    m_pSemSlotCount = sem_open("/SemSlotCount", oflags, S_IRUSR | S_IWUSR, m_uNumberOfSharedBuffer);
    if (m_pSemSlotCount == SEM_FAILED)
    {
        goto Cleanup;
    }

    // IPC mutex for buffer available
    m_pSemBufferCount = sem_open("/SemBufferCount", oflags, S_IRUSR | S_IWUSR, 0);
    if (m_pSemBufferCount == SEM_FAILED)
    {
        goto Cleanup;
    }

    return true;

Cleanup:

    if (m_pSharedBufferArraySeg != MAP_FAILED)
    {
        munmap(m_pSharedBufferArraySeg, uSharedMemorySize);
        m_pSharedBufferArraySeg = nullptr;
    }

    if (hMMF != -1)
    {
        ::close(hMMF);
        ::shm_unlink(sMMapName.c_str());
    }

    if (m_pSemArrayInUse != SEM_FAILED)
    {
        sem_close(m_pSemArrayInUse);
        m_pSemArrayInUse = nullptr;
    }

    if (m_pSemSlotCount == SEM_FAILED)
    {
        sem_close(m_pSemSlotCount);
        m_pSemSlotCount = nullptr;
    }
     
    if (m_pSemBufferCount == SEM_FAILED)
    {
        sem_close(m_pSemArrayInUse);
        m_pSemBufferCount = nullptr;
    }

    return false;
}


void 
SharedBufferArray::Close()
{
    if (m_pSharedBufferArraySeg != nullptr)
    {
        munmap(m_pSharedBufferArraySeg, m_uNumberOfSharedBuffer * SharedBuffer::SHARED_BUFFER_SIZE_MAX);
        m_pSharedBufferArraySeg = nullptr;

        // unlink the shared memory
        string sMMapName = "/SharedBufferArray";
        shm_unlink(sMMapName.c_str());
    }

    if (m_pSemBufferCount != nullptr)
    {
        sem_close(m_pSemBufferCount);
        m_pSemBufferCount = nullptr;
    }

    if (m_pSemSlotCount != nullptr)
    {
        sem_close(m_pSemSlotCount);
        m_pSemSlotCount = nullptr;
    }

    if (m_pSemArrayInUse != nullptr)
    {
        sem_close(m_pSemArrayInUse);
        m_pSemArrayInUse = nullptr;
    }
}


bool 
SharedBufferArray::Send(const SharedBuffer& buffer )
{
    // wait for our turn to write
    auto ret = sem_wait(m_pSemArrayInUse);
    if (ret != 0)
    {
        goto Done;
    }
   
    memcpy(&m_pSharedBufferArraySeg[m_uWritePointer*SharedBuffer::SHARED_BUFFER_SIZE_MAX],
            &buffer.Data()[0],
            SharedBuffer::SHARED_BUFFER_SIZE_MAX);

    // move ahead to the next write, wrap around if needed
    m_uWritePointer = (m_uWritePointer+1) % m_uNumberOfSharedBuffer;

    // release the lock
    sem_post(m_pSemArrayInUse);

Done:

    return Post();
}


SharedBuffer
SharedBufferArray::Receive()
{
    SharedBuffer buffer;

    // wait for our turn to write
    auto ret = sem_wait(m_pSemArrayInUse);
    if (ret != 0)
    {
        goto Done;
    }
    
    buffer.Fill(&m_pSharedBufferArraySeg[m_uReadPointer*SharedBuffer::SHARED_BUFFER_SIZE_MAX], SharedBuffer::SHARED_BUFFER_SIZE_MAX);

    // move ahead to the next read, wrap around if needed
    m_uReadPointer = (m_uReadPointer+1) % m_uNumberOfSharedBuffer;

    // release the lock
    sem_post(m_pSemArrayInUse);

Done:

    Post();

    return buffer;
}


SharedBufferArrayEvent
SharedBufferArray::Wait()
{
    // wait for the semaphore to be available
    if (m_enRole == SharedBufferRole::Consumer)
    {
        auto ret = sem_wait(m_pSemBufferCount);
        if (ret == 0)
        {
            return SharedBufferArrayEvent::BufferReady;
        }
    }
    else
    {
        auto ret = sem_wait(m_pSemSlotCount);
        if (ret == 0)
        {
            return SharedBufferArrayEvent::SlotReady;
        }
    }

    return SharedBufferArrayEvent::Stopped;
}

bool
SharedBufferArray::Post()
{
    // wait for the semaphore to be available
    if (m_enRole == SharedBufferRole::Consumer)
    {
        auto ret = sem_post(m_pSemSlotCount);
        if (ret == 0)
        {
            return true;
        }
    }
    else
    {
        auto ret = sem_post(m_pSemBufferCount);
        if (ret == 0)
        {
            return true;
        }
    }

    return false;
}