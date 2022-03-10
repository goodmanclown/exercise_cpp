// #include <limits.h>
#include "SharedBuffer.hxx"
#include "gtest/gtest.h"

#include <array>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

// Tests Pack()
class SharedBufferPack  : public ::testing::Test {
    public:

        SharedBufferPack() = default;

        ~SharedBufferPack() = default;

        void SetUp() override
        {
            size_t uIndexToexpectedPackResult = 0;

            {
                vector<uint8_t> result;
                expectedPackResult[uIndexToexpectedPackResult++] = result;
            }

            {
                vector<uint8_t> result(SharedBuffer::SHARED_BUFFER_SIZE_MAX, 0);

                size_t uIndexToResult = 0;

                result[uIndexToResult++] = 7;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = '1';
                result[uIndexToResult++] = '2';
                result[uIndexToResult++] = '3';
                result[uIndexToResult++] = '4';
                result[uIndexToResult++] = '5';
                result[uIndexToResult++] = '6';
                result[uIndexToResult++] = '7';

                expectedPackResult[uIndexToexpectedPackResult++] = result;
            }

            {
                vector<uint8_t> result(SharedBuffer::SHARED_BUFFER_SIZE_MAX, 0);

                size_t uIndexToResult = 0;

                result[uIndexToResult++] = 7;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = '1';
                result[uIndexToResult++] = '2';
                result[uIndexToResult++] = '3';
                result[uIndexToResult++] = '4';
                result[uIndexToResult++] = '5';
                result[uIndexToResult++] = '6';
                result[uIndexToResult++] = '7';

                result[uIndexToResult++] = 3;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 'a';
                result[uIndexToResult++] = 'b';
                result[uIndexToResult++] = 'c';
                expectedPackResult[uIndexToexpectedPackResult++] = result;
            }

            {
                vector<uint8_t> result(SharedBuffer::SHARED_BUFFER_SIZE_MAX, 'g');

                size_t uIndexToResult = 0;

                result[uIndexToResult++] = (0xff & SharedBuffer::SENTENCE_LENGTH_MAX);
                result[uIndexToResult++] = (0x00ff00 & SharedBuffer::SENTENCE_LENGTH_MAX) >> 8;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;

                expectedPackResult[uIndexToexpectedPackResult++] = result;
            }

            {
                vector<uint8_t> result(SharedBuffer::SHARED_BUFFER_SIZE_MAX, 'b');

                size_t uIndexToResult = 0;

                result[uIndexToResult++] = (0xff & SharedBuffer::SENTENCE_LENGTH_MAX);
                result[uIndexToResult++] = (0x00ff00 & SharedBuffer::SENTENCE_LENGTH_MAX) >> 8;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;

                expectedPackResult[uIndexToexpectedPackResult++] = result;
            }

            {
                vector<uint8_t> result(SharedBuffer::SHARED_BUFFER_SIZE_MAX, 0);

                size_t uIndexToResult = 0;

                result[uIndexToResult++] = 7;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = '1';
                result[uIndexToResult++] = '2';
                result[uIndexToResult++] = '3';
                result[uIndexToResult++] = '4';
                result[uIndexToResult++] = '5';
                result[uIndexToResult++] = '6';
                result[uIndexToResult++] = '7';

                result[uIndexToResult++] = 3;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 0;
                result[uIndexToResult++] = 'a';
                result[uIndexToResult++] = 'b';
                result[uIndexToResult++] = 'c';
                expectedPackResult[uIndexToexpectedPackResult++] = result;
            }

        };

        void TearDown() override {};

    protected:

        static const size_t TEST_SIZE = 6u;

        array<vector<uint8_t>, TEST_SIZE> expectedPackResult; 

        array<vector<string>, TEST_SIZE> inputTarget
        { 
            { 
                { "" },
                { "1234567" },
                { "1234567", "abc" },
                { string(SharedBuffer::SENTENCE_LENGTH_MAX, 'g') },
                { string(SharedBuffer::SHARED_BUFFER_SIZE_MAX, 'b') },
                { "1234567", "abc", string(SharedBuffer::SHARED_BUFFER_SIZE_MAX, 'b') }
            }, 
        };

        array<vector<string>, TEST_SIZE> expectedUnpackResult
        { 
            { 
                { },
                { "1234567" },
                { "1234567", "abc" },
                { string(SharedBuffer::SENTENCE_LENGTH_MAX, 'g') },
                { string(SharedBuffer::SENTENCE_LENGTH_MAX, 'b') },
                { "1234567", "abc", }
            }, 
        };
};

// Tests member api Pack
TEST_F(SharedBufferPack, Pack) {

    auto index = 0u;
    array<vector<uint8_t>, TEST_SIZE> result = { };


    for ( const auto& entry : inputTarget )
    {
        SharedBuffer buffer;

        for (const auto& sSentence : entry)
        {
    	    buffer.Pack(sSentence);
        }

        result[index++] = buffer.Data();
    }

    EXPECT_EQ(expectedPackResult, result);

}

TEST_F(SharedBufferPack, Unpack) {

    auto index = 0u;
    array<vector<uint8_t>, TEST_SIZE> result = { };

    for ( const auto& entry : inputTarget )
    {
        SharedBuffer buffer;

        for (const auto& sSentence : entry)
        {
    	    buffer.Pack(sSentence);
        }

        result[index++] = buffer.Data();
    }

    ASSERT_EQ(expectedPackResult, result);

    index = 0u;
    array<vector<string>, TEST_SIZE> unpackResult = {};

    for (const auto& entry : result)
    {
        SharedBuffer buffer;

        buffer.Fill(&entry[0], entry.size());

        unpackResult[index++] = buffer.Unpack();
    }

    EXPECT_EQ(expectedUnpackResult, unpackResult);
}