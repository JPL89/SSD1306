/*
	@File 		ssd1306.h
	@Author		JOSIMAR PEREIRA LEITE
	@country	Brazil
	@Date		07/06/2021
	

    Copyright (C) 2021  JOSIMAR PEREIRA LEITE

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/


#ifndef SSD1306_H_
#define SSD1306_H_

#define SSD1306_BLACK		0x00
#define SSD1306_WHITE		0xFF

#define SSD1306_ADDR_W		0x78
#define SSD1306_ADDR_R		0x79
#define SSD1306_COMMAD_BIT	0x00
#define SSD1306_DATA_BIT	0x40

#define SSD1306_SETCONTRAST 0x81
#define SSD1306_ENTIREDISPLAYON_RESUME 0xA4
#define SSD1306_ENTIREDISPLAYON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF
#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_ACTIVATE_SCROLL 0x2F
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10
#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR   0x22
#define SSD1306_PAGESTARTADDR 0xB0
#define SSD1306_SETSTARTLINE 0x40
#define SSD1306_SEGREMAP 0xA0
#define SSD1306_SETMULTIPLEXRATIO 0xA8
#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8
#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9
#define SSD1306_SETVCOMDETECT 0xDB
#define SSD1306_NOP 0xE3
#define SSD1306_CHARGEPUMP 0x8D
#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2
#define SSD1306_CL_WHITE 0
#define SSD1306_CL_BLACK 1

static unsigned char SSD1306_Cursor_x;
static unsigned char SSD1306_Cursor_y;

void SSD1306_Init(void);
void SSD1306_Send_Cmd(unsigned char cmd);
void SSD1306_Send_Char(unsigned char data);		
void SSD1306_Set_Cursor(unsigned char x, unsigned char y);
void SSD1306_Set_XY(unsigned char x, unsigned char y);
void SSD1306_Clear(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char color);
void SSD1306_DrawImage(const unsigned char * Img, unsigned char x, unsigned char y, int w, int h, unsigned char Color);
void SSD1306_Int_XY(unsigned long num, unsigned char x, unsigned char y, const unsigned char Font[], unsigned char color);
void SSD1306_Int(unsigned long num, const unsigned char Font[], unsigned char color);
void SSD1306_String_XY(const char * data, unsigned char x, unsigned char y, const unsigned char Font[], unsigned char color);
void SSD1306_String(const char * data, const unsigned char Font[], unsigned char color);	
void SSD1306_Float_XY(double f, unsigned long sfx, unsigned char x, unsigned char y, const unsigned char Font[], unsigned char color);
void SSD1306_Float(double f, unsigned long sfx, const unsigned char Font[], unsigned char color);
void SSD1306_Char(unsigned char data, const unsigned char Font[], unsigned char color);	


#endif /* SSD1306_H_ */
