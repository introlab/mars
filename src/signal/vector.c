	
	#include "vector.h"

	vector_signedchar * vector_signedchar_malloc(const unsigned int nElements) {

		vector_signedchar * obj;

		obj = (vector_signedchar *) malloc(sizeof(vector_signedchar));

		obj->array = (signed char *) malloc(sizeof(signed char) * nElements);
		obj->nElements = nElements;

		return obj;

	}
	
	vector_unsignedchar * vector_unsignedchar_malloc(const unsigned int nElements) {

		vector_unsignedchar * obj;

		obj = (vector_unsignedchar *) malloc(sizeof(vector_unsignedchar));

		obj->array = (unsigned char *) malloc(sizeof(unsigned char) * nElements);
		obj->nElements = nElements;

		return obj;

	}

	vector_signedshort * vector_signedshort_malloc(const unsigned int nElements) {

		vector_signedshort * obj;

		obj = (vector_signedshort *) malloc(sizeof(vector_signedshort));

		obj->array = (signed short *) malloc(sizeof(signed short) * nElements);
		obj->nElements = nElements;

		return obj;

	}

	vector_unsignedshort * vector_unsignedshort_malloc(const unsigned int nElements) {

		vector_unsignedshort * obj;

		obj = (vector_unsignedshort *) malloc(sizeof(vector_unsignedshort));

		obj->array = (unsigned short *) malloc(sizeof(unsigned short) * nElements);
		obj->nElements = nElements;

		return obj;

	}

	vector_signedint * vector_signedint_malloc(const unsigned int nElements) {

		vector_signedint * obj;

		obj = (vector_signedint *) malloc(sizeof(vector_signedint));

		obj->array = (signed int *) malloc(sizeof(signed int) * nElements);
		obj->nElements = nElements;

		return obj;

	}
	
	vector_unsignedint * vector_unsignedint_malloc(const unsigned int nElements) {

		vector_unsignedint * obj;

		obj = (vector_unsignedint *) malloc(sizeof(vector_unsignedint));

		obj->array = (unsigned int *) malloc(sizeof(unsigned int) * nElements);
		obj->nElements = nElements;

		return obj;

	}

	vector_float * vector_float_malloc(const unsigned int nElements) {

		vector_float * obj;

		obj = (vector_float *) malloc(sizeof(vector_float));

		obj->array = (float *) malloc(sizeof(float) * nElements);
		obj->nElements = nElements;

		return obj;

	}

	vector_double * vector_double_malloc(const unsigned int nElements) {

		vector_double * obj;

		obj = (vector_double *) malloc(sizeof(vector_double));

		obj->array = (double *) malloc(sizeof(double) * nElements);
		obj->nElements = nElements;

		return obj;

	}

	void vector_signedchar_free(vector_signedchar * obj) {

		free((void *) obj->array);
		free((void *) obj);

	}

	void vector_unsignedchar_free(vector_unsignedchar * obj) {

		free((void *) obj->array);
		free((void *) obj);

	}

	void vector_signedshort_free(vector_signedshort * obj) {

		free((void *) obj->array);
		free((void *) obj);

	}

	void vector_unsignedshort_free(vector_unsignedshort * obj) {

		free((void *) obj->array);
		free((void *) obj);

	}

	void vector_signedint_free(vector_signedint * obj) {

		free((void *) obj->array);
		free((void *) obj);

	}

	void vector_unsignedint_free(vector_unsignedint * obj){

		free((void *) obj->array);
		free((void *) obj);

	}

	void vector_float_free(vector_float * obj) {

		free((void *) obj->array);
		free((void *) obj);

	}

	void vector_double_free(vector_double * obj) {

		free((void *) obj->array);
		free((void *) obj);

	}