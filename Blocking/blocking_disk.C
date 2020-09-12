/*
     File        : blocking_disk.c

     Author      : 
     Modified    : 

     Description : 

*/

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include "assert.H"
#include "utils.H"
#include "console.H"
#include "scheduler.H"
#include "blocking_disk.H"

/*--------------------------------------------------------------------------*/
/* EXTERNS */
/*--------------------------------------------------------------------------*/

extern Scheduler* SYSTEM_SCHEDULER;

/*--------------------------------------------------------------------------*/
/* CONSTRUCTOR */
/*--------------------------------------------------------------------------*/

BlockingDisk::BlockingDisk(DISK_ID _disk_id, unsigned int _size) 
  : SimpleDisk(_disk_id, _size) {
}

// Overriding SIMPLE_DISK's read/write functions: we need to simply push onto a new Queue and then yield.
void BlockingDisk::wait_until_ready() {
	/* Return true if disk is ready to transfer data from/to disk, false otherwise. */
	while (!SimpleDisk::is_ready()) { // While the disk is not ready, hold the system in yield.
		Thread* curr = Thread::CurrentThread();
		SYSTEM_SCHEDULER->add(curr); // Add to thread using Scheduler
		SYSTEM_SCHEDULER->yield(); // Yield thread in queue
	}
}

/*--------------------------------------------------------------------------*/
/* SIMPLE_DISK FUNCTIONS */
/*--------------------------------------------------------------------------*/

// This is redundant now, but just leaving in...

void BlockingDisk::read(unsigned long _block_no, unsigned char * _buf) {
  // Virtualization
  SimpleDisk::read(_block_no, _buf);
}


void BlockingDisk::write(unsigned long _block_no, unsigned char * _buf) {
  SimpleDisk::write(_block_no, _buf);
}
