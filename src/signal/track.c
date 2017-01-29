    
    #include "track.h"

    track_obj * track_construct_zero(void) {

        track_obj * obj;

        obj = (track_obj *) malloc(sizeof(track_obj));

        obj->id = 0;
        obj->coord = coord_construct_zero();

        return obj;

    }

    track_obj * track_construct_idxyz(const unsigned long long id, const float x, const float y, const float z) {

        track_obj * obj;

        obj = (track_obj *) malloc(sizeof(track_obj));

        obj->id = id;
        obj->coord = coord_construct_xyz(x,y,z);

        return obj;

    }

    track_obj * track_construct_track(const track_obj * track) {

        track_obj * obj;

        obj = (track_obj *) malloc(sizeof(track_obj));

        obj->id = track->id;
        obj->coord = coord_construct_coord(track->coord);

        return obj;    

    }

    void track_copy_zero(track_obj * obj) {

        obj->id = 0;
        coord_copy_zero(obj->coord);

    }

    void track_copy_idxyz(track_obj * obj, const unsigned long long id, const float x, const float y, const float z) {

        obj->id = id;
        coord_copy_xyz(obj->coord, x, y, z);

    }

    void track_copy_track(track_obj * obj, const track_obj * track) {

        obj->id = track->id;
        coord_copy_coord(obj->coord,track->coord);

    }

    void track_destroy(track_obj * obj) {

        free((void *) obj);

    }

    void track_printf(track_obj * obj) {

        printf("%llu: (%+1.4f , %+1.4f , %+1.4f)\n", obj->id, obj->coord->x, obj->coord->y, obj->coord->z);

    }

    tracks_obj * tracks_construct_zero(const unsigned int nSignals) {

        tracks_obj * obj;
        unsigned int iSignal;

        obj = (tracks_obj *) malloc(sizeof(tracks_obj));

        obj->nSignals = nSignals;
        obj->array = (track_obj **) malloc(sizeof(track_obj *) * nSignals);

        for (iSignal = 0; iSignal < nSignals; iSignal++) {
            
            obj->array[iSignal] = track_construct_zero();

        }

        return obj;

    }

    void tracks_copy_zero(tracks_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            track_copy_zero(obj->array[iSignal]);

        }

    }

    void tracks_copy_tracks(tracks_obj * obj, const tracks_obj * tracks) {

        unsigned int iSignal;

        obj->nSignals = tracks->nSignals;

        for (iSignal = 0; iSignal < tracks->nSignals; iSignal++) {
            
            track_copy_track(obj->array[iSignal],tracks->array[iSignal]);

        }

    }

    void tracks_destroy(tracks_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {

            track_destroy(obj->array[iSignal]);

        }

    }

    void tracks_printf(tracks_obj * obj) {

        unsigned int iSignal;

        for (iSignal = 0; iSignal < obj->nSignals; iSignal++) {
            if (obj->array[iSignal] != NULL) {
                printf("%03u: %llu: (%+1.4f , %+1.4f , %+1.4f)\n", iSignal, obj->array[iSignal]->id, obj->array[iSignal]->coord->x, obj->array[iSignal]->coord->y, obj->array[iSignal]->coord->z);    
            }
            else {
                printf("%03u: (null)\n",iSignal);
            }
        }   

    }