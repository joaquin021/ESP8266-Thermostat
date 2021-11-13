#ifndef __USER_GRAPHICS_H
#define __USER_GRAPHICS_H

const unsigned short wrench[576] PROGMEM = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4208, 0x5AEB, 0x5AEB, 0x4A29, 0x0000, 0x0000,  // 0x0010 (16) pixels
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // 0x0020 (32) pixels
    0x0000, 0x0841, 0x632C, 0x632C, 0x632C, 0x632C, 0x1082, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // 0x0030 (48) pixels
    0x0000, 0x0000, 0x0000, 0x0000, 0x18C3, 0x18E3, 0x0000, 0x0000, 0x0000, 0x39C7, 0x632C, 0x632C, 0x632C, 0x632C, 0x39E7, 0x0000,  // 0x0040 (64) pixels
    0x0000, 0x0000, 0x1082, 0x18C3, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2104, 0x632C, 0x632C, 0x526A, 0x39E7,  // 0x0050 (80) pixels
    0x4A69, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x4A69, 0x39C7, 0x4228, 0x632C, 0x632C, 0x2124, 0x0000, 0x0000, 0x0000,  // 0x0060 (96) pixels
    0x0000, 0x0000, 0x10A2, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C,  // 0x0070 (112) pixels
    0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x18C3, 0x0000, 0x0000, 0x0000, 0x0000, 0x1082, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C,  // 0x0080 (128) pixels
    0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x18C3, 0x0000, 0x0000,  // 0x0090 (144) pixels
    0x0000, 0x0000, 0x0000, 0x4208, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C,  // 0x00A0 (160) pixels
    0x632C, 0x632C, 0x632C, 0x632C, 0x4A49, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x31A6, 0x632C, 0x632C, 0x632C, 0x632C,  // 0x00B0 (176) pixels
    0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x39C7, 0x0000, 0x0000, 0x0000,  // 0x00C0 (192) pixels
    0x0000, 0x0000, 0x0000, 0x4A69, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x5AEB, 0x2124, 0x0861, 0x0861, 0x2124, 0x5ACB, 0x632C,  // 0x00D0 (208) pixels
    0x632C, 0x632C, 0x632C, 0x632C, 0x4A69, 0x0000, 0x0000, 0x0000, 0x0000, 0x10A2, 0x4208, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C,  // 0x00E0 (224) pixels
    0x5AEB, 0x0841, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x5ACB, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x39E7, 0x0861, 0x0000,  // 0x00F0 (240) pixels
    0x4A29, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x2124, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2104,  // 0x0100 (256) pixels
    0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x4208, 0x5AEB, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C,  // 0x0110 (272) pixels
    0x0861, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x5AEB,  // 0x0120 (288) pixels
    0x5AEB, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x0861, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020,  // 0x0130 (304) pixels
    0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x5AEB, 0x4208, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C,  // 0x0140 (320) pixels
    0x2124, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x18E3, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x4A29,  // 0x0150 (336) pixels
    0x0000, 0x0841, 0x39C7, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x5ACB, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020, 0x5ACB,  // 0x0160 (352) pixels
    0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x39E7, 0x0861, 0x0000, 0x0000, 0x0000, 0x0000, 0x4A69, 0x632C, 0x632C, 0x632C, 0x632C,  // 0x0170 (368) pixels
    0x632C, 0x5ACB, 0x2104, 0x0020, 0x0020, 0x2104, 0x5ACB, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x4A49, 0x0000, 0x0000, 0x0000,  // 0x0180 (384) pixels
    0x0000, 0x0000, 0x0000, 0x39C7, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C,  // 0x0190 (400) pixels
    0x632C, 0x632C, 0x632C, 0x632C, 0x31A6, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4A49, 0x632C, 0x632C, 0x632C, 0x632C,  // 0x01A0 (416) pixels
    0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x4208, 0x0000, 0x0000, 0x0000,  // 0x01B0 (432) pixels
    0x0000, 0x0000, 0x18C3, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C,  // 0x01C0 (448) pixels
    0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x1082, 0x0000, 0x0000, 0x0000, 0x0000, 0x18C3, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C,  // 0x01D0 (464) pixels
    0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x10A2, 0x0000, 0x0000,  // 0x01E0 (480) pixels
    0x0000, 0x0000, 0x0000, 0x2124, 0x632C, 0x632C, 0x4228, 0x39C7, 0x4A69, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x632C, 0x4A69,  // 0x01F0 (496) pixels
    0x39E7, 0x526A, 0x632C, 0x632C, 0x2104, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x18C3, 0x1082, 0x0000, 0x0000,  // 0x0200 (512) pixels
    0x0000, 0x39E7, 0x632C, 0x632C, 0x632C, 0x632C, 0x39C7, 0x0000, 0x0000, 0x0000, 0x18E3, 0x18C3, 0x0000, 0x0000, 0x0000, 0x0000,  // 0x0210 (528) pixels
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1082, 0x632C, 0x632C, 0x632C, 0x632C, 0x0841, 0x0000,  // 0x0220 (544) pixels
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // 0x0230 (560) pixels
    0x0000, 0x0000, 0x4228, 0x630C, 0x630C, 0x4208, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  // 0x0240 (576) pixels
};

const unsigned char power[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00,
    0x3c, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x3c, 0x3c, 0x3c, 0x00, 0x00, 0x7e, 0x3c,
    0x7e, 0x00, 0x00, 0xfe, 0x3c, 0x7f, 0x00, 0x00, 0xfc, 0x3c, 0x3f, 0x00, 0x01, 0xf8, 0x3c, 0x1f,
    0x80, 0x03, 0xf0, 0x3c, 0x0f, 0xc0, 0x03, 0xf0, 0x3c, 0x0f, 0xc0, 0x03, 0xe0, 0x3c, 0x07, 0xc0,
    0x07, 0xe0, 0x3c, 0x07, 0xe0, 0x07, 0xc0, 0x3c, 0x03, 0xe0, 0x07, 0xc0, 0x3c, 0x03, 0xe0, 0x07,
    0xc0, 0x18, 0x03, 0xe0, 0x07, 0xc0, 0x00, 0x03, 0xe0, 0x07, 0xc0, 0x00, 0x03, 0xe0, 0x07, 0xc0,
    0x00, 0x03, 0xe0, 0x07, 0xe0, 0x00, 0x07, 0xe0, 0x03, 0xe0, 0x00, 0x07, 0xc0, 0x03, 0xf0, 0x00,
    0x0f, 0xc0, 0x03, 0xf0, 0x00, 0x0f, 0xc0, 0x01, 0xf8, 0x00, 0x1f, 0x80, 0x00, 0xfe, 0x00, 0x7f,
    0x00, 0x00, 0xff, 0x81, 0xff, 0x00, 0x00, 0x7f, 0xff, 0xfe, 0x00, 0x00, 0x3f, 0xff, 0xfc, 0x00,
    0x00, 0x0f, 0xff, 0xf0, 0x00, 0x00, 0x07, 0xff, 0xe0, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

#endif