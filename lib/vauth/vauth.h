#ifndef HEADER_CURL_VAUTH_H
#define HEADER_CURL_VAUTH_H
/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 2014 - 2015, Steve Holme, <steve_holme@hotmail.com>.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at http://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/

#include <curl/curl.h>

struct SessionHandle;

#if !defined(CURL_DISABLE_CRYPTO_AUTH)
struct digestdata;
#endif

/* This is used to build a SPN string */
#if !defined(USE_WINDOWS_SSPI)
char *Curl_sasl_build_spn(const char *service, const char *instance);
#else
TCHAR *Curl_sasl_build_spn(const char *service, const char *instance);
#endif

#if defined(HAVE_GSSAPI)
char *Curl_sasl_build_gssapi_spn(const char *service, const char *instance);
#endif

/* This is used to generate a base64 encoded PLAIN cleartext message */
CURLcode sasl_create_plain_message(struct SessionHandle *data,
                                   const char *userp,
                                   const char *passwdp,
                                   char **outptr, size_t *outlen);

/* This is used to generate a base64 encoded LOGIN cleartext message */
CURLcode sasl_create_login_message(struct SessionHandle *data,
                                   const char *valuep, char **outptr,
                                   size_t *outlen);

/* This is used to generate a base64 encoded EXTERNAL cleartext message */
CURLcode sasl_create_external_message(struct SessionHandle *data,
                                      const char *user, char **outptr,
                                      size_t *outlen);

#if !defined(CURL_DISABLE_CRYPTO_AUTH)
/* This is used to decode a CRAM-MD5 challenge message */
CURLcode sasl_decode_cram_md5_message(const char *chlg64, char **outptr,
                                      size_t *outlen);

/* This is used to generate a CRAM-MD5 response message */
CURLcode sasl_create_cram_md5_message(struct SessionHandle *data,
                                      const char *chlg,
                                      const char *userp,
                                      const char *passwdp,
                                      char **outptr, size_t *outlen);

/* This is used to generate a base64 encoded DIGEST-MD5 response message */
CURLcode Curl_sasl_create_digest_md5_message(struct SessionHandle *data,
                                             const char *chlg64,
                                             const char *userp,
                                             const char *passwdp,
                                             const char *service,
                                             char **outptr, size_t *outlen);

/* This is used to decode a HTTP DIGEST challenge message */
CURLcode Curl_sasl_decode_digest_http_message(const char *chlg,
                                              struct digestdata *digest);

/* This is used to generate a HTTP DIGEST response message */
CURLcode Curl_sasl_create_digest_http_message(struct SessionHandle *data,
                                              const char *userp,
                                              const char *passwdp,
                                              const unsigned char *request,
                                              const unsigned char *uri,
                                              struct digestdata *digest,
                                              char **outptr, size_t *outlen);

/* This is used to clean up the digest specific data */
void Curl_sasl_digest_cleanup(struct digestdata *digest);
#endif /* !CURL_DISABLE_CRYPTO_AUTH */

#endif /* HEADER_CURL_VAUTH_H */