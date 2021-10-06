/*
 * CanIf_PBcfg.c
 *
 *  Created on: 4 Feb 2020
 *      Author: Yahia
 */

#include "CanIf.h"
#include "CanIf_PBcfg.h"
#include "PduR_CanIf.h"
#include "CanTp_Cbk.h"
#include "CanSm_Cbk.h"
#include "J1939Nm_Cbk.h"
#include "Xcp_Cbk.h"


/*****************************************************************************************/
/*                                Exported Variables Definition                          */
/*****************************************************************************************/
extern CanController CanControllerCfg[];
extern CanHardwareObject HOHObj[];





/*****************************************************************************************/
/*                                  Can Configuration                                    */
/*****************************************************************************************/
CanIfCtrlCfg CanIfCtrlCfg_CONTAINER[CanIf_MAX_CONTROLLERS_NUMBER] = {
		{
				/* CanIfCtrlId  */
				CAN0_ID,

				/* CanIfCtrlWakeupSupport */
				STD_OFF,

				/* CanIfCtrlCanCtrlRef  */
				&CanControllerCfg[0]
		}
		,
		{
				/* CanIfCtrlId  */
				CAN1_ID,

				/* CanIfCtrlWakeupSupport */
				STD_OFF,

				/* CanIfCtrlCanCtrlRef  */
				&CanControllerCfg[0]
		}
};




/*****************************************************************************************/
/*              Configurating multiple CANID ranges for a given same HRH.                */
/*****************************************************************************************/
CanIfHrhRangeCfg CanIfHrhRangeCfg_CONTAINER[CanIf_MAX_HRH_RANGE] = {
		{
				/* CanIfHrhRangeBaseId */
				0,

				/* CanIfHrhRangeMask */
				(uint32)0x7FFF,

				/* CanIfHrhRangeRxPduLowerCanId */
				(uint32)0x7FFF,

				/* CanIfHrhRangeRxPduRangeCanIdType */
				STANDARD_CAN,

				/* CanIfHrhRangeRxPduUpperCanId */
				(uint32)0x7FFF
		}
};




/*****************************************************************************************/
/*                                    HRH configuration                                  */
/*****************************************************************************************/
CanIfHrhCfg CanIfHrhCfg_CONTAINER[CAN_HRH_NUMBER] = {
		{
				/* CanIfHrhSoftwareFilter */
				STD_OFF,

				/* CanIfHrhCanCtrlIdRef */
				&CanIfCtrlCfg_CONTAINER[0],

				/* CanIfHrhIdSymRef */
				&HOHObj[1],

				/* CanIfHrhRangeConfig */
				NULL_PTR
		}
		,
		{
				/* CanIfHrhSoftwareFilter */
				STD_OFF,

				/* CanIfHrhCanCtrlIdRef */
				&CanIfCtrlCfg_CONTAINER[1],

				/* CanIfHrhIdSymRef */
				&HOHObj[3],

				/* CanIfHrhRangeConfig */
				NULL_PTR
		}
};




/*****************************************************************************************/
/*                                    HTH configuration                                  */
/*****************************************************************************************/
CanIfHthCfg CanIfHthCfg_CONTAINER[CAN_HTH_NUMBER] = {
		{
				/* CanIfHthCanCtrlIdRef */
				&CanIfCtrlCfg_CONTAINER[0],

				/* CanIfHthIdSymRef */
				&HOHObj[0]
		}
		,
		{
				/* CanIfHthCanCtrlIdRef */
				&CanIfCtrlCfg_CONTAINER[1],

				/* CanIfHthIdSymRef */
				&HOHObj[2]
		}
};



/*****************************************************************************************/
/*                                    HOH configuration                                  */
/*****************************************************************************************/
CanIfInitHohCfg CanIfInitHohCfg_CONTAINER[CanIf_MAX_HOH_NUMBER] = {
		{
				/* CanIfHrhCfgRef */
				&CanIfHrhCfg_CONTAINER[0],

				/* CanIfHthCfgRef */
				&CanIfHthCfg_CONTAINER[0]
		}
		,
		{
				/* CanIfHrhCfgRef */
				&CanIfHrhCfg_CONTAINER[1],

				/* CanIfHthCfgRef */
				&CanIfHthCfg_CONTAINER[1]
		}
};



/*****************************************************************************************/
/*                                   Buffer configuration                                */
/*****************************************************************************************/
CanIfBufferCfg CanIfBufferCfg_CONTAINER[CanIf_MAX_BUFFER_NUMBER] = {
		{
				/* CanIfBufferSize */
				0,

				/* CanIfBufferHthRef */
				NULL_PTR
		}
};



/*****************************************************************************************/
/*                                  Tx PDU configuration                                 */
/*****************************************************************************************/
CanIfTxPduCfg CanIfTxPduCfg_CONTAINER[CanIf_MAX_TxPDU_NUMBER] = {
		{
				/* CanIfTxPduCanId */
				CAN0_ID,

				/* CanIfTxPduCanIdMask */
				(uint32)0x7FF,

				/* CanIfTxPduCanIdType */
				STANDARD_CAN,

				/* CanIfTxPduId */
				0x0001,

				/* CanIfTxPduPnFilterPdu */
				STD_OFF,

				/* CanIfTxPduReadNotifyStatus */
				STD_OFF,

				/* CanIfTxPduTriggerTransmit */
				STD_OFF,

				/* CanIfTxPduTruncation */
				STD_ON,

				/* CanIfTxPduType */
				PDU_STATIC,

				/* CanIfTxPduUserTriggerTransmitName */
				NULL_PTR,

				/* CanIfTxPduUserTxConfirmationName */
				CanTp_TxConfirmation,

				/* CanIfTxPduUserTxConfirmationUL */
				CANIF_USER_CAN_TP,

				/* CanIfTxPduBufferRef */
				NULL_PTR,

				/* CanIfTxPduRef */
				NULL_PTR
		}
		,
		{
				/* CanIfTxPduCanId */
				CAN1_ID,

				/* CanIfTxPduCanIdMask */
				(uint32)0x7FF,

				/* CanIfTxPduCanIdType */
				STANDARD_CAN,

				/* CanIfTxPduId */
				0x0002,

				/* CanIfTxPduPnFilterPdu */
				STD_OFF,

				/* CanIfTxPduReadNotifyStatus */
				STD_OFF,

				/* CanIfTxPduTriggerTransmit */
				STD_ON,

				/* CanIfTxPduTruncation */
				STD_ON,

				/* CanIfTxPduType */
				PDU_STATIC,

				/* CanIfTxPduUserTriggerTransmitName */
				PduR_CanIfTriggerTransmit,

				/* CanIfTxPduUserTxConfirmationName */
				PduR_CanIfTxConfirmation,

				/* CanIfTxPduUserTxConfirmationUL */
				CANIF_USER_PDUR,

				/* CanIfTxPduBufferRef */
				NULL_PTR,

				/* CanIfTxPduRef */
				NULL_PTR
		}
};




/*****************************************************************************************/
/*                                  Rx PDU configuration                                 */
/*****************************************************************************************/
CanIfRxPduCfg CanIfRxPduCfg_CONTAINER[CanIf_MAX_RxPDU_NUMBER] = {
		{
				/* CanIfRxPduCanId */
				CAN0_ID,

				/* CanIfRxPduCanIdMask */
				(uint32)0x7FF,

				/* CanIfRxPduCanIdType */
				STANDARD_CAN,

				/* CanIfRxPduDataLength */
				5,

				/* CanIfRxPduDataLengthCheck */
				STD_ON,

				/* CanIfRxPduId */
				0x0003,

				/* CanIfRxPduReadData */
				STD_OFF,

				/* CanIfRxPduReadNotifyStatus */
				STD_OFF,

				/* CanIfRxPduUserRxIndicationName */
				PduR_CanIfRxIndication,

				/* CanIfRxPduUserRxIndicationUL */
				CANIF_USER_PDUR,

				/* CanIfRxPduHrhIdRef */
				&CanIfHrhCfg_CONTAINER[0],

				/* CanIfRxPduRef */
				NULL_PTR
		}
		,
		{
				/* CanIfRxPduCanId */
				CAN1_ID,

				/* CanIfRxPduCanIdMask */
				(uint32)0x7FF,

				/* CanIfRxPduCanIdType */
				STANDARD_CAN,

				/* CanIfRxPduDataLength */
				3,

				/* CanIfRxPduDataLength */
				STD_ON,

				/* CanIfRxPduId */
				0x0004,

				/* CanIfRxPduReadData */
				STD_OFF,

				/* CanIfRxPduReadNotifyStatus */
				STD_OFF,

				/* CanIfRxPduUserRxIndicationName */
				PduR_CanIfRxIndication,

				/* CanIfRxPduUserRxIndicationUL */
				CANIF_USER_PDUR,

				/* CanIfRxPduHrhIdRef */
				&CanIfHrhCfg_CONTAINER[1],

				/* CanIfRxPduRef */
				NULL_PTR
		}
};




/*****************************************************************************************/
/*                                 Public configuration                                  */
/*****************************************************************************************/
CanIfPublicCfg CanIfPublicCfg_CONTAINER[CanIf_MAX_PUBLIC_CONFIG_NUMBER] = {
		{
				/* CanIfBusMirroringSupport */
				CANIF_BusMirroringSupport,

				/* CanIfDevErrorDetect */
				CANIF_DevErrorDetect,

				/* CanIfMetaDataSupport */
				CANIF_MetaDataSupport,

				/* CanIfPublicCddHeaderFile */
				NULL_PTR,

				/* CanIfPublicHandleTypeEnum */
				CANIF_PublicHandleTypeEnum,

				/* CanIfPublicIcomSupport */
				CANIF_PublicIcomSupport,

				/* CanIfPublicMultipleDrvSupport */
				CANIF_PublicMultipleDrvSupport,

				/* CanIfPublicPnSupport */
				CANIF_PublicPnSupport,

				/* CanIfPublicReadRxPduDataApi */
				CANIF_PublicReadRxPduDataApi,

				/* CanIfPublicReadRxPduNotifyStatusApi */
				CANIF_PublicReadRxPduNotifyStatusApi,

				/* CanIfPublicReadTxPduNotifyStatusApi */
				CANIF_PublicReadTxPduNotifyStatusApi,

				/* CanIfPublicSetDynamicTxIdApi */
				CANIF_PublicSetDynamicTxIdApi,

				/* CanIfPublicTxBuffering */
				CANIF_PublicTxBuffering,

				/* CanIfPublicTxConfirmPollingSupport */
				CANIF_PublicTxConfirmPollingSupport,

				/* CanIfPublicWakeupCheckValidByNM */
				CANIF_PublicWakeupCheckValidByNM,

				/* CanIfPublicWakeupCheckValidSupport */
				CANIF_PublicWakeupCheckValidSupport,

				/* CanIfSetBaudrateApi */
				CANIF_SetBaudrateApi,

				/* CanIfTriggerTransmitSupport */
				CANIF_TriggerTransmitSupport,

				/* CanIfTxOfflineActiveSupport */
				CANIF_TxOfflineActiveSupport,

				/* CanIfVersionInfoApi */
				CANIF_VersionInfoApi,

				/* CanIfWakeupSupport */
				CANIF_WakeupSupport
		}
};



/*****************************************************************************************/
/*                                  Private configuration                                */
/*****************************************************************************************/
CanIfPrivateCfg CanIfPrivateCfg_CONTAINER[CanIf_MAX_PRIVATE_CONFIG_NUMBER] = {
		{
				/* CanIfFixedBuffer */
				CANIF_FixedBuffer,

				/* CanIfPrivateDataLengthCheck */
				CANIF_PrivateDataLengthCheck,

				/* CanIfPrivateSoftwareFilterType */
				CANIF_PrivateSoftwareFilterType,

				/* CanIfSupportTTCAN */
				CANIF_SupportTTCAN
		}
};



/*****************************************************************************************/
/*                                  CanIf Init Container                                 */
/*****************************************************************************************/
CanIfInitCfg CanIfInitCfg_CONTAINER[CanIf_MAX_INIT_SETS] = {
		{
				/* CanIfInitCfgSet */
				NULL_PTR,

				/* CanIfMaxBufferSize */
				CanIf_MaxSizeTxBuffers,

				/* CanIfMaxRxPduCfg */
				CanIf_MaxNumRxPDUs,

				/* CanIfMaxTxPduCfg */
				CanIf_MaxNumTxPDUs,

				/* CanIfRxPduConfig */
				CanIfRxPduCfg_CONTAINER,

				/* CanIfTxPduConfig */
				CanIfTxPduCfg_CONTAINER,

				/* CanIfBufferConfig */
				CanIfBufferCfg_CONTAINER,

				/* CanIfInitHohConfig */
				CanIfInitHohCfg_CONTAINER
		}
};



/*****************************************************************************************/
/*                                CanIf Config Container                                 */
/*****************************************************************************************/
CanIf_ConfigType CanIf_ConfigType_CONTAINER[CanIf_MAX_CONFIGURATION_SETS] = {
		{
				/* CanIfDispatchCfgRef */
				NULL_PTR,

				/* CanIfCtrlDrvCfgRef */
				NULL_PTR,

				/* CanIfInitCfgRef */
				CanIfInitCfg_CONTAINER,

				/* CanIfPrivateCfgRef */
				CanIfPrivateCfg_CONTAINER,

				/* CanIfPublicCfgRef */
				CanIfPublicCfg_CONTAINER,

				/* CanIfTrcvDrvCfgRef */
				NULL_PTR
		}
};








