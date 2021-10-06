/*
 * CanIf.c
 *
 *  Created on: 3 Feb 2020
 *      Author: Yahia
 */

/*****************************************************************************************/
/*                                   Include Common headres                              */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                   Include Other  headres                              */
/*****************************************************************************************/

#include "Det.h"

/*****************************************************************************************/
/*                                   Include Component headres                           */
/*****************************************************************************************/

#include "CanIf.h"
#include "PduR_CanIf.h"
#include "CanTp_Cbk.h"
#include "CanSm_Cbk.h"
#include "CanNm_Cbk.h"
#include "CanTSyn_Cbk.h"
#include "J1939Nm_Cbk.h"
#include "Xcp_Cbk.h"
#include "irq.h"


/*****************************************************************************************/
/*                                   Local Macro Definition                              */
/*****************************************************************************************/
#define valid                     (1U)
#define invalid                   (0U)
#define MAX_CONTROLLERS_NUMBER    NUM_OF_CAN_CONTROLLERS


/*****************************************************************************************/
/*                                Exported Variables Definition                          */
/*****************************************************************************************/

/*	  [ECUC_CanIf_00546]															   */
/*    Type Description    : This container contains the configuration (parameters) of  */
/* 	  an adressed CAN controller by an underlying CAN Driver module. This container is */
/* 	  configurable per CAN controller.                       						   */
extern CanIfCtrlCfg CanIfCtrlCfg_CONTAINER[CanIf_MAX_CONTROLLERS_NUMBER];

/*	  [ECUC_CanIf_00628]															   */
/*    Type Description    : Defines the parameters required for configurating multiple */
/* 	  CANID ranges for a given same HRH.											   */
extern CanIfHrhRangeCfg CanIfHrhRangeCfg_CONTAINER[CanIf_MAX_HRH_RANGE];

/*	  [ECUC_CanIf_00259]															   */
/*    Type Description    : This container contains configuration parameters for each  */
/* 	  hardware receive object (HRH).												   */
extern CanIfHrhCfg CanIfHrhCfg_CONTAINER[CAN_HRH_NUMBER];

/*	  [ECUC_CanIf_00258]															   */
/*    Type Description    : This container contains parameters related to each HTH.    */
extern CanIfHthCfg CanIfHthCfg_CONTAINER[CAN_HTH_NUMBER];

/*	  [ECUC_CanIf_00257]															   */
/*    Type Description    : This container contains the references to the configuration*/
/* 	  setup of each underlying CAN Driver.											   */
extern CanIfInitHohCfg CanIfInitHohCfg_CONTAINER[CanIf_MAX_HOH_NUMBER];

/*	  [ECUC_CanIf_00832]															   */
/*    Type Description    : This container contains the Txbuffer configuration. 	   */
/* 	  Multiple buffers with different sizes could be configured. If CanIfBufferSize    */
/* 	  equals 0, the CanIf Tx L-PDU only refers via this CanIfBufferCfg the 		   	   */
/*    corresponding CanIfHthCfg.													   */
extern CanIfBufferCfg CanIfBufferCfg_CONTAINER[CanIf_MAX_BUFFER_NUMBER];

/*	  [ECUC_CanIf_00248]															   */
/*    Type Description    : This container contains the configuration (parameters) of  */
/* 	  a transmit CAN L-PDU. It has to be configured as often as a transmit CAN L-PDU   */
/* 	  is needed. The SHORT-NAME of "CanIfTxPduConfig" container represents the symolic */
/*    name of Transmit L-PDU. This L-SDU consumes a meta data item of type CAN_ID_32.  */
extern CanIfTxPduCfg CanIfTxPduCfg_CONTAINER[CanIf_MAX_TxPDU_NUMBER];

/*	  [ECUC_CanIf_00249]															   */
/*    Type Description    : This container contains the configuration (parameters) of  */
/* 	  each receive CAN L-PDU. It has to be configured as often as a transmit CAN L-PDU */
/* 	  is needed. The SHORT-NAME of "CanIfTxPduConfig" container represents the symolic */
/*    name of Transmit L-PDU. This L-SDU consumes a meta data item of type CAN_ID_32.  */
extern CanIfRxPduCfg CanIfRxPduCfg_CONTAINER[CanIf_MAX_RxPDU_NUMBER];

/*	  [ECUC_CanIf_00246]															   */
/*    Type Description    : This container contains the public configuration 		   */
/* 	  (parameters) of the CAN Interface.											   */
extern CanIfPublicCfg CanIfPublicCfg_CONTAINER[CanIf_MAX_PUBLIC_CONFIG_NUMBER];

/*	  [ECUC_CanIf_00245]															   */
/*    Type Description    : This container contains the private configuration 		   */
/* 	  (parameters) of the CAN Interface.											   */
extern CanIfPrivateCfg CanIfPrivateCfg_CONTAINER[CanIf_MAX_PRIVATE_CONFIG_NUMBER];

/*	  [ECUC_CanIf_00247]															   */
/*    Type Description    : This container contains the init parameters of the CAN     */
/* 	  Interface.																	   */
extern CanIfInitCfg CanIfInitCfg_CONTAINER[CanIf_MAX_INIT_SETS];

/*	  [ECUC_CanIf_00244]															   */
/*    Type Description    : This container includes all necessary configuration        */
/* 	  sub-containers according the CAN Interface configuration structure.			   */
extern CanIf_ConfigType CanIf_ConfigType_CONTAINER[CanIf_MAX_CONFIGURATION_SETS];


/*****************************************************************************************/
/*                                Local Variables Definition                             */
/*****************************************************************************************/


/* Type Description    : Flag to check if the interrupt is disabled by another function */
/* FALSE: Interrupt is not disabled by another function.							    */
/* TRUE	: Interrupt is disabled by another function.								    */
extern uint8 InterruptIsAlreadyDisabled_Flag;

/*    Type Description       : variable to save Module state                             */
/*                             After power-up/reset, the Can module shall be in the state*/
/*                             CAN_UNINIT.   (SRS_BSW_00406)                             */
/*    Requirment              : SRS                                                      */
static CanIf_ModuleStateType ModuleState = CANIF_UNINIT;



/*****************************************************************************************/
/*                                   Local Function Definition                           */
/*****************************************************************************************/

//************************************************************************
//						CanIf_Init
//
//	Function Description    : This service Initializes internal and
//							  external interfaces of the CAN Interface
//							  for the further processing.
//	Parameter in			: const CanIf_ConfigType* ConfigPtr
//							  (Pointer to configuration parameter set,
//							  used e.g. for post build parameters)
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : none
//	Requirment				: SWS_CANIF_00001
//	Sync/Async				: Synchronous
//	Reentrancy				: Non Reentrant
//************************************************************************
void CanIf_Init(const CanIf_ConfigType* ConfigPtr)
{
	/* [SRS_BSW_00101]
	   The Basic Software Module shall be able to initialize variables and hardware
	   in a separate initialization function
	 * [SRS_BSW_00358]
	   The return type of init() functions implemented by AUTOSAR Basic Software
	   Modules shall be void
	 * [SRS_BSW_00414]
	   Init functions shall have a pointer to a configuration structure as single
	   parameter
	 * [SRS_Can_01021]
	   CAN The CAN Interface shall implement an interface for initialization
	 * [SRS_Can_01022]
	   The CAN Interface shall support the selection of configuration sets
	 * [SWS_CANIF_00085]
	   The service CanIf_Init() shall initialize the global variables and data
	   structures of the CanIf including flags and buffers.
	 */


#if(STD_ON == CANIF_DevErrorDetect)
	/* Report error CAN_E_PARAM_POINTER API called with wrong parameter */
	/* [SRS_BSW_00323]
	   All AUTOSAR Basic Software Modules shall check passed API parameters for validity
	 */
	if((NULL_PTR == CanIfCtrlCfg_CONTAINER) || (NULL_PTR == CanIfHrhRangeCfg_CONTAINER) ||\
			(NULL_PTR == CanIfHrhCfg_CONTAINER) || (NULL_PTR == CanIfHthCfg_CONTAINER) ||\
			(NULL_PTR == CanIfInitHohCfg_CONTAINER) || (NULL_PTR == CanIfBufferCfg_CONTAINER) ||\
			(NULL_PTR == CanIfTxPduCfg_CONTAINER) || (NULL_PTR == CanIfRxPduCfg_CONTAINER) ||\
			(NULL_PTR == CanIfPublicCfg_CONTAINER) || (NULL_PTR == CanIfPrivateCfg_CONTAINER) ||\
			(NULL_PTR == CanIfInitCfg_CONTAINER) || (NULL_PTR == CanIf_ConfigType_CONTAINER)){
		Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CanIf_Init_API, CANIF_E_PARAM_POINTER);
	}
	else
	{

	}

	/* The function CanIf_Init shall raise the error CANIF_E_UNINIT if the driver is not in
	 *   state CANIF_UNINIT
	 */
	if(CANIF_UNINIT != ModuleState)
	{
		Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CanIf_Init_API, CANIF_E_UNINIT);
	}
	else
	{

	}
#endif

	/* The function CanIf_Init shall change the module state to CAN_READY. */
	ModuleState = CANIF_READY;

}


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
//************************************************************************
Std_ReturnType CanIf_TriggerTransmit(PduIdType TxPduId, PduInfoType* PduInfoPtr)
{

	/* If the CAN hardware is free Can_Write() requests the SDU data from CanIf by its
	   service CanIf_TriggerTransmit() passing the L-SDUs corresponding ID and a pointer
	   to the CAN hardware’s buffer. CanIf forwards the trigger transmit request to the
	   corresponding upper layer (CanIfUser). CanIf passes the buffer pointer received
	   by CanDrv. The CanIfUser finally copies the SDU data to the buffer provided by
	   CanIf (the CAN hardware buffer) and returns status and number of bytes effectively
	   written.
	   */

	/* returnVal carries the return value of CanIf_TriggerTransmit */
	Std_ReturnType returnVal = E_NOT_OK;

	/* ui32CanIfTxPduCfg_Count is the counter for CanIfTxPduCfg_CONTAINER */
	uint32 ui32CanIfTxPduCfg_Count = 0;

	/* ui8CanIfTxPduNotFound_Flag is a flag that indicates if we find PDU in
	   CanIfTxPduCfg_CONTAINER or not */
	uint8 ui8CanIfTxPduNotFound_Flag = TRUE;

	/*
	 [SWS_CANIF_00884]
	 CanIf shall only provide the API function CanIf_TriggerTransmit() if TriggerTransmit
	 support is enabled (CanIfTriggerTransmitSupport = TRUE).
	 */
	if (STD_OFF == (CanIfPublicCfg_CONTAINER -> CanIfTriggerTransmitSupport))
	{
		return returnVal;
	}
	else
	{

	}

#if(STD_ON == CANIF_DevErrorDetect)

	/* The function CanIf_Init shall raise the error CANIF_E_UNINIT if the driver is not in
	 *   state CANIF_UNINIT
	 */
	/* Check the module state */
	if(CANIF_UNINIT == ModuleState)
	{
		/* Report error CANIF_E_UNINIT */
		Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CanIf_TriggerTransmit_API, CANIF_E_UNINIT);
	}
	/* Check the PduInfoPtr that is passed by the underlaying function */
	else if(NULL_PTR == PduInfoPtr)
	{
		/* Report error CANIF_E_PARAM_POINTER */
		Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CanIf_TriggerTransmit_API, CANIF_E_PARAM_POINTER);
	}
	else
	{

#endif
		/* Loop on CanIfTxPduCfg_CONTAINER */
		for(ui32CanIfTxPduCfg_Count = 0; ui32CanIfTxPduCfg_Count < CanIf_MAX_TxPDU_NUMBER; ui32CanIfTxPduCfg_Count++)
		{
			/* Check if we find PDU ID in CanIfTxPduCfg_CONTAINER */
			if(TxPduId == (CanIfTxPduCfg_CONTAINER[ui32CanIfTxPduCfg_Count].CanIfTxPduId))
			{
				/* Check if data length check is available and the can type used is Standard Can */
				if((STD_ON == (CanIfPrivateCfg_CONTAINER -> CanIfPrivateDataLengthCheck)) &&\
						((STANDARD_CAN == CanIfTxPduCfg_CONTAINER[ui32CanIfTxPduCfg_Count].CanIfTxPduCanIdType) || \
								(STANDARD_FD_CAN == CanIfTxPduCfg_CONTAINER[ui32CanIfTxPduCfg_Count].CanIfTxPduCanIdType)))
				{
					/* Check if PDU length exceeds the maximum length of Standard Can */
					if(PduInfoPtr -> SduLength > 8)
					{
						return returnVal;
					}
					else{}
				}
				/* Check if data length check is available and the can type used is Extended Can */
				else if((STD_ON == (CanIfPrivateCfg_CONTAINER -> CanIfPrivateDataLengthCheck)) &&\
						((EXTENDED_CAN == CanIfTxPduCfg_CONTAINER[ui32CanIfTxPduCfg_Count].CanIfTxPduCanIdType) || \
								(EXTENDED_FD_CAN == CanIfTxPduCfg_CONTAINER[ui32CanIfTxPduCfg_Count].CanIfTxPduCanIdType) ||\
								(MIXED_CAN == CanIfTxPduCfg_CONTAINER[ui32CanIfTxPduCfg_Count].CanIfTxPduCanIdType)))
				{
					/* Check if PDU length exceeds the maximum length of Extended Can */
					if(PduInfoPtr -> SduLength > 64)
					{
						return returnVal;
					}
					else{}
				}
				/* Check if the function pointer that should be called is null pointer */
				else if(NULL_PTR == CanIfTxPduCfg_CONTAINER[ui32CanIfTxPduCfg_Count].CanIfTxPduUserTriggerTransmitName)
				{
					return returnVal;
				}
				else
				{
					/* PDU ID found correctly */
					ui8CanIfTxPduNotFound_Flag = FALSE;
					/* Exit from the loop */
					break;
				}
			}
		}

		/* Check if we did not find the PDU ID in CanIfTxPduCfg_CONTAINER */
		if(TRUE == ui8CanIfTxPduNotFound_Flag)
		{
#if(STD_ON == CANIF_DevErrorDetect)
			/* Report error CANIF_E_INVALID_TXPDUID */
			Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CanIf_TriggerTransmit_API, CANIF_E_INVALID_TXPDUID);
#endif
		}
		else
		{
			/* [SWS_CANIF_00885]
			 * The function CanIf_TriggerTransmit() shall call the corresponding <User_TriggerTransmit>() function,
			   passing the translated TxPduId and the pointer to the PduInfo structure (PduInfoPtr). */
			if((CANIF_USER_CAN_NM == CanIfTxPduCfg_CONTAINER[ui32CanIfTxPduCfg_Count].CanIfTxPduUserTxConfirmationUL) &&\
					(CanNm_TriggerTransmit == CanIfTxPduCfg_CONTAINER[ui32CanIfTxPduCfg_Count].CanIfTxPduUserTriggerTransmitName))
			{
				/* Upon return, CanIf_TriggerTransmit() shall return the return value of its <User_TriggerTransmit>(). */
				return CanNm_TriggerTransmit(TxPduId, PduInfoPtr);
			}
			else if((CANIF_USER_PDUR == CanIfTxPduCfg_CONTAINER[ui32CanIfTxPduCfg_Count].CanIfTxPduUserTxConfirmationUL) &&\
					(PduR_CanIfTriggerTransmit == CanIfTxPduCfg_CONTAINER[ui32CanIfTxPduCfg_Count].CanIfTxPduUserTriggerTransmitName))
			{
				/* Upon return, CanIf_TriggerTransmit() shall return the return value of its <User_TriggerTransmit>(). */
				return PduR_CanIfTriggerTransmit(TxPduId, PduInfoPtr);
			}
			else if((CANIF_USER_XCP == CanIfTxPduCfg_CONTAINER[ui32CanIfTxPduCfg_Count].CanIfTxPduUserTxConfirmationUL) &&\
					(Xcp_CanIfTriggerTransmit == CanIfTxPduCfg_CONTAINER[ui32CanIfTxPduCfg_Count].CanIfTxPduUserTriggerTransmitName))
			{
				/* Upon return, CanIf_TriggerTransmit() shall return the return value of its <User_TriggerTransmit>(). */
				return Xcp_CanIfTriggerTransmit(TxPduId, PduInfoPtr);
			}
			else{}
		}
	}
	return returnVal;
}


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
//************************************************************************
void CanIf_ControllerBusOff(uint8 ControllerId)
{
	/* [SWS_CANIF_00218]
	 * This service indicates a Controller BusOff event referring to the corresponding CAN Controller with the abstract
	   CanIf ControllerId.
	 * The callback service CanIf_ControllerBusOff() is called by CanDrv and implementedinCanIf. It is called in case of
	   a mode change notification of the CanDrv.
	 * The call context of CanIf_ControllerBusOff() is either on interrupt level (interrupt mode) or on task level
	   (polling mode).
	 * This service always has to be available, so there does not exist an appropriate configuration parameter.
	 */

	/*	Disable interrupts	*/
	/*	Check if the interrupts is already disabled by another function	*/

	/* Type Description    : Flag to know whether if the interrupt should be enabled or not.*/
	/* This flag should be TRUE in the case that interrupt is disabled by another function  */
	/* and the current function that is being executed is called by that function's critical*/
	/* section so it should be the one who enables the interrupt back.						*/
	/* FALSE: Interrupt should be enabled													*/
	/* TRUE : Interrupt should not be enabled												*/
	uint8 ui8InterruptDontEnable_Flag = FALSE;

	if(False == InterruptIsAlreadyDisabled_Flag)
	{
		/*	If the interrupts is not disabled by another function, we 		*/
		/*	should disable it. and set the InterruptIsAlreadyDisabled_Flag	*/
		irq_Disable();
		InterruptIsAlreadyDisabled_Flag = TRUE;
		ui8InterruptDontEnable_Flag = FALSE;
	}
	else
	{
		/*	If the interrupts is disabled by another function, we should	*/
		/*	only set the ui8InterruptDontEnable_Flag to prevent this function	*/
		/*	from enabling the interrupt										*/
		ui8InterruptDontEnable_Flag = TRUE;
	}

	/* Counter used to loop on CanIfCtrlCfg_CONTAINER 						*/
	uint32 ui32CanIfCtrlCfg_Count = 0;

	/* Flag to check if the ControllerId is found in CanIfCtrlCfg_CONTAINER */
	uint8 ui8CanIfControllerIDNotFound_Flag = TRUE;

	/* Loop on the CanIfCtrlCfg_CONTAINER to find the ControllerId */
	for(ui32CanIfCtrlCfg_Count = 0; ui32CanIfCtrlCfg_Count < CanIf_MAX_CONTROLLERS_NUMBER; ui32CanIfCtrlCfg_Count++)
	{
		/* Configuration of CanIf_ControllerBusOff(): ID of the CAN 	*/
		/* Controller is published inside the configuration description */
		/* of the CanIf (see CanIfCtrlCfg).								*/

		/* Check if we found the ControllerId in CanIfCtrlCfg_CONTAINER */
		if(ControllerId == (CanIfCtrlCfg_CONTAINER[ui32CanIfCtrlCfg_Count].CanIfCtrlId))
		{
			/* Controller Id found correctly */
			ui8CanIfControllerIDNotFound_Flag = FALSE;
			/* Exit from the loop */
			break;
		}
		else{}
	}

	/*	Check if we found the ControllerIdin CanIfCtrlCfg_CONTAINER		*/
	if(TRUE == ui8CanIfControllerIDNotFound_Flag)
	{

#if(STD_ON == CANIF_DevErrorDetect)

		/* [SRS_BSW_00323]
		 * dIf parameter ControllerId of CanIf_ControllerBusOff () has an invalid value, CanIf shall report development error
		   code CANIF_E_PARAM_CONTROLLERID to the Det_ReportError service of the DET module, when CanIf_ControllerBusOff()
		   is called.
		 */
		Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, CanIf_ControllerBusOff_API, CANIF_E_PARAM_CONTROLLERID);
#endif

	}
	else if(CANIF_UNINIT == ModuleState)
	{
		/* If CanIf was not initialized before calling CanIf_ControllerBusOff(), CanIf shall not execute BusOff notification,
		   when CanIf_ControllerBusOff(), is called.
		 */
	}
	else
	{
		/* [SWS_CANIF_00724]
		 * When callback CanIf_ControllerBusOff(ControllerId) is called, the CanIf shall call CanSM_ControllerBusOff(ControllerId)
		   of the CanSm
		 */
		CanSM_ControllerBusOff(ControllerId);

		/* [SWS_CANIF_00866]
		 * If CanIf_SetControllerMode(ControllerId, CAN_CS_STOPPED) or CanIf_ControllerBusOff(ControllerId) is called, CanIf
		   shall set the PDU channel mode of the corresponding channel to CANIF_TX_OFFLINE.
		 */
		CanIf_SetPduMode(ControllerId, CANIF_TX_OFFLINE);
	}

	/* Check the ui8InterruptDontEnable_Flag flag to determine if we should enable the interrupt or not */
	if(TRUE == ui8InterruptDontEnable_Flag)
	{
		/* Reset ui8InterruptDontEnable_Flag flag without enabling interrupts */
		ui8InterruptDontEnable_Flag = FALSE;
	}
	else
	{
		/* Reset InterruptIsAlreadyDisabled_Flag flag and enable interrupts */
		InterruptIsAlreadyDisabled_Flag = FALSE;
		irq_Disable();
	}

}



