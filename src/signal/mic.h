#ifndef __MARS_SIGNAL_MIC
#define __MARS_SIGNAL_MIC

    /**
    * \file     mic.h
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

    //! Microphone.
    typedef struct mic_obj {

        coord_obj * coord;          ///< Coordinates of the microphone.

    } mic_obj;

    //! Microphones.
    typedef struct mics_obj {

        unsigned int nSignals;      ///< Number of microphones.
        mic_obj ** array;           ///< List of microphones.

    } mics_obj;

    /** Constructor. Initialize all coordinates to zero.
        \return                     Pointer to the instantiated object.
    */  
    mic_obj * mic_construct_zero(void);

    /** Constructor. Initialize x, y and z.        
        \param      x               X-coordinate (meter).
        \param      y               Y-coordinate (meter).        
        \param      z               Z-coordinate (meter).        
        \return                     Pointer to the instantiated object.
    */  
    mic_obj * mic_construct_xyz(const float x, const float y, const float z);

    /** Constructor. Initialize from existing mic object.
        \param      mic             Object to be cloned.
        \return                     Pointer to the instantiated object.
    */  
    mic_obj * mic_construct_mic(const mic_obj * mic);

    /** Set all fields to zero. No memory allocated.
        \param      obj             Object to be reset.
    */  
    void mic_copy_zero(mic_obj * obj);

    /** Set the x, y and z fields. No memory allocated.
        \param      obj             Object to be set.
        \param      x               X-coordinate (meter).
        \param      y               Y-coordinate (meter).        
        \param      z               Z-coordinate (meter).        
    */  
    void mic_copy_xyz(mic_obj * obj, const float x, const float y, const float z);    

    /** Set the fields. No memory allocated.
        \param      mic             Object from which fields are to be copied.
        \param      obj             Object to which fiedls are to be copied.
    */  
    void mic_copy_mic(mic_obj * obj, const mic_obj * mic);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void mic_destroy(mic_obj * obj);

    /** Print the content of this object in the console.
        \param      obj             Object, which content is to be printed.
    */
    void mic_printf(mic_obj * obj);

    /** Constructor. Initialize the list of objects with null pointers.
        \param      nSignals        Number of microphones.
        \return                     Pointer to the instantiaed object.
    */
    mics_obj * mics_construct_null(const unsigned int nSignals);

    /** Constructor. Initialize the list of objects with instantiated objects with fields set to zero.
        \param      nSignals        Number of microphones.
    */
    mics_obj * mics_construct_zero(const unsigned int nSignals);

    /** Constructor. Initialize the list of objects with instantiated objects with fields set to values in mics.
        \param      mics            Microphones to copy.
    */
    mics_obj * mics_construct_mics(const mics_obj * mics);

    /** Set all fields to zero. No memory allocated.
        \param      obj             Object to be reset.
    */  
    void mics_copy_zero(mics_obj * obj);

    /** Set the fields. No memory allocated.
        \param      mics            Object from which fields are to be copied.
        \param      obj             Object to which fiedls are to be copied.
    */  
    void mics_copy_mics(mics_obj * obj, const mics_obj * mics);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void mics_destroy(mics_obj * obj);

    /** Print the content of this object in the console.
        \param      obj             Object, which content is to be printed.
    */
    void mics_printf(mics_obj * obj);

#endif