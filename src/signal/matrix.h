#ifndef __MARS_SIGNAL_MATRIX
#define __MARS_SIGNAL_MATRIX

    #include <stdlib.h>

    /**
    * \file     matrix.h
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

    #include "vector.h"

    //! A structure that holds all the fields of a matrix with signed int elements. 
    typedef struct matrix_signedint {

        signed int ** array;        ///< Pointer to the array of elements.		 
        unsigned int nRows;         ///< Number of rows.
        unsigned int nCols;         ///< Number of columns.

    } matrix_signedint;

    //! A structure that holds all the fields of a matrix with unsigned int elements. 
    typedef struct matrix_unsignedint {

        unsigned int ** array;      ///< Pointer to the array of elements.		 
        unsigned int nRows;         ///< Number of rows.
        unsigned int nCols;         ///< Number of columns.

    } matrix_unsignedint;

    //! A structure that holds all the fields of a matrix with float elements. 
    typedef struct matrix_float {

        float ** array;             ///< Pointer to the array of elements.		 
        unsigned int nRows;         ///< Number of rows.
        unsigned int nCols;         ///< Number of columns.

    } matrix_float;

    /** Constructor of the vector object.	
        \param      nRows       Number of rows.
        \param      nCols       Number of columns.
        \return                 Pointer to the instantiated object.
    */	
    matrix_signedint * matrix_signedint_malloc(const unsigned int nRows, const unsigned int nCols);
	
    /** Constructor of the vector object.	
        \param      nRows       Number of rows.
        \param      nCols       Number of columns.
        \return                 Pointer to the instantiated object.
    */
    matrix_unsignedint * matrix_unsignedint_malloc(const unsigned int nRows, const unsigned int nCols);

    /** Constructor of the vector object.	
        \param      nRows       Number of rows.
        \param      nCols       Number of columns.
        \return                 Pointer to the instantiated object.
    */
    matrix_float * matrix_float_malloc(const unsigned int nRows, const unsigned int nCols);

    /** Destructor of the vector object.
        \param      obj         Pointer to the instantiated object.
    */
    void matrix_signedint_free(matrix_signedint * obj);

    /** Destructor of the vector object.
        \param      obj         Pointer to the instantiated object.
    */
    void matrix_unsignedint_free(matrix_unsignedint * obj);

    /** Destructor of the vector object.
        \param      obj         Pointer to the instantiated object.
    */
    void matrix_float_free(matrix_float * obj);

    /** Copy the matrix object.
        \param      objSrc      Pointer to the source object.
        \param      objDest     Pointer to the destination object.
        \return                 Return -1 if error, 0 otherwise.
    */
    int matrix_signedint_copy(const matrix_signedint * objSrc, matrix_signedint * objDest);    

    /** Copy the matrix object.
        \param      objSrc      Pointer to the source object.
        \param      objDest     Pointer to the destination object.
        \return                 Return -1 if error, 0 otherwise.
    */
    int matrix_unsignedint_copy(const matrix_unsignedint * objSrc, matrix_unsignedint * objDest);    

    /** Copy the matrix object.
        \param      objSrc      Pointer to the source object.
        \param      objDest     Pointer to the destination object.
        \return                 Return -1 if error, 0 otherwise.
    */
    int matrix_float_copy(const matrix_float * objSrc, matrix_float * objDest);    

    /** Copy the matrix object and generate a new object.
        \param      obj         Pointer to the source object.
        \return                 Pointer to the newly instantiated object.
    */
    matrix_signedint * matrix_signedint_clone(const matrix_signedint * obj);    

    /** Copy the matrix object and generate a new object.
        \param      obj         Pointer to the source object.
        \return                 Pointer to the newly instantiated object.
    */
    matrix_unsignedint * matrix_unsignedint_clone(const matrix_unsignedint * obj);    

    /** Copy the matrix object and generate a new object.
        \param      obj         Pointer to the source object.
        \return                 Pointer to the newly instantiated object.
    */
    matrix_float * matrix_float_clone(const matrix_float * obj);    

    /** Extract the vector at given row.
        \param      objSrc      Pointer to the source object.
        \param      objDest     Pointer to the destination object.
        \return                 Return -1 if error, 0 otherwise.
    */
    int matrix_signedint_export(const matrix_signedint * objSrc, vector_signedint * objDest, unsigned int iRow);

    /** Extract the vector at given row.
        \param      objSrc      Pointer to the source object.
        \param      objDest     Pointer to the destination object.
        \return                 Return -1 if error, 0 otherwise.
    */
    int matrix_unsignedint_export(const matrix_unsignedint * objSrc, vector_unsignedint * objDest, unsigned int iRow);

    /** Extract the vector at given row.
        \param      objSrc      Pointer to the source object.
        \param      objDest     Pointer to the destination object.
        \return                 Return -1 if error, 0 otherwise.
    */
    int matrix_float_export(const matrix_float * objSrc, vector_float * objDest, unsigned int iRow);

    int matrix_signedint_import(matrix_signedint * objDest, const vector_signedint * objSrc, unsigned int iRow);

    int matrix_unsignedint_import(matrix_unsignedint * objDest, const vector_unsignedint * objSrc, unsigned int iRow);

    int matrix_float_import(matrix_float * objDest, const vector_float * objSrc, unsigned int iRow);

    int matrix_signedint_importexport(matrix_signedint * objDest, const matrix_signedint * objSrc, unsigned int iRowDest, unsigned int iRowSrc);

    int matrix_unsignedint_importexport(matrix_unsignedint * objDest, const matrix_unsignedint * objSrc, unsigned int iRowDest, unsigned int iRowSrc);

    int matrix_float_importexport(matrix_float * objDest, const matrix_float * objSrc, unsigned int iRowDest, unsigned int iRowSrc);
    

#endif