    
    #include <mars/mars.h>
    #include "parameters.h"

    src_raw_cfg * parameters2src_raw(const parameters_obj * obj);

    msg_hops_cfg * parameters2msg_hops(const parameters_obj * obj);

    mod_stft_cfg * parameters2mod_stft(const parameters_obj * obj);

    msg_spectra_cfg * parameters2msg_spectra(const parameters_obj * obj);

    mod_ssl_cfg * parameters2mod_ssl(const parameters_obj * obj);

    msg_pots_cfg * parameters2msg_pots(const parameters_obj * obj);

    snk_pots_cfg * parameters2snk_pots(const parameters_obj * obj);

    mod_sst_cfg * parameters2mod_sst(const parameters_obj * obj);

    msg_tracks_cfg * parameters2msg_tracks(const parameters_obj * obj);

    snk_tracks_cfg * parameters2snk_tracks(const parameters_obj * obj);