/*
 * CanIf_Cbk.h
 *
 *  Created on: 5 Feb 2020
 *      Author: Yahia
 */

#ifndef __CANIF_CBK_H__
#define __CANIF_CBK_H__

/* Module Version 1.0.0 */
#define CANIF_CBK_SW_MAJOR_VERSION           (1U)
#define CANIF_CBK_SW_MINOR_VERSION           (0U)
#define CANIF_CBK_SW_PATCH_VERSION           (0U)

/* AUTOSAR Version 4.3.1 */
#define CANIF_CBK_AR_RELEASE_MAJOR_VERSION   (4U)
#define CANIF_CBK_AR_RELEASE_MINOR_VERSION   (3U)
#define CANIF_CBK_AR_RELEASE_PATCH_VERSION   (1U)

#include "Can_GeneralTypes.h"
/* AUTOSAR checking between Can_GeneralTypes and CanIf Modules */
#if ((CAN_GENERAL_TYPES_AR_RELEASE_MAJOR_VERSION != CANIF_CBK_AR_RELEASE_MAJOR_VERSION)\
 ||  (CAN_GENERAL_TYPES_AR_RELEASE_MINOR_VERSION != CANIF_CBK_AR_RELEASE_MINOR_VERSION)\
 ||  (CAN_GENERAL_TYPES_AR_RELEASE_PATCH_VERSION != CANIF_CBK_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Can_GeneralTypes.h does not match the expected version"
#endif

#include "Std_Types.h"
/* AUTOSAR checking between Std Types and CAN Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != CANIF_CBK_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != CANIF_CBK_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != CANIF_CBK_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif


//************************************************************************
//						Function Callback Prototype
//************************************************************************



//************************************************************************
//						CanIf_TriggerTransmit
//
//	Function Description    : Within this API, the upper layer module (called module)
//							  shall check whether the available data fits into the
//							  buffer size reported by PduInfoPtr->SduLength. If it
//							  fits, it shall copy its data into the buffer provided by
//							  PduInfoPtr->SduDataPtr and update the length of the
//							  actual copied data in PduInfoPtr->SduLength. If not, it
//							  returns E_NOT_OK without changing PduInfoPtr.
//	Parameter in			: PduIdType TxPduId
//							  (ID of the SDU that is requested to be transmitted.)
//	Parameter inout         : PduInfoType* PduInfoPtr
//							  (Contains a pointer to a buffer (SduDataPtr) to where
//							  the SDU data shall be copied, and the available buffer
//							  size in SduLengh. On return, the service will indicate
//							  the length of the copied SDU data in SduLength.)
//	Parameter out           : none
//	Return value            : Std_ReturnType (E_OK/E_NOT_OK)
//	Requirment				: SWS_CANIF_00883
//	Sync/Async				: Synchronous
//	Reentrancy				: Reentrant for different PduIds. Non reentrant for
//							  the same PduId.
//	Notes					:*CanIf shall only provide the API function
//							  CanIf_TriggerTransmit() if TriggerTransmit support is
//							  enabled (CanIfTriggerTransmitSupport = TRUE).
//							 *The function CanIf_TriggerTransmit() shall call the
//							  corresponding <User_TriggerTransmit>() function, passing
//							  the translated TxPduId and the pointer to the PduInfo
//							  structure (PduInfoPtr). Upon return, CanIf_TriggerTransmit()
//							  shall return the return value of its <User_TriggerTransmit>().
//************************************************************************
extern Std_ReturnType CanIf_TriggerTransmit(PduIdType TxPduId, PduInfoType* PduInfoPtr);
//************************************************************************



//************************************************************************
//						CanIf_TxConfirmation
//
//	Function Description    : This service confirms a previously successfully processed
//							  transmission of a CAN TxPDU.
//	Parameter in			: PduIdType CanTxPduId
//							  (ID of the SDU that is requested to be transmitted.)
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : none
//	Requirment				: SWS_CANIF_00007
//	Sync/Async				: Synchronous
//	Reentrancy				: Reentrant
//							  the same PduId.
//	Notes					:*The service CanIf_TxConfirmation() is implemented in CanIf and
//							  called by the CanDrv after the CAN L-PDU has been transmitted
//							  on the CAN network.
//							 *Due to the fact CanDrv does not support the HandleId concept as
//							  described in [14, Specification of ECU Configuration]: Within
//							  the service CanIf_TxConfirmation(), CanDrv uses PduInfo->swPduHandle
//							  as CanTxPduId, which was preserved from Can_Write(Hth, *PduInfo).
//							 *If configuration parameters CanIfPublicReadTxPduNotifyStatusApi and
//							  CanIfTxPduReadNotifyStatus for the Transmitted L-PDU are set to TRUE,
//							  and if CanIf_TxConfirmation() is called, CanIf shall set the
//							  notification status for the Transmitted L-PDU.
//							 *If parameter CanTxPduId of CanIf_TxConfirmation() has an invalid
//							  value, CanIf shall report development error code CANIF_E_PARAM_LPDU
//							  to the Det_ReportError service of the DET module, when
//							  CanIf_TxConfirmation() is called.
//							 *If CanIf was not initialized before calling CanIf_TxConfirmation(),
//							  CanIf shall not call the service <User_TxConfirmation>() and shall
//							  not set the Tx confirmation status, when CanIf_TxConfirmation() is
//							  called.
//							 *The call context of CanIf_TxConfirmation() is either on interrupt
//							  level (interrupt mode) or on task level (polling mode).
//							 *Configuration of CanIf_TxConfirmation(): Each Tx L-PDU (see
//							  CanIfTxPduCfg) has to be configured with a corresponding transmit
//							  confirmation service of an upper layer module (see [SWS_CANIF_00011])
//							  which is called in CanIf_TxConfirmation().
//************************************************************************
extern void CanIf_TxConfirmation(PduIdType CanTxPduId);
//************************************************************************



//************************************************************************
//						CanIf_RxIndication
//
//	Function Description    : This service indicates a successful reception of a received CAN
//							  Rx L-PDU to the CanIf after passing all filters and validation
//							  checks.
//	Parameter in			: const Can_HwType* Mailbox
//							  (Identifies the HRH and its corresponding CAN Controller)
//							  const PduInfoType* PduInfoPtr
//							  (Pointer to the received L-PDU)
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : none
//	Requirment				: SWS_CANIF_00006
//	Sync/Async				: Synchronous
//	Reentrancy				: Reentrant
//							  the same PduId.
//	Notes					:*The service CanIf_RxIndication() is implemented in CanIf and called
//							  by CanDrv after a CAN L-PDU has been received.
//							 *Within the service CanIf_RxIndication() the CanIf routes this
//							  indication to the configured upper layer target service(s).
//							 *If configuration parameters CanIfPublicReadRxPduNotifyStatusApi and
//							  CanIfRxPduReadNotifyStatus for the Received L-PDU are set to TRUE,
//							  and if CanIf_RxIndication() is called, the CanIf shall set the
//							  notification status for the Received L-PDU.
//							 *If parameter Mailbox->Hoh of CanIf_RxIndication() has an invalid
//							  value, CanIf shall report development error code CANIF_E_PARAM_HOH
//							  to the Det_ReportError service of the DET module, when
//							  CanIf_RxIndication() is called.
//							 *If parameter Mailbox->CanId of CanIf_RxIndication() has an invalid
//							  value, CanIf shall report development error code CANIF_E_PARAM_CANID
//							  to the Det_ReportError service of the DET module, when
//							  CanIf_RxIndication() is called.
//							 *If CanIf_RxIndication() is called with invalid PduInfoPtr-> SduLength,
//							  runtime error CANIF_E_INVALID_DATA_LENGTH is reported.
//							 *If parameter PduInfoPtr or Mailbox of CanIf_RxIndication() has an
//							  invalid value, CanIf shall report development error code
//							  CANIF_E_PARAM_POINTER to the Det_ReportError service of the DET module,
//							  when CanIf_RxIndication() is called.
//							 *If CanIf was not initialized before calling CanIf_RxIndication(), CanIf
//							  shall not execute Rx indication handling, when CanIf_RxIndication(), is
//							  called.
//							 *The call context of CanIf_RxIndication() is either on interrupt level
//							  (interrupt mode) or on task level (polling mode).
//							 *Configuration of CanIf_RxIndication(): Each Rx L-PDU (see CanIfRxPduCfg)
//							  has to be configured with a corresponding receive indication service of
//							  an upper layer module (see [SWS_CANIF_00012]) which is called in
//							  CanIf_RxIndication().
//************************************************************************
extern void CanIf_RxIndication(const Can_HwType* Mailbox, const PduInfoType* PduInfoPtr);
//************************************************************************



//************************************************************************
//						CanIf_ControllerBusOff
//
//	Function Description    : This service indicates a Controller BusOff event referring to the
//							  corresponding CAN Controller with the abstract CanIf ControllerId.
//	Parameter in			: uint8 ControllerId
//							  (Abstract CanIf ControllerId which is assigned to a CAN controller,
//							  where a BusOff occured.)
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : none
//	Requirment				: SWS_CANIF_00218
//	Sync/Async				: Synchronous
//	Reentrancy				: Reentrant
//							  the same PduId.
//	Notes					:*The callback service CanIf_ControllerBusOff() is called by CanDrv
//							  and implementedinCanIf. It is called in case of a mode change
//							  notification of the CanDrv.
//							 *If parameter ControllerId of CanIf_ControllerBusOff () has an invalid
//							  value, CanIf shall report development error code
//							  CANIF_E_PARAM_CONTROLLERID to the Det_ReportError service of the DET
//							  module, when CanIf_ControllerBusOff() is called.
//							 *If CanIf was not initialized before calling CanIf_ControllerBusOff(),
//							  CanIf shall not execute BusOff notification, when
//							  CanIf_ControllerBusOff(), is called.
//							 *The call context of CanIf_ControllerBusOff() is either on interrupt
//							  level (interrupt mode) or on task level (polling mode).
//							 *Configuration of CanIf_ControllerBusOff(): ID of the CAN Controller
//							  is published inside the configuration description of the CanIf
//							  (see CanIfCtrlCfg).
//							 *This service always has to be available, so there does not exist an
//							  appropriate configuration parameter.
//************************************************************************
extern void CanIf_ControllerBusOff(uint8 ControllerId);
//************************************************************************



//************************************************************************
//						CanIf_ControllerModeIndication
//
//	Function Description    : This service indicates a controller state transition referring to the
//							  corresponding CAN controller with the abstract CanIf ControllerId.
//	Parameter in			: uint8 ControllerId
//							  (Abstract CanIf ControllerId which is assigned to a CAN controller, which
//							  state has been transitioned.)
//							  Can_ControllerStateType ControllerMode
//							  (Mode to which the CAN controller transitioned)
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : none
//	Requirment				: SWS_CANIF_00699
//	Sync/Async				: Synchronous
//	Reentrancy				: Reentrant
//	Notes					:*The callback service CanIf_ControllerModeIndication() is called by
//							  CanDrv and implemented in CanIf. It is called in case of a state
//							  transition notification of the CanDrv.
//							 *If parameter ControllerId of CanIf_ControllerModeIndication() has an
//							  invalid value, CanIf shall report development error code
//							  CANIF_E_PARAM_CONTROLLERID to the Det_ReportError service of the DET module,
//							  when CanIf_ControllerModeIndication() is called.
//							 *If CanIf was not initialized before calling CanIf_ControllerModeIndication(),
//							  CanIf shall not execute state transition notification, when
//							  CanIf_ControllerModeIndication() is called.
//							 *The call context of CanIf_ControllerModeIndication() is either on interrupt
//							  level (interrupt mode) or on task level (polling mode).
//************************************************************************
extern void CanIf_ControllerModeIndication(uint8 ControllerId, Can_ControllerStateType ControllerMode);
//************************************************************************



//************************************************************************
//						CanIf_CurrentIcomConfiguration
//
//	Function Description    : This service shall inform about the change of the Icom Configuration
//							  of a CAN controller using the abstract CanIf ControllerId.
//	Parameter in			: uint8 ControllerId
//							  (Abstract CanIf ControllerId which is assigned to a CAN controller,
//							  which informs about the Configuration Id.)
//							  IcomConfigIdType ConfigurationId
//							  (Active Configuration Id.)
//							  IcomSwitch_ErrorType Error
//							  (ICOM_SWITCH_E_OK: No Error ICOM_SWITCH_E_FAILED: Switch to requested
//							  Configuration failed. Severe Error.)
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : none
//	Requirment				: SWS_CANIF_00862
//	Sync/Async				: Synchronous
//	Reentrancy				: Reentrant only for different controller Ids
//							  the same PduId.
//	Notes					:*TheinterfaceCanIf_CurrentIcomConfiguration()isusedbytheCanDrv to inform
//							  CanIf about the status of activation or deactivation of Pretended Networking
//							  for a given channel.
//							 *If CanIf_CurrentIcomConfiguration() is called, CanIf shall call CanSM_
//							  CurrentIcomConfiguration(ControllerId, ConfigurationId, Error) to inform
//							  CanSM about current status of ICOM.
//							 *If CanIf_CurrentIcomConfiguration() is called with invalidControllerId, CanIf
//							  shall report development error code CANIF_E_PARAM_CONTROLLERID to the
//							  Det_ReportError service of the DET module.
//							 *CanIf_CurrentIcomConfiguration() shall be pre compile time configurable ON/OFF
//							  by the configuration parameter CanIfPublicIcomSupport.
//************************************************************************
extern void CanIf_CurrentIcomConfiguration(uint8 ControllerId, IcomConfigIdType ConfigurationId, IcomSwitch_ErrorType Error);
//************************************************************************



#endif //__CANIF_CBK_H__

