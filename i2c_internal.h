#include "datatypes.h"
#include "reg_macro.h"

void I2C_init()
{
	PINSEL0  |= 0x50;        // Configure p0.2 as SCL & p0.3 as SDA
	I2SCLL    = VAL;
	I2SCLH    = VAL;         // Configure speed as 100 Kbps
	I2CONSET  = 1<<I2EN_BIT; // Enable I2C 
}

void I2C_St()              // START CONDITION
{
	I2CONSET = 1<<STA_BIT;
	while(!((I2CONSET>>SI_BIT)&1));
	I2CONCLR = 1<<STA_BIT;
}

void I2C_Stp()             // STOP CONDITION
{ 
	I2CONSET = 1<<STP_BIT;
	I2CONCLR = 1<<SI_BIT;
}

void I2C_reSt()            // RESTART CONDITION
{
	I2CONSET = 1<<STA_BIT;
	I2CONCLR = 1<<SI_BIT;
	while(!((I2CONSET>>SI_BIT)&1));
	I2CONCLR = 1<<STA_BIT;
}

void I2C_Write(u8 data)   // I2C WRITE TO EEPROM
{
	I2DAT = data;
	I2CONCLR = 1<<SI_BIT;
	while(!((I2CONSET>>SI_BIT)&1));
}

u8 I2C_noAck()            // NO ACKNOWLEDGEMENT
{
	I2CONCLR = 1<<AA_BIT;
	I2CONCLR = 1<<SI_BIT;
	while(!((I2CONSET>>SI_BIT)&1));
	return I2DAT;
}

u8 I2C_M_ack()           // MASTER ACKNOWLEDGEMENT
{
	I2CONSET = 1<<AA_BIT;
	I2CONCLR = 1<<SI_BIT;
	while(!((I2CONSET>>SI_BIT)&1));
	return I2DAT;
}


