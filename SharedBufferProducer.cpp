#include "SharedBufferProducer.hxx"

#include "SharedBuffer.hxx"

#include <fstream>
#include <iostream>


using namespace std;

void 
SharedBufferProducer::Start()
{
    if (m_uNumberOfSharedBuffer == 0 || m_sFilePathName.empty())
    {
        return;
    }

    // open the file
    ifstream fInputFile(m_sFilePathName);

    if (!fInputFile.is_open())
    {
        cerr << "cannot open input file: " << m_sFilePathName << endl;
        return;
    }

    auto ret = m_cSharedBufferArray.Open(m_uNumberOfSharedBuffer, SharedBufferRole::Producer);
    if (ret == false)
    {
        cerr << "cannot open shared buffer array" << endl;
        return;
    }

    SharedBuffer buffer;

    bool bStopped = false;
    string sSentence;
    while (!fInputFile.eof() && !bStopped)
    {
        if (sSentence.empty())
        {
            getline(fInputFile, sSentence);
            cout << sSentence << endl;
        }

        auto result = buffer.Pack(sSentence);

        if (result == SharedBuffer::PackResult::NG || result == SharedBuffer::PackResult::OK_WITH_SPACE)
        {
            // clear the buffer for next getline
            sSentence.clear();
            continue;
        }

        // Block until signaled
        auto enEvent = m_cSharedBufferArray.Wait();

        switch (enEvent)
        {
            case SharedBufferArrayEvent::SlotReady:
            {
                m_cSharedBufferArray.Send(buffer);

                // clear the buffer for next pack
                buffer.Clear();

                if (result == SharedBuffer::PackResult::FULL)
                {
                    // clear the buffer for next getline
                    sSentence.clear();
                }

            }
            break;

            case SharedBufferArrayEvent::Stopped:
            default: 
            {
                // buffer stopped 
                bStopped = true;
            }
            break;
        }
    }

    if (!bStopped && !buffer.Empty())
    {
        // send whatever is in the buffer
        // wait for shared buffer clear
        // Block until signaled
        auto enEvent = m_cSharedBufferArray.Wait();

        switch (enEvent)
        {
            case SharedBufferArrayEvent::SlotReady:
            {
                m_cSharedBufferArray.Send(move(buffer));
                break;

                default: 
                break;
            }
        }
    }

    m_cSharedBufferArray.Close();
}

