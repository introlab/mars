    
    #include "matrix.h"

    matrix_signedint * matrix_signedint_malloc(const unsigned int nRows, const unsigned int nCols) {

        matrix_signedint * obj;
        unsigned int iRow;

        obj = (matrix_signedint *) malloc(sizeof(matrix_signedint));

        obj->array = (signed int **) malloc(sizeof(signed int *) * nRows);
        
        for (iRow = 0; iRow < nRows; iRow++) {
            obj->array[iRow] = (signed int *) malloc(sizeof(signed int) * nCols);
        }

        obj->nRows = nRows;
        obj->nCols = nCols;

        return obj;

    }

    matrix_unsignedint * matrix_unsignedint_malloc(const unsigned int nRows, const unsigned int nCols) {

        matrix_unsignedint * obj;
        unsigned int iRow;

        obj = (matrix_unsignedint *) malloc(sizeof(matrix_unsignedint));

        obj->array = (unsigned int **) malloc(sizeof(unsigned int *) * nRows);
        
        for (iRow = 0; iRow < nRows; iRow++) {
            obj->array[iRow] = (unsigned int *) malloc(sizeof(unsigned int) * nCols);
        }

        obj->nRows = nRows;
        obj->nCols = nCols;

        return obj;

    }

    matrix_float * matrix_float_malloc(const unsigned int nRows, const unsigned int nCols) {

        matrix_float * obj;
        unsigned int iRow;

        obj = (matrix_float *) malloc(sizeof(matrix_float));

        obj->array = (float **) malloc(sizeof(float *) * nRows);
        
        for (iRow = 0; iRow < nRows; iRow++) {
            obj->array[iRow] = (float *) malloc(sizeof(float) * nCols);
        }

        obj->nRows = nRows;
        obj->nCols = nCols;

        return obj;

    }

    void matrix_signedint_free(matrix_signedint * obj) {

        unsigned int iRow;

        for (iRow = 0; iRow < obj->nRows; iRow++) {
            free((void *) obj->array[iRow]);
        }
        free((void *) obj->array);
        free((void *) obj);

    }

    void matrix_unsignedint_free(matrix_unsignedint * obj) {

        unsigned int iRow;

        for (iRow = 0; iRow < obj->nRows; iRow++) {
            free((void *) obj->array[iRow]);
        }
        free((void *) obj->array);
        free((void *) obj);

    }

    void matrix_float_free(matrix_float * obj) {

        unsigned int iRow;

        for (iRow = 0; iRow < obj->nRows; iRow++) {
            free((void *) obj->array[iRow]);
        }
        free((void *) obj->array);
        free((void *) obj);

    }

    int matrix_signedint_copy(const matrix_signedint * objSrc, matrix_signedint * objDest) {

        unsigned int iRow;

        for (iRow = 0; iRow < objSrc->nRows; iRow++) {
            memcpy(objDest->array[iRow],objSrc->array[iRow],sizeof(signed int) * objSrc->nCols);
        }

        return 0;

    }

    int matrix_unsignedint_copy(const matrix_unsignedint * objSrc, matrix_unsignedint * objDest) {

        unsigned int iRow;

        for (iRow = 0; iRow < objSrc->nRows; iRow++) {
            memcpy(objDest->array[iRow],objSrc->array[iRow],sizeof(unsigned int) * objSrc->nCols);
        }

        return 0;

    }

    int matrix_float_copy(const matrix_float * objSrc, matrix_float * objDest) {

        unsigned int iRow;

        for (iRow = 0; iRow < objSrc->nRows; iRow++) {
            memcpy(objDest->array[iRow],objSrc->array[iRow],sizeof(float) * objSrc->nCols);
        }

        return 0;

    }

    matrix_signedint * matrix_signedint_clone(const matrix_signedint * obj) {

        matrix_signedint * objNew;

        objNew = matrix_signedint_malloc(obj->nRows,obj->nCols);

        matrix_signedint_copy(obj, objNew);

        return objNew;

    }   

    matrix_unsignedint * matrix_unsignedint_clone(const matrix_unsignedint * obj) {

        matrix_unsignedint * objNew;

        objNew = matrix_unsignedint_malloc(obj->nRows,obj->nCols);

        matrix_unsignedint_copy(obj, objNew);

        return objNew;

    }    

    matrix_float * matrix_float_clone(const matrix_float * obj) {

        matrix_float * objNew;

        objNew = matrix_float_malloc(obj->nRows,obj->nCols);

        matrix_float_copy(obj, objNew);

        return objNew;

    }       

    int matrix_signedint_export(const matrix_signedint * objSrc, vector_signedint * objDest, unsigned int iRow) {

        memcpy(objDest->array, objSrc->array[iRow], sizeof(signed int) * objSrc->nCols);

    }

    int matrix_unsignedint_export(const matrix_unsignedint * objSrc, vector_unsignedint * objDest, unsigned int iRow) {

        memcpy(objDest->array, objSrc->array[iRow], sizeof(unsigned int) * objSrc->nCols);

    }

    int matrix_float_export(const matrix_float * objSrc, vector_float * objDest, unsigned int iRow) {

        memcpy(objDest->array, objSrc->array[iRow], sizeof(float) * objSrc->nCols);

    }

    int matrix_signedint_import(matrix_signedint * objDest, const vector_signedint * objSrc, unsigned int iRow) {

        memcpy(objDest->array[iRow], objSrc->array, sizeof(signed int) * objSrc->nElements);

    }

    int matrix_unsignedint_import(matrix_unsignedint * objDest, const vector_unsignedint * objSrc, unsigned int iRow) {

        memcpy(objDest->array[iRow], objSrc->array, sizeof(unsigned int) * objSrc->nElements);

    }

    int matrix_float_import(matrix_float * objDest, const vector_float * objSrc, unsigned int iRow) {

        memcpy(objDest->array[iRow], objSrc->array, sizeof(float) * objSrc->nElements);

    }

    int matrix_signedint_importexport(matrix_signedint * objDest, const matrix_signedint * objSrc, unsigned int iRowDest, unsigned int iRowSrc) {

        memcpy(objDest->array[iRowDest], objSrc->array[iRowSrc], sizeof(signed int) * objDest->nCols);

    }

    int matrix_unsignedint_importexport(matrix_unsignedint * objDest, const matrix_unsignedint * objSrc, unsigned int iRowDest, unsigned int iRowSrc) {

        memcpy(objDest->array[iRowDest], objSrc->array[iRowSrc], sizeof(unsigned int) * objDest->nCols);

    }

    int matrix_float_importexport(matrix_float * objDest, const matrix_float * objSrc, unsigned int iRowDest, unsigned int iRowSrc) {

        memcpy(objDest->array[iRowDest], objSrc->array[iRowSrc], sizeof(float) * objDest->nCols);

    }