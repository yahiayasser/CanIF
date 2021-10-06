/*
 * CanTp_Cbk.h
 *
 *  Created on: 3 Feb 2020
 *      Author: Yahia
 */

#ifndef CANTP_CBK_H_
#define CANTP_CBK_H_


extern void CanTp_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr);
extern void CanTp_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);

#endif /* CANTP_CBK_H_ */
