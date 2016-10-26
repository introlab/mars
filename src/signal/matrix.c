    
    #include "matrix.h"

    matrix_signedchar * matrix_signedchar_malloc(const unsigned int nRows, const unsigned int nCols) {

        matrix_signedchar * obj;
        unsigned int iRow;

        obj = (matrix_signedchar *) malloc(sizeof(matrix_signedchar));

        obj->array = (signed char **) malloc(sizeof(signed char *) * nRows);
        
        for (iRow = 0; iRow < nRows; iRow++) {
            obj->array[iRow] = (signed char *) malloc(sizeof(signed char) * nCols);
        }

        obj->nRows = nRows;
        obj->nCols = nCols;

        return obj;

    }

    matrix_unsignedchar * matrix_unsignedchar_malloc(const unsigned int nRows, const unsigned int nCols) {

        matrix_unsignedchar * obj;
        unsigned int iRow;

        obj = (matrix_unsignedchar *) malloc(sizeof(matrix_unsignedchar));

        obj->array = (unsigned char **) malloc(sizeof(unsigned char *) * nRows);
        
        for (iRow = 0; iRow < nRows; iRow++) {
            obj->array[iRow] = (unsigned char *) malloc(sizeof(unsigned char) * nCols);
        }

        obj->nRows = nRows;
        obj->nCols = nCols;

        return obj;

    }

    matrix_signedshort * matrix_signedshort_malloc(const unsigned int nRows, const unsigned int nCols) {

        matrix_signedshort * obj;
        unsigned int iRow;

        obj = (matrix_signedshort *) malloc(sizeof(matrix_signedshort));

        obj->array = (signed short **) malloc(sizeof(signed short *) * nRows);
        
        for (iRow = 0; iRow < nRows; iRow++) {
            obj->array[iRow] = (signed short *) malloc(sizeof(signed short) * nCols);
        }

        obj->nRows = nRows;
        obj->nCols = nCols;

        return obj;

    }

    matrix_unsignedshort * matrix_unsignedshort_malloc(const unsigned int nRows, const unsigned int nCols) {

        matrix_unsignedshort * obj;
        unsigned int iRow;

        obj = (matrix_unsignedshort *) malloc(sizeof(matrix_unsignedshort));

        obj->array = (unsigned short **) malloc(sizeof(unsigned short *) * nRows);
        
        for (iRow = 0; iRow < nRows; iRow++) {
            obj->array[iRow] = (unsigned short *) malloc(sizeof(unsigned short) * nCols);
        }

        obj->nRows = nRows;
        obj->nCols = nCols;

        return obj;

    }

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

    matrix_double * matrix_double_malloc(const unsigned int nRows, const unsigned int nCols) {

        matrix_double * obj;
        unsigned int iRow;

        obj = (matrix_double *) malloc(sizeof(matrix_double));

        obj->array = (double **) malloc(sizeof(double *) * nRows);
        
        for (iRow = 0; iRow < nRows; iRow++) {
            obj->array[iRow] = (double *) malloc(sizeof(double) * nCols);
        }

        obj->nRows = nRows;
        obj->nCols = nCols;

        return obj;

    }

    void matrix_signedchar_free(matrix_signedchar * obj) {

        unsigned int iRow;

        for (iRow = 0; iRow < obj->nRows; iRow++) {
            free((void *) obj->array[iRow]);
        }
        free((void *) obj->array);
        free((void *) obj);

    }

    void matrix_unsignedchar_free(matrix_unsignedchar * obj) {

        unsigned int iRow;

        for (iRow = 0; iRow < obj->nRows; iRow++) {
            free((void *) obj->array[iRow]);
        }
        free((void *) obj->array);
        free((void *) obj);

    }

    void matrix_signedshort_free(matrix_signedshort * obj) {

        unsigned int iRow;

        for (iRow = 0; iRow < obj->nRows; iRow++) {
            free((void *) obj->array[iRow]);
        }
        free((void *) obj->array);
        free((void *) obj);

    }

    void matrix_unsignedshort_free(matrix_unsignedshort * obj) {

        unsigned int iRow;

        for (iRow = 0; iRow < obj->nRows; iRow++) {
            free((void *) obj->array[iRow]);
        }
        free((void *) obj->array);
        free((void *) obj);

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

    void matrix_double_free(matrix_double * obj) {

        unsigned int iRow;

        for (iRow = 0; iRow < obj->nRows; iRow++) {
            free((void *) obj->array[iRow]);
        }
        free((void *) obj->array);
        free((void *) obj);

    }
