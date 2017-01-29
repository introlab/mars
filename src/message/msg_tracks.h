#ifndef __MARS_MESSAGE_TRACKS
#define __MARS_MESSAGE_TRACKS

    /**
    * \file     msg_tracks.h
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

    #include "../signal/track.h"

    //! Message that contains the tracked sources
    typedef struct msg_tracks_obj {

        unsigned long long timeStamp;           ///< Time stamp.

        tracks_obj * tracks;                    ///< List of tracked sources.

    } msg_tracks_obj;

    //! Configuration of the message that contains the tracked sources
    typedef struct msg_tracks_cfg {

        unsigned int nTracks;                   ///< Number of tracked sources.

    } msg_tracks_cfg;

    /** Constructor. Initialize all elements according to the configuration file.
        \param      cfg             Configuration.
        \return                     Pointer to the instantiated object.
    */  
    msg_tracks_obj * msg_tracks_construct(const msg_tracks_cfg * cfg);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void msg_tracks_destroy(msg_tracks_obj * obj);

    /** Constructor.
        \return                     Pointer to the instantiated object.
    */ 
    msg_tracks_cfg * msg_tracks_cfg_construct(void);

    /** Destructor. Free memory.
        \param      cfg             Object to be destroyed.
    */
    void msg_tracks_cfg_destroy(msg_tracks_cfg * cfg);

#endif