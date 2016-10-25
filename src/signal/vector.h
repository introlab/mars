#ifndef __MARS_SIGNAL_VECTOR
#define __MARS_SIGNAL_VECTOR

    #include <stdlib.h>

    /**
    * \file     vector.h
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

    //! A structure that holds all the fields of a vector with signed char elements. 
    typedef struct vector_signedchar {

        signed char * array;        ///< Pointer to the array of elements.		 
        unsigned int nElements;     ///< Number of elements.

    } vector_signedchar;

    //! A structure that holds all the fields of a vector with unsigned char elements. 
    typedef struct vector_unsignedchar {

        unsigned char * array;      ///< Pointer to the array of elements.		 
        unsigned int nElements;     ///< Number of elements.

    } vector_unsignedchar;

    //! A structure that holds all the fields of a vector with signed short elements. 
    typedef struct vector_signedshort {

        signed short * array;       ///< Pointer to the array of elements.		 
        unsigned int nElements;     ///< Number of elements.

    } vector_signedshort;

    //! A structure that holds all the fields of a vector with unsigned short elements. 
    typedef struct vector_unsignedshort {

        unsigned short * array;     ///< Pointer to the array of elements.		 
        unsigned int nElements;     ///< Number of elements.

    } vector_unsignedshort;

    //! A structure that holds all the fields of a vector with signed int elements. 
    typedef struct vector_signedint {

        signed int * array;         ///< Pointer to the array of elements.		 
        unsigned int nElements;     ///< Number of elements.

    } vector_signedint;

    //! A structure that holds all the fields of a vector with unsigned int elements. 
    typedef struct vector_unsignedint {

        unsigned int * array;       ///< Pointer to the array of elements.		 
        unsigned int nElements;     ///< Number of elements.

    } vector_unsignedint;

    //! A structure that holds all the fields of a vector with float elements. 
    typedef struct vector_float {

        float * array;              ///< Pointer to the array of elements.		 
        unsigned int nElements;     ///< Number of elements.

    } vector_float;

    //! A structure that holds all the fields of a vector with double elements. 
    typedef struct vector_double {

        double * array;             ///< Pointer to the array of elements.		 
        unsigned int nElements;     ///< Number of elements.

    } vector_double;

    /** Constructor of the vector object.	
        \param      nElements   Number of elements.
        \return                 Pointer to the instantiated object.
    */
    vector_signedchar * vector_signedchar_malloc(const unsigned int nElements);

    /** Constructor of the vector object.	
        \param      nElements   Number of elements.
        \return                 Pointer to the instantiated object.
    */
    vector_unsignedchar * vector_unsignedchar_malloc(const unsigned int nElements);
    
    /** Constructor of the vector object.	
        \param      nElements   Number of elements.
        \return                 Pointer to the instantiated object.
    */
    vector_signedshort * vector_signedshort_malloc(const unsigned int nElements);

    /** Constructor of the vector object.	
        \param      nElements   Number of elements.
        \return                 Pointer to the instantiated object.
    */	
    vector_unsignedshort * vector_unsignedshort_malloc(const unsigned int nElements);

    /** Constructor of the vector object.	
        \param      nElements   Number of elements.
        \return                 Pointer to the instantiated object.
    */	
    vector_signedint * vector_signedint_malloc(const unsigned int nElements);

    /** Constructor of the vector object.	
        \param      nElements   Number of elements.
        \return                 Pointer to the instantiated object.
    */	
    vector_unsignedint * vector_unsignedint_malloc(const unsigned int nElements);

    /** Constructor of the vector object.	
        \param     nElements    Number of elements.
        \return                 Pointer to the instantiated object.
    */	
    vector_float * vector_float_malloc(const unsigned int nElements);

    /** Constructor of the vector object.	
        \param      nElements   Number of elements.
        \return                 Pointer to the instantiated object.
    */	
    vector_double * vector_double_malloc(const unsigned int nElements);

    /** Destructor of the vector object.
        \param      obj         Pointer to the instantiated object.
    */
    void vector_signedchar_free(vector_signedchar * obj);

    /** Destructor of the vector object.
        \param      obj         Pointer to the instantiated object.
    */
    void vector_unsignedchar_free(vector_unsignedchar * obj);

    /** Destructor of the vector object.
        \param      obj         Pointer to the instantiated object.
    */
    void vector_signedshort_free(vector_signedshort * obj);

    /** Destructor of the vector object.
        \param      obj         Pointer to the instantiated object.
	*/	
    void vector_unsignedshort_free(vector_unsignedshort * obj);

    /** Destructor of the vector object.
        \param      obj         Pointer to the instantiated object.
    */
    void vector_signedint_free(vector_signedint * obj);

    /** Destructor of the vector object.
        \param      obj         Pointer to the instantiated object.
    */
    void vector_unsignedint_free(vector_unsignedint * obj);

    /** Destructor of the vector object.
        \param      obj         Pointer to the instantiated object.
    */
    void vector_float_free(vector_float * obj);

    /** Destructor of the vector object.
        \param      obj         Pointer to the instantiated object.
    */
    void vector_double_free(vector_double * obj);

#endif