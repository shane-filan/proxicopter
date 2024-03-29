/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : PE_Const.h
**     Project     : ProcessorExpert
**     Processor   : MC56F8257
**     Component   : PE_Const
**     Version     : Driver 01.02
**     Compiler    : Metrowerks DSP C Compiler
**     Date/Time   : 2012-11-22, 23:31, # CodeGen: 33
**     Abstract    :
**         This component "PE_Const" contains internal definitions
**         of the constants.
**     Settings    :
**     Contents    :
**         No public methods
**
**     Copyright : 1997 - 2011 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

#ifndef __PE_Const_H
#define __PE_Const_H

/* Constants for detecting running mode */
#define HIGH_SPEED        0x00         /* High speed */
#define LOW_SPEED         0x01         /* Low speed */
#define SLOW_SPEED        0x02         /* Slow speed */

/* Reset cause constants */
#define RSTSRC_POR        0x04         /* Power-on reset */
#define RSTSRC_PIN        0x08         /* External reset bit */
#define RSTSRC_COP_LOR    0x10         /* COP Loss of Reference reset */
#define RSTSRC_COP_CPU    0x20         /* CPU Time-Out reset */
#define RSTSRC_SWR        0x40         /* Software reset */

/* Memory modes */
#define INT_EXT_MODE      0x00         /* Internal & external memory mode */
#define EXT_MODE          0x01         /* External memory mode */

#endif /* _PE_Const_H */
/*
** ###################################################################
**
**     This file was created by Processor Expert 5.3 [05.01]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
