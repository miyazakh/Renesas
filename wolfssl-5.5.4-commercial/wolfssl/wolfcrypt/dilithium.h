/* dilithium.h
 *
 * Copyright (C) 2006-2022 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/*!
    \file wolfssl/wolfcrypt/dilithium.h
*/

/* Interfaces for Dilithium NIST Level 1 (Dilithium512) and Dilithium NIST Level 5
 * (Dilithium1024). */

#ifndef WOLF_CRYPT_DILITHIUM_H
#define WOLF_CRYPT_DILITHIUM_H

#include <wolfssl/wolfcrypt/types.h>

#if defined(HAVE_PQC) && defined(HAVE_DILITHIUM)

#ifdef HAVE_LIBOQS
#include <oqs/oqs.h>
#endif

#ifdef __cplusplus
    extern "C" {
#endif

/* Macros Definitions */

#ifdef HAVE_LIBOQS
#define DILITHIUM_LEVEL2_KEY_SIZE     OQS_SIG_dilithium_2_length_secret_key
#define DILITHIUM_LEVEL2_SIG_SIZE     OQS_SIG_dilithium_2_length_signature
#define DILITHIUM_LEVEL2_PUB_KEY_SIZE OQS_SIG_dilithium_2_length_public_key
#define DILITHIUM_LEVEL2_PRV_KEY_SIZE (DILITHIUM_LEVEL2_PUB_KEY_SIZE+DILITHIUM_LEVEL2_KEY_SIZE)

#define DILITHIUM_LEVEL3_KEY_SIZE     OQS_SIG_dilithium_3_length_secret_key
#define DILITHIUM_LEVEL3_SIG_SIZE     OQS_SIG_dilithium_3_length_signature
#define DILITHIUM_LEVEL3_PUB_KEY_SIZE OQS_SIG_dilithium_3_length_public_key
#define DILITHIUM_LEVEL3_PRV_KEY_SIZE (DILITHIUM_LEVEL3_PUB_KEY_SIZE+DILITHIUM_LEVEL3_KEY_SIZE)

#define DILITHIUM_LEVEL5_KEY_SIZE     OQS_SIG_dilithium_5_length_secret_key
#define DILITHIUM_LEVEL5_SIG_SIZE     OQS_SIG_dilithium_5_length_signature
#define DILITHIUM_LEVEL5_PUB_KEY_SIZE OQS_SIG_dilithium_5_length_public_key
#define DILITHIUM_LEVEL5_PRV_KEY_SIZE (DILITHIUM_LEVEL5_PUB_KEY_SIZE+DILITHIUM_LEVEL5_KEY_SIZE)
#endif

#define DILITHIUM_MAX_KEY_SIZE     DILITHIUM_LEVEL5_PRV_KEY_SIZE
#define DILITHIUM_MAX_SIG_SIZE     DILITHIUM_LEVEL5_SIG_SIZE
#define DILITHIUM_MAX_PUB_KEY_SIZE DILITHIUM_LEVEL5_PUB_KEY_SIZE
#define DILITHIUM_MAX_PRV_KEY_SIZE DILITHIUM_LEVEL5_PRV_KEY_SIZE

#define SHAKE_VARIANT 1
#define AES_VARIANT   2

/* Structs */

struct dilithium_key {
    bool pubKeySet;
    bool prvKeySet;
    byte level; /* 2,3 or 5 */
    byte sym; /* SHAKE_VARIANT or AES_VARIANT */
    byte p[DILITHIUM_MAX_PUB_KEY_SIZE];
    byte k[DILITHIUM_MAX_PRV_KEY_SIZE];
};

#ifndef WC_DILITHIUMKEY_TYPE_DEFINED
    typedef struct dilithium_key dilithium_key;
    #define WC_DILITHIUMKEY_TYPE_DEFINED
#endif

/* Functions */

WOLFSSL_API
int wc_dilithium_sign_msg(const byte* in, word32 inLen, byte* out, word32 *outLen,
                       dilithium_key* key);
WOLFSSL_API
int wc_dilithium_verify_msg(const byte* sig, word32 sigLen, const byte* msg,
                         word32 msgLen, int* res, dilithium_key* key);

WOLFSSL_API
int wc_dilithium_init(dilithium_key* key);
WOLFSSL_API
int wc_dilithium_set_level_and_sym(dilithium_key* key, byte level, byte sym);
WOLFSSL_API
int wc_dilithium_get_level_and_sym(dilithium_key* key, byte* level, byte *sym);
WOLFSSL_API
void wc_dilithium_free(dilithium_key* key);

WOLFSSL_API
int wc_dilithium_import_public(const byte* in, word32 inLen, dilithium_key* key);
WOLFSSL_API
int wc_dilithium_import_private_only(const byte* priv, word32 privSz,
                                  dilithium_key* key);
WOLFSSL_API
int wc_dilithium_import_private_key(const byte* priv, word32 privSz,
                                 const byte* pub, word32 pubSz,
                                 dilithium_key* key);

WOLFSSL_API
int wc_dilithium_export_public(dilithium_key*, byte* out, word32* outLen);
WOLFSSL_API
int wc_dilithium_export_private_only(dilithium_key* key, byte* out, word32* outLen);
WOLFSSL_API
int wc_dilithium_export_private(dilithium_key* key, byte* out, word32* outLen);
WOLFSSL_API
int wc_dilithium_export_key(dilithium_key* key, byte* priv, word32 *privSz,
                         byte* pub, word32 *pubSz);

WOLFSSL_API
int wc_dilithium_check_key(dilithium_key* key);

WOLFSSL_API
int wc_dilithium_size(dilithium_key* key);
WOLFSSL_API
int wc_dilithium_priv_size(dilithium_key* key);
WOLFSSL_API
int wc_dilithium_pub_size(dilithium_key* key);
WOLFSSL_API
int wc_dilithium_sig_size(dilithium_key* key);

WOLFSSL_API int wc_Dilithium_PrivateKeyDecode(const byte* input,
                                              word32* inOutIdx,
                                              dilithium_key* key, word32 inSz);
WOLFSSL_API int wc_Dilithium_PublicKeyDecode(const byte* input,
                                             word32* inOutIdx,
                                             dilithium_key* key, word32 inSz);
WOLFSSL_API int wc_Dilithium_KeyToDer(dilithium_key* key, byte* output,
                                      word32 inLen);
WOLFSSL_API int wc_Dilithium_PrivateKeyToDer(dilithium_key* key, byte* output,
                                             word32 inLen);
WOLFSSL_API int wc_Dilithium_PublicKeyToDer(dilithium_key* key, byte* output,
                                            word32 inLen, int withAlg);

#ifdef __cplusplus
    }    /* extern "C" */
#endif

#endif /* HAVE_PQC && HAVE_DILITHIUM */
#endif /* WOLF_CRYPT_DILITHIUM_H */