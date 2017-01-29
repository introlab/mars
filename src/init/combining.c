
    #include "combining.h"

    assignations_obj * combining_generate(const unsigned int nPots, const unsigned int nTracks) {

        unsigned int nCombinations;
        unsigned int iCombination;
        unsigned int iPot;
        assignations_obj * obj;

        nCombinations = 1;

        for (iPot = 0; iPot < nPots; iPot++) {

            nCombinations *= (2+nTracks);

        }

        obj = assignations_construct_null(nCombinations);      

        obj->array[0] = assignation_construct_zero(nPots);
        for (iPot = 0; iPot < nPots; iPot++) {

            obj->array[0]->array[iPot] = -2;

        }


        for (iCombination = 1; iCombination < nCombinations; iCombination++) {

            obj->array[iCombination] = combining_increment(obj->array[iCombination-1],nTracks);

        }

        return obj;

    }

    assignation_obj * combining_increment(const assignation_obj * src, const unsigned int nTracks) {

        assignation_obj * obj;
        unsigned int iPot;
        signed int carry;

        obj = assignation_construct_assignation(src);

        carry = 1;

        for (iPot = 0; iPot < obj->nPots; iPot++) {

            obj->array[obj->nPots - iPot - 1] += carry;

            if (obj->array[obj->nPots - iPot - 1] == nTracks) {

            	obj->array[obj->nPots - iPot - 1] = -2;
            	carry = 1;

            }
            else {
            	
            	carry = 0;

            }

        }

        return obj;

    }