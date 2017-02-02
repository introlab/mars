
    #include "kalman2kalman.h"

    kalman2kalman_obj * kalman2kalman_construct(const float deltaT, const float sigmaQ, const float sigmaR, const float epsilon) {

        kalman2kalman_obj * obj;

        obj = (kalman2kalman_obj *) malloc(sizeof(kalman2kalman_obj));

        obj->deltaT = deltaT;
        obj->sigmaQ = sigmaQ;
        obj->sigmaR = sigmaR;
        obj->epsilon = epsilon;

        obj->F = matrix_construct_zero(6,6);
        obj->Ft = matrix_construct_zero(6,6);
        obj->Q = matrix_construct_zero(6,6);
        obj->H = matrix_construct_zero(3,6);
        obj->Ht = matrix_construct_zero(6,3);
        obj->R = matrix_construct_zero(3,3);

        obj->F->array[0][0] = 1.0f;
        obj->F->array[0][3] = deltaT;
        obj->F->array[1][1] = 1.0f;
        obj->F->array[1][4] = deltaT;
        obj->F->array[2][2] = 1.0f;
        obj->F->array[2][5] = deltaT;
        obj->F->array[3][3] = 1.0f;
        obj->F->array[4][4] = 1.0f;
        obj->F->array[5][5] = 1.0f;

        obj->Ft->array[0][0] = 1.0f;
        obj->Ft->array[3][0] = deltaT;
        obj->Ft->array[1][1] = 1.0f;
        obj->Ft->array[4][1] = deltaT;
        obj->Ft->array[2][2] = 1.0f;
        obj->Ft->array[5][2] = deltaT;
        obj->Ft->array[3][3] = 1.0f;
        obj->Ft->array[4][4] = 1.0f;
        obj->Ft->array[5][5] = 1.0f;

        obj->Q->array[3][3] = sigmaQ*sigmaQ;
        obj->Q->array[4][4] = sigmaQ*sigmaQ;
        obj->Q->array[5][5] = sigmaQ*sigmaQ;

        obj->H->array[0][0] = 1.0f;
        obj->H->array[1][1] = 1.0f;
        obj->H->array[2][2] = 1.0f;

        obj->Ht->array[0][0] = 1.0f;
        obj->Ht->array[1][1] = 1.0f;
        obj->Ht->array[2][2] = 1.0f;

        obj->R->array[0][0] = sigmaR*sigmaR;
        obj->R->array[1][1] = sigmaR*sigmaR;
        obj->R->array[2][2] = sigmaR*sigmaR;

        obj->FP = matrix_construct_zero(6,6);
        obj->FPFt = matrix_construct_zero(6,6);

        obj->K = matrix_construct_zero(6,3);
        obj->PHt = matrix_construct_zero(6,3);
        obj->HP = matrix_construct_zero(3,6);
        obj->HPHt = matrix_construct_zero(3,3);
        obj->HPHt_R = matrix_construct_zero(3,3);
        obj->HPHt_Rinv = matrix_construct_zero(3,3);
        obj->Hx = matrix_construct_zero(3,1);
        obj->z = matrix_construct_zero(3,1);
        obj->z_Hx = matrix_construct_zero(3,1);
        obj->Kz_Hx = matrix_construct_zero(6,1);
        obj->pKz_Hx = matrix_construct_zero(6,1);
        obj->KHP = matrix_construct_zero(6,6);
        obj->pKHP = matrix_construct_zero(6,6);

        return obj;

    }

    void kalman2kalman_destroy(kalman2kalman_obj * obj) {

        matrix_destroy(obj->F);
        matrix_destroy(obj->Ft);
        matrix_destroy(obj->Q);
        matrix_destroy(obj->H);
        matrix_destroy(obj->Ht);
        matrix_destroy(obj->R);

        free((void *) obj);

    }

    void kalman2kalman_init(kalman2kalman_obj * obj, const pot_obj * pot, kalman_obj * kalman) {

        matrix_copy_zero(kalman->x_llm1);
        matrix_copy_zero(kalman->x_lm1lm1);
        matrix_copy_zero(kalman->P_llm1);
        matrix_copy_zero(kalman->P_lm1lm1);

        kalman->P_lm1lm1->array[0][0] = obj->sigmaQ * obj->sigmaQ;
        kalman->P_lm1lm1->array[1][1] = obj->sigmaQ * obj->sigmaQ;
        kalman->P_lm1lm1->array[2][2] = obj->sigmaQ * obj->sigmaQ;
        kalman->P_lm1lm1->array[3][3] = obj->sigmaQ * obj->sigmaQ;
        kalman->P_lm1lm1->array[4][4] = obj->sigmaQ * obj->sigmaQ;
        kalman->P_lm1lm1->array[5][5] = obj->sigmaQ * obj->sigmaQ;

        kalman->x_lm1lm1->array[0][0] = pot->coord->x;
        kalman->x_lm1lm1->array[1][0] = pot->coord->y;
        kalman->x_lm1lm1->array[2][0] = pot->coord->z;

    }

    void kalman2kalman_predict(kalman2kalman_obj * obj, kalman_obj * kalman) {

        float xx, xy, xz;
        float vx, vy, vz;
        float norm, norm2, proj;

        matrix_mul(kalman->x_llm1, obj->F, kalman->x_lm1lm1);
        matrix_mul(obj->FP, obj->F, kalman->P_lm1lm1);
        matrix_mul(obj->FPFt, obj->FP, obj->Ft);
        matrix_add(kalman->P_llm1, obj->FPFt, obj->Q);

        xx = kalman->x_llm1->array[0][0];
        xy = kalman->x_llm1->array[1][0];
        xz = kalman->x_llm1->array[2][0];
        vx = kalman->x_llm1->array[3][0];
        vy = kalman->x_llm1->array[4][0];
        vz = kalman->x_llm1->array[5][0];

        norm2 = xx*xx + xy*xy + xz*xz;
        norm = sqrtf(norm2);
        proj = xx*vx + xy*vy + xz*vz;

        kalman->x_llm1->array[0][0] = xx / (norm + obj->epsilon);
        kalman->x_llm1->array[1][0] = xy / (norm + obj->epsilon);
        kalman->x_llm1->array[2][0] = xz / (norm + obj->epsilon);
        kalman->x_llm1->array[3][0] = vx - xx * proj / (norm2 + obj->epsilon);
        kalman->x_llm1->array[4][0] = vy - xy * proj / (norm2 + obj->epsilon);
        kalman->x_llm1->array[5][0] = vz - xz * proj / (norm2 + obj->epsilon);

    }

    void kalman2kalman_update(kalman2kalman_obj * obj, const postprob_obj * postprob, const pots_obj * pots, kalman_obj * kalman) {

        unsigned int iS;
        float maxValue;
        unsigned int maxIndex;
        float updateFactor;
        
        // Find potential source with max prob

        maxValue = postprob->probs[0];
        maxIndex = 0;

        for (iS = 1; iS < postprob->nPots; iS++) {

            if (maxValue < postprob->probs[iS]) {
                maxValue = postprob->probs[iS];
                maxIndex = iS;
            }

        }

        obj->z->array[0][0] = pots->array[maxIndex]->coord->x;
        obj->z->array[1][0] = pots->array[maxIndex]->coord->y;
        obj->z->array[2][0] = pots->array[maxIndex]->coord->z;

        // Compute K
        matrix_mul(obj->HP, obj->H, kalman->P_llm1);
        matrix_mul(obj->HPHt, obj->HP, obj->Ht);
        matrix_add(obj->HPHt_R, obj->HPHt, obj->R);
        matrix_inv(obj->HPHt_Rinv, obj->HPHt_R);
        matrix_mul(obj->PHt, kalman->P_llm1, obj->Ht);
        matrix_mul(obj->K, obj->PHt, obj->HPHt_Rinv);

        updateFactor = postprob->probTotal;

        // Update x
        matrix_mul(obj->Hx, obj->H, kalman->x_llm1);
        matrix_sub(obj->z_Hx, obj->z, obj->Hx);
        matrix_mul(obj->Kz_Hx, obj->K, obj->z_Hx);
        matrix_scale(obj->pKz_Hx, obj->Kz_Hx, updateFactor);
        matrix_add(kalman->x_lm1lm1, kalman->x_llm1, obj->pKz_Hx);


        // Update P
        matrix_mul(obj->KHP, obj->K, obj->HP);
        matrix_scale(obj->pKHP, obj->KHP, updateFactor);
        matrix_sub(kalman->P_lm1lm1, kalman->P_llm1, obj->pKHP);

    }

    void kalman2kalman_estimate(kalman2kalman_obj * obj, const kalman_obj * kalman, coord_obj * coord) {

        coord->x = kalman->x_lm1lm1->array[0][0];
        coord->y = kalman->x_lm1lm1->array[1][0];
        coord->z = kalman->x_lm1lm1->array[2][0];

    }