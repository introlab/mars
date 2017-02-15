    
    #include "lowpass.h"

    impulse_obj * lowpass_init_factor(const unsigned int factor) {

        impulse_obj * imp;

        switch (factor) {
            
            case 2:

                imp = impulse_construct(9);

                imp->array[0] = -0.06949739023630510f;
                imp->array[1] = +0.03815380641276960f;
                imp->array[2] = +0.14799145238264600f;
                imp->array[3] = +0.26458222629848500f;
                imp->array[4] = +0.31455211866466300f;
                imp->array[5] = +0.26458222629848500f;
                imp->array[6] = +0.14799145238264600f;
                imp->array[7] = +0.03815380641276960f;
                imp->array[8] = -0.06949739023630510f;                                    

            break;

            case 3:

                imp = impulse_construct(9);

                imp->array[0] = +0.01935034734158260f;
                imp->array[1] = -0.11953633515543500f;
                imp->array[2] = -0.00739117499036838f;
                imp->array[3] = +0.31295018832752800f;
                imp->array[4] = +0.50661918168905900f;
                imp->array[5] = +0.31295018832752800f;
                imp->array[6] = -0.00739117499036838f;
                imp->array[7] = -0.11953633515543500f;
                imp->array[8] = +0.01935034734158260f;

            break;

            default:

                printf("Invalid low pass cut off frequency\n");
                exit(EXIT_FAILURE);

            break;
        }

        return imp;

    }
