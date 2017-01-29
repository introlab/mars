#ifndef __MARS_SIGNAL_FRAME
#define __MARS_SIGNAL_FRAME

    /**
    * \file     frame.h
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

    //! Frame in the time-domain
    typedef struct frame_obj {

        unsigned int frameSize;     ///< Number of samples in the frame.
        float * array;              ///< Array with elements in the frame.

    } frame_obj;

    //! Frames in the time-domain
    typedef struct frames_obj {

        unsigned int nSignals;      ///< Number of frames.
        frame_obj ** array;         ///< List of frames.

    } frames_obj;

    /** Constructor. Initialize all elements to 0.
        \param      frameSize       Number of samples in the frame.
        \return                     Pointer to the instantiated object.
    */  
    frame_obj * frame_construct_zero(const unsigned int frameSize);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void frame_destroy(frame_obj * obj);

    /** Print the content of the object.
        \param      obj             Object to be used.
    */
    void frame_printf(const frame_obj * obj);

    /** Constructor. Fill the array of objects with null pointers.
        \param      nSignals        Number of frames.    
        \return                     Pointer to the instantiated object.
    */ 
    frames_obj * frames_construct_null(const unsigned int nSignals);

    /** Constructor. Fill the array of objects instantiated to zero.
        \param      nSignals        Number of frames.
        \param      frameSize       Number of samples per frame.
        \return                     Pointer to the instantiated object.
    */  
    frames_obj * frames_construct_zero(const unsigned int nSignals, const unsigned int frameSize);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void frames_destroy(frames_obj * obj);

    /** Print the content of the object.
        \param      obj             Object to be used.
    */
    void frames_printf(const frames_obj * obj);

#endif