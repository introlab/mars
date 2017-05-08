    
    #include "name.h"

    int name_check_file_raw(const char * str) {

        regex_t reg;
        regmatch_t match;
        int rtnValue;

        regcomp(&reg, ".raw$", REG_EXTENDED);
        rtnValue = regexec(&reg, str, 1, &match, 0);
        regfree(&reg);

        return rtnValue;

    }

    int name_check_file_wav(const char * str) {

        regex_t reg;
        regmatch_t match;
        int rtnValue;

        regcomp(&reg, ".wav$", REG_EXTENDED);
        rtnValue = regexec(&reg, str, 1, &match, 0);
        regfree(&reg);

        return rtnValue;

    }

    int name_check_file_cfg(const char * str) {

        regex_t reg;
        regmatch_t match;
        int rtnValue;

        regcomp(&reg, ".cfg$", REG_EXTENDED);
        rtnValue = regexec(&reg, str, 1, &match, 0);
        regfree(&reg);

        return rtnValue;

    }

    int name_check_file_spectrabin(const char * str) {

        regex_t reg;
        regmatch_t match;
        int rtnValue;

        regcomp(&reg, ".spectra.bin$", REG_EXTENDED);
        rtnValue = regexec(&reg, str, 1, &match, 0);
        regfree(&reg);

        return rtnValue;

    }

    int name_check_file_xcsbin(const char * str) {

        regex_t reg;
        regmatch_t match;
        int rtnValue;

        regcomp(&reg, ".xcs.bin$", REG_EXTENDED);
        rtnValue = regexec(&reg, str, 1, &match, 0);
        regfree(&reg);

        return rtnValue;

    }

    int name_check_file_potbin(const char * str) {

        regex_t reg;
        regmatch_t match;
        int rtnValue;

        regcomp(&reg, ".pot.bin$", REG_EXTENDED);
        rtnValue = regexec(&reg, str, 1, &match, 0);
        regfree(&reg);

        return rtnValue;

    }

    int name_check_file_potxml(const char * str) {

        regex_t reg;
        regmatch_t match;
        int rtnValue;

        regcomp(&reg, ".pot.xml$", REG_EXTENDED);
        rtnValue = regexec(&reg, str, 1, &match, 0);
        regfree(&reg);

        return rtnValue;

    }

    int name_check_file_trackbin(const char * str) {

        regex_t reg;
        regmatch_t match;
        int rtnValue;

        regcomp(&reg, ".track.bin$", REG_EXTENDED);
        rtnValue = regexec(&reg, str, 1, &match, 0);
        regfree(&reg);

        return rtnValue;

    }

    int name_check_file_trackxml(const char * str) {

        regex_t reg;
        regmatch_t match;
        int rtnValue;

        regcomp(&reg, ".track.xml$", REG_EXTENDED);
        rtnValue = regexec(&reg, str, 1, &match, 0);
        regfree(&reg);

        return rtnValue;

    }

    int name_check_file_trackjson(const char * str) {

        regex_t reg;
        regmatch_t match;
        int rtnValue;

        regcomp(&reg, ".track.json$", REG_EXTENDED);
        rtnValue = regexec(&reg, str, 1, &match, 0);
        regfree(&reg);

        return rtnValue;

    }    

    int name_check_ipv4_raw(const char * str) {

        regex_t reg;
        regmatch_t match;
        int rtnValue;

        regcomp(&reg, "^[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}:[0-9]{1,5}.raw$", REG_EXTENDED);
        rtnValue = regexec(&reg, str, 1, &match, 0);
        regfree(&reg);

        return rtnValue;

    }

    int name_check_ipv4_potxml(const char * str) {

        regex_t reg;
        regmatch_t match;
        int rtnValue;

        regcomp(&reg, "^[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}:[0-9]{1,5}.pot.xml$", REG_EXTENDED);
        rtnValue = regexec(&reg, str, 1, &match, 0);
        regfree(&reg);

        return rtnValue;

    }

    int name_check_ipv4_trackxml(const char * str) {

        regex_t reg;
        regmatch_t match;
        int rtnValue;

        regcomp(&reg, "^[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}:[0-9]{1,5}.track.xml$", REG_EXTENDED);
        rtnValue = regexec(&reg, str, 1, &match, 0);
        regfree(&reg);

        return rtnValue;

    }

    int name_check_ipv4_trackjson(const char * str) {

        regex_t reg;
        regmatch_t match;
        int rtnValue;

        regcomp(&reg, "^[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}:[0-9]{1,5}.track.json$", REG_EXTENDED);
        rtnValue = regexec(&reg, str, 1, &match, 0);
        regfree(&reg);

        return rtnValue;

    }    

    int name_check_hw(const char * str) {

        regex_t reg;
        regmatch_t match;
        int rtnValue;

        regcomp(&reg, "^hw:[0-9]{1},[0-9]{1}$", REG_EXTENDED);
        rtnValue = regexec(&reg, str, 1, &match, 0);
        regfree(&reg);

        return rtnValue;

    }

    int name_check_plughw(const char * str) {

        regex_t reg;
        regmatch_t match;
        int rtnValue;

        regcomp(&reg, "^plughw:[0-9]{1},[0-9]{1}$", REG_EXTENDED);
        rtnValue = regexec(&reg, str, 1, &match, 0);
        regfree(&reg);

        return rtnValue;

    }
