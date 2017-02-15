    
    #include "lowpass.h"

    impulse_obj * lowpass_init_factor(const unsigned int factor) {

        impulse_obj * imp;

        switch (factor) {
            
            case 2:

                imp = impulse_construct(20);

                imp->array[0] = +0.03121650187000000f;
                imp->array[1] = +0.00259255667096523f;
                imp->array[2] = -0.04871760502801840f;
                imp->array[3] = -0.04242772708383730f;
                imp->array[4] = +0.02951582434738460f;
                imp->array[5] = +0.03446598729951020f;
                imp->array[6] = -0.07115238183061050f;
                imp->array[7] = -0.08715744745776130f;
                imp->array[8] = +0.15023718866150000f;
                imp->array[9] = +0.44199589797022000f;
                imp->array[10] = +0.44199589797022000f;
                imp->array[11] = +0.15023718866150000f;
                imp->array[12] = -0.08715744745776130f;
                imp->array[13] = -0.07115238183061050f;
                imp->array[14] = +0.03446598729951020f;
                imp->array[15] = +0.02951582434738460f;
                imp->array[16] = -0.04242772708383730f;
                imp->array[17] = -0.04871760502801840f;
                imp->array[18] = +0.00259255667096523f;
                imp->array[19] = +0.03121650187000000f;                

            break;

            case 3:

                imp = impulse_construct(20);

                imp->array[0] = +0.00554244859610514f;
                imp->array[1] = +0.04571757220979140f;
                imp->array[2] = +0.04153846196285300f;
                imp->array[3] = +0.01685010740788020f;
                imp->array[4] = -0.03281767941407700f;
                imp->array[5] = -0.06525670228564110f;
                imp->array[6] = -0.03491237098904920f;
                imp->array[7] = +0.07064770243098220f;
                imp->array[8] = +0.21015971579524900f;
                imp->array[9] = +0.30895093488774900f;
                imp->array[10] = +0.30895093488774900f;
                imp->array[11] = +0.21015971579524900f;
                imp->array[12] = +0.07064770243098220f;
                imp->array[13] = -0.03491237098904920f;
                imp->array[14] = -0.06525670228564110f;
                imp->array[15] = -0.03281767941407700f;
                imp->array[16] = +0.01685010740788020f;
                imp->array[17] = +0.04153846196285300f;
                imp->array[18] = +0.04571757220979140f;
                imp->array[19] = +0.00554244859610514f;

            break;

            default:

                printf("Invalid low pass cut off frequency\n");
                exit(EXIT_FAILURE);

            break;
        }

        return imp;

    }
