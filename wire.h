/*
	@File 		
	@Author		JOSIMAR PEREIRA LEITE
	@country	Brazil
	@Date		20/06/21
	

    Copyright (C) 2021  JOSIMAR PEREIRA LEITE

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
 
  
*/

#ifndef WIRE_H
#define WIRE_H

#include <xc.h>

#define SCL_HIGH            PORTCbits.RC3=1
#define SCL_LOW             PORTCbits.RC3=0

#define SDA_HIGH            PORTCbits.RC4=1
#define SDA_LOW             PORTCbits.RC4=0

unsigned char Wire_Test(unsigned char Slave);
unsigned char Wire_Nack(void);
unsigned char Wire_Ack(void);
void Wire_Stop(void);
void Wire_Start(void);
void Wire_Write(unsigned char data);
void Wire_Init(void);

#endif	

