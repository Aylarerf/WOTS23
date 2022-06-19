#include <stdint.h>
#include <string.h>

#include "params.h"



/**
 * Given a params struct where the following properties have been initialized;
 *  - n; the number of bytes of hash function output
 *  - func; one of {XMSS_SHA2, XMSS_SHAKE128, XMSS_SHAKE256}
 *  - wots_w; the Winternitz parameter
 *  - optionally, bds_k; the BDS traversal trade-off parameter,
 * this function initializes the remainder of the params structure.
 */
int wots_initialize_params(wots_params *params)
{
    switch (oid) {
        case 0x00000021:
        case 0x00000022:
        case 0x00000023:
        case 0x00000024:
        case 0x00000025:
        case 0x00000026:
        case 0x00000027:
        case 0x00000028:

        case 0x00000031:
        case 0x00000032:
        case 0x00000033:
        case 0x00000034:
        case 0x00000035:
        case 0x00000036:
        case 0x00000037:
        case 0x00000038:
            params->n = 24;
            params->padding_len = 4;
            break;

    case 0x00000001:
        case 0x00000002:
        case 0x00000003:
        case 0x00000004:
        case 0x00000005:
        case 0x00000006:
        case 0x00000007:
        case 0x00000008:

        case 0x00000011:
        case 0x00000012:
        case 0x00000013:
        case 0x00000014:
        case 0x00000015:
        case 0x00000016:
        case 0x00000017:
        case 0x00000018:

        case 0x00000029:
        case 0x0000002a:
        case 0x0000002b:
        case 0x0000002c:
        case 0x0000002d:
        case 0x0000002e:
        case 0x0000002f:
        case 0x00000030:
            params->n = 32;
            params->padding_len = 32;
            break;
            case 0x00000009:
        case 0x0000000a:
        case 0x0000000b:
        case 0x0000000c:
        case 0x0000000d:
        case 0x0000000e:
        case 0x0000000f:
        case 0x00000010:

        case 0x00000019:
        case 0x0000001a:
        case 0x0000001b:
        case 0x0000001c:
        case 0x0000001d:
        case 0x0000001e:
        case 0x0000001f:
        case 0x00000020:
            params->n = 64;
            params->padding_len = 64;
            break;

        default:
            return -1;
    
    
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
