/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_init.h"
#include "hal_usb.h"
#include "app_usb_desc.h"

/*
 * Macros.
 */

/*
 * Variables.
 */

/* BOARD_USB_PORT buffer descriptor table buffer. */
__attribute__((aligned(512u))) static USB_BufDespTable_Type usb_bd_tbl;

/* setup Packet Buffer, be used for receive setup packet. */
static uint8_t app_usb_setup_buffer[8u];

/* xfer Buffer, be used for xfer packet. */
static uint8_t app_usb_xfer_buffer[64u];

/* be used for remember BOARD_USB_PORT addr before set addr in BOARD_USB_PORT. */
static uint8_t app_usb_device_addr;

/* bd index flag, be used to recorgnize which bd can be used. */
static uint32_t app_usb_bd_oddeven[2u];

/*
 * Declerations.
 */
void app_usb_init(void);

/*
 * Functions.
 */
int main(void)
{
    BOARD_Init();

    printf("USB basic example.\r\n");
    app_usb_init();

    while (1)
    {
    }
}

void app_usb_init(void)
{
    memset(&usb_bd_tbl, 0, sizeof(usb_bd_tbl));
    USB_Device_Init_Type usb_init;
    usb_init.BufDespTable_Addr       = (uint32_t)&usb_bd_tbl; /* set bdt addr. */
    USB_InitDevice(BOARD_USB_PORT, &usb_init);                           /* enable BOARD_USB_PORT. */
    USB_Enable(BOARD_USB_PORT, true);

    NVIC_ClearPendingIRQ(BOARD_USB_IRQn);
    USB_EnableInterrupts(BOARD_USB_PORT, USB_INT_RESET,     true); /* enable interrupts. */
    USB_EnableInterrupts(BOARD_USB_PORT, USB_INT_TOKENDONE, true); /* enable interrupts. */
    USB_EnableInterrupts(BOARD_USB_PORT, USB_INT_STALL,     true); /* enable interrupts. */
    NVIC_SetPriority(BOARD_USB_IRQn, 3u);
    NVIC_EnableIRQ(BOARD_USB_IRQn);
}

/* BOARD_USB_PORT setup handler. */
void app_usb_setup_handler(void)
{
    uint16_t len = 0;

    if ( USB_SETUP_DESC_GETDESC == app_usb_setup_buffer[1] ) /* BOARD_USB_PORT std req code 6: get descriptor. */
    {
        if ( USB_SETUP_DESC_GETDESC_DEVDESC == (app_usb_setup_buffer[3] ) ) /* desc type 1: device desc. */
        {
            memcpy( app_usb_xfer_buffer, usb_dev_desc, sizeof(usb_dev_desc) );
            len = sizeof(usb_dev_desc);
        }
        else if ( USB_SETUP_DESC_GETDESC_CFGDESC == (app_usb_setup_buffer[3] ) ) /* desc type 2: configuration desc. */
        {
            memcpy( app_usb_xfer_buffer, usb_conf_desc, sizeof(usb_conf_desc) );
            len = sizeof(usb_conf_desc);
        }
        else if( USB_SETUP_DESC_GETDESC_STRDESC == ( app_usb_setup_buffer[3] ) ) /* desc type 3: string desc. */
        {
            if( USB_SETUP_DESC_GETDESC_STRDESC_LANGUAGEID == ( app_usb_setup_buffer[2] ) ) /* language id. */
            {
                memcpy( app_usb_xfer_buffer, usb_language_id, sizeof(usb_language_id) );
                len = sizeof(usb_language_id);
            }
            else if( USB_SETUP_DESC_GETDESC_STRDESC_MANUFACTURER == (app_usb_setup_buffer[2] ) ) /* manufacturer. */
            {
                memcpy( app_usb_xfer_buffer, usb_str_desc, sizeof(usb_str_desc) );
                len = sizeof(usb_str_desc);
            }
            else if( USB_SETUP_DESC_GETDESC_STRDESC_PRODUCT == (app_usb_setup_buffer[2] ) ) /* product. */
            {
                memcpy( app_usb_xfer_buffer, usb_str_desc, sizeof(usb_str_desc) );
                len = sizeof(usb_str_desc);
            }
            else if( USB_SETUP_DESC_GETDESC_STRDESC_SN == ( app_usb_setup_buffer[2] ) ) /* sn. */
            {
                memcpy( app_usb_xfer_buffer, usb_str_desc, sizeof(usb_str_desc) );
                len = sizeof(usb_str_desc);
            }
            else /* send ZLP. */
            {
                len = 0;
            }
        }
        else if( USB_SETUP_DESC_GETDESC_DEVQUALIFIER == (app_usb_setup_buffer[3] ) ) /* desc type 3: device qualifier. */
        {
            USB_EnableEndPointStall(BOARD_USB_PORT, USB_EP_0, true); /* BOARD_USB_PORT HS need, fs mode enter stall status. */
            return;
        }
        else if( USB_SETUP_DESC_GETDESC_REPORTDESC == ( app_usb_setup_buffer[3] ) ) /* desc type 3: report desc. */
        {
            memcpy( app_usb_xfer_buffer, usb_rpt_desc, sizeof(usb_rpt_desc) );
            len    = sizeof(usb_rpt_desc);
        }
        else /* send ZLP. */
        {
            len = 0;
        }
    }
    else if( USB_SETUP_DESC_SETADDR == app_usb_setup_buffer[1] ) /* get BOARD_USB_PORT device addr from host. */
    {
        app_usb_device_addr = app_usb_setup_buffer[2];
        len = 0;
    }
    else if( USB_SETUP_DESC_SETCFG == app_usb_setup_buffer[1] ) /* enable EP1. */
    {
        USB_EnableEndPoint(BOARD_USB_PORT, 1, USB_EndPointMode_Bulk, true);
        len = 0;
    }
    else if(USB_SETUP_DESC_SETIDEL == app_usb_setup_buffer[1] ) /* send ZLP. */
    {
        len = 0;
    }
    /* if buffer size more than std req need, size = need. */
    if(len > ( ( (uint16_t)app_usb_setup_buffer[7] )<<8) + app_usb_setup_buffer[6] )
    {
        len = ( ( (uint16_t)app_usb_setup_buffer[7] )<<8) + app_usb_setup_buffer[6];
    }
    if(len != 0)
    {
        /* ready for receive ZLP from host. */
        USB_BufDesp_Xfer(&usb_bd_tbl.Index[app_usb_bd_oddeven[0u] ^ 1u], 1u, app_usb_setup_buffer, sizeof(app_usb_setup_buffer) );
        USB_BufDesp_Xfer(&usb_bd_tbl.Index[app_usb_bd_oddeven[0u]     ], 1u, app_usb_setup_buffer, sizeof(app_usb_setup_buffer) );
    }
    else
    {
        /* ready for receive setup packet. */
        USB_BufDesp_Xfer(&usb_bd_tbl.Index[app_usb_bd_oddeven[0u]], 1u, app_usb_setup_buffer, sizeof(app_usb_setup_buffer) );
    }
    /* send data. */
    USB_BufDesp_Xfer(&usb_bd_tbl.Index[app_usb_bd_oddeven[1u]], 1u, app_usb_xfer_buffer, len);
}

/* tokdne handler. */
void app_usb_tokdne_handler(void)
{
    /* get something information. */
    uint32_t ep_index = USB_GetEndPointIndex(BOARD_USB_PORT); /* endpoint index. */
    USB_BufDesp_OddEven_Type bd_oddeven = USB_GetBufDespOddEven(BOARD_USB_PORT); /* odd_even. */
    USB_BufDesp_Type *bd = USB_GetBufDesp(BOARD_USB_PORT); /* which bd xfer data done. */
    USB_TokenPid_Type token = USB_BufDesp_GetTokenPid(bd); /* token pid. */
    USB_BufDesp_Reset(bd); /* reset the bd. */
    USB_ClearInterruptStatus(BOARD_USB_PORT, USB_INT_TOKENDONE); /* clear the interrupt flag. */
    if(USB_TokenPid_IN == token)
    {
        /* oddeven change. */
        app_usb_bd_oddeven[ (ep_index << 1u) + 1u] = 2u + (bd_oddeven ^ 1u);
    }
    else
    {
        /* oddeven change. */
        app_usb_bd_oddeven[ (ep_index << 1u) ] = bd_oddeven ^ 1u;
    }
    if(USB_TokenPid_SETUP == token)
    {
        /* setup process. */
        app_usb_setup_handler();
        USB_EnableSuspend(BOARD_USB_PORT, false);
    }
    else if(0u != app_usb_device_addr && 0u == USB_BufDesp_GetPacketSize(bd) )
    {
        /* set BOARD_USB_PORT address after recv device addr from Host and send ZLP for Host. */
        USB_SetDeviceAddr(BOARD_USB_PORT, app_usb_device_addr);
        app_usb_device_addr = 0u;
    }
}

/* reset handler. */
void app_usb_reset_handler(void *buffer, uint8_t len)
{
    /* reset the odd_even flag. */
    app_usb_bd_oddeven[0u] = 0u;
    app_usb_bd_oddeven[1u] = 2u;
    /* reset bd oddeven. */
    USB_EnableOddEvenReset(BOARD_USB_PORT, true);
    USB_EnableOddEvenReset(BOARD_USB_PORT, false);
    /* device addr = 0. */
    USB_SetDeviceAddr(BOARD_USB_PORT, 0x00u);
    app_usb_device_addr = 0;
    for (uint32_t i = 0u; i < 16u; i++)
    {
        /* disable all end point. */
        USB_EnableEndPoint(BOARD_USB_PORT, i, USB_EndPointMode_NULL, false);
    }
    /* enable ep0. */
    USB_EnableEndPoint(BOARD_USB_PORT, 0u, USB_EndPointMode_Control, true);
    /* prepare for recv setup packet. */
    USB_BufDesp_Xfer(&usb_bd_tbl.Index[app_usb_bd_oddeven[0u] ], 1u, buffer, len);
}

/* BOARD_USB_PORT interrupt handler. */
void BOARD_USB_IRQHandler(void)
{
    /* get interrupt status. */
    uint32_t flag = USB_GetInterruptStatus(BOARD_USB_PORT);

    if (flag & USB_INT_RESET)
    { /* BOARD_USB_PORT reset. */
        USB_ClearInterruptStatus(BOARD_USB_PORT, USB_INT_RESET);
        app_usb_reset_handler( app_usb_setup_buffer,sizeof(app_usb_setup_buffer) );
        return;
    }
    if (flag & USB_INT_TOKENDONE)
    { /* BOARD_USB_PORT token done. */
        app_usb_tokdne_handler();
        return;
    }
    if (flag & USB_INT_STALL)
    { /* BOARD_USB_PORT stall. */
        USB_ClearInterruptStatus(BOARD_USB_PORT, USB_INT_STALL);
        USB_EnableEndPointStall(BOARD_USB_PORT, USB_EP_0, false);  /* get qualifier will make ep0 stall, clear it. */
        USB_BufDesp_Xfer(&usb_bd_tbl.Index[app_usb_bd_oddeven[0u] ], 1, app_usb_setup_buffer, sizeof(app_usb_setup_buffer) );
        return;
    }
}

/* EOF. */
