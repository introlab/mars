	
	#include "indexing.h"

	unsigned int indexing_wrap(const signed int index, const unsigned int arraySize) {

		unsigned int newIndex;

		if (index < 0) {

			newIndex = (unsigned int) (index + arraySize);

		}
		else {

			newIndex = (unsigned int) index;

		}

		return newIndex;

	}
