#ifndef XMSS_PARAMS_H
#define XMSS_PARAMS_H

#include <stdint.h>

/* These are merely internal identifiers for the supported hash functions. */
#define XMSS_SHA2 0
#define XMSS_SHAKE128 1
#define XMSS_SHAKE256 2

/* This is a result of the OID definitions in the draft; needed for parsing. */
#define XMSS_OID_LEN 4


typedef struct {
    unsigned int func;
    unsigned int n;
    unsigned int padding_len;
    unsigned int wots_w;
    unsigned int wots_log_w;
    unsigned int wots_len1;
    unsigned int wots_len2;
    unsigned int wots_len;
    unsigned int wots_sig_bytes;
    unsigned int index_bytes;
    unsigned int sig_bytes;
    unsigned int pk_bytes;
    unsigned long long sk_bytes;
    unsigned int bds_k;
} wots_params;



/* Given a params struct where the following properties have been initialized;
    - full_height; the height of the complete (hyper)tree
    - n; the number of bytes of hash function output
    - d; the number of layers (d > 1 implies XMSSMT)
    - func; one of {XMSS_SHA2, XMSS_SHAKE128, XMSS_SHAKE256}
    - wots_w; the Winternitz parameter
    - optionally, bds_k; the BDS traversal trade-off parameter,
    this function initializes the remainder of the params structure. */
int wots_initialize_params(wots_params *params);

#endif
