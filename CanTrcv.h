/*
 * CanTrcv.h
 *
 *  Created on: 3 Feb 2020
 *      Author: Yahia
 */

#ifndef CANTRCV_H_
#define CANTRCV_H_

/* Module Version 1.0.0 */
#define CAN_TRCV_SW_MAJOR_VERSION           (1U)
#define CAN_TRCV_SW_MINOR_VERSION           (0U)
#define CAN_TRCV_SW_PATCH_VERSION           (0U)

/* AUTOSAR Version 4.3.1 */
#define CAN_TRCV_AR_RELEASE_MAJOR_VERSION   (4U)
#define CAN_TRCV_AR_RELEASE_MINOR_VERSION   (3U)
#define CAN_TRCV_AR_RELEASE_PATCH_VERSION   (1U)

#include "ComStack_Types.h"
/* AUTOSAR checking between ComStack_Types and CAN_TRCV Modules */
#if ((COMSTACK_TYPES_AR_RELEASE_MAJOR_VERSION != CAN_TRCV_AR_RELEASE_MAJOR_VERSION)\
 ||  (COMSTACK_TYPES_AR_RELEASE_MINOR_VERSION != CAN_TRCV_AR_RELEASE_MINOR_VERSION)\
 ||  (COMSTACK_TYPES_AR_RELEASE_PATCH_VERSION != CAN_TRCV_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of ComStack_Types.h does not match the expected version"
#endif

#include "Can_GeneralTypes.h"
/* AUTOSAR checking between Can_GeneralTypes and CAN_TRCV Modules */
#if ((CAN_GENERAL_TYPES_AR_RELEASE_MAJOR_VERSION != CAN_TRCV_AR_RELEASE_MAJOR_VERSION)\
 ||  (CAN_GENERAL_TYPES_AR_RELEASE_MINOR_VERSION != CAN_TRCV_AR_RELEASE_MINOR_VERSION)\
 ||  (CAN_GENERAL_TYPES_AR_RELEASE_PATCH_VERSION != CAN_TRCV_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Can_GeneralTypes.h does not match the expected version"
#endif

#include "Std_Types.h"
/* AUTOSAR checking between Std_Types and CAN_TRCV Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != CAN_TRCV_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != CAN_TRCV_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != CAN_TRCV_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

extern Std_ReturnType CanTrcv_CheckWakeFlag(uint8 Transceiver);
extern Std_ReturnType CanTrcv_CheckWakeup(uint8 Transceiver);
extern Std_ReturnType CanTrcv_GetBusWuReason(uint8 Transceiver, CanTrcv_TrcvWakeupReasonType* reason);
extern Std_ReturnType CanTrcv_GetOpMode(uint8 Transceiver, CanTrcv_TrcvModeType* OpMode);
extern Std_ReturnType CanTrcv_SetOpMode(uint8 Transceiver, CanTrcv_TrcvModeType OpMode);
extern Std_ReturnType CanTrcv_SetWakeupMode(uint8 Transceiver, CanTrcv_TrcvWakeupModeType TrcvWakeupMode);

#endif /* CANTRCV_H_ */
