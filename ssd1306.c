/*
	@File 		ssd1306.cpp
	@Author		JOSIMAR PEREIRA LEITE
	@country	Brazil
	@Date		07/06/2021
	

    Copyright (C) 2021  JOSIMAR PEREIRA LEITE

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
*/
#include "ssd1306.h"
#include "wire.h"

void SSD1306_Send_Cmd(unsigned char cmd)
{
	Wire_Start();
	Wire_Write( SSD1306_ADDR_W );
	Wire_Write( SSD1306_COMMAD_BIT );
	Wire_Write( cmd );
	Wire_Stop();
}

void SSD1306_Send_Char(unsigned char data)
{
	Wire_Start();
	Wire_Write( SSD1306_ADDR_W );
	Wire_Write( SSD1306_DATA_BIT );
	Wire_Write( data );
	Wire_Stop();
}

void SSD1306_Set_XY(unsigned char x, unsigned char y)
{
	 SSD1306_Cursor_x = x;
	 SSD1306_Cursor_y = y;
}

void SSD1306_Set_Cursor(unsigned char x, unsigned char y)
{
	SSD1306_Send_Cmd(0xB0 | y);
	SSD1306_Send_Cmd(0x10 | (x >> 4));
	SSD1306_Send_Cmd(0x0F & x);
}

void SSD1306_Char(unsigned char data, const unsigned char Font[], unsigned char color)
{
	unsigned char wd				= (unsigned char) ( Font[0] );	// font width
	unsigned char pg				= (unsigned char) ( Font[2] );	// font pages
	unsigned char st				= (unsigned char) ( Font[3] );	// font start
	unsigned char ch				= 0;							// character
	unsigned char fh				= 5;							// font header size
	int row							= 0;							// row
	int col							= 0;							// col
	int i							= 0;							// loop
	
	int font_data_w_h 	= (2*(data-st));
	int font_data_pos	= (wd*pg) * (data-st);
	
	int id = (font_data_pos + font_data_w_h) + fh;
	
	unsigned char char_w = (unsigned char) ( Font[id++] );
	id++;
	
	for (col=0; col<pg; col++)
	{
		SSD1306_Set_Cursor( SSD1306_Cursor_x,  (unsigned char) (SSD1306_Cursor_y + col) );
		
		for (row=0; row < wd; row++)
		{
			ch = (unsigned char) ( Font[ ( id + row + i) ] );
			
			SSD1306_Send_Char( ch ^ color);
		}
		
		i += wd; 
	}
	
	 SSD1306_Cursor_x += char_w + 1;
}

void SSD1306_String_XY(const char * data, unsigned char x, unsigned char y, const unsigned char Font[], unsigned char color)
{
	SSD1306_Cursor_x = x;
	SSD1306_Cursor_y = y;
	
	while(*data)
	{
		SSD1306_Char(*data++, Font, color);
	}
}

void SSD1306_String(const char * data, const unsigned char Font[], unsigned char color)
{
	while(*data)
	{
		SSD1306_Char(*data++, Font, color);
	}
}


void SSD1306_Int_XY(unsigned long num, unsigned char x, unsigned char y, const unsigned char Font[], unsigned char color)
{
	SSD1306_Cursor_x = x;
	SSD1306_Cursor_y = y;

	if(!num)
	{
		SSD1306_Char(48,Font,color);
		return;
	}
		
	int i = 9;
	unsigned char buf[10];
	
	for (int x=0; x<10; x++)
	{
		buf[x] = 0xFF;
	}
	
	while(num)
	{
		buf[i--]=num%10;
		num=num/10;
	}
	
	for(i=0; i<10; i++)
	{
		if(buf[i] != 0xFF)
			SSD1306_Char(buf[i] + 48, Font, color);
	}
}

void SSD1306_Int(unsigned long num, const unsigned char Font[], unsigned char color)
{
	if(!num)
	{
		SSD1306_Char(48,Font,color);
		return;
	}
	
	int i = 9;
	unsigned char buf[10];
	
	for (int x=0; x<10; x++)
	{
		buf[x] = 0xFF;
	}
	
	while(num)
	{
		buf[i--]=num%10;
		num=num/10;
	}
	
	for(i=0;i<10;i++)
	{
		if(buf[i] != 0xFF)
		SSD1306_Char(buf[i] + 48,Font,color);
	}
}


void SSD1306_Float_XY(double f, unsigned long sfx, unsigned char x, unsigned char y, const unsigned char Font[], unsigned char color)
{
	SSD1306_Cursor_x = x;
	SSD1306_Cursor_y = y;
	
	switch(sfx)
	{
		case 1: sfx = 10; break;
		case 2: sfx = 100; break;
		case 3: sfx = 1000; break;
		case 4: sfx = 10000; break;
		case 5: sfx = 100000; break;
		case 6: sfx = 1000000; break;
		case 7: sfx = 10000000; break;
		case 8: sfx = 100000000; break;
		
		default: sfx = 10;
	}

	unsigned char Buffer[10] = { 0 };
	
	for(int i=0; i<10; i++) Buffer[i] = 0xFF;
	
	int k = 10;
	
	unsigned long num = (unsigned long) f;
	
	while(num)
	{
		Buffer[--k] = num%10;
		num /=10;
	}
	
	for(int i=0; i<10; i++)
	{
		if(Buffer[i] != 0xFF)
		{
			SSD1306_Cursor_x += 1;
			SSD1306_Char(Buffer[i] + 48, Font, color);
		}
	}
	
	SSD1306_Char('.',Font, color);
	
	unsigned long tmp = (unsigned long) (f * sfx);
	
	SSD1306_Int_XY(tmp % sfx, SSD1306_Cursor_x, SSD1306_Cursor_y, Font, color);
}

void SSD1306_Float(double f, unsigned long sfx, const unsigned char Font[], unsigned char color)
{
	switch(sfx)
	{
		case 1: sfx = 10; break;
		case 2: sfx = 100; break;
		case 3: sfx = 1000; break;
		case 4: sfx = 10000; break;
		case 5: sfx = 100000; break;
		case 6: sfx = 1000000; break;
		case 7: sfx = 10000000; break;
		case 8: sfx = 100000000; break;
		
		default: sfx = 10;
	}

	unsigned char Buffer[10] = { 0 };
	
	for(int i=0; i<10; i++) Buffer[i] = 0xFF;
	
	int k = 10;
	
	unsigned long num = (unsigned long) f;
	
	while(num)
	{
		Buffer[--k] = num%10;
		num /=10;
	}
	
	for(int i=0; i<10; i++)
	{
		if(Buffer[i] != 0xFF)
		{
			SSD1306_Cursor_x += 1;
			SSD1306_Char(Buffer[i] + 48, Font, color);
		}
	}
	
	SSD1306_Char('.',Font, color);
	
	unsigned long tmp = (unsigned long) ( f * sfx);
	
	SSD1306_Int(tmp % sfx, Font, color);
}

void SSD1306_Clear(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char color)
{
	SSD1306_Set_Cursor(x,y);
	
	for (int i=0; i<(h/8)+1;i++)
	{
		for (int k=0; k<w;k++)
		{
			SSD1306_Send_Char(color);
		}
		
		SSD1306_Set_Cursor(x,(unsigned char)( y+i) );
	}
}

void SSD1306_DrawImage(const unsigned char * Img, unsigned char x, unsigned char y, int w, int h, unsigned char Color)
{
	SSD1306_Set_Cursor(x,y);
	
	int k=0;
	
	for (int i=0; i<(h/8)+1;i++)
	{
		for (; k<(w*i); k++)
		{
			SSD1306_Send_Char(Img[k] ^ Color);
		}
		
		SSD1306_Set_Cursor( x, (unsigned char) (y+i));
	}
}

void SSD1306_Init(void)
{	
	// Send Start Commands
	SSD1306_Send_Cmd(SSD1306_DISPLAYOFF);	// 0xAE
	SSD1306_Send_Cmd(SSD1306_SETDISPLAYCLOCKDIV);	// 0xD5
	SSD1306_Send_Cmd(0x80);	// the suggested ratio 0x80
	SSD1306_Send_Cmd(0xA8);	// 0xA8 SSD1306_SETMULTIPLEX
	SSD1306_Send_Cmd(128 - 1);
	SSD1306_Send_Cmd(SSD1306_SETDISPLAYOFFSET);	// 0xD3
	SSD1306_Send_Cmd(0x00);	// no offset
	SSD1306_Send_Cmd(SSD1306_SETSTARTLINE | 0x00);	// line #0
	SSD1306_Send_Cmd(SSD1306_CHARGEPUMP);	// 0x8D
	SSD1306_Send_Cmd(0x14);
	SSD1306_Send_Cmd(SSD1306_MEMORYMODE);	// 0x20
	SSD1306_Send_Cmd(0x00);	// 0x0 act like ks0108
	SSD1306_Send_Cmd(SSD1306_SEGREMAP | 0x01);
	SSD1306_Send_Cmd(SSD1306_COMSCANDEC);
	SSD1306_Send_Cmd(SSD1306_SETCOMPINS);	// 0xDA
	SSD1306_Send_Cmd(0x12);
	SSD1306_Send_Cmd(SSD1306_SETCONTRAST);	// 0x81
	SSD1306_Send_Cmd(255); //0..255
	SSD1306_Send_Cmd(SSD1306_SETPRECHARGE);	// 0xd9
	SSD1306_Send_Cmd(0x22);//SSD1306_EXTERNALVCC
	SSD1306_Send_Cmd(SSD1306_SETVCOMDETECT);	// 0xDB
	SSD1306_Send_Cmd(0x40);
	SSD1306_Send_Cmd(0xA4);	// 0xA4 SSD1306_DISPLAYALLON_RESUME
	SSD1306_Send_Cmd(SSD1306_DISPLAYON);		// DISPLAY ON
}
