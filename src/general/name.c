    
    #include "name.h"

    int name_check_file_raw(const char * str) {

        regex_t reg;
        regmatch_t match;

        regcomp(&reg, ".raw$", REG_EXTENDED);
        return regexec(&reg, str, 1, &match, 0);

    }

    int name_check_file_wav(const char * str) {

        regex_t reg;
        regmatch_t match;

        regcomp(&reg, ".wav$", REG_EXTENDED);
        return regexec(&reg, str, 1, &match, 0);

    }

    int name_check_file_cfg(const char * str) {

        regex_t reg;
        regmatch_t match;

        regcomp(&reg, ".cfg$", REG_EXTENDED);
        return regexec(&reg, str, 1, &match, 0);

    }

    int name_check_file_potbin(const char * str) {

        regex_t reg;
        regmatch_t match;

        regcomp(&reg, ".pot.bin$", REG_EXTENDED);
        return regexec(&reg, str, 1, &match, 0);

    }

    int name_check_file_potxml(const char * str) {

        regex_t reg;
        regmatch_t match;

        regcomp(&reg, ".pot.xml$", REG_EXTENDED);
        return regexec(&reg, str, 1, &match, 0);

    }

    int name_check_file_trackbin(const char * str) {

        regex_t reg;
        regmatch_t match;

        regcomp(&reg, ".track.bin$", REG_EXTENDED);
        return regexec(&reg, str, 1, &match, 0);

    }

    int name_check_file_trackxml(const char * str) {

        regex_t reg;
        regmatch_t match;

        regcomp(&reg, ".track.xml$", REG_EXTENDED);
        return regexec(&reg, str, 1, &match, 0);

    }

    int name_check_ipv4(const char * str) {

        regex_t reg;
        regmatch_t match;

        regcomp(&reg, "^[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}:[0-9]{1,5}$", REG_EXTENDED);
        return regexec(&reg, str, 1, &match, 0);

    }

    int name_check_hw(const char * str) {

        regex_t reg;
        regmatch_t match;

        regcomp(&reg, "^hw:[0-9]{1},[0-9]{1}$", REG_EXTENDED);
        return regexec(&reg, str, 1, &match, 0);

    }