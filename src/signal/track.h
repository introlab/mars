#ifndef __MARS_SIGNAL_TRACK
#define __MARS_SIGNAL_TRACK
    
    /**
    * \file     track.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2017-01-25
    * \copyright
    *
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    *
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
    * 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <http://www.gnu.org/licenses/>.
    *
    */

    #include <stdlib.h>
    #include <stdio.h>

    #include "../utils/coord.h"

    //! Tracked source
    typedef struct track_obj {

        unsigned long long id;          ///< Source unique ID.
        coord_obj * coord;              ///< Coordinates of the source.

    } track_obj;

    //! Tracked sources
    typedef struct tracks_obj {

        unsigned int nSignals;          ///< Number of tracked sources (some may be empty with ID = 0).
        track_obj ** array;             ///< List of tracked sources.

    } tracks_obj;

    /** Constructor. Initialize all coordinates and energy to zero.
        \return                     Pointer to the instantiated object.
    */  
    track_obj * track_construct_zero(void);


    /** Constructor. Initialize id, x, y and z.        
        \param      id              ID.
        \param      x               X-coordinate (meter).
        \param      y               Y-coordinate (meter).        
        \param      z               Z-coordinate (meter).    
        \return                     Pointer to the instantiated object.
    */  
    track_obj * track_construct_idxyz(const unsigned long long id, const float x, const float y, const float z);

    /** Constructor. Clone the object.
        \param      track           Object to be cloned.
        \return                     Pointer to the instantiated object.
    */  
    track_obj * track_construct_track(const track_obj * track);

    /** Set all fields to zero. No memory allocated.
        \param      obj             Object to be reset.
    */  
    void track_copy_zero(track_obj * obj);

    /** Set the id, x, y, and z fields. No memory allocated.
        \param      obj             Object to be set.
        \param      id              ID.
        \param      x               X-coordinate (meter).
        \param      y               Y-coordinate (meter).        
        \param      z               Z-coordinate (meter).        
    */  
    void track_copy_idxyz(track_obj * obj, const unsigned long long id, const float x, const float y, const float z);    

    /** Set the fields. No memory allocated.
        \param      track           Object from which fields are to be copied.
        \param      obj             Object to which fields are to be copied.
    */  
    void track_copy_track(track_obj * obj, const track_obj * track);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void track_destroy(track_obj * obj);

    /** Print the content of this object in the console.
        \param      obj             Object, which content is to be printed.
    */
    void track_printf(track_obj * obj);

    /** Constructor. Initialize the list of objects with instantiated points.
        \param      nSignals        Number of potential sources.
        \return                     Pointer to the instantiaed object.
    */
    tracks_obj * tracks_construct_zero(const unsigned int nSignals);

    /** Set the fields to zero. No memory allocated.
        \param      obj             Object to be modified.
    */  
    void tracks_copy_zero(tracks_obj * obj);

    /** Set the fields. No memory allocated.
        \param      tracks          Object from which fields are to be copied.
        \param      obj             Object to which fields are to be copied.
    */  
    void tracks_copy_tracks(tracks_obj * obj, const tracks_obj * tracks);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void tracks_destroy(tracks_obj * obj);

    /** Print the content of this object in the console.
        \param      obj             Object, which content is to be printed.
    */
    void tracks_printf(tracks_obj * obj);    

#endif