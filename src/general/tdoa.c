
	#include "tdoa.h"
	
	matrix_float * tdoa_delay(const matrix_float * points, const matrix_float * mics, const unsigned int fS, const float c) {

		unsigned int iMic1;
		unsigned int iMic2;
		unsigned int iPoint;
		unsigned int iPair;
		unsigned int iDim;
		
		unsigned int nPairs;

		float dist1, dist2;
		float dist12;
		matrix_float * tdoas;

		nPairs = (unsigned int) (mics->nRows * (mics->nRows-1) / 2);

		tdoas = matrix_float_malloc(points->nRows,nPairs);

		for (iPoint = 0; iPoint < points->nRows; iPoint++) {

			iPair = 0;

			for (iMic1 = 0; iMic1 < mics->nRows; iMic1++) {

				dist1 = 0.0f;

				for (iDim = 0; iDim < 3; iDim++) {

					dist1 += (mics->array[iMic1][iDim] - points->array[iPoint][iDim]) * (mics->array[iMic1][iDim] - points->array[iPoint][iDim]);

				}

				dist1 = sqrtf(dist1);

				for (iMic2 = (iMic1+1); iMic2 < mics->nRows; iMic2++) {

					dist2 = 0.0f;

					for (iDim = 0; iDim < 3; iDim++) {

						dist2 += (mics->array[iMic2][iDim] - points->array[iPoint][iDim]) * (mics->array[iMic2][iDim] - points->array[iPoint][iDim]);

					}

					dist2 = sqrtf(dist2);

					dist12 = dist1-dist2;

					tdoas->array[iPoint][iPair] = dist12 * (((float) fS)/c);

					iPair++;

				}

			}

		}

		return tdoas;		

	}

	matrix_signedint * tdoa_round(const matrix_float * tdoas) {

		matrix_signedint * tdoasRounded;
		
		unsigned int iPoint;
		unsigned int iPair;

		tdoasRounded = matrix_signedint_malloc(tdoas->nRows, tdoas->nCols);
		
		for (iPoint = 0; iPoint < tdoas->nRows; iPoint++) {

			for (iPair = 0; iPair < tdoas->nCols; iPair++) {

				tdoasRounded->array[iPoint][iPair] = (signed int) roundf(tdoas->array[iPoint][iPair]);

			}

		}

		return tdoasRounded;

	}

	matrix_unsignedint * tdoa_wrap(const matrix_signedint * tdoas, const unsigned int frameSize) {

        matrix_unsignedint * tdoasWrapped;

        unsigned int iPoint;
        unsigned int iPair;

        tdoasWrapped = matrix_unsignedint_malloc(tdoas->nRows, tdoas->nCols);

        for (iPoint = 0; iPoint < tdoas->nRows; iPoint++) {

            for (iPair = 0; iPair < tdoas->nCols; iPair++) {

                tdoasWrapped->array[iPoint][iPair] = (unsigned int) indexing_wrap(tdoas->array[iPoint][iPair], frameSize);

            }

        }

        return tdoasWrapped;

	}