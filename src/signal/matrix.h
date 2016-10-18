#ifndef __MARS_SIGNAL_MATRIX
#define __MARS_SIGNAL_MATRIX

	#include <stdlib.h>

	//! \file matrix.h

	//! A structure that holds all the fields of a matrix with signed char elements. 
	typedef struct matrix_signedchar {

		signed char ** array; 		///< Pointer to the array of elements.		 
		unsigned int nRows;			///< Number of rows.
		unsigned int nCols; 		///< Number of columns.

	} matrix_signedchar;

	//! A structure that holds all the fields of a matrix with unsigned char elements. 
	typedef struct matrix_unsignedchar {

		unsigned char ** array; 	///< Pointer to the array of elements.		 
		unsigned int nRows;			///< Number of rows.
		unsigned int nCols;			///< Number of columns.

	} matrix_unsignedchar;

	//! A structure that holds all the fields of a matrix with signed short elements. 
	typedef struct matrix_signedshort {

		signed short ** array; 		///< Pointer to the array of elements.		 
		unsigned int nRows;			///< Number of rows.
		unsigned int nCols;			///< Number of columns.

	} matrix_signedshort;

	//! A structure that holds all the fields of a matrix with unsigned short elements. 
	typedef struct matrix_unsignedshort {

		unsigned short ** array; 	///< Pointer to the array of elements.		 
		unsigned int nRows;			///< Number of rows.
		unsigned int nCols;			///< Number of columns.

	} matrix_unsignedshort;

	//! A structure that holds all the fields of a matrix with signed int elements. 
	typedef struct matrix_signedint {

		signed int ** array; 		///< Pointer to the array of elements.		 
		unsigned int nRows;			///< Number of rows.
		unsigned int nCols;			///< Number of columns.

	} matrix_signedint;

	//! A structure that holds all the fields of a matrix with unsigned int elements. 
	typedef struct matrix_unsignedint {

		unsigned int ** array; 		///< Pointer to the array of elements.		 
		unsigned int nRows;			///< Number of rows.
		unsigned int nCols;			///< Number of columns.

	} matrix_unsignedint;

	//! A structure that holds all the fields of a matrix with float elements. 
	typedef struct matrix_float {

		float ** array;  			///< Pointer to the array of elements.		 
		unsigned int nRows;			///< Number of rows.
		unsigned int nCols;			///< Number of columns.

	} matrix_float;

	//! A structure that holds all the fields of a matrix with double elements. 
	typedef struct matrix_double {

		double ** array; 			///< Pointer to the array of elements.		 
		unsigned int nRows;			///< Number of rows.
		unsigned int nCols;			///< Number of columns.

	} matrix_double;

	/** Constructor of the vector object.	
		\param 		nRows	 	Number of rows.
		\param		nCols		Number of columns.
		\return					Pointer to the instantiated object.
	*/
	matrix_signedchar * matrix_signedchar_malloc(const unsigned int nRows, const unsigned int nCols);

	/** Constructor of the vector object.	
		\param 		nRows	 	Number of rows.
		\param		nCols		Number of columns.
		\return					Pointer to the instantiated object.
	*/
	matrix_unsignedchar * matrix_unsignedchar_malloc(const unsigned int nRows, const unsigned int nCols);
	
	/** Constructor of the vector object.	
		\param 		nRows	 	Number of rows.
		\param		nCols		Number of columns.
		\return					Pointer to the instantiated object.
	*/
	matrix_signedshort * matrix_signedshort_malloc(const unsigned int nRows, const unsigned int nCols);
	
	/** Constructor of the vector object.	
		\param 		nRows	 	Number of rows.
		\param		nCols		Number of columns.
		\return					Pointer to the instantiated object.
	*/	
	matrix_unsignedshort * matrix_unsignedshort_malloc(const unsigned int nRows, const unsigned int nCols);

	/** Constructor of the vector object.	
		\param 		nRows	 	Number of rows.
		\param		nCols		Number of columns.
		\return					Pointer to the instantiated object.
	*/	
	matrix_signedint * matrix_signedint_malloc(const unsigned int nRows, const unsigned int nCols);
	
	/** Constructor of the vector object.	
		\param 		nRows	 	Number of rows.
		\param		nCols		Number of columns.
		\return					Pointer to the instantiated object.
	*/
	matrix_unsignedint * matrix_unsignedint_malloc(const unsigned int nRows, const unsigned int nCols);

	/** Constructor of the vector object.	
		\param 		nRows	 	Number of rows.
		\param		nCols		Number of columns.
		\return					Pointer to the instantiated object.
	*/
	matrix_float * matrix_float_malloc(const unsigned int nRows, const unsigned int nCols);

	/** Constructor of the vector object.	
		\param 		nRows	 	Number of rows.
		\param		nCols		Number of columns.
		\return					Pointer to the instantiated object.
	*/
	matrix_double * matrix_double_malloc(const unsigned int nRows, const unsigned int nCols);

	/** Destructor of the vector object.
		\param		obj 		Pointer to the instantiated object.
	*/
	void matrix_signedchar_free(matrix_signedchar * obj);
	
	/** Destructor of the vector object.
		\param		obj 		Pointer to the instantiated object.
	*/
	void matrix_unsignedchar_free(matrix_unsignedchar * obj);

	/** Destructor of the vector object.
		\param		obj 		Pointer to the instantiated object.
	*/
	void matrix_signedshort_free(matrix_signedshort * obj);

	/** Destructor of the vector object.
		\param		obj 		Pointer to the instantiated object.
	*/
	void matrix_unsignedshort_free(matrix_unsignedshort * obj);

	/** Destructor of the vector object.
		\param		obj 		Pointer to the instantiated object.
	*/
	void matrix_signedint_free(matrix_signedint * obj);

	/** Destructor of the vector object.
		\param		obj 		Pointer to the instantiated object.
	*/
	void matrix_unsignedint_free(matrix_unsignedint * obj);

	/** Destructor of the vector object.
		\param		obj 		Pointer to the instantiated object.
	*/
	void matrix_float_free(matrix_float * obj);

	/** Destructor of the vector object.
		\param		obj 		Pointer to the instantiated object.
	*/
	void matrix_double_free(matrix_double * obj);

#endif