
    #include <stdlib.h>
    #include <stdio.h>

    #include <mars/mars.h>

    int main (int argc, char *argv[]) {

        normaloff_obj * normaloff;
        unsigned int iSample;
        float * values;

        values = (float *) malloc(sizeof(float) * 10);

        normaloff = normaloff_construct_rnd(1E-20, 1000);

        normaloff_generate(normaloff, 10, values);


    }