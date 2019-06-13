#include <cmath>

#include "hierarchicalQueue.h"

static class hierarchicalQueueClass : public TclClass {
public:
        hierarchicalQueueClass() : TclClass("Queue/HIER") {}
        TclObject* create(int, const char*const*) {
	         return (new hierarchicalQueue);
	}
} class_hierarchical_queue;

void hierarchicalQueue::enque(Packet* p)
{
  hdr_ip* iph = hdr_ip::access(p);

  
  // if IPv6 priority = 15 enqueue to queue1
  if (iph->prio_ == 15) {
    q1_->enque(p);
    if ((q1_->length() + q2_->length()) > qlim_) {
      q1_->remove(p);
      drop(p);
    }
  }
  else {
    q2_->enque(p);
    if ((q1_->length() + q2_->length()) > qlim_) {
      q2_->remove(p);
      drop(p);
    }
  }
}


Packet* hierarchicalQueue::deque()
{
  Packet *p;
  
  if (deq_turn_ == 1) {
    p =  q1_->deque();
    if (p == 0) {
      p = q2_->deque();
      deq_turn_ = 1;
    }
    else {
      deq_turn_ = 2;
    }
  }
  else {
    p =  q2_->deque();
    if (p == 0) {
      p = q1_->deque();
      deq_turn_ = 2;
    }
    else {
      deq_turn_ = 1;
    }
  }
  
  return (p);
}
