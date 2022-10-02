/*
	@File 		
	@Author		JOSIMAR PEREIRA LEITE
	@country	Brazil
	@Date		02/10/22
	

    Copyright (C) 2021  JOSIMAR PEREIRA LEITE

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
 
  
*/

#include "config.h"

#include <xc.h>
#include "ssd1306.h"
#include "wire.h"
#include "Arial_Bold_16x17.h"

int main(void) 
{
    // WAIT VCC
    __delay_ms(500);
    
    Wire_Init();
    
    SSD1306_Init();
    
    SSD1306_Clear(0, 0, 128, 64, 0);
    
    SSD1306_String_XY("Hello world", 0, 0, Font_Arial_Bold_16x17, 0);
    
    while(1)
    {
        
    }
    
    return 0;
}
