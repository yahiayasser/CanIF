/*
 * CanIf_CanTrcv.h
 *
 *  Created on: 2 Feb 2020
 *      Author: Yahia
 */

#ifndef CANIF_CANTRCV_H_
#define CANIF_CANTRCV_H_




/* Module Version 1.0.0 */
#define CANIF_CANTRCV_SW_MAJOR_VERSION           (1U)
#define CANIF_CANTRCV_SW_MINOR_VERSION           (0U)
#define CANIF_CANTRCV_SW_PATCH_VERSION           (0U)

/* AUTOSAR Version 4.3.1 */
#define CANIF_CANTRCV_AR_RELEASE_MAJOR_VERSION   (4U)
#define CANIF_CANTRCV_AR_RELEASE_MINOR_VERSION   (3U)
#define CANIF_CANTRCV_AR_RELEASE_PATCH_VERSION   (1U)


#include "ComStack_Types.h"
/* AUTOSAR checking between ComStack_Types and CanIf_CanTrcv Modules */
#if ((COMSTACK_TYPES_AR_RELEASE_MAJOR_VERSION != CANIF_CANTRCV_AR_RELEASE_MAJOR_VERSION)\
 ||  (COMSTACK_TYPES_AR_RELEASE_MINOR_VERSION != CANIF_CANTRCV_AR_RELEASE_MINOR_VERSION)\
 ||  (COMSTACK_TYPES_AR_RELEASE_PATCH_VERSION != CANIF_CANTRCV_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of ComStack_Types.h does not match the expected version"
#endif
#include "BitHelper.h"




//************************************************************************
//						Function Callback Prototype
//************************************************************************



//************************************************************************
//						CanIf_ConfirmPnAvailability
//
//	Function Description    : This service indicates that the transceiver is running in PN
//							  communication mode referring to the corresponding CAN transceiver
//							  with the abstract CanIf TransceiverId.
//	Parameter in			: uint8 TransceiverId
//							  (Abstract CanIf TransceiverId, which is assigned to a CAN transceiver,
//							  which was checked for PN availability.)
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : none
//	Requirment				: SWS_CANIF_00815
//	Sync/Async				: Synchronous
//	Reentrancy				: Reentrant
//							  the same PduId.
//	Notes					:*If CanIf_ConfirmPnAvailability() is called, CanIf calls
//							  <User_ConfirmPnAvailability>().
//							 *CanIf passes the delivered parameter TransceiverId to the upper
//							  layer module.
//							 *If parameter TransceiverId of CanIf_ConfirmPnAvailability() has an
//							  invalid value, CanIf shall report development error code
//							  CANIF_E_PARAM_TRCV to the Det_ReportError service of the DET module,
//							  when CanIf_ConfirmPnAvailability() is called.
//							 *If CanIf was not initialized before calling CanIf_ConfirmPnAvailability(),
//							  CanIf shall not execute notification, when CanIf_ConfirmPnAvailability()
//							  is called.
//							 *The call context of CanIf_ConfirmPnAvailability() is either on interrupt
//							  level (interrupt mode) or on task level (polling mode).
//							 *Configuration of CanIf_ConfirmPnAvailability(): This function shall be
//							  pre compile time configurable ON/OFF by the configuration parameter
//							  CanIfPublicPnSupport.
//************************************************************************
extern void CanIf_ConfirmPnAvailability(uint8 TransceiverId);
//************************************************************************



//************************************************************************
//						CanIf_ClearTrcvWufFlagIndication
//
//	Function Description    : This service indicates that the transceiver has cleared the WufFlag
//							  referring to the corresponding CAN transceiver with the abstract
//							  CanIf TransceiverId.
//	Parameter in			: uint8 TransceiverId
//							  (Abstract CanIf TransceiverId, which is assigned to a CAN transceiver,
//							  which this function was called.)
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : none
//	Requirment				: SWS_CANIF_00762
//	Sync/Async				: Synchronous
//	Reentrancy				: Reentrant
//							  the same PduId.
//	Notes					:*If CanIf_ClearTrcvWufFlagIndication() is called, CanIf calls
//							  <User_ClearTrcvWufFlagIndication>().
//							 *CanIf passes the delivered parameter TransceiverId to the upper
//							  layer module.
//							 *If parameter TransceiverId of CanIf_ClearTrcvWufFlagIndication() has an
//							  invalid value, CanIf shall report development error code
//							  CANIF_E_PARAM_TRCV to the Det_ReportError service of the DET module,
//							  when CanIf_ClearTrcvWufFlagIndication() is called.
//							 *If CanIf was not initialized before calling
//							  CanIf_ClearTrcvWufFlagIndication(), CanIf shall not execute notification,
//							  when CanIf_ClearTrcvWufFlagIndication() is called.
//							 *The call context of CanIf_ClearTrcvWufFlagIndication() is either on
//							  interrupt level (interrupt mode) or on task level (polling mode).
//							 *Configuration of CanIf_ClearTrcvWufFlagIndication (): This function shall
//							  be pre compile time configurable ON/OFF by the configuration parameter
//							  CanIfPublicPnSupport.
//************************************************************************
extern void CanIf_ClearTrcvWufFlagIndication(uint8 TransceiverId);
//************************************************************************



//************************************************************************
//						CanIf_CheckTrcvWakeFlagIndication
//
//	Function Description    : This service indicates that the check of the transceiver’s wake-up flag
//							  has been finished by the corresponding CAN transceiver with the abstract
//							  CanIf TransceiverId. This indication is used to cope with the asynchronous
//							  transceiver communication.
//	Parameter in			: uint8 TransceiverId
//							  (Abstract CanIf TransceiverId, which is assigned to a CAN transceiver,
//							  which this function was called.)
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : none
//	Requirment				: SWS_CANIF_00763
//	Sync/Async				: Synchronous
//	Reentrancy				: Reentrant
//							  the same PduId.
//	Notes					:*If CanIf_CheckTrcvWakeFlagIndication() is called, CanIf calls
//							  <User_CheckTrcvWakeFlagIndication>().
//							 *CanIf passes the delivered parameter TransceiverId to the upper
//							  layer module.
//							 *If parameter TransceiverId of CanIf_CheckTrcvWakeFlagIndication() has an
//							  invalid value, CanIf shall report development error code
//							  CANIF_E_PARAM_TRCV to the Det_ReportError service of the DET module,
//							  when CanIf_CheckTrcvWufFlagIndication() is called.
//							 *If CanIf was not initialized before calling
//							  CanIf_CheckTrcvWufFlagIndication(), CanIf shall not execute notification,
//							  when CanIf_CheckTrcvWufFlagIndication() is called.
//							 *The call context of CanIf_CheckTrcvWufFlagIndication() is either on
//							  interrupt level (interrupt mode) or on task level (polling mode).
//							 *Configuration of CanIf_CheckTrcvWufFlagIndication (): This function shall
//							  be pre compile time configurable ON/OFF by the configuration parameter
//							  CanIfPublicPnSupport.
//************************************************************************
extern void CanIf_CheckTrcvWakeFlagIndication(uint8 TransceiverId);
//************************************************************************



//************************************************************************
//						CanIf_TrcvModeIndication
//
//	Function Description    : This service indicates a transceiver state transition referring to the
//							  corresponding CAN transceiver with the abstract CanIf TransceiverId.
//	Parameter in			: uint8 TransceiverId
//							  (Abstract CanIf TransceiverId, which is assigned to a CAN transceiver,
//							  which state has been transitioned.)
//							  CanTrcv_TrcvModeType TransceiverMode
//							  (Mode to which the CAN transceiver transitioned)
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : none
//	Requirment				: SWS_CANIF_00764
//	Sync/Async				: Synchronous
//	Reentrancy				: Reentrant
//							  the same PduId.
//	Notes					:*The callback service CanIf_TrcvModeIndication() is called by CanDrv and
//							  implemented in CanIf. It is called in case of a state transition
//							  notification of the CanDrv.
//							 *If parameter TransceiverId of CanIf_TrcvModeIndication() has an
//							  invalid value, CanIf shall report development error code
//							  CANIF_E_PARAM_TRCV to the Det_ReportError service of the DET module,
//							  when CanIf_TrcvModeIndication() is called.
//							 *If CanIf was not initialized before calling
//							  CanIf_TrcvModeIndication(), CanIf shall not execute notification,
//							  when CanIf_TrcvModeIndication() is called.
//							 *The call context of CanIf_TrcvModeIndication() is either on
//							  interrupt level (interrupt mode) or on task level (polling mode).
//							 *Configuration of CanIf_TrcvModeIndication(): If transceivers are not
//							  supported (CanIfTrcvDrvCfg is not configured, see CanIfTrcvDrvCfg),
//							  CanIf_TrcvModeIndication() shall not be provided by CanIf.
//************************************************************************
extern void CanIf_TrcvModeIndication(uint8 TransceiverId, CanTrcv_TrcvModeType TransceiverMode);
//************************************************************************

#endif /* CANIF_CANTRCV_H_ */
