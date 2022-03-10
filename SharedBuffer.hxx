#pragma once

#include <string>
#include <vector>

/**
 * @brief defining a Shared Buffer
 */
class SharedBuffer
{
public:

    static const uint16_t SHARED_BUFFER_SIZE_MAX = 1024;
    static const uint8_t  SENTENCE_LENGTH_SIZE = sizeof(unsigned long);
    static constexpr uint16_t SENTENCE_LENGTH_MAX = SHARED_BUFFER_SIZE_MAX - SENTENCE_LENGTH_SIZE;

    /**
     * @brief a header to the sentence length and sentence
     * 
     */
    struct SharedBufferBlockHeader
    {
        unsigned long   m_uSentenceLength = 0;
        uint8_t         m_Sentence[0];
    };

    enum class PackResult
    {
        NG = 0,
        OK_WITH_SPACE = 1,
        FULL,
        NOT_ENOUGH_SPACE
    };


    /**
     * @brief Construct a new Shared Buffer object
     */
    SharedBuffer() 
    {   // resize to SHARED_BUFFER_SIZE_MAX
        // m_vContent.resize(SHARED_BUFFER_SIZE_MAX, 0); 
    };


    /**
     * @brief Destructor
     */
    ~SharedBuffer() = default;


    /**
     * @brief clear buffer content
     * 
     */
    void Clear() 
    { 
        m_vContent.clear(); 
        m_iAvailableContentLength = SHARED_BUFFER_SIZE_MAX; 
    };


    /**
     * @return true if the buffer content is empty
     * 
     */
    // bool Empty() { return (reinterpret_cast<SharedBufferBlockHeader*>(&m_vContent[0])->m_uSentenceLength == 0); };
    bool Empty() const { return m_vContent.empty(); };


    /**
     * @return reference to the internal vector
     */
    const std::vector<uint8_t>& Data() const { return m_vContent; };

    /**
     * @brief fill buffer content
     * 
     * @param content - pointer to an array
     * @param content_length - length of the input array
     * 
     */
    void Fill(const uint8_t content[], uint16_t content_length);

    /**
     * @brief pack the input sentence to input buffer
     * 
     * @param sSentence - sentence to be packed to the input buffer
     * 
     * @return OK - Packing is ok and content is not full
     * @return NG - sentence is not packed to the buffer
     * @return FULL - Packing is ok and content is full
     * @return NO_ENOUGH_SPACE - sentence is not packed to the buffer due to not enough space
     */
    PackResult Pack(const std::string& sSentence);


    /**
     * @brief unpack the input content
     * 
     * @param - shared content to be unpacked
     * 
     * @return a vector of sentences unpacked from the shared buffer
     */
    std::vector<std::string> Unpack();


private:

    int16_t                 m_iAvailableContentLength = SHARED_BUFFER_SIZE_MAX;
    std::vector<uint8_t>    m_vContent;
};


