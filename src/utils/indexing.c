    
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

    unsigned int indexing_cycle(const signed int index, const unsigned int arraySize) {

        signed int newIndex;

        if (index > 0) {
            newIndex = index;
        }
        else {
            newIndex = -1 * index;
        }
            
        newIndex %= 2*(arraySize-1);

        if ((newIndex+1) > arraySize) {
            newIndex = 2*(arraySize-1) - newIndex;
        }

        return ((unsigned int) newIndex);

    }