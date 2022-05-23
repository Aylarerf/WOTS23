
#include <stdint.h>

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
} wots_params;



/* Given a params struct where the following properties have been initialized
    - n; the number of bytes of hash function output
    - wots_w; the Winternitz parameter
    
int wots_initialize_params(wots_params *params);

#endif
