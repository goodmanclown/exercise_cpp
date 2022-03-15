#include "SharedBuffer.hxx"

#include <cstring>

using namespace std;

void 
SharedBuffer::Fill(const uint8_t content[], uint16_t content_length) 
{
    if (m_vContent.empty())
    {   // resize it, if this has not been used before
        m_vContent.resize(SHARED_BUFFER_SIZE_MAX, 0); 
    }

    memcpy(&m_vContent[0], content, content_length <= SHARED_BUFFER_SIZE_MAX ? content_length : SHARED_BUFFER_SIZE_MAX);
};

SharedBuffer::PackResult
SharedBuffer::Pack(const string& sSentence)
{
    if (sSentence.empty()) return PackResult::NG;

    if (m_vContent.empty())
    {   // resize it, if this has not been used before
        m_vContent.resize(SHARED_BUFFER_SIZE_MAX, 0); 
    }

    size_t uOffsetToSentenceLength = SHARED_BUFFER_SIZE_MAX - m_iAvailableContentLength;

    // check if there is enough space left
    size_t uSentenceLength = sSentence.length();

    if (uOffsetToSentenceLength == 0 && sSentence.length() > SENTENCE_LENGTH_MAX)
    {   // truncate the input to fit into this new buffer
        uSentenceLength = SENTENCE_LENGTH_MAX;
    }

    if (uOffsetToSentenceLength + SENTENCE_LENGTH_SIZE + uSentenceLength > SHARED_BUFFER_SIZE_MAX)
    {
        return PackResult::NOT_ENOUGH_SPACE;
    }

    auto hdr = reinterpret_cast<SharedBufferBlockHeader*>(&m_vContent[uOffsetToSentenceLength]);

    hdr->m_uSentenceLength = uSentenceLength;
    memcpy(hdr->m_Sentence, &sSentence[0], uSentenceLength);

    m_iAvailableContentLength = m_iAvailableContentLength - SENTENCE_LENGTH_SIZE - uSentenceLength;

    if (m_iAvailableContentLength == 0)
    {
        return PackResult::FULL;
    }

    return PackResult::OK_WITH_SPACE;
}


vector<string> 
SharedBuffer::Unpack()
{
    vector<string> vSentences;
    if (m_vContent.empty() == true) return vSentences;

    // first 4 bytes are length
    size_t uOffsetToSentenceLength = 0;
    int iAvailableContentLength = SHARED_BUFFER_SIZE_MAX;

    do
    {
        auto hdr = reinterpret_cast<SharedBufferBlockHeader*>(&m_vContent[uOffsetToSentenceLength]);

        auto uExpectedSentenceLength = hdr->m_uSentenceLength;

        if (uExpectedSentenceLength == 0 || uExpectedSentenceLength > SENTENCE_LENGTH_MAX
            || uExpectedSentenceLength > iAvailableContentLength)
        {
            // something wrong with this buffer
            // throw out any sentence unpack
            vSentences.clear();
            break;
        }

        string sSentence(uExpectedSentenceLength, 0);
        uint16_t uIndexToSentence = 0;
        for (uint16_t index = 0; index < uExpectedSentenceLength; ++index)
        {
            if (hdr->m_Sentence[index])
            {
                sSentence[uIndexToSentence++] = hdr->m_Sentence[index];
            }
            else
            {   // hit a null
                break;
            }
        }

        if (sSentence.length() != uExpectedSentenceLength)
        {
            // something wrong with this buffer
            // throw out any sentence unpack
            vSentences.clear();
            break;
        }

        // constructed sentence length match expected length
        vSentences.push_back(sSentence);

        // reduce available length
        iAvailableContentLength = iAvailableContentLength - uExpectedSentenceLength - SENTENCE_LENGTH_SIZE;

        // move offset to start of next sentence
        uOffsetToSentenceLength = uOffsetToSentenceLength + uExpectedSentenceLength + SENTENCE_LENGTH_SIZE;
    }
    while (iAvailableContentLength >= 0);

    return vSentences;
}