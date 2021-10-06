/*
 * CanIf_Types.h
 *
 *  Created on: 7 Feb 2020
 *      Author: Yahia
 */

#ifndef CANIF_TYPES_H_
#define CANIF_TYPES_H_

/* Module Version 1.0.0 */
#define CANIF_TYPES_SW_MAJOR_VERSION           (1U)
#define CANIF_TYPES_SW_MINOR_VERSION           (0U)
#define CANIF_TYPES_SW_PATCH_VERSION           (0U)

/* AUTOSAR Version 4.3.1 */
#define CANIF_TYPES_AR_RELEASE_MAJOR_VERSION   (4U)
#define CANIF_TYPES_AR_RELEASE_MINOR_VERSION   (3U)
#define CANIF_TYPES_AR_RELEASE_PATCH_VERSION   (1U)

#include "Std_Types.h"
/* AUTOSAR checking between Std_Types and CanIf_Types Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != CANIF_TYPES_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != CANIF_TYPES_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != CANIF_TYPES_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

#include "Can_GeneralTypes.h"
/* AUTOSAR checking between Can_GeneralTypes and CanIf_Types Modules */
#if ((CAN_GENERAL_TYPES_AR_RELEASE_MAJOR_VERSION != CANIF_TYPES_AR_RELEASE_MAJOR_VERSION)\
 ||  (CAN_GENERAL_TYPES_AR_RELEASE_MINOR_VERSION != CANIF_TYPES_AR_RELEASE_MINOR_VERSION)\
 ||  (CAN_GENERAL_TYPES_AR_RELEASE_PATCH_VERSION != CANIF_TYPES_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Can_GeneralTypes.h does not match the expected version"
#endif
#include "ComStack_Types.h"
/* AUTOSAR checking between ComStack_Types and CanIf_Types Modules */
#if ((COMSTACK_TYPES_AR_RELEASE_MAJOR_VERSION != CANIF_TYPES_AR_RELEASE_MAJOR_VERSION)\
 ||  (COMSTACK_TYPES_AR_RELEASE_MINOR_VERSION != CANIF_TYPES_AR_RELEASE_MINOR_VERSION)\
 ||  (COMSTACK_TYPES_AR_RELEASE_PATCH_VERSION != CANIF_TYPES_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of ComStack_Types.h does not match the expected version"
#endif


#endif /* CANIF_TYPES_H_ */
