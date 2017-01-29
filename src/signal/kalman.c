
    #include "kalman.h"
    
    kalman_obj * kalman_construct_zero(void) {

        kalman_obj * obj;

        obj = (kalman_obj *) malloc(sizeof(kalman_obj));

        obj->x_lm1lm1 = matrix_construct_zero(6,1);
        obj->x_llm1 = matrix_construct_zero(6,1);
        obj->P_lm1lm1 = matrix_construct_zero(6,6);
        obj->P_llm1 = matrix_construct_zero(6,6);

        return obj;

    }

    void kalman_copy_kalman(kalman_obj * obj, const kalman_obj * src) {

        matrix_copy_matrix(obj->x_lm1lm1, src->x_lm1lm1);
        matrix_copy_matrix(obj->x_llm1, src->x_llm1);
        matrix_copy_matrix(obj->P_lm1lm1, src->P_lm1lm1);
        matrix_copy_matrix(obj->P_llm1, src->P_llm1);

    }

    void kalman_destroy(kalman_obj * obj) {

        matrix_destroy(obj->x_lm1lm1);
        matrix_destroy(obj->x_llm1);
        matrix_destroy(obj->P_lm1lm1);
        matrix_destroy(obj->P_llm1);

    }

    void kalman_printf(const kalman_obj * obj) {

        printf("x_lm1lm1:\n");
        matrix_printf(obj->x_lm1lm1);
        printf("x_llm1:\n");
        matrix_printf(obj->x_llm1);
        printf("P_lm1lm1:\n");
        matrix_printf(obj->P_lm1lm1);
        printf("P_llm1:\n");
        matrix_printf(obj->P_llm1);


    }