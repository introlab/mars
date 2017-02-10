    
    #include "track.h"

    tracks_obj * tracks_construct_zero(const unsigned int nTracks) {

        tracks_obj * obj;

        obj = (tracks_obj *) malloc(sizeof(tracks_obj));

        obj->nTracks = nTracks;
        obj->array = (float *) malloc(sizeof(float) * 3 * nTracks);
        memset(obj->array, 0x00, sizeof(float) * 3 * nTracks);
        obj->ids = (unsigned long long *) malloc(sizeof(unsigned long long) * nTracks);
        memset(obj->ids, 0x00, sizeof(unsigned long long) * nTracks);

        return obj;

    }

    void tracks_destroy(tracks_obj * obj) {

        free((void *) obj->array);
        free((void *) obj->ids);
        free((void *) obj);

    }

    void tracks_printf(const tracks_obj * obj) {

        unsigned int iTrack;

        for (iTrack = 0; iTrack < obj->nTracks; iTrack++) {

            printf("(%04llu): %+1.3f %+1.3f %+1.3f\n",
                   obj->ids[iTrack],
                   obj->array[iTrack * 3 + 0],
                   obj->array[iTrack * 3 + 1],
                   obj->array[iTrack * 3 + 2]);
            
        }


    }