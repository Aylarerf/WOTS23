#include <stdint.h>
#include <string.h>
#include "params.h"

#define n 32



/**
 * Given a params struct where the following properties have been initialized;
 *  - n; the number of bytes of hash function output

 *  - wots_w; the Winternitz parameter
 * this function initializes the remainder of the params structure.
 */

int wots_initialize_params(wots_params *params)
{
    
    if (params->wots_w == 16) {
        params->wots_log_w = 4;
        params->wots_len1 = 8 * params->n / params->wots_log_w;
        /* len_2 = floor(log(len_1 * (w - 1)) / log(w)) + 1 */
        params->wots_len2 = 3;
    }
  
    params->wots_len = params->wots_len1 + params->wots_len2;
    params->wots_sig_bytes = params->wots_len * params->n;

    
    
