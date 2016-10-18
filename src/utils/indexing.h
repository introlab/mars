#ifndef __MARS_UTILS_INDEXING
#define __MARS_UTILS_INDEXING

	//! \file indexing.h

	/** Wrap the index withing the positive range [0,N-1]
		\param 		index   	The index that is a signed integer
		\param 		arraySize   The size of the range (N)
		\return					Wrapped index
	*/
	unsigned int indexing_wrap(const signed int index, const unsigned int arraySize);

	/** Cycle the index withing the positive range [0,N/2+1]
		\param 		index   	The index that is a signed integer
		\param 		arraySize   The size of the range (N/2+1)
		\return					Cycled index
	*/
	unsigned int indexing_cycle(const signed int index, const unsigned int arraySize);

#endif