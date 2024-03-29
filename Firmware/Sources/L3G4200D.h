/** ###################################################################
**     Filename    : L3G4200D.h
**     Project     : ProcessorExpert
**     Processor   : MC56F8257
**     Component   : L3G4200D
**     Version     : Driver 01.03
**     Compiler    : Metrowerks DSP C Compiler
**     Date/Time   : 2012-11-06, 21:40, # CodeGen: 0
**     Abstract    :
**         This gyro driver module.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/

#include "Quadro_Public.h"

/* I2C address */
#define L3G4200D_I2C_ADDR  0x68

/* Register addressing */
#define L3G_WHO_AM_I      (0x0F)
#define L3G_CTRL_REG1     (0x20)
#define L3G_CTRL_REG2     (0x21)
#define L3G_CTRL_REG3     (0x22)
#define L3G_CTRL_REG4     (0x23)
#define L3G_CTRL_REG5     (0x24)
#define L3G_REFERENCE     (0x25)
#define L3G_OUT_TEMP      (0x26)
#define L3G_STATUS_REG    (0x27)
#define L3G_OUT_X_L       (0x28)
#define L3G_OUT_X_H       (0x29)
#define L3G_OUT_Y_L       (0x2A)
#define L3G_OUT_Y_H       (0x2B)
#define L3G_OUT_Z_L       (0x2C)
#define L3G_OUT_Z_H       (0x2D)
#define L3G_FIFO_CTRL_REG (0x2E)
#define L3G_FIFO_SRC_REG  (0x2F)
#define L3G_INT1_CFG      (0x30)
#define L3G_INT1_SRC      (0x31)
#define L3G_INT1_TSH_XH   (0x32)
#define L3G_INT1_TSH_XL   (0x33)
#define L3G_INT1_TSH_YH   (0x34)
#define L3G_INT1_TSH_YL   (0x35)
#define L3G_INT1_TSH_ZH   (0x36)
#define L3G_INT1_TSH_ZL   (0x37)
#define L3G_INT1_DURATION (0x38)

#define FINDZERO 49

QuadRes L3G4200D_MeasuregyroSum();
QuadRes L3G4200D_EvaluateGyroRate();
QuadRes L3G4200D_InitializeGyro();
QuadRes L3G4200D_MeasureGyro();
QuadRes L3G4200D_CalibrateGyro();
QuadRes L3G4200D_ReadGyroTemp();
