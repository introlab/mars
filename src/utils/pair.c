    
    #include "pair.h"

    unsigned int pair_nPairs(const unsigned int nMics) {

        return ((nMics-1)*nMics/2);

    }

    unsigned int pair_iPair(const unsigned int nMics, const unsigned int iMic1, const unsigned int iMic2) {

        return (nMics*iMic1 - (iMic1*iMic1+3*iMic1)/2 + iMic2 - 1);

    }