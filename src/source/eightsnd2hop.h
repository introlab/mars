#ifndef __MARS_SOURCE_EIGHTSND2HOP
#define __MARS_SOURCE_EIGHTSND2HOP

    /**
    * \file     eightsnd2hop.h
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

    #include "../signal/vector.h"
    #include "../utils/fifo.h"
    #include <stdlib.h>
    #include <string.h>
    #include <alsa/asoundlib.h>
    #include <semaphore.h>
    #include <pthread.h>
    #include <limits.h>
    #include <math.h>

    //! A structure that holds all the fields to extract samples from a RAW file. 
    typedef struct eightsnd2hop_obj {

        unsigned int hopSize;               ///< Size of the hop.
        unsigned int nMics;                 ///< Number of microphones/channels.
        unsigned int sampleRate;            ///< Sample rate (samples/sec).
        char * sndCardName;                 ///< Name of the sound card.
        unsigned int nMaxElements;          ///< Maximum number of elements in the buffer.
        fifo_obj * bufferAvailable;         ///< Buffer with unused hops.
        fifo_obj * bufferFilled;            ///< Buffer with filled hops.
        snd_pcm_t * captureHandle;          ///< Structure to handle the sound card capture.
        sem_t semaphore;                    ///< Semaphore to count the elements in the buffer.
        pthread_t thread;                   ///< Thread to poll the soundcard.
        char state;                         ///< State (0 = not started, 1 = running).

    } eightsnd2hop_obj;

    /** Constructor of the eightsnd2hop object.	
        \param      hopSize     Number of samples per hop.
        \param      sampleRate  Sample rate (samples/sec).
        \param      sndCardName Name of the sound car.
        \return                 Pointer to the instantiated object.
    */
    eightsnd2hop_obj * eightsnd2hop_construct(const unsigned int hopSize, const unsigned int sampleRate, const char * sndCardName);

    /** Destructor of the eightsnd2hop object.
        \param      obj         Pointer to the instantiated object.
    */
    void eightsnd2hop_destroy(eightsnd2hop_obj * obj);

    /** Extract the next hop from the sound card and push samples in the hops
        \param      obj         Pointer to the instantiated object.
        \param      hops        Pointer to an array of hops vectors.
        \return                 Return -1 if there is an error, 0 otherwise.
    */
    int eightsnd2hop_process(eightsnd2hop_obj * obj, vector_float ** hops);

    /** Thread that polls the sound card continuously
        \param      dataPtr     Pointer to the instantiated object (casted in a void pointer).
        \return                 Return NULL if thread is stopped.
    */
    void * eightsnd2hop_thread( void * dataPtr );

#endif