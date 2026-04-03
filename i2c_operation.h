/* ---- I2C READ & WRITE OPERATIONS ---- */

#include "i2c_internal.h"

void Byte_Write(u8, u8, u8);
u8 Random_Read(u8, u8);
void Page_Write(u8, u8, u8*, u8);
void Seq_Read(u8, u8, u8*, u8);


void Byte_Write(u8 SlaveAddr, u8 WordAddr, u8 DataWord)
{
	I2C_St();
	I2C_Write(SlaveAddr<<1);
	I2C_Write(WordAddr);
	I2C_Write(DataWord);
	I2C_Stp();
}

u8 Random_Read(u8 SlaveAddr, u8 WordAddr)
{
	u8 read;
	I2C_St();
	I2C_Write(SlaveAddr<<1);
	I2C_Write(WordAddr);
	I2C_reSt();
	I2C_Write((SlaveAddr<<1)|1);
	read = I2C_noAck();
	I2C_Stp();
	return read;
}

void Page_Write(u8 SlaveAddr, u8 WordAddr, u8 *s, u8 nbyte)
{
	int i;
	I2C_St();
	I2C_Write(SlaveAddr<<1);
	I2C_Write(WordAddr);
	for(i=0;i<nbyte;i++)
		I2C_Write(s[i]);
	I2C_Stp();
}

void Seq_Read(u8 SlaveAddr, u8 WordAddr, u8 *s, u8 nbyte)
{
	int i;
	I2C_St();
	I2C_Write(SlaveAddr<<1);
	I2C_Write(WordAddr);
	I2C_reSt();
	I2C_Write((SlaveAddr<<1)|1);
	for(i=0;i<nbyte-1;i++)
		s[i] = I2C_M_ack();
	s[i] = I2C_noAck();
	I2C_Stp();
}

/* -------------------------------------- */
