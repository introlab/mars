#ifndef __MARS_GENERAL_FILE2PARAMETERS
#define __MARS_GENERAL_FILE2PARAMETERS

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <libconfig.h>

    #include "parameters.h"

    void file2parameters(parameters * params, const char * fileName);

#endif