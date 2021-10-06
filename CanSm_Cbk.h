/*
 * CanSm_Cbk.h
 *
 *  Created on: 3 Feb 2020
 *      Author: Yahia
 */

#ifndef CANSM_CBK_H_
#define CANSM_CBK_H_

extern void CanSM_CheckTransceiverWakeFlagIndication(uint8 Transceiver);
extern void CanSM_ClearTrcvWufFlagIndication(uint8 Transceiver);
extern void CanSM_ConfirmPnAvailability(uint8 TransceiverId);
extern void CanSM_ControllerBusOff(uint8 ControllerId);
extern Std_ReturnType CanSM_TriggerTransmit(PduIdType TxPduId, PduInfoType* PduInfoPtr);
//void CanSM_ControllerModeIndication (uint8 ControllerId, Can_ControllerStateType ControllerMode);
//void CanSM_TransceiverModeIndication(uint8 TransceiverId, CanTrcv_TrcvModeType TransceiverMode);


#endif /* CANSM_CBK_H_ */
