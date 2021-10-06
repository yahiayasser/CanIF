/*
 * CanIf_Cfg.h
 *
 *  Created on: 3 Feb 2020
 *      Author: Yahia
 */

#ifndef CANIF_CFG_H_
#define CANIF_CFG_H_


/* Module Version 1.0.0 */
#define CANIF_CFG_SW_MAJOR_VERSION           (1U)
#define CANIF_CFG_SW_MINOR_VERSION           (0U)
#define CANIF_CFG_SW_PATCH_VERSION           (0U)

/* AUTOSAR Version 4.3.1 */
#define CANIF_CFG_AR_RELEASE_MAJOR_VERSION   (4U)
#define CANIF_CFG_AR_RELEASE_MINOR_VERSION   (3U)
#define CANIF_CFG_AR_RELEASE_PATCH_VERSION   (1U)


#define CANIF_MODE		Interrupt_Mode
#define Interrupt_Mode	(0x00)
#define Polling_Mode	(0x01)
#define Mixed_Mode		(0x02)

#define CANIF_HANDLE_TYPE 			CAN_HANDLE_TYPE

#define CanIf_MaxSizeTxBuffers		0U

#define CanIf_MaxNumRxPDUs			10U

#define CanIf_MaxNumTxPDUs			10U

/*****************************************************************************************/
/*                          CanIf Public/Private configuration                           */
/*****************************************************************************************/

/*
	[ECUC_CanIf_00827]
	STD_ON: Minimum buffer element length is fixed to 8 Bytes.
	STD_OFF: Buffer element length depends on the size of the referencing PDUs.
*/
#define CANIF_FixedBuffer STD_OFF

/*
	[ECUC_CanIf_00617]
	STD_ON: Enabled
	STD_OFF: Disabled
*/
#define CANIF_PrivateDataLengthCheck STD_OFF

/*
	[ECUC_CanIf_00847]
	STD_ON: Enabled
	STD_OFF: Disabled
*/
#define CANIF_BusMirroringSupport STD_OFF


/*
	[ECUC_CanIf_00614]
	STD_ON: Enabled
	STD_OFF: Disabled
*/
#define CANIF_DevErrorDetect STD_ON

/*
	[ECUC_CanIf_00824]
	STD_ON: Enabled
	STD_OFF: Disabled
*/
#define CANIF_MetaDataSupport STD_OFF

/*
	[ECUC_CanIf_00742]
	UINT8:  For CAN hardware units with less than 255 HW objects
	UINT16: For CAN hardware units with more than 255 HW objects
*/
#define CANIF_PublicHandleTypeEnum UINT8
#define UINT8  (0x00)
#define UINT16 (0x01)

/*
	[ECUC_CanIf_00607]
	STD_ON: Enabled
	STD_OFF: Disabled
*/
#define CANIF_PublicReadRxPduDataApi STD_OFF

/*
	[ECUC_CanIf_00608]
	STD_ON: Enabled
	STD_OFF: Disabled
*/
#define CANIF_PublicReadRxPduNotifyStatusApi STD_ON

/*
	[ECUC_CanIf_00609]
	STD_ON: Enabled
	STD_OFF: Disabled
*/
#define CANIF_PublicReadTxPduNotifyStatusApi STD_ON

/*
	[ECUC_CanIf_00610]
	STD_ON: Enabled
	STD_OFF: Disabled
*/
#define CANIF_PublicSetDynamicTxIdApi  STD_OFF

/*
	[ECUC_CanIf_00618]
	STD_ON: Enabled
	STD_OFF: Disabled
*/
#define CANIF_PublicTxBuffering  STD_ON

/*
	[ECUC_CanIf_00733]
	STD_ON: Enabled
	STD_OFF: Disabled
*/
#define CANIF_PublicTxConfirmPollingSupport  STD_OFF

/*
	[ECUC_CanIf_00611]
	STD_ON: Enabled
	STD_OFF: Disabled
*/
#define CANIF_PublicWakeupCheckValidSupport  STD_OFF
#if(STD_ON == CANIF_PublicWakeupCheckValidSupport)
/*
	[ECUC_CanIf_00741]
	STD_ON: Enabled
	STD_OFF: Disabled
*/
#define CANIF_PublicWakeupCheckValidByNM STD_OFF
#else
#endif

/*
	[ECUC_CanIf_00838]
	STD_ON: Enabled
	STD_OFF: Disabled
*/
#define CANIF_SetBaudrateApi  STD_OFF

/*
	[ECUC_CanIf_00844]
	STD_ON: Enabled
	STD_OFF: Disabled
*/
#define CANIF_TriggerTransmitSupport  STD_ON

/*
	[ECUC_CanIf_00837]
	STD_ON: Enabled
	STD_OFF: Disabled
*/
#define CANIF_TxOfflineActiveSupport  STD_OFF

/*
	[ECUC_CanIf_00613]
	STD_ON: Enabled
	STD_OFF: Disabled
*/
#define CANIF_VersionInfoApi  STD_OFF

/*
	[ECUC_CanIf_00843]
	STD_ON: Enabled
	STD_OFF: Disabled
*/
#define CANIF_WakeupSupport  STD_OFF

/*
	[ECUC_CanIf_00839]
	STD_ON: Enabled
	STD_OFF: Disabled
*/
#define CANIF_PublicIcomSupport  STD_OFF

/*
	[ECUC_CanIf_00612]
	STD_ON: Enabled
	STD_OFF: Disabled
*/
#define CANIF_PublicMultipleDrvSupport  STD_ON

/*
	[ECUC_CanIf_00772]
	STD_ON: Enabled
	STD_OFF: Disabled
*/
#define CANIF_PublicPnSupport  STD_OFF

/*
	[ECUC_CanIf_00741]
	STD_ON: Enabled
	STD_OFF: Disabled
*/
#define CANIF_PublicWakeupCheckValidByNM	STD_OFF

/*
	[ECUC_CanIf_00675]
	STD_ON: Enabled
	STD_OFF: Disabled
*/
#define CANIF_SupportTTCAN  STD_OFF

/*
	[ECUC_CanIf_00619]
	CANIF_SW_FILTER_BINARY
	CANIF_SW_FILTER_INDEX
	CANIF_SW_FILTER_LINEAR
	CANIF_SW_FILTER_TABLE
*/
#define CANIF_PrivateSoftwareFilterType  CANIF_SW_FILTER_BINARY


#endif /* CANIF_CFG_H_ */
