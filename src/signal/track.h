#ifndef __MARS_SIGNAL_TRACK
#define __MARS_SIGNAL_TRACK
    
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    typedef struct tracks_obj {

        unsigned int nTracks;
        unsigned long long * ids;
        float * array;
        
    } tracks_obj;

    tracks_obj * tracks_construct_zero(const unsigned int nTracks);

    void tracks_destroy(tracks_obj * obj);

    void tracks_printf(const tracks_obj * obj);

#endif