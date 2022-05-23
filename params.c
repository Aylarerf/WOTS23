#include <stdint.h>
#include <string.h>

#include "params.h"



/**
 * Given a params struct where the following properties have been initialized;
 *  - full_height; the height of the complete (hyper)tree
 *  - n; the number of bytes of hash function output
 *  - func; one of {XMSS_SHA2, XMSS_SHAKE128, XMSS_SHAKE256}
 *  - wots_w; the Winternitz parameter
 *  - optionally, bds_k; the BDS traversal trade-off parameter,
 * this function initializes the remainder of the params structure.
 */
int wots_initialize_params(wots_params *params)
{
    
    if (params->wots_w == 4) {
        params->wots_log_w = 2;
        params->wots_len1 = 8 * params->n / params->wots_log_w;
        /* len_2 = floor(log(len_1 * (w - 1)) / log(w)) + 1 */
        params->wots_len2 = 5;
    }
    else if (params->wots_w == 16) {
        params->wots_log_w = 4;
        params->wots_len1 = 8 * params->n / params->wots_log_w;
        /* len_2 = floor(log(len_1 * (w - 1)) / log(w)) + 1 */
        params->wots_len2 = 3;
    }
    else if (params->wots_w == 256) {
        params->wots_log_w = 8;
        params->wots_len1 = 8 * params->n / params->wots_log_w;
        /* len_2 = floor(log(len_1 * (w - 1)) / log(w)) + 1 */
        params->wots_len2 = 2;
    }
    else {
        return -1;
    }
    params->wots_len = params->wots_len1 + params->wots_len2;
    params->wots_sig_bytes = params->wots_len * params->n;

    
  

    return 0;
}
