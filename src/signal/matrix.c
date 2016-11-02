    
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

    matrix_signedint * matrix_signedint_copy(const matrix_signedint * obj) {

        matrix_signedint * objNew;
        unsigned int iRow;
        unsigned int iCol;

        objNew = matrix_signedint_malloc(obj->nRows, obj->nCols);

        for (iRow = 0; iRow < obj->nRows; iRow++) {

            for (iCol = 0; iCol < obj->nCols; iCol++) {

                objNew->array[iRow][iCol] = obj->array[iRow][iCol];

            }

        }

        return objNew;        

    }

    matrix_unsignedint * matrix_unsignedint_copy(const matrix_unsignedint * obj) {

        matrix_unsignedint * objNew;
        unsigned int iRow;
        unsigned int iCol;

        objNew = matrix_unsignedint_malloc(obj->nRows, obj->nCols);

        for (iRow = 0; iRow < obj->nRows; iRow++) {

            for (iCol = 0; iCol < obj->nCols; iCol++) {

                objNew->array[iRow][iCol] = obj->array[iRow][iCol];

            }

        }

        return objNew;       

    }

    matrix_float * matrix_float_copy(const matrix_float * obj) {

        matrix_float * objNew;
        unsigned int iRow;
        unsigned int iCol;

        objNew = matrix_float_malloc(obj->nRows, obj->nCols);

        for (iRow = 0; iRow < obj->nRows; iRow++) {

            for (iCol = 0; iCol < obj->nCols; iCol++) {

                objNew->array[iRow][iCol] = obj->array[iRow][iCol];

            }

        }

        return objNew;    

    }