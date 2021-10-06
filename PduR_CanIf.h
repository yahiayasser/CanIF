/*
 * PduR_CanIf.h
 *
 *  Created on: 3 Feb 2020
 *      Author: Yahia
 */

#ifndef PDUR_CANIF_H_
#define PDUR_CANIF_H_

extern void PduR_CanIfRxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr);
extern void PduR_CanIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result);
extern Std_ReturnType PduR_CanIfTriggerTransmit(PduIdType TxPduId, PduInfoType* PduInfoPtr);

#endif /* PDUR_CANIF_H_ */
