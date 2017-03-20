#ifndef __MARS_UTILS_SORT
#define __MARS_UTILS_SORT

    #include <string.h>

    unsigned int sort_find(const float * arraySorted, const unsigned int nElements, const float valueToFind);

    void sort_merge(const float * arrayUnsorted, float * arraySorted, float * arrayWork, const unsigned int * indexUnsorted, unsigned int * indexSorted, unsigned int * indexWork, const unsigned int nElements);

    void sort_merge_conquer(float * arraySorted, float * arrayWork, unsigned int * indexSorted, unsigned int * indexWork, const float * arraySortedLeft, const unsigned int * indexSortedLeft, const unsigned int nElementsLeft, const float * arraySortedRight, const unsigned int * indexSortedRight, const unsigned int nElementsRight);

#endif