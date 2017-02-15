   
    #include "hop2hop.h"

    hop2hop_obj * hop2hop_construct_zero(const unsigned int nHops) {

        hop2hop_obj * obj;

        obj = (hop2hop_obj *) malloc(sizeof(hop2hop_obj));

        obj->nHops = nHops;

        return obj;

    }

    void hop2hop_destroy(hop2hop_obj * obj) {

        free((void *) obj);

    }

    void hop2hop_filter(const hop2hop_obj * obj, const hops_obj * hopsIn, impulse_obj * impulse, firs_obj * firs, hops_obj * hopsOut) {

        unsigned int iHop;
        unsigned int iSample;
        unsigned int iCoefficient;
        float y;

        for (iHop = 0; iHop < obj->nHops; iHop++) {

            for (iSample = 0; iSample < hopsIn->hopSize; iSample++) {

                memmove(&(firs->xs[iHop][1]), &(firs->xs[iHop][0]), sizeof(float) * (firs->nCoefficients-1));
                firs->xs[iHop][0] = hopsIn->array[iHop][iSample];

                y = 0.0f;

                for (iCoefficient = 0; iCoefficient < impulse->nCoefficients; iCoefficient++) {

                    y += impulse->array[iCoefficient] * firs->xs[iHop][iCoefficient];

                }

                hopsOut->array[iHop][iSample] = y;

            }

        }

    }

    void hop2hop_downsample(const hop2hop_obj * obj, const hops_obj * hopsIn, hops_obj * hopsOut) {

        unsigned int factor;
        unsigned int iHop;
        unsigned int iSampleIn;
        unsigned int iSampleOut;

        factor = hopsIn->hopSize / hopsOut->hopSize;

        for (iHop = 0; iHop < obj->nHops; iHop++) {

            for (iSampleOut = 0; iSampleOut < hopsOut->hopSize; iSampleOut++) {

                iSampleIn = iSampleOut * factor;

                hopsOut->array[iHop][iSampleOut] = hopsIn->array[iHop][iSampleIn];

            }

        }

    }

    void hop2hop_upsample(const hop2hop_obj * obj, const hops_obj * hopsIn, hops_obj * hopsOut) {

        unsigned int factor;
        unsigned int iHop;
        unsigned int iSampleIn;
        unsigned int iSampleOut;

        factor = hopsOut->hopSize / hopsIn->hopSize;

        for (iHop = 0; iHop < obj->nHops; iHop++) {

            memset(hopsOut->array[iHop], 0x00, sizeof(float) * hopsOut->hopSize);

            for (iSampleIn = 0; iSampleIn < hopsIn->hopSize; iSampleIn++) {

                iSampleOut = iSampleIn * factor;

                hopsOut->array[iHop][iSampleOut] = hopsIn->array[iHop][iSampleIn];

            }

        }

    }
