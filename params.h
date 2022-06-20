
#include <stdint.h>

typedef struct {
   
    unsigned int n;
    unsigned int padding_len;
    unsigned int wots_w;
    unsigned int wots_log_w;
    unsigned int wots_len1;
    unsigned int wots_len2;
    unsigned int wots_len;
    unsigned int wots_sig_bytes;
    
} wots_params;




    
int wots_initialize_params(wots_params *params);


