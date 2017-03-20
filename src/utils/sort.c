
    #include "sort.h"
    #include <stdio.h>
    #include <stdlib.h>

    unsigned int sort_find(const float * arraySorted, const unsigned int nElements, const float valueToFind) {

        unsigned int lowerBound;
        unsigned int upperBound;
        unsigned int iElement;
        unsigned int iElementPrev;
        char compare;

        iElementPrev = 0;
        lowerBound = 0;
        upperBound = nElements;

        while(1) {

            iElement = (upperBound + lowerBound)/2;

            if (iElement == iElementPrev) {
                break;
            }

            iElementPrev = iElement;

            if (valueToFind < arraySorted[iElement]) {

                upperBound = iElement;

            }
            else {

                lowerBound = iElement;

            }

        }

        return upperBound;

    }

    void sort_merge(const float * arrayUnsorted, float * arraySorted, float * arrayWork, const unsigned int * indexUnsorted, unsigned int * indexSorted, unsigned int * indexWork, const unsigned int nElements) {

        unsigned int nElementsLeft;
        unsigned int nElementsRight;
        unsigned int iRow;

        nElementsLeft = nElements / 2;
        nElementsRight = nElements - nElementsLeft;

        if (nElementsLeft > 1) {

            sort_merge((const float *) &(arrayUnsorted[0]),
                       &(arraySorted[0]),
                       &(arrayWork[0]),
                       (const unsigned int *) &(indexUnsorted[0]),
                       &(indexSorted[0]),
                       &(indexWork[0]),
                       nElementsLeft);

        }
        else {

            arraySorted[0] = arrayUnsorted[0];
            indexSorted[0] = indexUnsorted[0];

        }
        if (nElementsRight > 1) {

            sort_merge((const float *) &(arrayUnsorted[nElementsLeft]),
                       &(arraySorted[nElementsLeft]),
                       &(arrayWork[nElementsLeft]),
                       (const unsigned int *) &(indexUnsorted[nElementsLeft]),
                       &(indexSorted[nElementsLeft]),
                       &(indexWork[0]),
                       nElementsRight);

        }
        else {

            arraySorted[nElementsLeft] = arrayUnsorted[nElementsLeft];
            indexSorted[nElementsLeft] = indexUnsorted[nElementsLeft];

        }

        sort_merge_conquer(arraySorted,
                           arrayWork,
                           indexSorted,
                           indexWork,
                           &(arraySorted[0]),
                           &(indexSorted[0]),
                           nElementsLeft,
                           &(arraySorted[nElementsLeft]),
                           &(indexSorted[nElementsLeft]),
                           nElementsRight);

    }

    void sort_merge_conquer(float * arraySorted, float * arrayWork, unsigned int * indexSorted, unsigned int * indexWork, const float * arraySortedLeft, const unsigned int * indexSortedLeft, const unsigned int nElementsLeft, const float * arraySortedRight, const unsigned int * indexSortedRight, const unsigned int nElementsRight) {

        unsigned int iElement;
        unsigned int nElements;
        unsigned int iElementLeft;
        unsigned int iElementRight;

        nElements = nElementsLeft + nElementsRight;

        iElementLeft = 0;
        iElementRight = 0;

        for (iElement = 0; iElement < nElements; iElement++) {

            if ((iElementLeft < nElementsLeft) && (iElementRight < nElementsRight)) {

                if (arraySortedLeft[iElementLeft] < arraySortedRight[iElementRight]) {

                    arrayWork[iElement] = arraySortedLeft[iElementLeft];
                    indexWork[iElement] = indexSortedLeft[iElementLeft];
                    iElementLeft++;

                }
                else {

                    arrayWork[iElement] = arraySortedRight[iElementRight];
                    indexWork[iElement] = indexSortedRight[iElementRight];
                    iElementRight++;

                }

            }
            else if ((iElementLeft < nElementsLeft) && (iElementRight >= nElementsRight)) {

                arrayWork[iElement] = arraySortedLeft[iElementLeft];
                indexWork[iElement] = indexSortedLeft[iElementLeft];
                iElementLeft++;
             
            }
            else if ((iElementLeft >= nElementsLeft) && (iElementRight < nElementsRight)) {

                arrayWork[iElement] = arraySortedRight[iElementRight];
                indexWork[iElement] = indexSortedRight[iElementRight];
                iElementRight++;

            }

        }

        memcpy(arraySorted,arrayWork,nElements*sizeof(float));
        memcpy(indexSorted,indexWork,nElements*sizeof(unsigned int));

    }