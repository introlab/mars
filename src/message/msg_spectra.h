#ifndef __MARS_MESSAGE_SPECTRA
#define __MARS_MESSAGE_SPECTRA

    /**
    * \file     msg_spectra.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  1.0
    * \date     2016-10-25
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

    //! A structure that holds all the fields in a spectra. 
    typedef struct msg_spectra_obj {

        unsigned long long id;      ///< Time stamp

        unsigned int frameSize;     ///< Size of the frame.
        unsigned int halfFrameSize; ///< Size of the frame divided by 2 plus 1.
        unsigned int nMics;         ///< Number of microphones/channels.
        float ** samples;           ///< Samples.

    } msg_spectra_obj;

    /** Constructor of the vector object.   
        \param      frameSize   Size of a frame.
        \param      nMics       Number of microphones/channels.
        \return                 Pointer to the instantiated object.
    */  
    msg_spectra_obj * msg_spectra_construct(const unsigned int frameSize, const unsigned int nMics);

    /** Destructor of the vector object.
        \param      obj         Pointer to the instantiated object.
    */
    void msg_spectra_destroy(msg_spectra_obj * obj);

#endif