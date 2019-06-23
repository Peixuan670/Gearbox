//
// Author:    Jae Chung
// File:      dtrr-queue.cc
// Written:   07/19/99 (for ns-2.1b4a)
// Modifed:   10/14/01 (for ns-2.1b8a)
//

#include "try.h"

static class TryQueueClass : public TclClass {
public:
        TryQueueClass() : TclClass("Queue/TRY") {}
        TclObject* create(int, const char*const*) {
	         return (new TryQueue);
	}
} class_try_queue;


void TryQueue::enque(Packet* p)
{
  hdr_ip* iph = hdr_ip::access(p);

  // test print out
  fprintf(stderr, "Source IP address: %x\n", iph->saddr());

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


Packet* TryQueue::deque()
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
