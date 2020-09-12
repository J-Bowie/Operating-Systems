/*
 File: scheduler.C
 
 Author:
 Date  :
 
 */

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include "scheduler.H"
#include "thread.H"
#include "console.H"
#include "utils.H"
#include "assert.H"
#include "simple_keyboard.H"

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* METHODS FOR CLASS   Q u e u e  */
/*--------------------------------------------------------------------------*/

Queue::Queue() { //Initialize Queue constructor
    thread = NULL;
    next = NULL;
    size = 0;	
}

Queue::Queue(Thread* _thread) { // Call new thread into Queue
    thread = _thread;
    next = NULL;	
}

unsigned int Queue::getSize() {
    return size;
}

void Queue::push(Thread* _thread) {
    if (!thread)
        thread = _thread;
	    
    else {
        if (!next)
	    next = new Queue(_thread);
	else
            next->push(_thread);			
    }
    size++;
}
	
Thread* Queue::pop() {
    if (!thread)
	return NULL;

    Thread* ret = thread;
    thread = next->thread;
  
    //Temporary Queue node to shift the linkedlist to the head so we can delete it
    Queue* tmp = next;
    next = next->next;
    delete tmp;
    
    return ret;
}

bool Queue::isEmpty() {
    return (size == 0);
}

/*--------------------------------------------------------------------------*/
/* METHODS FOR CLASS   S c h e d u l e r  */
/*--------------------------------------------------------------------------*/

Scheduler::Scheduler() {
    Console::puts("Constructed Scheduler.\n");
}

void Scheduler::yield() {
    Thread* thread = queue_list.pop();
    if (thread) // If the list is not empty, we will dispatch the next thread in queue and decrease queue list size
        Thread::dispatch_to(thread);  
    else
	Console::puts("ERROR: Need more threads");
}

void Scheduler::resume(Thread * _thread) {
    queue_list.push(_thread); // Simply push the thread onto queue
    Console::puts("Resumed thread");
}

void Scheduler::add(Thread * _thread) { // Similar to resume thread (we are just going to add to front of FIFO)
    queue_list.push(_thread);
    Console::puts("Created thread");
}

void Scheduler::terminate(Thread * _thread) {
    if (_thread)
	delete _thread; // Remove thread, and then yield the next thread in the queue
    yield();
}
