/*
 * CanTSyn_Cbk.h
 *
 *  Created on: 5 Feb 2020
 *      Author: Yahia
 */

#ifndef CANTSYN_CBK_H_
#define CANTSYN_CBK_H_

extern void CanTSyn_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr);
extern void CanTSyn_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);

#endif /* CANTSYN_CBK_H_ */
