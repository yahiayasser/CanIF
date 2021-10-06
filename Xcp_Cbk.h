/*
 * Xcp_Cbk.h
 *
 *  Created on: 4 Feb 2020
 *      Author: Yahia
 */

#ifndef XCP_CBK_H_
#define XCP_CBK_H_

extern void Xcp_CanIfRxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr);
extern void Xcp_CanIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result);
extern Std_ReturnType Xcp_CanIfTriggerTransmit(PduIdType TxPduId, PduInfoType* PduInfoPtr);

#endif /* XCP_CBK_H_ */
