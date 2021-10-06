/*
 * J1939Nm_Cbk.h
 *
 *  Created on: 4 Feb 2020
 *      Author: Yahia
 */

#ifndef J1939NM_CBK_H_
#define J1939NM_CBK_H_

extern void J1939Nm_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr);
extern void J1939Nm_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);

extern void J1939Tp_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr);
extern void J1939Tp_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);

#endif /* J1939NM_CBK_H_ */
