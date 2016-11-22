
    #include "minmax.h"

    unsigned int minmax_min_float(const float * elements, const unsigned int nElements) {

        float minValue;
        unsigned int minIndex;
        unsigned int iElement;

        minValue = elements[0];

        for (iElement = 0; iElement < nElements; iElement++) {

            if (elements[iElement] < minValue) {

                minValue = elements[iElement];
                minIndex = iElement;

            }

        }

        return minIndex;

    }

    unsigned int minmax_max_float(const float * elements, const unsigned int nElements) {

        float maxValue;
        unsigned int maxIndex;
        unsigned int iElement;

        maxValue = elements[0];
        maxIndex = 0;

        for (iElement = 0; iElement < nElements; iElement++) {

            if (elements[iElement] > maxValue) {

                maxValue = elements[iElement];
                maxIndex = iElement;

            }

        }

        return maxIndex;

    }

