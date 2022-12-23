/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __APP_USB_DESC_H__
#define __APP_USB_DESC_H__

#include "stdint.h"

/* usb setup desc code. */
#define USB_SETUP_DESC_GETDESC                      0x06u /* get desc. */
#define USB_SETUP_DESC_GETDESC_DEVDESC              0x01u /* get desc: dev desc. */
#define USB_SETUP_DESC_GETDESC_CFGDESC              0x02u /* get desc: cfg desc. */
#define USB_SETUP_DESC_GETDESC_STRDESC              0x03u /* get desc. str desc. */
#define USB_SETUP_DESC_GETDESC_STRDESC_LANGUAGEID   0x00u /* get str desc: language id. */
#define USB_SETUP_DESC_GETDESC_STRDESC_MANUFACTURER 0x01u /* get str desc: manufacturer. */
#define USB_SETUP_DESC_GETDESC_STRDESC_PRODUCT      0x02u /* get str desc: product. */
#define USB_SETUP_DESC_GETDESC_STRDESC_SN           0x03u /* get str desc: sn. */
#define USB_SETUP_DESC_GETDESC_DEVQUALIFIER         0x06u /* get desc: qualifier desc. */
#define USB_SETUP_DESC_GETDESC_REPORTDESC           0x22u /* get desc: report desc. */
#define USB_SETUP_DESC_SETADDR                      0x05u /* set device addr desc. */
#define USB_SETUP_DESC_SETCFG                       0x09u /* set cfg desc. */
#define USB_SETUP_DESC_SETIDEL                      0x0au /* set idle desc. */

/* usb device desc. */
uint8_t const usb_dev_desc[]  = 
{
    0x12,       /* desc length = 18. */
    0x01,       /* desc code: dev desc. */
    0x00, 0x02, /* version: USB2.0. */ 
    0x00,       /* device class field. */
    0x00,       /* device sub class field. */
    0x00,       /* device protocol field. */
    0x40,       /* max packet size. */
    0x81, 0x2F, /* verder id. 0x2F81 is MindMotion vender id. */
    0x01, 0x00, /* product id. */
    0x00, 0x01, /* product version. */
    0x01,       /* manufacturer str index. */
    0x02,       /* product str index. */
    0x03,       /* sn str index. */
    0x01        /* cfg num. */
};

/* usb config desc. */
uint8_t const usb_conf_desc[] = 
{
    /* cfg desc. */
    0x09,       /* cfg desc length = 9. */
    0x02,       /* desc code: cfg desc. */
    0x22, 0x00, /* total length: include cfg desc, interface desc and so on. */
    0x01,       /* interface num. */
    0x01,       /* cfg field. */
    0x00,       /* cfg str index, 0 mean there is no index. */
    0x80,       /* attribute. */
    0x32,       /* max power: 100mA. */
    /* interface desc. */
    0x09,       /* interface desc length = 9. */
    0x04,       /* desc code: interface desc. */
    0x00,       /* interface number, first interface is 0. */ 
    0x00,       /* alternate Setting. */
    0x01,       /* endpoint num. */
    0x03,       /* hid class. */
    0x01,       /* interface sub class. */
    0x02,       /* interface protocol: mouse. */
    0x00,       /* configuration str index, no index. */
    /* hid desc. */
    0x09,       /* hid desc length = 9. */
    0x21,       /* desc code: hid desc. */
    0x10, 0x01, /* hid version: 1.1. */
    0x21,       /* country code: US. */
    0x01,       /* num of child desc. */
    0x22,       /* child desc is report desc. */
    0x34, 0x00, /* report desc size. */
    /* endpoint desc. */
    0x07,       /* hid desc length = 9. */
    0x05,       /* desc code: endpoint desc. */
    0x81,       /* endpoint address. */
    0x03,       /* endpoint attribute: interrupt endpoint type. */
    0x40, 0x00, /* max packet size. */
    0x0a        /* interval time, 10ms. */
};

/* usb str desc, language id: EN_US. */
uint8_t const usb_language_id[] = 
{
    0x04,       /* str desc length = 4. */
    0x03,       /* desc code: str desc. */
    0x09, 0x04  /* en_us id.            */
};

/* usb str desc, Unicode string desc MindMotion. */
uint8_t const usb_str_desc[]=
{
	0x16,       /* str desc length = 22. */
    0x03,       /* desc code: str desc.  */
    'M', 0x00,  /* unicode 'M'. */
    'i', 0x00,  /* unicode 'i'. */
    'n', 0x00,  /* unicode 'n'. */
    'd', 0x00,  /* unicode 'd'. */
    'M', 0x00,  /* unicode 'M'. */
    'o', 0x00,  /* unicode 'o'. */
    't', 0x00,  /* unicode 't'. */
    'i', 0x00,  /* unicode 'i'. */
    'o', 0x00,  /* unicode 'o'. */
    'n', 0x00   /* unicode 'n'. */
};
 
/* usb report desc. */
uint8_t const usb_rpt_desc[]  = 
{
    0x05, 0x01, /* USAGE_PAGE ( Generic Desktop ).  */
    0x09, 0x02, /* USAGE_PAGE ( Mouse ).            */
    0xa1, 0x01, /* COLLECTION ( Application ).      */
    0x09, 0x01, /* USAGE ( Pointer ).               */
    0xa1, 0x00, /* COLLECTION ( Physical ).         */
    0x05, 0x09, /* USAGE_PAGE ( Button ).           */
    0x19, 0x01, /* USAGE_MINIMUM ( 1 ).             */
    0x29, 0x03, /* USAGE_MINIMUM ( 3 ).             */
    0x15, 0x00, /* LOGICAL_MINIMUM ( 0 ).           */
    0x25, 0x01, /* LOGICAL_MAXIMUM ( 1 ).           */
    0x95, 0x03, /* REPORT_COUNT ( 3 ).              */
    0x75, 0x01, /* REPORT_SIZE ( 1 ).               */
    0x81, 0x02, /* INPUT ( Data, Var, Abs ).        */
    0x95, 0x01, /* REPORT_COUNT ( 1 ).              */
    0x75, 0x05, /* REPORT_SIZE ( 5 ).               */
    0x81, 0x03, /* INPUT ( Cnst, Var, Abs ).        */
    0x05, 0x01, /* USAGE_PAGE ( Generic Desktop ).  */
    0x09, 0x30, /* USAGE ( X ).                     */
    0x09, 0x31, /* USAGE ( Y ).                     */
    0x09, 0x38, /* USAGE ( Wheel ).                 */
    0x15, 0x81, /* LOGICAL_MINIMUM ( -127 ).        */
    0x25, 0x7f, /* LOGICAL_MAXIMUM (  127 ).        */
    0x75, 0x08, /* REPORT_SIZE ( 8 ).               */
    0x95, 0x03, /* REPORT_COUNT ( 3 ).              */
    0x81, 0x06, /* INPUT ( Data, Var, Rel ).        */
    0xc0,       /* END_COLLECTION.                  */
    0xc0        /* END_COLLECTION.                  */
};

#endif /* __APP_USB_DESC_H__. */

