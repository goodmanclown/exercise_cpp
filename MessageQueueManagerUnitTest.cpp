// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "MessageQueueManager.hxx"

#include "gtest/gtest.h"

#include <algorithm>
#include <array>

using namespace std;

// Tests member api CreateSubscription
TEST(MessageQueueManager, CreateSubscription) {

    auto pMgr = CreateMessageQueueManager();

    auto qName = "test_queue";

    SubscriptionHandle h;

    EXPECT_FALSE(pMgr->CreateSubscription(qName, h));

    ASSERT_TRUE(pMgr->CreateMessageQueue(qName));

    EXPECT_TRUE(pMgr->CreateSubscription(qName, h));
    EXPECT_EQ(0, h);

    // get subscription again
    EXPECT_TRUE(pMgr->CreateSubscription(qName, h));
    EXPECT_EQ(0, h);

    ASSERT_TRUE(pMgr->PostMessage(qName, "test_msg_1"));

    EXPECT_TRUE(pMgr->CreateSubscription(qName, h));
    EXPECT_EQ(1, h);

    // get subscription again
    EXPECT_TRUE(pMgr->CreateSubscription(qName, h));
    EXPECT_EQ(1, h);
}

// Tests member api GetMessage
TEST(MessageQueueManager, GetNextMessage) {

    auto pMgr = CreateMessageQueueManager();

    auto qName = "test_queue";

    SubscriptionHandle h;
    ASSERT_TRUE(pMgr->CreateMessageQueue(qName));
    ASSERT_TRUE(pMgr->CreateSubscription(qName, h));
    ASSERT_EQ(0, h);

    array<string, 3> msgArray {
        {
            "test_msg_1",
            "test_msg_2",
            "test_msg_3"
        }
    };

    // post some messages
    for_each(msgArray.cbegin(), msgArray.cend(),
        [&pMgr, &qName](const auto& entry)
        {
            ASSERT_TRUE(pMgr->PostMessage(qName, entry));
        }
    );

    // get the messages
    for_each(msgArray.cbegin(), msgArray.cend(),
        [&pMgr, &h](const auto& entry)
        {
            string out_msg;
            EXPECT_TRUE(pMgr->GetNextMessage(h, out_msg));
            EXPECT_EQ(entry, out_msg);
        }
    );

    // post some messages
    for (size_t index = 0; index < msgArray.size(); ++index)
    {
        ASSERT_TRUE(pMgr->PostMessage(qName, msgArray[index]));

        if (index == 0)
        {   // create a new subscription after the first message is posted
            SubscriptionHandle h;
            ASSERT_TRUE(pMgr->CreateSubscription(qName, h));
            ASSERT_EQ(1, h);
        }
    }
    
    // get the messages for h=0
    for_each(msgArray.cbegin(), msgArray.cend(),
        [&pMgr](const auto& entry)
        {
            string out_msg;
            EXPECT_TRUE(pMgr->GetNextMessage(0, out_msg));
            EXPECT_EQ(entry, out_msg);
        }
    );

    // get the messages for h=1
    for(size_t index = 1; index < msgArray.size(); ++index)
    {
        string out_msg;
        EXPECT_TRUE(pMgr->GetNextMessage(1, out_msg));
        EXPECT_EQ(msgArray[index], out_msg);
    }
}