#include "SharedBufferConsumer.hxx"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

void 
SharedBufferConsumer::Start()
{
    if (m_uNumberOfSharedBuffer == 0 || m_sStringToSearch.empty())
    {
        return;
    }

    auto ret = m_cSharedBufferArray.Open(m_uNumberOfSharedBuffer, SharedBufferRole::Consumer);
    if (ret == false)
    {
        cerr << "cannot open shared buffer array" << endl;
        return;
    }

    bool bStopped = false;
    while (!bStopped)
    {
        // Block until signaled
        auto enEvent = m_cSharedBufferArray.Wait();

        switch (enEvent)
        {
        case SharedBufferArrayEvent::BufferReady:
        {
            // Data available for reading
            // SharedBuffer buffer;
            // auto ret = m_cSharedBufferArray.Receive(buffer);
            // if (ret == true)
            SharedBuffer buffer = m_cSharedBufferArray.Receive();
            if (!buffer.Empty())
            {
                // unpack, validate and convert content to sentences
                auto vSentences = buffer.Unpack();
                if (vSentences.empty())
                {
                    continue;
                }

                for (const auto& sSentence : vSentences)
                {
                    if (sSentence.find(m_sStringToSearch) != string::npos)
                    {
                        cout << sSentence << endl;
                    }
                }
            }
        }
        break;

        case SharedBufferArrayEvent::Stopped:
        default: 
        {
            bStopped = true;
        }
        break;
        }
    }
}
