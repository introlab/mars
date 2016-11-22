    
    #include "vector.h"

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

    int vector_signedint_copy(const vector_signedint * objSrc, vector_signedint * objDest) {

        memcpy(objDest->array,objSrc->array,sizeof(signed int) * objSrc->nElements);

    }

    int vector_unsignedint_copy(const vector_unsignedint * objSrc, vector_unsignedint * objDest) {

        memcpy(objDest->array,objSrc->array,sizeof(unsigned int) * objSrc->nElements);

    }

    int vector_float_copy(const vector_float * objSrc, vector_float * objDest) {

        memcpy(objDest->array,objSrc->array,sizeof(float) * objSrc->nElements);

    }

    vector_signedint * vector_signedint_clone(const vector_signedint * obj) {

        vector_signedint * objNew;

        objNew = vector_signedint_malloc(obj->nElements);

        vector_signedint_copy(obj, objNew);

        return objNew;

    }

    vector_unsignedint * vector_unsignedint_clone(const vector_unsignedint * obj) {

        vector_unsignedint * objNew;

        objNew = vector_unsignedint_malloc(obj->nElements);

        vector_unsignedint_copy(obj, objNew);

        return objNew;


    }

    vector_float * vector_float_clone(const vector_float * obj) {

        vector_float * objNew;

        objNew = vector_float_malloc(obj->nElements);

        vector_float_copy(obj, objNew);

        return objNew;

    }

    void vector_signedint_printf(const vector_signedint * obj) {

        unsigned int iElement;

        for (iElement = 0; iElement < obj->nElements; iElement++) {

            printf("(%03u): %+04d\n",iElement,obj->array[iElement]);

        }

    }

    void vector_unsignedint_printf(const vector_unsignedint * obj) {

        unsigned int iElement;

        for (iElement = 0; iElement < obj->nElements; iElement++) {

            printf("(%03u): %04u\n",iElement,obj->array[iElement]);

        }

    }

    void vector_float_printf(const vector_float * obj) {

        unsigned int iElement;

        for (iElement = 0; iElement < obj->nElements; iElement++) {

            printf("(%03u): %+02.2f\n",iElement,obj->array[iElement]);

        }

    }