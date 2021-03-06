#include <stdint.h>
#include <string.h>
#include <openssl/sha.h>

#include "hash_address.h"
#include "utils.h"
#include "params.h"
#include "hash.h"
#include "fips202.h"




void set_key_and_mask(uint32_t addr[8], uint32_t key_and_mask)
{
    addr[7] = key_and_mask;
}

void set_chain_addr(uint32_t addr[8], uint32_t chain)
{
    addr[5] = chain;
}

void set_hash_addr(uint32_t addr[8], uint32_t hash)
{
    addr[6] = hash;
}

#define XMSS_HASH_PADDING_F 0
#define XMSS_HASH_PADDING_PRF 3


void addr_to_bytes(unsigned char *bytes, const uint32_t addr[8])
{
    int i;
    for (i = 0; i < 8; i++) {
        ull_to_bytes(bytes + i*4, 4, addr[i]);
    }
}

/*
 * Computes PRF(key, in), for a key of PARAMSN bytes, and a 32-byte input.
 */
int prf(byte *out, const byte in[32],
        const byte *key)
{
    byte buf[2 * PARAMSN + 32];

    ull_to_bytes(buf, PARAMSN, XMSS_HASH_PADDING_PRF);
    memcpy(buf + PARAMSN, key, PARAMSN);
    memcpy(buf + (2*PARAMSN), in, 32);
    core_hash(out, buf, (2*PARAMSN) + 32);
    return 0;
}


int thash_f(byte *out, const byte *in,
            const byte *pub_seed, uint32_t addr[8])
{
    byte buf[3 * PARAMSN];
    byte bitmask[PARAMSN];
    byte addr_as_bytes[32];
    unsigned int i;

    /* Set the function padding. */
    ull_to_bytes(buf, PARAMSN, XMSS_HASH_PADDING_F);

    /* Generate the n-byte key. */
    set_key_and_mask(addr, 0);
    addr_to_bytes(addr_as_bytes, addr);
    prf(buf + PARAMSN, addr_as_bytes, pub_seed);

    /* Generate the n-byte mask. */
    set_key_and_mask(addr, 1);
    addr_to_bytes(addr_as_bytes, addr);
    prf(bitmask, addr_as_bytes, pub_seed);

    for (i = 0; i < PARAMSN; i++) {
        buf[2*PARAMSN + i] = in[i] ^ bitmask[i];
    }
    core_hash(out, buf, 3 * PARAMSN);
    return 0;
}
