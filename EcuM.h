/*
 * EcuM.h
 *
 *  Created on: 31 Jan 2020
 *      Author: Yahia
 */

#ifndef ECUM_H_
#define ECUM_H_

 /* Module Version 1.0.0 */
#define EcuM_SW_MAJOR_VERSION           (1U)
#define EcuM_SW_MINOR_VERSION           (0U)
#define EcuM_SW_PATCH_VERSION           (0U)

/* AUTOSAR Version 4.3.1 */
#define EcuM_AR_RELEASE_MAJOR_VERSION   (4U)
#define EcuM_AR_RELEASE_MINOR_VERSION   (3U)
#define EcuM_AR_RELEASE_PATCH_VERSION   (1U)

#include "Std_Types.h"
/* AUTOSAR checking between Std_Types and Can_GeneralTypes Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != EcuM_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != EcuM_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != EcuM_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif



/*
	[SWS_EcuM_04040]
	EcuM_WakeupSourceType defines a bitfield with 5 pre-defined positions (see Range).
	The bitfield provides one bit for each wakeup source.
	In WAKEUP, all bits cleared indicates that no wakeup source is known.
	In STARTUP, all bits cleared indicates that no reason for restart or reset is known. In
	this case, ECUM_WKSOURCE_RESET shall be assumed.
*/
typedef uint32 EcuM_WakeupSourceType;
/* Power cycle (bit 0) */
#define ECUM_WKSOURCE_POWER				((EcuM_WakeupSourceType) 0x01U)
/* Hardware reset (bit 1). If the Mcu driver cannot distinguish between a power cycle and a reset reason, then this shall be the default wakeup source. (default) */
#define ECUM_WKSOURCE_RESET				((EcuM_WakeupSourceType) 0x02U)
/* Internal reset of µC (bit 2) The internal reset typically only resets the µC core but not peripherals or memory controllers. The exact behavior is hardware specific. This source may also indicate an unhandled exception. */
#define ECUM_WKSOURCE_INTERNAL_RESET	((EcuM_WakeupSourceType) 0x04U)
/* Reset by internal watchdog (bit 3) */
#define ECUM_WKSOURCE_INTERNAL_WDG		((EcuM_WakeupSourceType) 0x08U)
/* Reset by external watchdog (bit 4), if detection supported by hardware */
#define ECUM_WKSOURCE_EXTERNAL_WDG		((EcuM_WakeupSourceType) 0x10U)



void EcuM_ValidateWakeupEvent(EcuM_WakeupSourceType sources);


#endif /* ECUM_H_ */
