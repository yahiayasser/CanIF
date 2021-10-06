/*
 * CanIf.h
 *
 *  Created on: 31 Jan 2020
 *      Author: Yahia
 */

#ifndef CANIF_H_
#define CANIF_H_

/* Module Version 1.0.0 */
#define CANIF_SW_MAJOR_VERSION           (1U)
#define CANIF_SW_MINOR_VERSION           (0U)
#define CANIF_SW_PATCH_VERSION           (0U)

/* AUTOSAR Version 4.3.1 */
#define CANIF_AR_RELEASE_MAJOR_VERSION   (4U)
#define CANIF_AR_RELEASE_MINOR_VERSION   (3U)
#define CANIF_AR_RELEASE_PATCH_VERSION   (1U)

#include "CanIf_Types.h"
/* AUTOSAR checking between CanIf and CanIf_Types Modules */
#if ((CANIF_AR_RELEASE_MAJOR_VERSION != CANIF_TYPES_AR_RELEASE_MAJOR_VERSION)\
 ||  (CANIF_AR_RELEASE_MINOR_VERSION != CANIF_TYPES_AR_RELEASE_MINOR_VERSION)\
 ||  (CANIF_AR_RELEASE_PATCH_VERSION != CANIF_TYPES_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

#include "BitHelper.h"
#include "SchM_Can.h"
#include "CanTrcv.h"
#include "CanTrcv.h"
#include "Can.h"
#include "CanIf_PBcfg.h"
#include "CanIf_Cfg.h"
#include "EcuM.h"
/* [SRS_Can_01172]
 * CanIf shall include the header file Mirror.h if Bus Mirroring is enabled
*/
#if(STD_ON == CANIF_BusMirroringSupport)
#include "Mirror.h"
#endif

/*****************************************************************************************/
/*                                    Macro Definition                                   */
/*****************************************************************************************/
/* Id for the company in the AUTOSAR
  **/
#define CANIF_VENDOR_ID    (0x100)

/* CANIF Module Id */
#define CANIF_MODULE_ID    (0x03C)

/* CANIF Instance Id */
#define CANIF_INSTANCE_ID  (0U)

/* PDU Type */
typedef uint8 Can_TypeType;
#define PDU_STATIC	((Can_TypeType)0x00)
#define PDU_DYNAMIC	((Can_TypeType)0x01)

/* CanIf Users Enum */
typedef uint8 CanIf_UserType;
#define	CANIF_USER_CAN_NM		((CanIf_UserType)0x00)
#define	CANIF_USER_CAN_TP		((CanIf_UserType)0x01)
#define	CANIF_USER_CAN_TSyn 	((CanIf_UserType)0x02)
#define	CANIF_USER_CDD 			((CanIf_UserType)0x03)
#define	CANIF_USER_J1939NM 		((CanIf_UserType)0x04)
#define	CANIF_USER_J1939TP	 	((CanIf_UserType)0x05)
#define	CANIF_USER_PDUR			((CanIf_UserType)0x06)
#define	CANIF_USER_XCP 			((CanIf_UserType)0x07)

/* software filtering methods */
typedef uint8 CanIf_SwFilterType;
#define	CANIF_SW_FILTER_BINARY	((CanIf_SwFilterType)0x00)
#define	CANIF_SW_FILTER_INDEX	((CanIf_SwFilterType)0x01)
#define	CANIF_SW_FILTER_LINEAR	((CanIf_SwFilterType)0x02)
#define	CANIF_SW_FILTER_TABLE	((CanIf_SwFilterType)0x03)


/* CanIf_ModuleStateType ENUM */
/*    Type Description        : variable define can Module state                         */
/*    Type range              :  0->1                                                 */
/*    Requirment              : SWS                                                      */
typedef enum{
/*  CanIf_ModuleStateType
 *  CANIF_UNINIT : After power-up/reset, the Can module shall be in the state CAN_UNINIT.
 *  CANIF_READY  : The function Can_Init shall change the module state to CANIF_READY
 */
	CANIF_UNINIT,
	CANIF_READY
}CanIf_ModuleStateType;

/* CanIf_DetErrorType ENUM */
typedef enum{
	CANIF_E_PARAM_CANID = 10,
	CANIF_E_PARAM_HOH = 12,
	CANIF_E_PARAM_LPDU,
	CANIF_E_PARAM_CONTROLLERID = 15,
	CANIF_E_PARAM_WAKEUPSOURCE,
	CANIF_E_PARAM_TRCV,
	CANIF_E_PARAM_TRCVMODE,
	CANIF_E_PARAM_TRCVWAKEUPMODE,
	CANIF_E_PARAM_POINTER,
	CANIF_E_PARAM_CTRLMODE,
	CANIF_E_PARAM_PDU_MODE,
	CANIF_E_UNINIT = 30,
	CANIF_E_INVALID_TXPDUID = 50,
	CANIF_E_INVALID_RXPDUID = 60,
	CANIF_E_INVALID_DATA_LENGTH,
	CANIF_E_DATA_LENGTH_MISMATCH,
	CANIF_E_STOPPED = 70,
	CANIF_E_INIT_FAILED = 80,
	CANIF_E_TXPDU_LENGTH_EXCEEDED = 90
}CanIf_DetErrorType;

/* CanIf_ServiceId ENUM */
typedef uint8 CanIf_ServiceId;
#define CanIf_Init_API							((CanIf_ServiceId)0x01)
#define CanIf_DeInit_API						((CanIf_ServiceId)0x02)
#define CanIf_SetControllerMode_API				((CanIf_ServiceId)0x03)
#define CanIf_GetControllerMode_API				((CanIf_ServiceId)0x4B)
#define CanIf_Transmit_API						((CanIf_ServiceId)0x49)
#define CanIf_ReadRxPduData_API					((CanIf_ServiceId)0x06)
#define CanIf_ReadTxNotifStatus_API				((CanIf_ServiceId)0x07)
#define CanIf_ReadRxNotifStatus_API				((CanIf_ServiceId)0x08)
#define CanIf_SetPduMode_API					((CanIf_ServiceId)0x09)
#define CanIf_GetPduMode_API					((CanIf_ServiceId)0x0A)
#define CanIf_GetVersionInfo_API				((CanIf_ServiceId)0x0B)
#define CanIf_SetDynamicTxId_API				((CanIf_ServiceId)0x0C)
#define CanIf_SetTrcvMode_API					((CanIf_ServiceId)0x0D)
#define CanIf_GetTrcvMode_API					((CanIf_ServiceId)0x0E)
#define CanIf_GetTrcvWakeupReason_API			((CanIf_ServiceId)0x0F)
#define CanIf_SetTrcvWakeupMode_API				((CanIf_ServiceId)0x10)
#define CanIf_CheckValidation_API				((CanIf_ServiceId)0x12)
#define CanIf_GetTxConfirmationState_API		((CanIf_ServiceId)0x19)
#define CanIf_ClearTrcvWufFlag_API				((CanIf_ServiceId)0x1E)
#define CanIf_CheckTrcvWakeFlag_API				((CanIf_ServiceId)0x1F)
#define CanIf_SetBaudrate_API					((CanIf_ServiceId)0x27)
#define CanIf_SetIcomConfiguration_API			((CanIf_ServiceId)0x25)
#define CanIf_GetControllerRxErrorCounter_API	((CanIf_ServiceId)0x4D)
#define CanIf_GetControllerTxErrorCounter_API	((CanIf_ServiceId)0x4E)
#define CanIf_EnableBusMirroring_API			((CanIf_ServiceId)0x4C)

/* CanIf_ServiceId ENUM for Callback Functions */
#define CanIf_TriggerTransmit_API				((CanIf_ServiceId)0x41)
#define CanIf_TxConfirmation_API				((CanIf_ServiceId)0x13)
#define CanIf_RxIndication_API					((CanIf_ServiceId)0x14)
#define CanIf_ControllerBusOff_API				((CanIf_ServiceId)0x16)
#define CanIf_ConfirmPnAvailability_API			((CanIf_ServiceId)0x1A)
#define CanIf_ClearTrcvWufFlagIndication_API	((CanIf_ServiceId)0x20)
#define CanIf_CheckTrcvWakeFlagIndication_API	((CanIf_ServiceId)0x21)
#define CanIf_ControllerModeIndication_API		((CanIf_ServiceId)0x17)
#define CanIf_TrcvModeIndication_API			((CanIf_ServiceId)0x22)
#define CanIf_CurrentIcomConfiguration_API		((CanIf_ServiceId)0x26)



/*****************************************************************************************/
/*             			 Containers and configuration parameters	   	                 */
/*****************************************************************************************/


//****************************************************************************************
//						CanIfCtrlCfg
//	[ECUC_CanIf_00546]
//  This container contains the configuration (parameters) of an adressed CAN controller
//	by an underlying CAN Driver module. This container is configurable per CAN controller.
//****************************************************************************************
typedef struct{
	//************************************************************************************
	//					CanIfCtrlId   [ECUC_CanIf_00647]
	//
	//	This parameter abstracts from the CAN Driver specific parameter Controller. Each
	//	controller of all connected CAN Driver modules shall be assigned to one specific
	//	ControllerId of the CanIf. Range: 0..number of configured controllers of all CAN
	//	Driver modules
	//************************************************************************************
	uint8 CanIfCtrlId;
	//************************************************************************************
	//					CanIfCtrlWakeupSupport   [ECUC_CanIf_00637]
	//
	//	This parameter defines if a respective controller of the referenced CAN Driver
	//	modules is queriable for wake up events.
	//************************************************************************************
	boolean CanIfCtrlWakeupSupport;
	//************************************************************************************
	//					CanIfCtrlCanCtrlRef   [ECUC_CanIf_00636]
	//
	//	This parameter references to the logical handle of the underlying CAN controller
	//	from the CAN Driver module to be served by the CAN Interface module. The following
	//	parameters of CanController config container shall be referenced by this link:
	//	CanControllerId, CanWakeupSourceRef
	//	Range: 0..max. number of underlying supported CAN controllers
	//************************************************************************************
	CanController* CanIfCtrlCanCtrlRef;
}CanIfCtrlCfg;



/*****************************************************************************************/
/*              Configurating multiple CANID ranges for a given same HRH.                */
/*****************************************************************************************/
//****************************************************************************************
//						CanIfHrhRangeCfg
//	[ECUC_CanIf_00628]
//  Defines the parameters required for configurating multiple CANID ranges for a given
//	same HRH.
//****************************************************************************************
typedef struct
{
	//************************************************************************************
	//					CanIfHrhRangeBaseId    [ECUC_CanIf_00825]
	//
	//	CAN Identifier used as base value in combination with CanIfHrhRangeMask for a masked
	//	ID range in which all CAN Ids shall pass the software filtering. The size of this
	//	parameter is limited by CanIfHrhRangeRxPduRangeCanIdType.
	uint32 CanIfHrhRangeBaseId;
	//************************************************************************************
	//					CanIfHrhRangeMask   [ECUC_CanIf_00826]
	//
	//	Used as mask value in combination with CanIfHrhRangeBaseId for a masked ID range in
	//	which all CAN Ids shall pass the software filtering. The size of this parameter is
	//	limited by CanIfHrhRangeRxPduRangeCanIdType.
	uint32 CanIfHrhRangeMask;
	//************************************************************************************
	//					CanIfHrhRangeRxPduLowerCanId   [ECUC_CanIf_00629]
	//
	//	Lower CAN Identifier of a receive CAN L-PDU for identifier range definition, in
	//	which all CAN Ids shall pass the software filtering.
	uint32 CanIfHrhRangeRxPduLowerCanId;
	//************************************************************************************
	//					CanIfHrhRangeRxPduRangeCanIdType   [ECUC_CanIf_00644]
	//
	//	Specifies whether a configured Range of CAN Ids shall only consider standard CAN Ids
	//	or extended CAN Ids.
	CanIdTypeType CanIfHrhRangeRxPduRangeCanIdType;
	//************************************************************************************
	//					CanIfHrhRangeRxPduUpperCanId    [ECUC_CanIf_00630]
	//
	//	Upper CAN Identifier of a receive CAN L-PDU for identifier range definition, in
	//	which all CAN Ids shall pass the software filtering.
	uint32 CanIfHrhRangeRxPduUpperCanId;
}CanIfHrhRangeCfg;

/*****************************************************************************************/
/*                                    HRH configuration                                  */
/*****************************************************************************************/
//****************************************************************************************
//						CanIfHrhCfg
//	[ECUC_CanIf_00259]
//  This container contains configuration parameters for each hardware receive object (HRH).
//****************************************************************************************
typedef struct
{
	//************************************************************************************
	//					CanIfHrhSoftwareFilter    [ECUC_CanIf_00630]
	//
	//	Upper CAN Identifier of a receive CAN L-PDU for identifier range definition, in
	//	which all CAN Ids shall pass the software filtering.
	boolean CanIfHrhSoftwareFilter;
	//************************************************************************************
	//					CanIfHrhCanCtrlIdRef    [ECUC_CanIf_00632]
	//
	//	Selects the hardware receive objects by using the HRH range/list from CAN Driver
	//	configuration to define, for which HRH a software filtering has to be performed at
	//	during receive processing.
	CanIfCtrlCfg* CanIfHrhCanCtrlIdRef;
	//************************************************************************************
	//					CanIfHrhIdSymRef    [ECUC_CanIf_00631]
	//
	//	Reference to controller Id to which the HRH belongs to. A controller can contain
	//	one or more HRHs.
	CanHardwareObject* CanIfHrhIdSymRef;
	//************************************************************************************
	//					CanIfHrhRangeConfig    [ECUC_CanIf_00634]
	//
	//	The parameter refers to a particular HRH object in the CanDrv configuration .
	//	CanIf receives the following information of the CanDrv module by this reference:
	//		• CanHandleType (see ECUC_Can_00323)
	//		• CanObjectId (see ECUC_Can_00326)
	CanIfHrhRangeCfg* CanIfHrhRangeConfig;
}CanIfHrhCfg;




/*****************************************************************************************/
/*                                    HTH configuration                                  */
/*****************************************************************************************/
//****************************************************************************************
//						CanIfHrhCfg
//	[ECUC_CanIf_00258]
//  This container contains parameters related to each HTH.
//****************************************************************************************
typedef struct
{
	//************************************************************************************
	//					CanIfHthCanCtrlIdRef    [ECUC_CanIf_00625]
	//
	//	Reference to controller Id to which the HTH belongs to. A controller can contain
	//	one or more HTHs.
	CanIfCtrlCfg* CanIfHthCanCtrlIdRef;
	//************************************************************************************
	//					CanIfHthIdSymRef    [ECUC_CanIf_00627]
	//
	//	The parameter refers to a particular HTH object in the CanDrv configuration.
	//	CanIf receives the following information of the CanDrv module by this reference:
	//		• CanHandleType (see ECUC_Can_00323)
	//		• CanObjectId (see ECUC_Can_00326)
	CanHardwareObject* CanIfHthIdSymRef;
}CanIfHthCfg;



/*****************************************************************************************/
/*                                    HOH configuration                                  */
/*****************************************************************************************/
//****************************************************************************************
//						CanIfInitHohCfg
//	[ECUC_CanIf_00257]
//  This container contains the references to the configuration setup of each underlying
//	CAN Driver.
//****************************************************************************************
typedef struct
{
	//************************************************************************************
	//					CanIfHrhCfgRef
	//
	//	This container contains configuration parameters for each hardware receive object
	//	(HRH).
	CanIfHrhCfg* CanIfHrhCfgRef;
	//************************************************************************************
	//					CanIfHthCfgRef
	//
	//	This container contains configuration parameters for each hardware transmit object
	//	(HTH).
	CanIfHthCfg* CanIfHthCfgRef;
}CanIfInitHohCfg;



/*****************************************************************************************/
/*                                   Buffer configuration                                */
/*****************************************************************************************/
//****************************************************************************************
//						CanIfBufferCfg
//	[ECUC_CanIf_00832]
//  This container contains the Txbuffer configuration. Multiple buffers with different sizes
//	could be configured. If CanIfBufferSize (ECUC_CanIf_00834) equals 0, the CanIf Tx L-PDU
//	only refers via this CanIfBufferCfg the corresponding CanIfHthCfg.
//****************************************************************************************
typedef struct
{
	//************************************************************************************
	//					CanIfBufferSize    [ECUC_CanIf_00834]
	//
	//	This parameter defines the number of CanIf Tx L-PDUs which can be buffered in one
	//	Txbuffer. If this value equals 0, the CanIf does not perform Txbuffering for the
	//	CanIf Tx L-PDUs which are assigned to this Txbuffer. If CanIfPublicTxBuffering equals
	//	False, this parameter equals 0 for all TxBuffer. If the CanHandleType of the referred
	//	HTH equals FULL, this parameter equals 0 for this TxBuffer.
	uint8 CanIfBufferSize;
	//************************************************************************************
	//					CanIfBufferHthRef    [ECUC_CanIf_00833]
	//
	//	Reference to HTH, that defines the hardware object or the pool of hardware objects
	//	configured for transmission. All the CanIf Tx L-PDUs refer via the CanIfBufferCfg and
	//	this parameter to the HTHs if TxBuffering is enabled, or not.
	//	Each HTH shall not be assigned to more than one buffer.
	CanIfHthCfg* CanIfBufferHthRef;
}CanIfBufferCfg;



/*****************************************************************************************/
/*                                  Tx PDU configuration                                 */
/*****************************************************************************************/
//****************************************************************************************
//						CanIfTxPduCfg
//	[ECUC_CanIf_00248]
//  This container contains the configuration (parameters) of a transmit CAN L-PDU. It has to
//	be configured as often as a transmit CAN L-PDU is needed.
//	The SHORT-NAME of "CanIfTxPduConfig" container represents the symolic name of Transmit
//	L-PDU. This L-SDU consumes a meta data item of type CAN_ID_32.
//****************************************************************************************
typedef struct
{
	//************************************************************************************
	//					CanIfTxPduCanId    [ECUC_CanIf_00592]
	//
	//	CAN Identifier of transmit CAN L-PDUs used by the CAN Driver for CAN L-PDU transmission.
	//	Range: 11 Bit For Standard CAN Identifier ... 29 Bit For Extended CAN identifier
	//	The CAN Identifier may be omitted for dynamic transmit L-PDUs.
	uint32 CanIfTxPduCanId;
	//************************************************************************************
	//					CanIfTxPduCanIdMask    [ECUC_CanIf_00823]
	//
	//	Identifier mask which denotes relevant bits in the CAN Identifier. This parameter may
	//	be used to keep parts of the CAN Identifier of dynamic transmit L-PDUs static.
	//	Range: 11 bits for Standard CAN Identifier, 29 bits for Extended CAN Identifier.
	uint32 CanIfTxPduCanIdMask;
	//************************************************************************************
	//					CanIfTxPduCanIdType    [ECUC_CanIf_00590]
	//
	//	Type of CAN Identifier of the transmit CAN L-PDU used by the CAN Driver module for
	//	CAN L-PDU transmission.
	Can_IdType CanIfTxPduCanIdType;
	//************************************************************************************
	//					CanIfTxPduId    [ECUC_CanIf_00591]
	//
	//	ECU wide unique, symbolic handle for transmit CAN L-SDU.
	//	Range: 0..max. number of CantTxPduIds
	uint32 CanIfTxPduId;
	//************************************************************************************
	//					CanIfTxPduPnFilterPdu    [ECUC_CanIf_00773]
	//
	//	If CanIfPublicPnFilterSupport is enabled, by this parameter PDUs could be configured
	//	which will pass the CanIfPnFilter. If there is no CanIfTxPduPnFilterPdu configured
	//	per controller, the corresponding controller applies no CanIfPnFilter.
	boolean CanIfTxPduPnFilterPdu;
	//************************************************************************************
	//					CanIfTxPduReadNotifyStatus    [ECUC_CanIf_00589]
	//
	//	Enables and disables transmit confirmation for each transmit CAN L-SDU for reading
	//	its notification status.
	boolean CanIfTxPduReadNotifyStatus;
	//************************************************************************************
	//					CanIfTxPduTriggerTransmit    [ECUC_CanIf_00840]
	//
	//	Determines if or if not CanIf shall use the trigger transmit API for this PDU.
	boolean CanIfTxPduTriggerTransmit;
	//************************************************************************************
	//					CanIfTxPduTruncation    [ECUC_CanIf_00845]
	//
	//	Enables/disables truncation of PDUs that exceed the configured size.
	boolean CanIfTxPduTruncation;
	//************************************************************************************
	//					CanIfTxPduType    [ECUC_CanIf_00593]
	//
	//	Defines the type of each transmit CAN L-PDU.
	Can_TypeType CanIfTxPduType;
	//************************************************************************************
	//					CanIfTxPduUserTriggerTransmitName    [ECUC_CanIf_00842]
	//
	//	This parameter defines the name of the <User_TriggerTransmit>. This parameter depends
	//	on the parameter CanIfTxPduUserTxConfirmationUL. If CanIfTxPduUserTxConfirmationUL
	//	equals CAN_TP, CAN_NM, PDUR, XCP, CAN_TSYN, J1939NM or J1939TP, the name of the
	//	<User_TriggerTransmit> is fixed. If CanIfTxPduUserTxConfirmationUL equals CDD, the
	//	name of the <User_TxConfirmation> is selectable.
	//	Please be aware that this parameter depends on the same parameter as
	//	CanIfTxPduUserTxConfirmationName. It shall be clear which upper layer is responsible
	//	for that PDU.
	Std_ReturnType(*CanIfTxPduUserTriggerTransmitName)(PduIdType, PduInfoType*);
	//************************************************************************************
	//					CanIfTxPduUserTxConfirmationName    [ECUC_CanIf_00528]
	//
	//	This parameter defines the name of the <User_TxConfirmation>. This parameter depends
	//	on the parameter CanIfTxPduUserTxConfirmationUL. If CanIfTxPduUserTxConfirmationUL
	//	equals CAN_TP, CAN_NM, PDUR, XCP, CAN_TSYN, J1939NM or J1939TP, the name of the
	//	<User_TxConfirmation> is fixed. If CanIfTxPduUserTxConfirmationUL equals CDD, the
	//	name of the <User_TxConfirmation> is selectable.
	void(*CanIfTxPduUserTxConfirmationName)(PduIdType, Std_ReturnType);
	//************************************************************************************
	//					CanIfTxPduUserTxConfirmationUL    [ECUC_CanIf_00527]
	//
	//	This parameter defines the upper layer (UL) module to which the confirmation of the
	//	successfully transmitted CanTxPduId has to be routed via the <User_TxConfirmation>.
	//	This <User_TxConfirmation> has to be invoked when the confirmation of the configured
	//	CanTxPduId will be received by a Tx confirmation event from the CAN Driver module.
	//	If no upper layer (UL) module is configured, no <User_TxConfirmation> has to be called
	//	in case of a Tx confirmation event of the CanTxPduId from the CAN Driver module.
	CanIf_UserType CanIfTxPduUserTxConfirmationUL;
	//************************************************************************************
	//					CanIfTxPduBufferRef    [ECUC_CanIf_00831]
	//
	//	Configurable reference to a CanIf buffer configuration.
	CanIfBufferCfg* CanIfTxPduBufferRef;
	//************************************************************************************
	//					CanIfTxPduRef    [ECUC_CanIf_00603]
	//
	//	Reference to the "global" Pdu structure to allow harmonization of handle IDs in the
	//	COM-Stack.
	Can_PduType* CanIfTxPduRef;
}CanIfTxPduCfg;



/*****************************************************************************************/
/*                                  Rx PDU configuration                                 */
/*****************************************************************************************/
//****************************************************************************************
//						CanIfTxPduCfg
//	[ECUC_CanIf_00249]
//  This container contains the configuration (parameters) of each receive CAN L-PDU.
//	The SHORT-NAME of "CanIfRxPduConfig" container represents the symolic name of receive
//	L-PDU. This L-SDU consumes a meta data item of type CAN_ID_32.
//****************************************************************************************
typedef struct
{
	//************************************************************************************
	//					CanIfRxPduCanId    [ECUC_CanIf_00598]
	//
	//	CAN Identifier of Receive CAN L-PDUs used by the CAN Interface. Exa: Software Filtering.
	//	This parameter is used if exactly one Can Identifier is assigned to the Pdu. If a range
	//	is assigned then the CanIfRxPduCanIdRange parameter shall be used.
	//	Range: 11 Bit For Standard CAN Identifier ... 29 Bit For Extended CAN identifier
	uint32 CanIfRxPduCanId;
	//************************************************************************************
	//					CanIfRxPduCanIdMask    [ECUC_CanIf_00522]
	//
	//	Identifier mask which denotes relevant bits in the CAN Identifier. This parameter defines
	//	a CAN Identifier range in an alternative way to CanIfRxPduCanIdRange. It identifies the
	//	bits of the configured CAN Identifier that must match the received CAN Identifier.
	//	Range: 11 bits for Standard CAN Identifier, 29 bits for Extended CAN Identifier.
	uint32 CanIfRxPduCanIdMask;
	//************************************************************************************
	//					CanIfRxPduCanIdType    [ECUC_CanIf_00596]
	//
	//	CAN Identifier of receive CAN L-PDUs used by the CAN Driver for CAN L-PDU reception.
	Can_IdType CanIfRxPduCanIdType;
	//************************************************************************************
	//					CanIfRxPduDataLength    [ECUC_CanIf_00599]
	//
	//	Data length of the received CAN L-PDUs used by the CAN Interface. This information is
	//	used for Data Length Check. Additionally it might specify the valid bits in case of the
	//	discrete DLC for CAN FD L-PDUs > 8 bytes.
	//	The data area size of a CAN L-PDU can have a range from 0 to 64 bytes.
	uint8 CanIfRxPduDataLength;
	//************************************************************************************
	//					CanIfRxPduDataLengthCheck    [ECUC_CanIf_00846]
	//
	//	This parameter switches the message specific data length check. True: Data length check
	//	will be executed during the reception of this PDU. False: No data length check will be
	//	executed during the reception of this PDU.
	boolean CanIfRxPduDataLengthCheck;
	//************************************************************************************
	//					CanIfRxPduId    [ECUC_CanIf_00597]
	//
	//	ECU wide unique, symbolic handle for receive CAN L-SDU. It shall fulfill ANSI/AUTOSAR
	//	definitions for constant defines.
	//	Range: 0..max. number of defined CanRxPduIds
	uint32 CanIfRxPduId;
	//************************************************************************************
	//					CanIfRxPduReadData    [ECUC_CanIf_00600]
	//
	//	Enables and disables the Rx buffering for reading of received L-SDU data.
	boolean CanIfRxPduReadData;
	//************************************************************************************
	//					CanIfRxPduReadNotifyStatus    [ECUC_CanIf_00595]
	//
	//	Enables and disables receive indication for each receive CAN L-SDU for reading its
	//	notification status.
	boolean CanIfRxPduReadNotifyStatus;
	//************************************************************************************
	//					CanIfRxPduUserRxIndicationName    [ECUC_CanIf_00530]
	//
	//	This parameter defines the name of the <User_RxIndication>. This parameter depends on
	//	the parameter CanIfRxPduUserRxIndicationUL. If CanIfRxPduUserRxIndicationUL equals
	//	CAN_TP, CAN_NM, PDUR, XCP, CAN_TSYN, J1939NM or J1939TP, the name of the
	//	<User_RxIndication> is fixed. If CanIfRxPduUserRxIndicationUL equals CDD, the name of
	//	the <User_RxIndication> is selectable.
	void (*CanIfRxPduUserRxIndicationName )(PduIdType, const PduInfoType*);
	//************************************************************************************
	//					CanIfRxPduUserRxIndicationUL    [ECUC_CanIf_00829]
	//
	//	This parameter defines the upper layer (UL) module to which the indication of the
	//	successfully received CANRXPDUID has to be routed via <User_RxIndication>. This
	//	<User_RxIndication> has to be invoked when the indication of the configured CANRXPDUID
	//	will be received by an Rx indication event from the CAN Driver module. If no upper
	//	layer (UL) module is configured, no <User_RxIndication> has to be called in case of an
	//	Rx indication event of the CANRXPDUID from the CAN Driver module.
	CanIf_UserType CanIfRxPduUserRxIndicationUL;
	//************************************************************************************
	//					CanIfRxPduHrhIdRef    [ECUC_CanIf_00602]
	//
	//	The HRH to which Rx L-PDU belongs to, is referred through this parameter.
	CanIfHrhCfg* CanIfRxPduHrhIdRef;
	//************************************************************************************
	//					CanIfRxPduRef    [ECUC_CanIf_00601]
	//
	//	Reference to the "global" Pdu structure to allow harmonization of handle IDs in the
	//	COM-Stack.
	Can_PduType* CanIfRxPduRef;
}CanIfRxPduCfg;




/*****************************************************************************************/
/*                              CanIf Public Configuration                               */
/*****************************************************************************************/
//****************************************************************************************
//						CanIfPublicCfg
//	[ECUC_CanIf_00246]
//  This container contains the public configuration (parameters) of the CAN Interface.
//****************************************************************************************
typedef struct
{
	//************************************************************************************
	//					CanIfBusMirroringSupport   [ECUC_CanIf_00847]
	//
	//	Enable support for Bus Mirroring.
	boolean CanIfBusMirroringSupport;
	//************************************************************************************
	//					CanIfDevErrorDetect    [ECUC_CanIf_00614]
	//
	//	Switches the development error detection and notification on or off.
	boolean CanIfDevErrorDetect;
	//************************************************************************************
	//					CanIfMetaDataSupport    [ECUC_CanIf_00824]
	//
	//	Enable support for dynamic ID handling using L-SDU MetaData.
	boolean CanIfMetaDataSupport;
	//************************************************************************************
	//					CanIfPublicCddHeaderFile    [ECUC_CanIf_00671]
	//
	//	Defines header files for callback functions which shall be included in case of CDDs.
	//	Range of characters is 1.. 32.
	uint8* CanIfPublicCddHeaderFile;
	//************************************************************************************
	//					CanIfPublicHandleTypeEnum    [ECUC_CanIf_00742]
	//
	//	This parameter is used to configure the Can_HwHandleType. The Can_HwHandleType
	//	represents the hardware object handles of a CAN hardware unit. For CAN hardware units
	//	with more than 255 HW objects the extended range shall be used (UINT16).
	uint8 CanIfPublicHandleTypeEnum;
	//************************************************************************************
	//					CanIfPublicIcomSupport    [ECUC_CanIf_00839]
	//
	//	Selects support of Pretended Network features in CanIf.
	boolean CanIfPublicIcomSupport;
	//************************************************************************************
	//					CanIfPublicMultipleDrvSupport    [ECUC_CanIf_00612]
	//
	//	Selects support for multiple CAN Drivers.
	boolean CanIfPublicMultipleDrvSupport;
	//************************************************************************************
	//					CanIfPublicPnSupport    [ECUC_CanIf_00772]
	//
	//	Selects support of Partial Network features in CanIf.
	boolean CanIfPublicPnSupport;
	//************************************************************************************
	//					CanIfPublicReadRxPduDataApi    [ECUC_CanIf_00607]
	//
	//	Enables / Disables the API CanIf_ReadRxPduData() for reading received L-SDU data.
	boolean CanIfPublicReadRxPduDataApi;
	//************************************************************************************
	//					CanIfPublicReadRxPduNotifyStatusApi    [ECUC_CanIf_00608]
	//
	//	Enables and disables the API for reading the notification status of receive L-PDUs.
	boolean CanIfPublicReadRxPduNotifyStatusApi;
	//************************************************************************************
	//					CanIfPublicReadTxPduNotifyStatusApi    [ECUC_CanIf_00609]
	//
	//	Enables and disables the API for reading the notification status of transmit L-PDUs.
	boolean CanIfPublicReadTxPduNotifyStatusApi;
	//************************************************************************************
	//					CanIfPublicSetDynamicTxIdApi    [ECUC_CanIf_00610]
	//
	//	Enables and disables the API for reconfiguration of the CAN Identifier for each
	//	Transmit L-PDU.
	boolean CanIfPublicSetDynamicTxIdApi;
	//************************************************************************************
	//					CanIfPublicTxBuffering    [ECUC_CanIf_00618]
	//
	//	Enables and disables the buffering of transmit L-PDUs (rejected by the CanDrv) within
	//	the CAN Interface module.
	boolean CanIfPublicTxBuffering;
	//************************************************************************************
	//					CanIfPublicTxConfirmPollingSupport    [ECUC_CanIf_00733]
	//
	//	Configuration parameter to enable/disable the API to poll for Tx Confirmation state.
	boolean CanIfPublicTxConfirmPollingSupport;
	//************************************************************************************
	//					CanIfPublicWakeupCheckValidByNM    [ECUC_CanIf_00741]
	//
	//	If enabled, only NM messages shall validate a detected wake-up event in CanIf. If
	//	disabled, all received messages corresponding to a configured Rx PDU shall validate
	//	such a wake-up event. This parameter depends on CanIfPublicWakeupCheckValidSupport and
	//	shall only be configurable, if it is enabled.
	boolean CanIfPublicWakeupCheckValidByNM;
	//************************************************************************************
	//					CanIfPublicWakeupCheckValidSupport    [ECUC_CanIf_00611]
	//
	//	Selects support for wake up validation
	boolean CanIfPublicWakeupCheckValidSupport;
	//************************************************************************************
	//					CanIfSetBaudrateApi    [ECUC_CanIf_00838]
	//
	//	Configuration parameter to enable/disable the CanIf_SetBaudrate API to change the baud
	//	rate of a CAN Controller. If this parameter is set to true the CanIf_SetBaudrate API
	//	shall be supported. Otherwise the API is not supported.
	boolean CanIfSetBaudrateApi;
	//************************************************************************************
	//					CanIfTriggerTransmitSupport    [ECUC_CanIf_00844]
	//
	//	Enables the CanIf_TriggerTransmit API at Pre-Compile-Time. Therefore, this parameter
	//	defines if there shall be support for trigger transmit transmissions.
	boolean CanIfTriggerTransmitSupport;
	//************************************************************************************
	//					CanIfTxOfflineActiveSupport    [ECUC_CanIf_00837]
	//
	//	Determines wether TxOffLineActive feature (see SWS_CANIF_00072) is supported by CanIf.
	boolean CanIfTxOfflineActiveSupport;
	//************************************************************************************
	//					CanIfVersionInfoApi    [ECUC_CanIf_00613]
	//
	//	Enables and disables the API for reading the version information about the CAN Interface.
	boolean CanIfVersionInfoApi;
	//************************************************************************************
	//					CanIfWakeupSupport    [ECUC_CanIf_00843]
	//
	//	Enables the CanIf_CheckWakeup API at Pre-Compile-Time. Therefore, this parameter defines
	//	if there shall be support for wake-up.
	boolean CanIfWakeupSupport;
}CanIfPublicCfg;




/*****************************************************************************************/
/*                             CanIf Private Configuration                               */
/*****************************************************************************************/
//****************************************************************************************
//						CanIfPrivateCfg
//	[ECUC_CanIf_00245]
//  This container contains the private configuration (parameters) of the CAN Interface.
//****************************************************************************************
typedef struct
{
	//************************************************************************************
	//					CanIfFixedBuffer    [ECUC_CanIf_00827]
	//
	//	This parameter defines if the buffer element length shall be fixed to 8 Bytes for
	//	buffers to which only PDUs < 8 Bytes are assigned.
	//	TRUE: Minimum buffer element length is fixed to 8 Bytes. FALSE: Buffer element length
	//	depends on the size of the referencing PDUs.
	boolean CanIfFixedBuffer;
	//************************************************************************************
	//					CanIfPrivateDataLengthCheck    [ECUC_CanIf_00617]
	//
	//	Selects whether Data Length Check is supported.
	boolean CanIfPrivateDataLengthCheck;
	//************************************************************************************
	//					CanIfPrivateSoftwareFilterType    [ECUC_CanIf_00619]
	//
	//	Selects the desired software filter mechanism for reception only. Each implemented
	//	software filtering method is identified by this enumeration number.
	CanIf_SwFilterType CanIfPrivateSoftwareFilterType;
	//************************************************************************************
	//					CanIfSupportTTCAN    [ECUC_CanIf_00675]
	//
	//	Defines whether TTCAN is supported.
	boolean CanIfSupportTTCAN;
}CanIfPrivateCfg;

/*****************************************************************************************/
/*                                  CanIf Init Container                                 */
/*****************************************************************************************/
//****************************************************************************************
//						CanIf_ConfigType
//
//  This container contains the configuration parameters of the CAN
//  interface module.
//****************************************************************************************
//****************************************************************************************
//
//	[SWS_CANIF_00144]
//	This type defines a data structure for the post build parameters
//	of the CAN interface for all underlying CAN drivers.
//	At initialization the CanIf gets a pointer to a structure of this
//	type to get access to its configuration data, which is necessary
//	for initialization.
//
typedef struct
{
	//****************************************************************************************
	//					CanIfInitCfgSet [ECUC_CanIf_00623]
	//
	//	Selects the CAN Interface specific configuration setup. This
	//  type of the external data structure shall contain the post
	//  build initialization data for the CAN Interface for all
	//	underlying CAN Dirvers.
	//	constant to CanIf_ConfigType
	//
	//	Length: 1-32
	//****************************************************************************************
	uint8* CanIfInitCfgSet;
	//****************************************************************************************
	//					CanIfMaxBufferSize  [ECUC_CanIf_00828]
	//
	//	Maximum total size of all Tx buffers.
	//****************************************************************************************
	uint64 CanIfMaxBufferSize;
	//****************************************************************************************
	//					CanIfMaxRxPduCfg   [ECUC_CanIf_00830]
	//
	//	Maximum number of Pdus.
	//****************************************************************************************
	uint64 CanIfMaxRxPduCfg;
	//****************************************************************************************
	//					CanIfMaxTxPduCfg   [ECUC_CanIf_00829]
	//
	//	Maximum number of Pdus.
	//****************************************************************************************
	uint64 CanIfMaxTxPduCfg;
	//****************************************************************************************
	//					CanIfRxPduCfg [ECUC_CanIf_00249]
	//
	//	This container contains the configuration (parameters) of each
	//	receive CAN L-PDU.
	//****************************************************************************************
	CanIfRxPduCfg* CanIfRxPduConfig;
	//****************************************************************************************
	//					CanIfTxPduCfg [ECUC_CanIf_00248]
	//
	//	This container contains the configuration (parameters) of each
	//	transmit receive CAN L-PDU.
	//****************************************************************************************
	CanIfTxPduCfg* CanIfTxPduConfig;
	//****************************************************************************************
	//					CanIfBufferCfg [ECUC_CanIf_00832]
	//
	//	This container contains the Tx buffer configuration. Multiple
	//	buffers with different sizes could be configured
	//****************************************************************************************
	CanIfBufferCfg* CanIfBufferConfig;
	//****************************************************************************************
	//					CanIfInitHohCfg [ECUC_CanIf_00257]
	//
	//	This container contains the references to the configuration
	//	setup of each underlying CAN Driver.
	//****************************************************************************************
	CanIfInitHohCfg* CanIfInitHohConfig;
}CanIfInitCfg;
//************************************************************************



/*****************************************************************************************/
/*                                Callback Configuration                                 */
/*****************************************************************************************/
//****************************************************************************************
//						CanIfDispatchCfg
//	[ECUC_CanIf_00250]
//  Callback functions provided by upper layer modules of the CanIf. The callback functions
//	defined in this container are common to all configured CAN Driver / CAN Transceiver
//	Driver modules.
//****************************************************************************************
typedef struct{
	//****************************************************************************************
	//					CanIfDispatchUserCheckTrcvWakeFlagIndicationName [ECUC_CanIf_00791]
	//
	//	This parameter defines the name of <User_CheckTrcvWakeFlagIndication>. If
	//	CanIfDispatchUserCheckTrcvWakeFlagIndicationUL equals CAN_SM the name of
	//	<User_CheckTrcvWakeFlagIndication> is fixed. If it equals CDD, the name is selectable.
	//	If CanIfPublicPnSupport equals False, this parameter shall not be configurable.
	//****************************************************************************************
	void (*CanIfDispatchUserCheckTrcvWakeFlagIndicationName)(uint8);
	//****************************************************************************************
	//					CanIfDispatchUserCheckTrcvWakeFlagIndicationUL [ECUC_CanIf_00792]
	//
	//	This parameter defines the upper layer module to which the CheckTrcvWakeFlagIndication
	//	from the Driver modules have to be routed. If CanIfPublicPnSupport equals False, this
	//	parameter shall not be configurable.
	//****************************************************************************************
	CanIf_UserType CanIfDispatchUserCheckTrcvWakeFlagIndicationUL;
	//****************************************************************************************
	//					CanIfDispatchUserClearTrcvWufFlagIndicationName [ECUC_CanIf_00789]
	//
	//	This parameter defines the name of <User_ClearTrcvWufFlagIndication>. If
	//	CanIfDispatchUserClearTrcvWufFlagIndicationUL equals CAN_SM the name of
	//	<User_ClearTrcvWufFlagIndication> is fixed. If it equals CDD, the name is selectable.
	//	If CanIfPublicPnSupport equals False, this parameter shall not be configurable.
	//****************************************************************************************
	void (*CanIfDispatchUserClearTrcvWufFlagIndicationName)(uint8);
	//****************************************************************************************
	//					CanIfDispatchUserClearTrcvWufFlagIndicationUL [ECUC_CanIf_00790]
	//
	//	This parameter defines the upper layer module to which the ClearTrcvWufFlagIndication
	//	from the Driver modules have to be routed. If CanIfPublicPnSupport equals False, this
	//	parameter shall not be configurable.
	//****************************************************************************************
	CanIf_UserType CanIfDispatchUserClearTrcvWufFlagIndicationUL;
	//****************************************************************************************
	//					CanIfDispatchUserConfirmPnAvailabilityName [ECUC_CanIf_00819]
	//
	//	This parameter defines the name of <User_ConfirmPnAvailability>. If
	//	CanIfDispatchUserConfirmPnAvailabilityUL equals CAN_SM the name of
	//	<User_ConfirmPnAvailability> is fixed. If it equals CDD, the name is selectable. If
	//	CanIfPublicPnSupport equals False, this parameter shall not be configurable.
	//****************************************************************************************
	void (*CanIfDispatchUserConfirmPnAvailabilityName)(uint8);
	//****************************************************************************************
	//					CanIfDispatchUserConfirmPnAvailabilityUL [ECUC_CanIf_00820]
	//
	//	This parameter defines the upper layer module to which the ConfirmPnAvailability
	//	notification from the Driver modules have to be routed. If CanIfPublicPnSupport equals
	//	False, this parameter shall not be configurable.
	//****************************************************************************************
	CanIf_UserType CanIfDispatchUserConfirmPnAvailabilityUL;
	//****************************************************************************************
	//					CanIfDispatchUserCtrlBusOffName [ECUC_CanIf_00257]
	//
	//	This container contains the references to the configuration
	//	setup of each underlying CAN Driver.
	//****************************************************************************************
	void (*CanIfDispatchUserCtrlBusOffName)(uint8);
	//****************************************************************************************
	//					CanIfDispatchUserCtrlBusOffUL [ECUC_CanIf_00525]
	//
	//	This parameter defines the name of <User_ControllerBusOff>. This parameter depends on
	//	the parameter CanIfDispatchUserCtrlBusOffUL. If CanIfDispatchUserCtrlBusOffUL equals
	//	CAN_SM the name of <User_ControllerBusOff> is fixed. If CanIfDispatchUserCtrlBusOffUL
	//	equals CDD, the name of <User_ControllerBusOff> is selectable.
	//****************************************************************************************
	CanIf_UserType CanIfDispatchUserCtrlBusOffUL;
	//****************************************************************************************
	//					CanIfDispatchUserCtrlModeIndicationName [ECUC_CanIf_00547]
	//
	//	This parameter defines the upper layer (UL) module to which the notifications of all
	//	ControllerBusOff events from the CAN Driver modules have to be routed via
	//	<User_ControllerBusOff>. There is no possibility to configure no upper layer (UL) module
	//	as the provider of <User_ControllerBusOff>.
	//****************************************************************************************
	void (*CanIfDispatchUserCtrlModeIndicationName)(uint8, Can_ControllerStateType);
	//****************************************************************************************
	//					CanIfDispatchUserCtrlModeIndicationUL [ECUC_CanIf_00683]
	//
	//	This parameter defines the name of <User_ControllerModeIndication>. This parameter
	//	depends on the parameter CanIfDispatchUserCtrlModeIndicationUL. If
	//	CanIfDispatchUserCtrlModeIndicationUL equals CAN_SM the name of
	//	<User_ControllerModeIndication> is fixed. If CanIfDispatchUserCtrlModeIndicationUL equals
	//	CDD, the name of <User_ControllerModeIndication> is selectable.
	//****************************************************************************************
	CanIf_UserType CanIfDispatchUserCtrlModeIndicationUL;
	//****************************************************************************************
	//					CanIfDispatchUserTrcvModeIndicationName [ECUC_CanIf_00684]
	//
	//	This parameter defines the upper layer (UL) module to which the notifications of all
	//	ControllerTransition events from the CAN Driver modules have to be routed via
	//	<User_ControllerModeIndication>.
	//****************************************************************************************
	void (*CanIfDispatchUserTrcvModeIndicationName)(uint8, CanTrcv_TrcvModeType);
	//****************************************************************************************
	//					CanIfDispatchUserTrcvModeIndicationUL [ECUC_CanIf_00685]
	//
	//	This parameter defines the name of <User_TrcvModeIndication>. This parameter depends on
	//	the parameter CanIfDispatchUserTrcvModeIndicationUL. If CanIfDispatchUserTrcvModeIndicationUL
	//	equals CAN_SM the name of <User_TrcvModeIndication> is fixed. If
	//	CanIfDispatchUserTrcvModeIndicationUL equals CDD, the name of <User_TrcvModeIndication>
	//	is selectable.
	//****************************************************************************************
	CanIf_UserType CanIfDispatchUserTrcvModeIndicationUL;
	//****************************************************************************************
	//					CanIfDispatchUserValidateWakeupEventName [ECUC_CanIf_00686]
	//
	//	This parameter defines the upper layer (UL) module to which the notifications of all
	//	TransceiverTransition events from the CAN Transceiver Driver modules have to be routed
	//	via <User_TrcvModeIndication>. If no UL module is configured, no upper layer callback
	//	function will be called.
	//****************************************************************************************
	void (*CanIfDispatchUserValidateWakeupEventName )(EcuM_WakeupSourceType);
	//****************************************************************************************
	//					CanIfDispatchUserValidateWakeupEventUL [ECUC_CanIf_00531]
	//
	//	This parameter defines the name of <User_ValidateWakeupEvent>. This parameter depends on
	//	the parameter CanIfDispatchUserValidateWakeupEventUL. If CanIfDispatchUserValidateWakeupEventUL
	//	equals ECUM, the name of <User_ValidateWakeupEvent> is fixed. If
	//	CanIfDispatchUserValidateWakeupEventUL equals CDD, the name of <User_ValidateWakeupEvent>
	//	is selectable.
	//****************************************************************************************
	CanIf_UserType CanIfDispatchUserValidateWakeupEventUL;
}CanIfDispatchCfg;


/*****************************************************************************************/
/*                                Can Driver Configuration                               */
/*****************************************************************************************/
//****************************************************************************************
//						CanIfCtrlDrvCfg
//	[ECUC_CanIf_00253]
//  Configuration parameters for all the underlying CAN Driver modules are aggregated under
//	this container. For each CAN Driver module a seperate instance of this container has to
//	be provided.
//****************************************************************************************
typedef struct{
	//****************************************************************************************
	//					CanIfCtrlDrvInitHohConfigRef [ECUC_CanIf_00642]
	//
	//	Reference to the Init Hoh Configuration
	//****************************************************************************************
	CanIfInitHohCfg* CanIfCtrlDrvInitHohConfigRef;
	//****************************************************************************************
	//					CanIfCtrlDrvNameRef [ECUC_CanIf_00638]
	//
	//	CAN Interface Driver Reference.
	//	This reference can be used to get any information (Ex. Driver Name, Vendor ID)
	//	from the CAN driver. The CAN Driver name can be derived from the ShortName of the CAN
	//	driver module.
	//****************************************************************************************
//	CanGeneral* CanIfCtrlDrvNameRef;

}CanIfCtrlDrvCfg;


/*****************************************************************************************/
/*                                 Can Trcv Configuration                                */
/*****************************************************************************************/
//****************************************************************************************
//						CanIfTrcvCfg
//	[ECUC_CanIf_00587]
//	This container contains the configuration (parameters) of one addressed CAN transceiver
//	by the underlying CAN Transceiver Driver module. For each CAN transceiver a seperate
//	instance of this container has to be provided.
//****************************************************************************************
typedef struct{
	//****************************************************************************************
	//					CanIfTrcvId [ECUC_CanIf_00654]
	//
	//	This parameter abstracts from the CAN Transceiver Driver specific parameter Transceiver.
	//	Each transceiver of all connected CAN Transceiver Driver modules shall be assigned to one
	//	specific TransceiverId of the CanIf.
	//	Range: 0..number of configured transceivers of all CAN Transceiver Driver modules
	//****************************************************************************************
	uint8* CanIfTrcvId;
	//****************************************************************************************
	//					CanIfTrcvWakeupSupport [ECUC_CanIf_00606]
	//
	//	This parameter defines if a respective transceiver of the referenced CAN Transceiver
	//	Driver modules is queriable for wake up events.
	//****************************************************************************************
	boolean CanIfTrcvWakeupSupport;
	//****************************************************************************************
	//					CanIfTrcvCanTrcvRef [ECUC_CanIf_00605]
	//
	//	This parameter references to the logical handle of the underlying CAN transceiver from
	//	the CAN transceiver driver module to be served by the CAN Interface module.
	//	Range: 0..max. number of underlying supported CAN transceivers
	//****************************************************************************************
//	CanTrcvChannel* CanIfTrcvCanTrcvRef;
}CanIfTrcvCfg;


/*****************************************************************************************/
/*                               CanIf Trcv Configuration                                */
/*****************************************************************************************/
//****************************************************************************************
//						CanIfTrcvDrvCfg
//	[ECUC_CanIf_00273]
//  This container contains the configuration (parameters) of all addressed CAN transceivers
//	by each underlying CAN Transceiver Driver module. For each CAN transceiver Driver a
//	seperate instance of this container shall be provided.
//****************************************************************************************
typedef struct{
	//****************************************************************************************
	//					CanIfTrcvCfgRef
	//
	//	This container contains the configuration (parameters) of one addressed CAN transceiver
	//	by the underlying CAN Transceiver Driver module. For each CAN transceiver a seperate
	//	instance of this container has to be provided.
	//****************************************************************************************
	CanIfTrcvCfg* CanIfTrcvCfgRef;
}CanIfTrcvDrvCfg;


/*****************************************************************************************/
/*                                CanIf Config Container                                 */
/*****************************************************************************************/
//****************************************************************************************
//						CanIf_ConfigType
//	[ECUC_CanIf_00244]
//  This container includes all necessary configuration sub-containers according the CAN
//	Interface configuration structure.
//****************************************************************************************
typedef struct
{
	//****************************************************************************************
	//					CanIfCtrlDrvCfgRef
	//
	//	Configuration parameters for all the underlying CAN Driver modules are aggregated under
	//	this container. For each CAN Driver module a seperate instance of this container has
	//	to be provided.
	//****************************************************************************************
	CanIfCtrlDrvCfg* CanIfCtrlDrvCfgRef;
	//****************************************************************************************
	//					CanIfDispatchCfgRef
	//
	//	Callback functions provided by upper layer modules of the CanIf. The callback functions
	//	defined in this container are common to all configured CAN Driver / CAN Transceiver
	//	Driver modules.
	//****************************************************************************************
	CanIfDispatchCfg* CanIfDispatchCfgRef;
	//****************************************************************************************
	//					CanIfInitCfgRef
	//
	//	This container contains the init parameters of the CAN Interface.
	//****************************************************************************************
	CanIfInitCfg* CanIfInitCfgRef;
	//****************************************************************************************
	//					CanIfPrivateCfgRef
	//
	//	This container contains the private configuration (parameters) of the CAN Interface.
	//****************************************************************************************
	CanIfPrivateCfg* CanIfPrivateCfgRef;
	//****************************************************************************************
	//					CanIfPublicCfgRef
	//
	//	This container contains the public configuration (parameters) of the CAN Interface.
	//****************************************************************************************
	CanIfPublicCfg* CanIfPublicCfgRef;
	//****************************************************************************************
	//					CanIfTrcvDrvCfgRef
	//
	//	This container contains the configuration (parameters) of all addressed CAN transceivers
	//	by each underlying CAN Transceiver Driver module. For each CAN transceiver Driver a
	//	seperate instance of this container shall be provided.
	//****************************************************************************************
	CanIfTrcvDrvCfg* CanIfTrcvDrvCfgRef;
}CanIf_ConfigType;



//************************************************************************
//						CanIf_PduModeType
//
//  This enumeration defines the parameters for the PDU mode.
//************************************************************************
//
//	[SWS_CANIF_00137]
//	The PduMode of a channel defines its transmit or receive activity.
//	Communication direction (transmission and/or reception) of the
//	channel can be controlled separately or together by upper layers.
//
typedef enum
{
//	= 0 Transmit and receive path of the corresponding channel are
//	disabled => no communication mode.
	CANIF_OFFLINE,

//	Transmit path of the corresponding channel is disabled.
//	The receive path is enabled.
	CANIF_TX_OFFLINE,

//	Transmit path of the corresponding channel is in offline active
//	mode (see SWS_ CANIF_00072). The receive path is disabled.
//	This mode requires CanIfTxOfflineActive Support = TRUE.
	CANIF_TX_OFFLINE_ACTIVE,

//	 Transmit and receive path of the corresponding channel are
//	 enabled => full operation mode.
	CANIF_ONLINE
}CanIf_PduModeType;
//************************************************************************



//************************************************************************
//						CanIf_NotifStatusType
//
//  This enumeration defines the parameters for return value of CAN
//	L-PDU notification status.
//************************************************************************
//
//	[SWS_CANIF_00201]
//	Return value of CAN L-PDU notification status.
//
typedef enum
{
//	No transmit or receive event occurred for the requested L-PDU.
	CANIF_NO_NOTIFICATION,

//	The requested Rx/Tx CAN L-PDU was successfully transmitted or
//	received.
	CANIF_TX_RX_NOTIFICATION,
}CanIf_NotifStatusType;
//************************************************************************




//************************************************************************
//						Function Prototype
//************************************************************************

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
//	Notes					:*All underlying CAN controllers and
//							  transceivers still remain not operational.
//							  The service CanIf_Init() is called only by
//							  the EcuM.
//							 *The service CanIf_Init() shall initialize the
//							  global variables and data structures of the
//							  CanIf including flags and buffers.
//************************************************************************
void CanIf_Init(const CanIf_ConfigType* ConfigPtr);
//************************************************************************



//************************************************************************
//						CanIf_DeInit
//
//	Function Description    : De-initializes the CanIf module.
//	Parameter in			: none
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : none
//	Requirment				: SWS_CANIF_91002
//	Sync/Async				: Synchronous
//	Reentrancy				: Non Reentrant
//	Notes					:*General behaviour and constraints on
//							  de-initialization functions are specified by
//							  [SWS_BSW_00152], [SWS_BSW_00072],
//							  [SWS_BSW_00232], [SWS_BSW_00233].
//							 *Caller of the CanIf_DeInit() function has to
//							  be sure there are no on-going transmissions/
//							  receptions, nor any pending transmission
//							  confirmations.
//************************************************************************
void CanIf_DeInit(void);
//************************************************************************



//************************************************************************
//						CanIf_SetControllerMode
//
//	Function Description    : This service calls the corresponding CAN
//							  Driver service for changing of the CAN controller mode.
//	Parameter in			: uint8 ControllerId
//							  (Abstracted CanIf ControllerId which is assigned to a
//							  CAN controller, which is requested for mode transition.)
//							  Can_ControllerStateType ControllerMode
//							  (Requested mode transition)
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : Std_ReturnType (E_OK/E_NOT_OK)
//	Requirment				: SWS_CANIF_00003
//	Sync/Async				: Asynchronous
//	Reentrancy				: Reentrant (Not for the same controller)
//	Notes					:*The service CanIf_SetControllerMode() initiates a
//							  transition to the requested CAN controller mode
//							  ControllerMode of the CAN controller which is assigned
//							  by parameter ControllerId.
//							 *[SWS_CANIF_00308] The service CanIf_SetControllerMode()
//							  shall call Can_SetControllerMode(Controller, Transition)
//							  for the requested CAN controller.
//							 *[SWS_CANIF_00311] If parameter ControllerId of
//							  CanIf_SetControllerMode() has an invalid value, the
//							  CanIf shall report development error code
//							  CANIF_E_PARAM_CONTROLLERID to the Det_ReportError service
//							  of the DET module, when CanIf_SetControllerMode() is
//							  called.(SRS_BSW_00323).
//							 *[SWS_CANIF_00774] If parameter ControllerMode of
//							  CanIf_SetControllerMode() has an invalid value
//							  (not CAN_CS_STARTED, CAN_CS_SLEEP or CAN_CS_STOPPED),
//							  theCanIfshallreportdevelopmenterrorcodeCANIF_E_PARAM_CTRLMODE
//							  to the Det_ReportError service of the DET module, when
//							  CanIf_SetControllerMode() is called.(SRS_BSW_00323).
//							 *The ID of the CAN controller is published inside the
//							  configuration description of the CanIf.
//************************************************************************
Std_ReturnType CanIf_SetControllerMode(uint8 ControllerId, Can_ControllerStateType ControllerMode);
//************************************************************************



//************************************************************************
//						CanIf_GetControllerMode
//
//	Function Description    : This service calls the corresponding CAN Driver
//							  service for obtaining the current status of the CAN controller.
//	Parameter in			: uint8 ControllerId
//							  (Abstracted CanIf ControllerId which is assigned to a CAN
//							  controller, which is requested for current operation mode.)
//	Parameter inout         : none
//	Parameter out           : Can_ControllerStateType* ControllerModePtr
//							  (Pointer to a memory location, where the current mode of
//							  the CAN controller will be stored.)
//	Return value            : Std_ReturnType (E_OK/E_NOT_OK)
//	Requirment				: SWS_CANIF_00229
//	Sync/Async				: Synchronous
//	Reentrancy				: Non Reentrant
//	Notes					:*[SWS_CANIF_00313] If parameter ControllerId of
//							  CanIf_GetControllerMode() has an invalid, the CanIf shall
//							  report development error code CANIF_E_PARAM_CONTROLLERID
//							  to the Det_ReportError service of the DET, when
//							  CanIf_GetControllerMode() is called.(SRS_BSW_00323).
//							 *[SWS_CANIF_00656] If parameter ControllerModePtr of CanIf_
//							  GetControllerMode() has an invalid value, the CanIf shall
//							  report development error code CANIF_E_PARAM_POINTER to the
//							  Det_ReportError service of the DET, when
//							  CanIf_GetControllerMode() is called.(SRS_BSW_00323).
//							 *The ID of the CAN controller module is published inside
//							  the configuration description of the CanIf.
//************************************************************************
Std_ReturnType CanIf_GetControllerMode(uint8 ControllerId, Can_ControllerStateType* ControllerModePtr);
//************************************************************************



//************************************************************************
//						CanIf_GetControllerErrorState
//
//	Function Description    : This service calls the corresponding CAN Driver
//							  service for obtaining the  error state of the CAN controller.
//	Parameter in			: uint8 ControllerId
//							  (Abstracted CanIf ControllerId which is assigned to a CAN
//							  controller, which is requested for ErrorState.)
//	Parameter inout         : none
//	Parameter out           : Can_ErrorStateType* ErrorStatePtr
//							  (Pointer to a memory location, where the  error state of
//							  the CAN controller will be stored.)
//	Return value            : Std_ReturnType (E_OK/E_NOT_OK)
//	Requirment				: SWS_CANIF_91001
//	Sync/Async				: Synchronous
//	Reentrancy				: Non Reentrant for the same ControllerId
//	Notes					:*[SWS_CANIF_00898] If parameter ControllerId of
//							  CanIf_GetControllerErrorState() has an invalid value, the
//							  CanIf shall report development error code
//							  CANIF_E_PARAM_CONTROLLERID to the Det_ReportError service
//							  of the DET, when CanIf_GetControllerErrorState() is called.
//							  (SRS_BSW_00323).
//							 *[SWS_CANIF_00899] If parameter ErrorStatePtr of CanIf_
//							  GetControllerErrorState() is a null pointer, the CanIf
//							  shall report development error code CANIF_E_PARAM_POINTER
//							  to the Det_ReportError service of the DET, when
//							  CanIf_GetControllerErrorState() is called.(SRS_BSW_00323).
//************************************************************************
Std_ReturnType CanIf_GetControllerErrorState(uint8 ControllerId, Can_ErrorStateType* ErrorStatePtr);
//************************************************************************



//************************************************************************
//						CanIf_Transmit
//
//	Function Description    : Requests transmission of a PDU.
//	Parameter in			: PduIdType TxPduId
//							  (Identifier of the PDU to be transmitted.)
//							  const PduInfoType* PduInfoPtr
//							  (Length of and pointer to the PDU data and pointer to
//							  MetaData.)
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : Std_ReturnType (E_OK/E_NOT_OK)
//	Requirment				: SWS_CANIF_00005
//	Sync/Async				: Synchronous
//	Reentrancy				: Reentrant for different PduIds. Non reentrant for the same PduId.
//	Notes					:*PduInfoPtr is a pointer to a L-SDU user memory, CAN Identifier,
//							  L-SDU handle and Data Length (see [1, Specification of CAN Driver]).
//							 *CanIf shall set the two most significant bits (’IDentifier
//							  Extension flag’ (see [12, ISO 11898-1:2015]) and ’CAN FD flag’) of
//							  the CanId ( PduInfoPtr->id) before CanIf passes the predefined
//							  CanId to CanDrv at call of Can_Write() (see [1, Specification of
//							  CAN Driver], definition of Can_IdType [SWS_Can_00416]). The CanId
//							  format type of each CAN L-PDU can be configured by
//							  CanIfTxPduCanIdType, refer to CanIfTxPduCanIdType.
//							 *CanIf_Transmit() shall accept a NULL pointer as
//							  PduInfoPtr->SduDataPtr, ifthePDUisconfiguredfortriggeredtransmission:
//							  CanIfTxPduTriggerTransmit = TRUE.
//							 *If the call of Can_Write() returns E_OK the transmit request service
//							  CanIf_Transmit() shall return E_OK.
//							 *If the call of Can_Write() returns E_NOT_OK,then the transmit request
//							  service CanIf_Transmit() shall return E_NOT_OK. If the transmit
//							  request service CanIf_Transmit() returns E_NOT_OK, then the upper
//							  layer module is responsible to repeat the transmit request.
//							 *If parameter TxPduId of CanIf_Transmit() has an invalid value,
//							  CanIf shall report development error code CANIF_E_INVALID_TXPDUID
//							  to the Det_ReportError service of the DET, when CanIf_Transmit()
//							  is called.
//							 *If parameter PduInfoPtr of CanIf_Transmit() has an invalid value,
//							  CanIf shall report development errorcode CANIF_E_PARAM_POINTER to
//							  the Det_ReportError service of the DET module, when
//							  CanIf_Transmit() is called.
//							 *When CanIf_Transmit() is called with PduInfoPtr->SduLength exceeding
//							  the maximum length of the PDU referenced by TxPduId:
//							  	  • SduLength > 8 if the Can_IdType indicates a classic CAN frame
//								  • SduLength > 64 if the Can_IdType indicates a CAN FD frame
//							  CanIf shall report runtime error code CANIF_E_DATA_LENGTH_MISMATCH
//							  to the Det_ReportRuntimeError() service of the DET.
//							 *Besides static configured transmissions there are dynamic
//							  transmissions, too. Therefore, the valid data length is always passed
//							  by PduInfoPtr->SduLength. Furthermore, even the frame type might
//							  change via CanIf_SetDynamicTxId(). [SWS_CANIF_00893] ensures that
//							  not matching transmit requests can be detected via DET.
//							 *When CanIf_Transmit() is called with PduInfoPtr->SduLength exceeding
//							  the maximum length of the PDU referenced by TxPduId and
//							  CanIfTxPduTruncation is enabled, CanIf shall transmit as much data as
//							  possible and discard the rest.
//							 *When CanIf_Transmit() is called withPduInfoPtr->SduLength exceeding
//							  the maximum length of the PDU referenced by TxPduId and
//							  CanIfTxPduTruncation is disabled, CanIf shall report the runtime
//							  error CANIF_E_TXPDU_LENGTH_EXCEEDED and return E_NOT_OK without
//							  further actions.
//							 *During the call of CanIf_Transmit() the buffer of PduInfoPtr is
//							  controlled by CanIf and this buffer should not be accessed for
//							  read/write from another call context. After return of this call the
//							  ownership changes to the upper layer.
//************************************************************************
Std_ReturnType CanIf_Transmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr);
//************************************************************************



//************************************************************************
//						CanIf_ReadRxPduData
//
//	Function Description    : This service provides the Data Length and the received
//							  data of the requested CanIfRxSduId to the calling upper
//							  layer.
//	Parameter in			: PduIdType CanIfRxSduId
//							  (Receive L-SDU handle specifying the corresponding CAN
//							  L-SDU ID and implicitly the CAN Driver instance as well
//							  as the corresponding CAN controller device.)
//	Parameter inout         : none
//	Parameter out           : PduInfoType* CanIfRxInfoPtr
//							  (Contains the length (SduLength) of the received PDU, a
//							  pointer to a buffer (SduDataPtr) containing the PDU, and
//							  the MetaData related to this PDU.)
//	Return value            : Std_ReturnType (E_OK/E_NOT_OK)
//	Requirment				: SWS_CANIF_00194
//	Sync/Async				: Synchronous
//	Reentrancy				: Non Reentrant
//	Notes					:*The function CanIf_ReadRxPduData() shall not accept a
//							  request and return E_NOT_OK,if the corresponding
//							  controller mode refrenced by ControllerId is different to
//							  CAN_CS_STARTED and the channel mode is in the receive
//							  path online.
//							 *If parameter CanIfRxSduId of CanIf_ReadRxPduData() has
//							  an invalid value, e.g. not configured to be stored within
//							  CanIf via CanIfRxPduReadData, CanIf shall report
//							  development error code CANIF_E_INVALID_RXPDUID to the
//							  Det_ReportError service of the DET, when
//							  CanIf_ReadRxPduData() is called.
//							 *If parameter CanIfRxInfoPtr of CanIf_ReadRxPduData () has
//							  an invalid value, CanIf shall report development error
//							  code CANIF_E_PARAM_POINTER to the Det_ReportError service
//							  of the DET module, when CanIf_ReadRxPduData() is called.
//							 *CanIf_ReadRxPduData() shall not be used for CanIfRxSduId,
//							  which are defined to receive multiple CAN-Ids
//							  (range reception).
//							 *During the call of CanIf_ReadRxPduData() the buffer of
//							  CanIfRxInfoPtr is controlled by CanIf and this buffer
//							  should not be accessed for read/write from another call
//							  context. After return of this call the ownership changes
//							  to the upper layer.
//							 *Configuration of CanIf_ReadRxPduData(): This API can be
//							  enabled or disabled at pre-compile time configuration by
//							  the configuration parameter CanIfPublicReadRxPduDataApi.
//************************************************************************
Std_ReturnType CanIf_ReadRxPduData(PduIdType CanIfRxSduId, PduInfoType* CanIfRxInfoPtr);
//************************************************************************



//************************************************************************
//						CanIf_ReadTxNotifStatus
//
//	Function Description    : This service returns the confirmation status
//							  (confirmation occurred or not) of a specific
//							  static or dynamic CAN Tx L-PDU, requested by
//							  the CanIfTxSduId.
//	Parameter in			: PduIdType CanIfTxSduId
//							  (L-SDU handle to be transmitted. This
//							  handle specifies the corresponding CAN L-SDU
//							  ID and implicitly the CAN Driver instance as
//							  well as the corresponding CAN controller
//							  device.)
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : CanIf_NotifStatusType
//							  (Current confirmation status of the
//							  corresponding CAN Tx L-PDU. )
//	Requirment				: SWS_CANIF_00202
//	Sync/Async				: Synchronous
//	Reentrancy				: Non Reentrant
//	Notes					:*This function notifies the upper layer about
//							  any transmit confirmation event to the
//							  corresponding requested L-SDU.
//							 *If configuration parameters
//							  CanIfPublicReadTxPduNotifyStatusApi and
//							  CanIfTxPduReadNotifyStatus for the transmitted
//							  L-SDU are set to TRUE, and if
//							  CanIf_ReadTxNotifStatus() is called, the
//							  CanIf shall reset the notification status for
//							  the transmitted L-SDU.
//							 *If parameter CanIfTxSduId of
//							  CanIf_ReadTxNotifStatus() is out of range or
//							  if no status information was configured for
//							  this CAN Tx L-SDU, CanIf shall report
//							  development error code CANIF_E_INVALID_TXPDUID
//							  to the Det_ReportError service of the DET when
//							  CanIf_ReadTxNotifStatus () is called.
//							 *Configuration of CanIf_ReadTxNotifyStatus():
//							  This API can be enabled or disabled at pre-compile
//							  time configuration globally by the parameter
//							  CanIfPublicReadTxPduNotifyStatusApi.
//************************************************************************
CanIf_NotifStatusType CanIf_ReadTxNotifStatus(PduIdType CanIfTxSduId);
//************************************************************************



//************************************************************************
//						CanIf_ReadRxNotifStatus
//
//	Function Description    : This service returns the indication status
//							  (indication occurred or not) of a specific CAN Rx
//							  L-PDU, requested by the CanIfRxSduId.
//	Parameter in			: PduIdType CanIfRxSduId
//							  (Receive L-SDU handle specifying the corresponding
//							  CAN L-SDU ID and implicitly the CAN Driver instance
//							  as well as the corresponding CAN controller device.)
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : CanIf_NotifStatusType
//							  (Current indication status of the corresponding CAN
//							  Rx L-PDU. )
//	Requirment				: SWS_CANIF_00202
//	Sync/Async				: Synchronous
//	Reentrancy				: Non Reentrant
//	Notes					:*This function notifies the upper layer about any
//  	  	  	  	  	  	  receive indication event to the corresponding
//							  requested L-SDU.
//							 *If configuration parameters
//							  CanIfPublicReadRxPduNotifyStatusApi and
//							  CanIfRxPduReadNotifyStatus are set to TRUE, and if
//							  CanIf_ReadRxNotifStatus() is called, then CanIf
//							  shall reset the notification status for the
//							  received L-SDU.
//							 *If parameter CanIfRxSduId of CanIf_
//							  ReadRxNotifStatus() is out of range or if status
//							  for CanRxPduId was requested whereas
//							  CanIfRxPduReadData is disabled or if no status
//							  information was configured for this CAN Rx L-SDU,
//							  CanIf shall report development error code
//							  CANIF_E_INVALID_RXPDUID to the Det_ReportError
//							  service of the DET, when CanIf_ReadRxNotifStatus()
// 	  	  	  	  	  	  	  is called.
//							 *The function CanIf_ReadRxNotifStatus() must not be
//							  used for CanIfRxSduIds, which are defined to receive
//							  multiple CAN-Ids (range reception).
//							 *Configuration of CanIf_ReadRxNotifStatus(): This
//							  API can be enabled or disabled at pre-compile time
//							  configuration globally by the parameter
//							  CanIfPublicReadRxPduNotifyStatusApi.
//************************************************************************
CanIf_NotifStatusType CanIf_ReadRxNotifStatus(PduIdType CanIfRxSduId);
//************************************************************************



//************************************************************************
//						CanIf_SetPduMode
//
//	Function Description    : This service sets the requested mode at the L-PDUs of a
//							  predefined logical PDU channel.
//	Parameter in			: uint8 ControllerId
//							  (All PDUs of the own ECU connected to the corresponding
//							  CanIf ControllerId, which is assigned to a physical CAN
//							  controller are addressed.)
//							  CanIf_PduModeType PduModeRequest
//							  (Requested PDU mode change)
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : Std_ReturnType (E_OK/E_NOT_OK)
//	Requirment				: SWS_CANIF_00008
//	Sync/Async				: Synchronous
//	Reentrancy				: Non Reentrant
//	Notes					:*The channel parameter denoting the predefined logical PDU
//							  channel can be derived from parameter ControllerId of
//							  function CanIf_SetPduMode().
//							 *If CanIf_SetPduMode() is called with invalid ControllerId,
//							  CanIf shall report development error code
//							  CANIF_E_PARAM_CONTROLLERID to the Det_ReportError service
//							  of the DET module.
//							 *If CanIf_SetPduMode() is called with invalid PduModeRequest,
//							  CanIf shall report development error code
//							  CANIF_E_PARAM_PDU_MODE to the Det_ReportError service of
//							  the DET module.
//							 *The service CanIf_SetPduMode() shall not accept any request
//							  and shall return E_NOT_OK, if the controller mode referenced
//							  by ControllerId is not in state CAN_CS_STARTED.
//************************************************************************
Std_ReturnType CanIf_SetPduMode(uint8 ControllerId, CanIf_PduModeType PduModeRequest);
//************************************************************************



//************************************************************************
//						CanIf_GetPduMode
//
//	Function Description    : This service reports the current mode of a requested PDU
//							  channel.
//	Parameter in			: uint8 ControllerId
//							  (All PDUs of the own ECU connected to the corresponding
//							  CanIf ControllerId, which is assigned to a physical CAN
//							  controller are addressed.)
//	Parameter inout         : none
//	Parameter out           : CanIf_PduModeType* PduModePtr
//							  (Pointer to a memory location, where the current mode of
//							  the logical PDU channel will be stored.)
//	Return value            : Std_ReturnType (E_OK/E_NOT_OK)
//	Requirment				: SWS_CANIF_00009
//	Sync/Async				: Synchronous
//	Reentrancy				: Reentrant (Not for the same channel)
//	Notes					:*If CanIf_GetPduMode() is called with invalid ControllerId,
//							  CanIf shall report development error code
//							  CANIF_E_PARAM_CONTROLLERID to the Det_ReportError service
//							  of the DET module.
//							 *If CanIf_GetPduMode() is called with invalid PduModePtr,
//							  CanIf shall report development error code
//							  CANIF_E_PARAM_POINTER to the Det_ReportError service of
//							  the DET module.
//************************************************************************
Std_ReturnType CanIf_GetPduMode(uint8 ControllerId, CanIf_PduModeType* PduModePtr);
//************************************************************************



//************************************************************************
//						CanIf_GetVersionInfo
//
//	Function Description    : This service returns the version information of the
//							  called CAN Interface module.
//	Parameter in			: none
//	Parameter inout         : none
//	Parameter out           : Std_VersionInfoType* VersionInfo
//							  (Pointer to where to store the version information of
//							  this module.)
//	Return value            : none
//	Requirment				: SWS_CANIF_00158
//	Sync/Async				: Synchronous
//	Reentrancy				: Reentrant
//************************************************************************
void CanIf_GetVersionInfo(Std_VersionInfoType* VersionInfo);
//************************************************************************



//************************************************************************
//						CanIf_SetDynamicTxId
//
//	Function Description    : This service reconfigures the corresponding CAN identifier
//							  of the requested CAN L-PDU.
//	Parameter in			: PduIdType CanIfTxSduId
//							  (L-SDU handle to be transmitted. This handle specifies
//							  the corresponding CAN L-SDU ID and implicitly the CAN
//							  Driver instance as well as the corresponding CAN
//							  controller device.)
//							  Can_IdType CanId
//							  (Standard/Extended CAN ID of CAN L-SDU that shall be
//							  transmitted as FD or conventional CAN frame.)
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : none
//	Requirment				: SWS_CANIF_00189
//	Sync/Async				: Synchronous
//	Reentrancy				: Non Reentrant
//	Notes					:*If parameter CanIfTxSduId of CanIf_SetDynamicTxId () has
//							  an invalid value, CanIf shall report development error
//							  code CANIF_E_INVALID_TXPDUID to the Det_ReportError
//							  service of the DET module, when CanIf_SetDynamicTxId()
//							  is called.
//							 *If parameter CanId of CanIf_SetDynamicTxId() has an
//							  invalid value, CanIf shall report development error code
//							  CANIF_E_PARAM_CANID to the Det_ReportError service of the
//							  DET module, when CanIf_SetDynamicTxId() is called.
//							 *If CanIf was not initialized before calling
//							  CanIf_SetDynamicTxId(), then the function
//							  CanIf_SetDynamicTxId() shall not execute a reconfiguration
//							  of Tx CanId.
//							 *CanIf_SetDynamicTxId() shall not be interrupted by
//							  CanIf_Transmit(), if the same L-SDU ID is handled.
//							 *Configuration of CanIf_SetDynamicTxId(): This function
//							  shall be pre compile time configurable On/Off by the
//							  configuration parameter CanIfPublicSetDynamicTxIdApi.
//************************************************************************
void CanIf_SetDynamicTxId(PduIdType CanIfTxSduId, Can_IdType CanId);
//************************************************************************



//************************************************************************
//						CanIf_SetTrcvMode
//
//	Function Description    : This service changes the operation mode of the tansceiver
//							  TransceiverId, via calling the corresponding CAN Transceiver
//							  Driver service.
//	Parameter in			: uint8 TransceiverId
//							  (Abstracted CanIf TransceiverId, which is assigned to a
//							  CAN transceiver, which is requested for mode transition.)
//							  CanTrcv_TrcvModeType TransceiverMode
//							  (Requested mode transition)
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : Std_ReturnType (E_OK/E_NOT_OK)
//	Requirment				: SWS_CANIF_00287
//	Sync/Async				: Asynchronous
//	Reentrancy				: Non Reentrant
//	Notes					:*The function CanIf_SetTrcvMode() shall call the function
//							  CanTrcv_SetOpMode(Transceiver, OpMode) on the corresponding
//							  requested CAN Transceiver Driver module.
//							 *The parameters of the service CanTrcv_SetOpMode() are of type:
//							  	  • OpMode: CanTrcv_TrcvModeType(desired operation mode)
//								  • Transceiver: uint8 (Transceiver to which function
//									call has to be applied)
//							 *If parameter TransceiverId of CanIf_SetTrcvMode() has an
//							  invalid value,the CanIf shall report development error code
//							  CANIF_E_PARAM_TRCV to the Det_ReportError service of the DET,
//							  when CanIf_SetTrcvMode () is called.
//							 *The mode of a transceiver can only be changed to CANTRCV_
//							  TRCVMODE_STANDBY, when the former mode of the transceiver
//							  has been CANTRCV_TRCVMODE_NORMAL. But this is not checked
//							  by the CanIf.
//							 *The mode of a transceiver can only be changed to CANTRCV_
//							  TRCVMODE_SLEEP, when the former mode of the transceiver has
//							  been CANTRCV_TRCVMODE_STANDBY (see [2]). But this is not
//							  checked by the CanIf.
//							 *If parameter TransceiverMode of CanIf_SetTrcvMode() has an
//							  invalid value (not CANTRCV_TRCVMODE_STANDBY,
//							  CANTRCV_TRCVMODE_SLEEP or CANTRCV_TRCVMODE_NORMAL), the CanIf
//							  shall report development error code CANIF_E_PARAM_TRCVMODE to
//							  the Det_ReportError service of the DET module, when
//							  CanIf_SetTrcvMode() is called.
//							 *The function CanIf_SetTrcvMode() should be applicable to all
//							  CAN transceivers with all values of TransceiverMode independent,
//							  if the transceiver hardware supports these modes or not. This is
//							  to ease up the view of the CanIf to the assigned physical CAN
//							  channel.
//							 *Configuration of CanIf_SetTrcvMode(): The number of supported
//							  transceiver types for each network is set up in the configuration
//							  phase (see CanIfTrcvCfg and CanIfTrcvDrvCfg). If no transceiver
//							  is used, this function may be omitted. Therefore, if no
//							  transceiver is configured in LT or PB class the API shall return
//							  with E_NOT_OK.
//************************************************************************
Std_ReturnType CanIf_SetTrcvMode(uint8 TransceiverId, CanTrcv_TrcvModeType TransceiverMode);
//************************************************************************



//************************************************************************
//						CanIf_GetTrcvMode
//
//	Function Description    : This function invokes CanTrcv_GetOpMode and updates the
//							  parameter TransceiverModePtr with the value OpMode provided
//							  by CanTrcv.
//	Parameter in			: uint8 TransceiverId
//							  (Abstracted CanIf TransceiverId, which is assigned to a
//							  CAN transceiver, which is requested for current operation
//							  mode.)
//	Parameter inout         : none
//	Parameter out           : CanTrcv_TrcvModeType* TransceiverModePtr
//							  (Requested mode of requested network the Transceiver is
//							  connected to.)
//	Return value            : Std_ReturnType (E_OK/E_NOT_OK)
//	Requirment				: SWS_CANIF_00288
//	Sync/Async				: Synchronous
//	Reentrancy				: Non Reentrant
//	Notes					:*The function CanIf_GetTrcvMode() shall call the function
//							  CanTrcv_GetOpMode(Transceiver, OpMode) on the corresponding
//							  requested CAN Transceiver Driver module.
//							 *The parameters of the service CanTrcv_GetOpMode() are of type:
//							  	  • OpMode: CanTrcv_TrcvModeType(desired operation mode)
//								  • Transceiver: uint8 (Transceiver to which API call
//									has to be applied)
//							 *If parameter TransceiverId of CanIf_GetTrcvMode() has an
//							  invalid value,the CanIf shall report development error code
//							  CANIF_E_PARAM_TRCV to the Det_ReportError service of the DET
//							  module,when CanIf_GetTrcvMode() is called.
//							 *If parameter TransceiverModePtr of CanIf_GetTrcvMode() has an
//							  invalid value, the CanIf shall report development error code
//							  CANIF_E_PARAM_POINTER to the Det_ReportError service of the
//							  DET module, when CanIf_GetTrcvMode() was called.
//							 *Configuration of CanIf_GetTrcvMode(): The number of supported
//							  transceiver types for each network is set up in the configuration
//							  phase (see CanIfTrcvCfg and CanIfTrcvDrvCfg). If no transceiver is
//							  used, this function may be omitted. Therefore, if no transceiver is
//							  configured in LT or PB class the API shall return with E_NOT_OK.
//************************************************************************
Std_ReturnType CanIf_GetTrcvMode(uint8 TransceiverId, CanTrcv_TrcvModeType* TransceiverModePtr);
//************************************************************************



//************************************************************************
//						CanIf_GetTrcvWakeupReason
//
//	Function Description    : This service returns the reason for the wake up of the
//							  transceiver TransceiverId, via calling the corresponding
//							  CAN Transceiver Driver service.
//	Parameter in			: uint8 TransceiverId
//							  (Abstracted CanIf TransceiverId, which is assigned to a
//							  CAN transceiver, which is requested for wake up reason mode.)
//	Parameter inout         : none
//	Parameter out           : CanTrcv_TrcvWakeupReasonType* TrcvWuReasonPtr
//							  (provided pointer to where the requested transceiver wake up
//							  reason shall be returned.)
//	Return value            : Std_ReturnType (E_OK/E_NOT_OK)
//	Requirment				: SWS_CANIF_00289
//	Sync/Async				: Synchronous
//	Reentrancy				: Non Reentrant
//	Notes					:*The ability to detect and differentiate the possible wake up
//							  reasons depends strongly on the CAN transceiver hardware.
//							 *The function CanIf_GetTrcvWakeupReason() shall call CanTrcv_
//							  GetBusWuReason(Transceiver, Reason) on the corresponding
//							  requested CanTrcv.
//							 * The parameters of the function CanTrcv_GetBusWuReason() are
//							  of type:
//							  	  • Reason: CanTrcv_TrcvWakeupReasonType
//								  • Transceiver: uint8 (Transceiver to which API call has
//									to be applied)
//							 *If parameter TransceiverId of CanIf_GetTrcvWakeupReason() has an
//							  invalid value, the CanIf shall report development error code
//							  CANIF_E_PARAM_TRCV to the Det_ReportError service of the DET module,
//							  when CanIf_GetTrcvWakeupReason() is called.
//							 *If parameter TrcvWuReasonPtr of CanIf_GetTrcvWakeupReason() has an
//							  invalid value, the CanIf shall report development error code
//							  CANIF_E_PARAM_POINTER to the Det_ReportError service of the DET
//							  module, when CanIf_GetTrcvWakeupReason() is called.
//							 *Please be aware, that if more than one network is available,
//							  each network may report a different wake-up reason. E.g. if an ECU
//							  uses CAN, a wake-up by CAN may occur and the incoming data may
//							  cause an internal wake-up for another CAN network.
//							 *The service CanIf_GetTrcvWakeupReason() has a "per network" view and
//							  does not vote the more important reason or sequence internally. The
//							  same may be true if e.g. one transceiver controls the power supply
//							  and the other is just powered or unpowered. Then one may be able to
//							  return CANIF_TRCV_WU_POWER_ON, whereas the other may state e.g.
//							  CANIF_TRCV_WU_RESET. It is up to the calling module to decide, how
//							  to handle the wake-up information.
//							 *Configuration of CanIf_GetTrcvWakeupReason(): The number of supported
//							  transceiver types for each network is set up in the configuration phase
//							  (see CanIfTrcvCfg and CanIfTrcvDrvCfg). If no transceiver is used, this
//							  function may be omitted. Therefore, if no transceiver is configured in
//							  LT or PB class the API shall return with E_NOT_OK.
//************************************************************************
Std_ReturnType CanIf_GetTrcvWakeupReason(uint8 TransceiverId, CanTrcv_TrcvWakeupReasonType* TrcvWuReasonPtr);
//************************************************************************



//************************************************************************
//						CanIf_SetTrcvWakeupReason
//
//	Function Description    : This function shall call CanTrcv_SetTrcvWakeupMode.
//	Parameter in			: uint8 TransceiverId
//							  (Abstracted CanIf TransceiverId, which is assigned to a CAN
//							  transceiver, which is requested for wake up notification mode
//							  transition.)
//							  CanTrcv_TrcvWakeupModeType TrcvWakeupMode
//							  (Requested transceiver wake up notification mode)
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : Std_ReturnType (E_OK/E_NOT_OK)
//	Requirment				: SWS_CANIF_00290
//	Sync/Async				: Synchronous
//	Reentrancy				: Non Reentrant
//	Notes					:*The function CanIf_SetTrcvWakeupMode() shall call
//							  CanTrcv_SetWakeupMode(Transceiver, TrcvWakeupMode) on the
//							  corresponding requested CanTrcv.
//							 * The parameters of the function CanTrcv_SetWakeupMode() are of type:
//									• TrcvWakeupMode: CanTrcv_TrcvWakeupModeType
//									• Transceiver: uint8 (Transceiver to which API call has
//									  to be applied)
//							 * The parameters of the function CanTrcv_GetBusWuReason() are
//							  of type:
//							  	  • Reason: CanTrcv_TrcvWakeupReasonType
//								  • Transceiver: uint8 (Transceiver to which API call has
//									to be applied)
//							 *The following three paragraphs are already described in the
//							  Specification of CanTrcv. They describe the behaviour of a CanTrcv
//							  in the respective transceiver wake-up mode, which is requested in
//							  parameter TrcvWakeupMode.
//							  CANIF_TRCV_WU_ENABLE: If the CanTrcv has a stored wake-up event
//							  pending for the addressed CanNetwork, the notification is executed
//							  within or immediately after the function CanTrcv_SetTrcvWakeupMode()
//							  (depending on the implementation).
//							  CANIF_TRCV_WU_DISABLE: No notifications for wake-up events for the
//							  addressed CanNetwork are passed through the CanTrcv. The transceiver
//							  device and the underlying communication driver has to buffer detected
//							  wake-up events and raise the event(s), when the wake-up notification
//							  is enabled again.
//							  CANIF_TRCV_WU_CLEAR: If notification of wake-up events is disabled
//							  (see description of mode CANIF_TRCV_WU_DISABLE), detected wake-up
//							  events are buffered. Calling CanIf_SetTrcvWakeupMode() with parameter
//							  CANIF_TRCV_WU_CLEAR clears these buffered events. Clearing of wake-up
//							  events has to be used, when the wake-up notification is disabled to
//							  clear all stored wake-up events under control of the higher layers of
//							  the CanTrcv.
//							 *If parameter TransceiverId of CanIf_SetTrcvWakeupMode() has an invalid
//							  value, the CanIf shall report development error code CANIF_E_PARAM_TRCV
//							  to the Det_ReportError service of the DET module, when
//							  CanIf_SetTrcvWakeupMode() is called.
//							 *If parameter TrcvWakeupMode of CanIf_SetTrcvWakeupMode() has an invalid
//							  value, the CanIf shall report development error code
//							  CANIF_E_PARAM_TRCVWAKEUPMODE to the Det_ReportError service of the DET
//							  module, when CanIf_SetTrcvWakeupMode() is called.
//							 *Configuration of CanIf_SetTrcvWakeupMode(): The number of supported
//							  transceiver types for each network is setup in the configuration phase
//							  (see CanIfTrcvCfg and CanIfTrcvDrvCfg). If no transceiver is used, this
//							  function may be omitted. Therefore, if no transceiver is configured in
//							  LT or PB class the API shall return with E_NOT_OK.
//************************************************************************
Std_ReturnType CanIf_SetTrcvWakeupMode(uint8 TransceiverId, CanTrcv_TrcvWakeupModeType TrcvWakeupMode);
//************************************************************************



//************************************************************************
//						CanIf_CheckWakeup
//
//	Function Description    : This service checks, whether an underlying CAN driver or a
//							  CAN transceiver driver already signals a wake up event.
//	Parameter in			: EcuM_WakeupSourceType WakeupSource
//							  (Source device, which initiated the wake up event: CAN
//							  controller or CAN transceiver)
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : Std_ReturnType (E_OK/E_NOT_OK)
//	Requirment				: SWS_CANIF_00219
//	Sync/Async				: Asynchronous
//	Reentrancy				: Reentrant
//	Notes					:*Integration Code calls this function.
//							 *If parameter WakeupSource of CanIf_CheckWakeup() has an invalid
//							  value, CanIf shall report development error code
//							  CANIF_E_PARAM_WAKEUPSOURCE to the Det_ReportError service of the
//							  DET, when CanIf_CheckWakeup() is called.
//							 *The call context of CanIf_CheckWakeup() is either on interrupt
//							  level (interrupt mode) or on task level (polling mode).
//							 *CanIf shall provide wake-up service CanIf_CheckWakeup () only, if
//							  	  • underlying CAN Controller provides wake-up support and
//								    wake-up is enabled by the parameter CanIfCtrlWakeupSupport and by
//									CanDrv configuration.
//								  • and/or underlying CAN Transceiver provides wake-up support and
//								    wake-up is enabled by the parameter CanIfTrcvWakeupSupport and by
//									CanTrcv configuration.
//								  • and configuration parameter CanIfWakeupSupport is enabled.
//							 *Configuration of CanIf_CheckWakeup(): If no wake-up shall be used, this
//							  API can be omitted by disabling of CanIfWakeupSupport.
//************************************************************************
Std_ReturnType CanIf_CheckWakeup(EcuM_WakeupSourceType WakeupSource);
//************************************************************************



//************************************************************************
//						CanIf_CheckValidation
//
//	Function Description    : This service checks, whether an underlying CAN driver or a
//							  CAN transceiver driver already signals a wake up event.
//	Parameter in			: EcuM_WakeupSourceType WakeupSource
//							  (Source device, which initiated the wake up event and which
//							  has to be validated: CAN controller or CAN transceiver.)
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : Std_ReturnType (E_OK/E_NOT_OK)
//	Requirment				: SWS_CANIF_00178
//	Sync/Async				: Synchronous
//	Reentrancy				: Reentrant
//	Notes					:*Integration Code calls this function.
//							 *If parameter WakeupSource of CanIf_CheckValidation () has an invalid
//							  value, the CanIf shall report development error code
//							  CANIF_E_PARAM_WAKEUPSOURCE to the Det_ReportError service of the DET
//							  module, when CanIf_CheckValidation() is called.
//							 *The call context of CanIf_CheckValidation() is either on interrupt
//							  level (interrupt mode) or on task level (polling mode).
//							 *The corresponding CAN controller and transceiver must be switched on
//							  via CanTrcv_SetOpMode(Transceiver, CANTRCV_TRCVMODE_NORMAL) and
//							  Can_SetControllerMode(Controller, CAN_CS_STARTED) and the corresponding
//							  mode indications must have been called.
//							 *Configuration of CanIf_CheckValidation(): If no validation is needed,
//							  this API can be omitted by disabling of
//							  CanIfPublicWakeupCheckValidSupport.
//************************************************************************
Std_ReturnType CanIf_CheckValidation(EcuM_WakeupSourceType WakeupSource);
//************************************************************************



//************************************************************************
//						CanIf_GetTxConfirmationState
//
//	Function Description    : This service reports, if any TX confirmation has been done for the
//							  whole CAN controller since the last CAN controller start.
//	Parameter in			: uint8 ControllerId
//							  (Abstracted CanIf ControllerId which is assigned to a CAN controller.)
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : CanIf_NotifStatusType
//							  (Combined TX confirmation status for all TX PDUs of the CAN controller)
//	Requirment				: SWS_CANIF_00734
//	Sync/Async				: Synchronous
//	Reentrancy				: Reentrant (Not for the same controller)
//	Notes					:*If parameter ControllerId of CanIf_GetTxConfirmationState() has an
//							  invalid value, the CanIf shall report development error code
//							  CANIF_E_PARAM_CONTROLLERID to the Det_ReportError service of the DET
//							  module, when CanIf_GetTxConfirmationState() is called.
//							 *The call context of CanIf_GetTxConfirmationState() is on task level
//							  (polling mode).
//							 *Configuration of CanIf_GetTxConfirmationState(): If BusOff Recovery
//							  of CanSm doesn’t need the status of the Tx confirmations, this API
//							  can be omitted by disabling of CanIfPublicTxConfirmPollingSupport.
//************************************************************************
CanIf_NotifStatusType CanIf_GetTxConfirmationState(uint8 ControllerId);
//************************************************************************



//************************************************************************
//						CanIf_ClearTrcvWufFlag
//
//	Function Description    : Requests the CanIf module to clear the WUF flag of the designated
//							  CAN transceiver.
//	Parameter in			: uint8 TransceiverId
//							  (Abstract CanIf TransceiverId, which is assigned to the designated
//							  CAN transceiver.)
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : Std_ReturnType (E_OK/E_NOT_OK)
//	Requirment				: SWS_CANIF_00760
//	Sync/Async				: Asynchronous
//	Reentrancy				: Reentrant for different CAN transceivers
//	Notes					:*Within CanIf_ClearTrcvWufFlag() the function
//							  CanTrcv_ClearTrcvWufFlag() shall be called.
//							 *If parameter TransceiverId of CanIf_ClearTrcvWufFlag() has an
//							  invalid value, the CanIf shall report development error code
//							  CANIF_E_PARAM_TRCV to the Det_ReportError service of the DET module,
//							  when CanIf_ClearTrcvWufFlag() is called.
//							 *Configuration of CanIf_ClearTrcvWufFlag(): Whether the CanIf
//							  supports this function shall be pre compile time configurable On/Off
//							  by the configuration parameter CanIfPublicPnSupport.
//************************************************************************
Std_ReturnType CanIf_ClearTrcvWufFlag(uint8 TransceiverId);
//************************************************************************



//************************************************************************
//						CanIf_CheckTrcvWakeFlag
//
//	Function Description    : Requests the CanIf module to check the Wake flag of the designated
//							  CAN transceiver.
//	Parameter in			: uint8 TransceiverId
//							  (Abstract CanIf TransceiverId, which is assigned to the designated
//							  CAN transceiver.)
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : Std_ReturnType (E_OK/E_NOT_OK)
//	Requirment				: SWS_CANIF_00761
//	Sync/Async				: Asynchronous
//	Reentrancy				: Reentrant for different CAN transceivers
//	Notes					:*Within CanIf_CheckTrcvWakeFlag() the function CanTrcv_CheckWakeFlag()
//							  shall be called.
//							 *If parameter TransceiverId of CanIf_CheckTrcvWakeFlag() has an invalid
//							  value, the CanIf shall report development error code CANIF_E_PARAM_TRCV
//							  to the Det_ReportError service of the DET module, when
//							  CanIf_CheckTrcvWakeFlag() is caled.
//							 *Configuration of CanIf_CheckTrcvWakeFlag(): Whether the CanIf supports
//							  this function shall be pre compile time configurable On/Off by the
//							  configuration parameter CanIfPublicPnSupport.
//************************************************************************
Std_ReturnType CanIf_CheckTrcvWakeFlag(uint8 TransceiverId);
//************************************************************************



//************************************************************************
//						CanIf_SetBaudrate
//
//	Function Description    : This service shall set the baud rate configuration of the CAN
//							  controller. Depending on necessary baud rate modifications the
//							  controller might have to reset.
//	Parameter in			: uint8 ControllerId
//							  (Abstract CanIf ControllerId which is assigned to a CAN controller,
//							  whose baud rate shall be set.)
//							  uint16 BaudRateConfigID
//							  (references a baud rate configuration by ID (see CanController
//							  BaudRateConfigID))
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : Std_ReturnType (E_OK/E_NOT_OK)
//	Requirment				: SWS_CANIF_00867
//	Sync/Async				: Synchronous
//	Reentrancy				: Reentrant for different ControllerIds. Non reentrant for the same
//							  ControllerId.
//	Notes					:*The service CanIf_SetBaudrate() shall call Can_SetBaudrate(Controller,
//							  BaudRateConfigID) for the requested CAN Controller.
//							 *If CanIf_SetBaudrate() is called with invalid ControllerId, CanIf shall
//							  report development error code CANIF_E_PARAM_CONTROLLERID to the
//							  Det_ReportError service of the DET module.
//							 *The parameter BaudRateConfigID of CanIf_SetBaudrate() is not checked by
//							  CanIf. This has to be done by responsible CanDrv.
//							 *The call context of CanIf_SetBaudrate() is on task level (polling mode).
//							 *If CanIf supports changing baud rate and thus CanIf_SetBaudrate(), shall
//							  be configurable via CanIfSetBaudrateApi.
//************************************************************************
Std_ReturnType CanIf_SetBaudrate(uint8 ControllerId, uint16 BaudRateConfigID);
//************************************************************************



//************************************************************************
//						CanIf_SetIcomConfiguration
//
//	Function Description    : This service shall change the Icom Configuration of a CAN controller
//							  to the requested one.
//	Parameter in			: uint8 ControllerId
//							  (Abstract CanIf ControllerId which is assigned to a CAN controller.)
//							  IcomConfigIdType ConfigurationId
//							  (Requested Configuration)
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : Std_ReturnType (E_OK/E_NOT_OK)
//	Requirment				: SWS_CANIF_00861
//	Sync/Async				: Asynchronous
//	Reentrancy				: Reentrant only for different controller Ids
//	Notes					:*The interface CanIf_SetIcomConfiguration() is called by CanSm to activate
//							  Pretended Networking and load the requested ICOM configuration via CAN
//							  Driver.
//							 *The service CanIf_SetIcomConfiguration() shall call Can_
//							  SetIcomConfiguration(Controller, ConfigurationId) for the requested
//							  CanDrv to set the requested ICOM configuration.
//							 *If CanIf_SetIcomConfiguration() is called with invalid ControllerId,
//							  CanIf shall report development error code CANIF_E_PARAM_CONTROLLERID to
//							  the Det_ReportError service of the DET module.
//							 *CanIf_SetIcomConfiguration() shall be pre compile time configurable
//							  ON/OFF by the configuration parameter CanIfPublicIcomSupport.
//************************************************************************
Std_ReturnType CanIf_SetIcomConfiguration(uint8 ControllerId, IcomConfigIdType ConfigurationId);
//************************************************************************



//************************************************************************
//						CanIf_GetControllerRxErrorCounter
//
//	Function Description    : This service calls the corresponding CAN Driver service for obtaining
//							  the Rx error counter of the CAN controller.
//	Parameter in			: uint8 ControllerId
//							  (Abstract CanIf ControllerId which is assigned to a CAN controller.)
//	Parameter inout         : none
//	Parameter out           : uint8* RxErrorCounterPtr
//							  (Pointer to a memory location, where the current Rx error counter
//							  of the CAN controller will be stored.)
//	Return value            : Std_ReturnType (E_OK/E_NOT_OK)
//	Requirment				: SWS_CANIF_91003
//	Sync/Async				: Synchronous
//	Reentrancy				: Non Reentrant for the same ControllerId
//	Notes					:*If parameter ControllerId of CanIf_GetControllerRxErrorCounter() has an
//							  invalid value, the CanIf shall report development error code
//							  CANIF_E_PARAM_CONTROLLERID to the Det_ReportError service of the DET,
//							  when CanIf_GetControllerRxErrorCounter() is called.
//							 *If parameter RxErrorCounterPtr of CanIf_GetControllerRxErrorCounter()
//							  is a null pointer, the CanIf shall report development error code
//							  CANIF_E_PARAM_POINTER to the Det_ReportError service of the DET, when
//							  CanIf_GetControllerRxErrorCounter() is called.
//************************************************************************
Std_ReturnType CanIf_GetControllerRxErrorCounter(uint8 ControllerId, uint8* RxErrorCounterPtr);
//************************************************************************



//************************************************************************
//						CanIf_GetControllerTxErrorCounter
//
//	Function Description    : This service calls the corresponding CAN Driver service for obtaining
//							  the Tx error counter of the CAN controller.
//	Parameter in			: uint8 ControllerId
//							  (Abstract CanIf ControllerId which is assigned to a CAN controller.)
//	Parameter inout         : none
//	Parameter out           : uint8* TxErrorCounterPtr
//							  (Pointer to a memory location, where the current Tx error counter
//							  of the CAN controller will be stored.)
//	Return value            : Std_ReturnType (E_OK/E_NOT_OK)
//	Requirment				: SWS_CANIF_91004
//	Sync/Async				: Synchronous
//	Reentrancy				: Non Reentrant for the same ControllerId
//	Notes					:*If parameter ControllerId of CanIf_GetControllerTxErrorCounter() has
//							  an invalid value, the CanIf shall report development error code
//							  CANIF_E_PARAM_CONTROLLERID to the Det_ReportError service of the DET,
//							  when CanIf_GetControllerTxErrorCounter() is called.
//							 *If parameter TxErrorCounterPtr of CanIf_GetControllerTxErrorCounter()
//							  is a null pointer, the CanIf shall report development error code
//							  CANIF_E_PARAM_POINTER to the Det_ReportError service of the DET,
//							  when CanIf_GetControllerTxErrorCounter() is called.
//************************************************************************
Std_ReturnType CanIf_GetControllerTxErrorCounter(uint8 ControllerId, uint8* TxErrorCounterPtr);
//************************************************************************



//************************************************************************
//						CanIf_EnableBusMirroring
//
//	Function Description    : Enables or disables mirroring for a CAN controller.
//	Parameter in			: uint8 ControllerId
//							  (Abstract CanIf ControllerId which is assigned to a CAN controller.)
//							  boolean MirroringActive
//							  (TRUE: Mirror_ReportCanFrame will be called for each frame received
//							  or transmitted on the given controller. FALSE: Mirror_ ReportCanFrame
//							  will not be called for the given controller.)
//	Parameter inout         : none
//	Parameter out           : none
//	Return value            : Std_ReturnType (E_OK/E_NOT_OK)
//	Requirment				: SWS_CANIF_91005
//	Sync/Async				: Synchronous
//	Reentrancy				: Reentrant
//	Notes					:*If Bus Mirroring is not enabled (see CanIfBusMirroringSupport), the
//							  API CanIf_EnableBusMirroring() can be omitted.
//							 *If parameter ControllerId of CanIf_EnableBusMirroring() has an
//							  invalid value, the CanIf shall report development error code
//							  CANIF_E_PARAM_CONTROLLERID to the Det_ReportError service of the DET,
//							  when CanIf_EnableBusMirroring() is called.
//************************************************************************
Std_ReturnType CanIf_EnableBusMirroring(uint8 ControllerId, boolean MirroringActive);
//************************************************************************


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
 Std_ReturnType CanIf_TriggerTransmit(PduIdType TxPduId, PduInfoType* PduInfoPtr);
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
 void CanIf_TxConfirmation(PduIdType CanTxPduId);
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
 void CanIf_RxIndication(const Can_HwType* Mailbox, const PduInfoType* PduInfoPtr);
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
 void CanIf_ControllerBusOff(uint8 ControllerId);
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
 void CanIf_ControllerModeIndication(uint8 ControllerId, Can_ControllerStateType ControllerMode);
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
 void CanIf_CurrentIcomConfiguration(uint8 ControllerId, IcomConfigIdType ConfigurationId, IcomSwitch_ErrorType Error);
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
 void CanIf_ConfirmPnAvailability(uint8 TransceiverId);
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
 void CanIf_ClearTrcvWufFlagIndication(uint8 TransceiverId);
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
 void CanIf_CheckTrcvWakeFlagIndication(uint8 TransceiverId);
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
 void CanIf_TrcvModeIndication(uint8 TransceiverId, CanTrcv_TrcvModeType TransceiverMode);
 //************************************************************************


#endif /* CANIF_H_ */
