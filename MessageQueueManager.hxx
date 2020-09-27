#pragma once

#include "IMessageQueueManager.h"

#include <queue>
#include <set>
#include <vector>
#include <unordered_map>

bool isStringEmptyOrWhiteSpace(const std::string& in);

// Abstract base class for a message queue manager
class MessageQueueManager : public IMessageQueueManager
{
public:

    MessageQueueManager() = default;

    ~MessageQueueManager() = default;

	// Create a Message Queue with the given name.
	//
	// Returns false on failure, or if the given queue already exists
	bool CreateMessageQueue(const std::string& in_queueName) override;

	// Post a message to a message queue.
	// - Posting an empty message is considered a failure case.
	// - Messages should be stored internally until all subscribers have received them via a GetNextMessage call.
	//
	// Returns false on failure, or if the given queue does not exist.
	bool PostMessage(const std::string& in_queueName, const std::string& in_message) override;

	// Create a unique subscription to a given message queue.
	// - Returns a handle to the subscription in out_handle
	// - The subscription must only receive *new* messages created by PostMessage calls that occur *after* the CreateSubscription call
	//
	// Returns false on failure, or if the given queue does not exist
	bool CreateSubscription(const std::string& in_queueName, SubscriptionHandle& out_handle) override;

	// Get the next message from the message queue for a given subscription
	// - Returns the message in out_message, and advances the subscription to the following message
	// - If there are no more messages for the subscription, returns true and out_message is set to an empty string
	// 
	// Returns false on failure 
	bool GetNextMessage(SubscriptionHandle in_handle, std::string& out_message) override;

private:

    using MessagePtr = std::shared_ptr<std::string>;
    using MessageQueue = std::queue<MessagePtr>;
    using SubHandleList = std::unordered_map<SubscriptionHandle, MessageQueue>;
    using SubHandleListPtr = std::shared_ptr<SubHandleList>;
    using MessageQueueName = std::unordered_map<std::string, SubHandleListPtr>;

    MessageQueueName    mMessageQueueName;
    SubscriptionHandle  mNextSubscriptionHandle = 0;
};