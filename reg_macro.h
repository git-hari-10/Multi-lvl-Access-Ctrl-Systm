/* ---- I2C REGISTERS ---- */

#define AA_BIT   2
#define SI_BIT   3
#define STP_BIT  4
#define STA_BIT  5
#define I2EN_BIT 6

/* ----------------------- */


/* ---- SPEED CONFIGURES ---- */

#define PCLK           15000000          // 15MHz
#define I2C_SPEED       100000				   // 100 Kbps Speed 
#define VAL     ((PCLK/I2C_SPEED)/2)   

/* -------------------------- */

