/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "board_init.h"

#include "mbedtls/sha1.h"

/*
 * Macros.
 */


/*
 * Variables.
 */
 /* sha1 test */
char source_cxt[] = "MindMotion";
uint32_t encrypt_cxt_raw[16];
char * encrypt_cxt = (char *)encrypt_cxt_raw;


/*
 * Declerations.
 */

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();

    printf("\r\nmbedtls v2.24.0\r\n");

    /* show the plaintext. */
    printf("source context is: %s\r\n", source_cxt);

    /* encrypt. */
    mbedtls_sha1_context sha1_ctx;
    mbedtls_sha1_init(&sha1_ctx);
    mbedtls_sha1_starts(&sha1_ctx);
    mbedtls_sha1_update(&sha1_ctx, (unsigned char *)source_cxt, strlen(source_cxt));
    mbedtls_sha1_finish(&sha1_ctx, (unsigned char *)encrypt_cxt);
    mbedtls_sha1_free(&sha1_ctx);

    /* show the ciphetext. */
    printf("sha1 encrypt context is: [");
    char *ptr8 = encrypt_cxt;
    while (*ptr8)
    {
        printf("%02x", *ptr8);
        ptr8++;
    }
    printf("]\r\n");

    while (1);
}

/* on-line calculator: https://tool.oschina.net/encrypt */

/* EOF. */
