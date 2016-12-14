
    #include "sort.h"

    #include <stdio.h>

    unsigned int sort_ascend_unsignedint(unsigned int * elementsDest, unsigned int * indexesDest, const unsigned int * elementsSrc, const unsigned int nElements) {

        unsigned int iElement;
        unsigned char swapped;
        unsigned int element;
        unsigned int index;

        for (iElement = 0; iElement < nElements; iElement++) {

            elementsDest[iElement] = elementsSrc[iElement];
            indexesDest[iElement] = iElement;

        }

        do {        

            swapped = 0;

	        for (iElement = 0; iElement < (nElements-1); iElement++) {

                if (elementsDest[iElement+1] < elementsDest[iElement]) {

                    element = elementsDest[iElement];
                    index = indexesDest[iElement];

                    elementsDest[iElement] = elementsDest[iElement+1];
                    elementsDest[iElement+1] = element;
                    indexesDest[iElement] = indexesDest[iElement+1];
                    indexesDest[iElement+1] = index;

                    swapped = 1;

                }

	        }

        } while (swapped == 1);

        return 0;

    }