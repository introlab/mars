    
    #include "mixture.h"

    mixture_obj * mixture_construct_zero(const unsigned int S, const unsigned int T) {

        mixture_obj * obj;
        unsigned int iT;
        unsigned int iS;
        unsigned int iC;

        obj = (mixture_obj *) malloc(sizeof(mixture_obj));

        obj->assignations = combining_generate(S, T);

        obj->S = S;
        obj->T = T;
        obj->TND = T + 2;
        obj->C = obj->assignations->nSignals;
       
        obj->p_E_A = (float *) malloc(sizeof(float) * obj->S);
        obj->p_E_I = (float *) malloc(sizeof(float) * obj->S);
        obj->p_z_D = (float *) malloc(sizeof(float) * obj->S);

        for (iS = 0; iS < S; iS++) {

            obj->p_E_A[iS] = 0.0f;
            obj->p_E_I[iS] = 0.0f;
            obj->p_z_D[iS] = 0.0f;

        }

        obj->p_z_C = (float **) malloc(sizeof(float *) * obj->T);

        for (iT = 0; iT < obj->T; iT++) {

            obj->p_z_C[iT] = malloc(sizeof(float) * obj->S);

            for (iS = 0; iS < obj->S; iS++) {

                obj->p_z_C[iT][iS] = 0.0f;

            }

        }


        obj->p_Eszs_phics = (float **) malloc(sizeof(float *) * obj->S);
        obj->p_phics = (float **) malloc(sizeof(float *) * obj->S);

        for (iS = 0; iS < obj->S; iS++) {

            obj->p_Eszs_phics[iS] = (float *) malloc(sizeof(float) * obj->TND);
            obj->p_phics[iS] = (float *) malloc(sizeof(float) * obj->TND);

            for (iT = 0; iT < obj->TND; iT++) {

                obj->p_Eszs_phics[iS][iT] = 0.0f;
                obj->p_phics[iS][iT] = 0.0f;

            }

        }


        obj->p_Ez_phic = (float *) malloc(sizeof(float) * obj->C);
        obj->p_phic = (float *) malloc(sizeof(float) * obj->C);
        obj->p_phic_Ez = (float *) malloc(sizeof(float) * obj->C);

        for (iC = 0; iC < obj->C; iC++) {

            obj->p_Ez_phic[iC] = 0.0f;
            obj->p_phic[iC] = 0.0f;
            obj->p_phic_Ez[iC] = 0.0f;

        }

        return obj;

    }

    void mixture_destroy(mixture_obj * obj) {



    }

    void mixture_printf(const mixture_obj * obj) {

        unsigned int iS;
        unsigned int iT;
        unsigned int iCp;
        unsigned int iCs;
        unsigned int iC;

        printf("    s = ");

        for (iS = 0; iS < obj->S; iS++) {
            printf("   %01u   ",iS);
        }

        printf("\n");

        printf("p_E_A = ");

        for (iS = 0; iS < obj->S; iS++) {
            printf("%+1.3f ",obj->p_E_A[iS]);
        }

        printf("\n");

        printf("p_E_I = ");

        for (iS = 0; iS < obj->S; iS++) {
            printf("%+1.3f ",obj->p_E_I[iS]);
        }

        printf("\n");

        printf("\n");
        printf("p_z_C:\n\n");

        printf("        ");
        for (iS = 0; iS < obj->S; iS++) {
            printf(" s = %01u  ",iS);
        }

        printf("\n");

        for (iT = 0; iT < obj->T; iT++) {

            printf("t = %+01d ",((signed int) iT));

            for (iS = 0; iS < obj->S; iS++) {
                printf(" %+1.3f ",obj->p_z_C[iT][iS]);
            }

            printf("\n");

        }

        printf("\n");

        printf("p_z_D = ");

        for (iS = 0; iS < obj->S; iS++) {
            printf("%+1.3f ",obj->p_z_D[iS]);
        }

        printf("\n");

        printf("\n");
        printf("p_Eszs_phics:\n\n");

        printf("        ");
        for (iS = 0; iS < obj->S; iS++) {
            printf(" s = %01u  ",iS);
        }

        printf("\n");

        for (iT = 0; iT < obj->TND; iT++) {

            printf("t = %+01d ",((signed int) iT)-2);

            for (iS = 0; iS < obj->S; iS++) {
                printf(" %+1.3f ",obj->p_Eszs_phics[iS][iT]);
            }

            printf("\n");

        }

        printf("\n");
        printf("p_phics:\n\n");

        printf("        ");
        for (iS = 0; iS < obj->S; iS++) {
            printf(" s = %01u  ",iS);
        }

        printf("\n");

        for (iT = 0; iT < obj->TND; iT++) {

            printf("t = %+01d ",((signed int) iT)-2);

            for (iS = 0; iS < obj->S; iS++) {
                printf(" %+1.3f ",obj->p_phics[iS][iT]);
            }

            printf("\n");

        }

        printf("\n");
        printf("p_Ez_phic:\n\n");

        iC = 0;

        for (iCp = 0; iCp < (obj->C/obj->S); iCp++) {

            for (iCs = 0; iCs < obj->S; iCs++) {

                printf("(");

                for (iS = 0; iS < obj->S; iS++) {

                    printf("%+1d",obj->assignations->array[iC]->array[iS]);

                    if (iS != (obj->S-1)) {
                    	printf(",");
                    }

                }

                printf("): ");
            
                printf("%+1.3f - ",obj->p_Ez_phic[iC]);

                iC++;

            }

            printf("\n");

        }

        printf("\n");
        printf("p_phic:\n\n");

        iC = 0;

        for (iCp = 0; iCp < (obj->C/obj->S); iCp++) {

            for (iCs = 0; iCs < obj->S; iCs++) {

                printf("(");

                for (iS = 0; iS < obj->S; iS++) {

                    printf("%+1d",obj->assignations->array[iC]->array[iS]);

                    if (iS != (obj->S-1)) {
                    	printf(",");
                    }

                }

                printf("): ");
            
                printf("%+1.3f - ",obj->p_phic[iC]);

                iC++;

            }

            printf("\n");

        }

        printf("\n");
        printf("p_phic_Ez:\n\n");

        iC = 0;

        for (iCp = 0; iCp < (obj->C/obj->S); iCp++) {

            for (iCs = 0; iCs < obj->S; iCs++) {

                printf("(");

                for (iS = 0; iS < obj->S; iS++) {

                    printf("%+1d",obj->assignations->array[iC]->array[iS]);

                    if (iS != (obj->S-1)) {
                    	printf(",");
                    }

                }

                printf("): ");
            
                printf("%+1.3f - ",obj->p_phic_Ez[iC]);

                iC++;

            }

            printf("\n");

        }    

    }