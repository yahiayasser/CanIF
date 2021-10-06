/*
 * CanNm_Cbk.h
 *
 *  Created on: 5 Feb 2020
 *      Author: Yahia
 */

#ifndef CANNM_CBK_H_
#define CANNM_CBK_H_

extern void CanNm_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr);
extern void CanNm_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);
extern Std_ReturnType CanNm_TriggerTransmit(PduIdType TxPduId, PduInfoType* PduInfoPtr);

#endif /* CANNM_CBK_H_ */
