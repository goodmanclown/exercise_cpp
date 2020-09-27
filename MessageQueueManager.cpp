#include "MessageQueueManager.hxx"

#include <algorithm>

using namespace std;

std::unique_ptr<class IMessageQueueManager> 
CreateMessageQueueManager()
{
    return std::unique_ptr<IMessageQueueManager>(new MessageQueueManager());
}

bool isStringEmptyOrWhiteSpace(const std::string& in)
{
    return all_of(in.cbegin(), in.cend(), 
        [](const auto& entry)
        {
            return entry == ' ';
        }
    );
}

bool 
MessageQueueManager::CreateMessageQueue(const std::string& in_queueName)
{
    // check and make sure the input is not empty or white space only
    if (isStringEmptyOrWhiteSpace(in_queueName))
    {
        return false;
    }

    // check if queue is already created for this name
    if (!mMessageQueueName.empty())
    {
        if (mMessageQueueName.find(in_queueName) != mMessageQueueName.cend())
        {
            return false;
        }
    }

    // create a message queue with no subscription
    mMessageQueueName.emplace(in_queueName, nullptr);

    return true;
}

bool 
MessageQueueManager::PostMessage(const std::string& in_queueName, const std::string& in_message)
{
    // check and make sure the input is not empty or white space only
    if (isStringEmptyOrWhiteSpace(in_message))
    {
        return false;
    }

    // queue not created
    if (mMessageQueueName.empty())
    {
        return false;
    }

    // queue not created
    auto iter = mMessageQueueName.find(in_queueName);
    if (iter == mMessageQueueName.end())
    {
        return false;
    }

    auto& subList = iter->second;

    // check if sub list is empty
    if (subList == nullptr || subList->empty())
    {
        return false;
    }

    // make a copy of the input message
    MessagePtr pMsg(new std::string(in_message));

    // go through the sub list and attach the message to each queue
    for (auto& entry : *subList)
    {
        // queue the message
        entry.second.push(pMsg);
    }

    return true;
}

bool 
MessageQueueManager::CreateSubscription(const std::string& in_queueName, SubscriptionHandle& out_handle)
{
    // queue not created
    if (mMessageQueueName.empty())
    {
        return false;
    }

    // queue not created
    auto iter = mMessageQueueName.find(in_queueName);
    if (iter == mMessageQueueName.cend())
    {
        return false;
    }

    auto subList = iter->second;
    if (subList != nullptr)
    {
        // find the first entry that has empty message queue
        auto iter = find_if(subList->begin(), subList->end(),
            [](const auto& entry)
            {
                return entry.second.empty();
            }
        );

        // find such an entry
        if (iter != subList->end())
        {
            out_handle = iter->first;
            return true;
        }

        // no subscription is created for this queue yet
        auto newSubscriptionHandle = mNextSubscriptionHandle++;

        MessageQueue msgQ;
        subList->emplace(newSubscriptionHandle, msgQ);

        out_handle = newSubscriptionHandle;

        return true;
    }

    // no subscription is created for this queue yet
    auto newSubscriptionHandle = mNextSubscriptionHandle++;

    MessageQueue msgQ;
    SubHandleListPtr pSubList(new SubHandleList());
    pSubList->emplace(newSubscriptionHandle, msgQ);
    iter->second.swap(pSubList);

    out_handle = newSubscriptionHandle;

    return true;
}

bool 
MessageQueueManager::GetNextMessage(SubscriptionHandle in_handle, std::string& out_message)
{
    // queue not created
    if (mMessageQueueName.empty())
    {
        return false;
    }

    // go through all the msg queue to find this handle
    for (const auto& entry : mMessageQueueName)
    {
        auto pSubList = entry.second;
        if (pSubList != nullptr)
        {   // find the subscription handle
            auto iter = pSubList->find(in_handle);
            if (iter != pSubList->end())
            {
                auto& msgQ = iter->second;
                if (msgQ.empty())
                {
                    out_message.clear();
                    return true;
                }
                else
                {
                    auto pMsg = msgQ.front();
                    out_message = *pMsg;
                    msgQ.pop();
                    return true;
                }
            }
        }
    }

    return false;
}
