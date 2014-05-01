#include "SingLinkedListNode.hxx"

#include <stdint.h>


/**
 * class to represent a job
 */
class SchedulerJob : public SingLinkedListNode {

public:

	/**
    * Constructor
    *
	 * @param priority - priority of job to be scheduled
	 * @param id - id of job to be scheduled
    *
    */
 	SchedulerJob(uint32_t priority, uint32_t id):SingLinkedListNode(priority),mId(id) { };


	/**
    * Copy Constructor
    */
 	SchedulerJob(const SchedulerJob& rhs):SingLinkedListNode(rhs),mId(rhs.mId) { };

	
	/**
    * Destructor
    */
 	virtual ~SchedulerJob() { };

	
	/**
    * assignment operator
	 */ 
 	SchedulerJob& operator=(const SchedulerJob& rhs) {
		 if (this == &rhs) return *this;

	 	SingLinkedListNode::operator=(rhs);
	 	mId = rhs.mId;

	 	return *this;  
 	};


	/**
	 * @return mId
	 */
	uint32_t	getId() const { return mId; };


	/**
	 * @return priority
	 */
	uint32_t	getPriority() const { return getValue(); };


protected:

	/**
	 * @param: out - a reference to output stream to append to
    *
	 * @return ostream of the content of this object
    */
	virtual ostream& append(ostream&out) const { 
		SingLinkedListNode::append(out);

		out << mId << std::endl;

		return out;
	};


private:

	/**
    * id of this job
    */
 	uint32_t mId;

};


typedef SchedulerJob* SchedulerJobPtr;
