/* 
 * File:   status.hpp
 * Author: c
 *
 * Created on 4 maj 2013, 21:53
 */

#ifndef __SMPP_STATUS_HPP__
#define	__SMPP_STATUS_HPP__

#define SMPP_ESME_ROK			0x00000000 //No Error
#define SMPP_ESME_RINVMSGLEN	0x00000001 //Message Length is invalid
#define SMPP_ESME_RINVCMDLEN	0x00000002 //Command Length is invalid
#define SMPP_ESME_RINVCMDID		0x00000003 //Invalid Command ID
#define SMPP_ESME_RINVBNDSTS	0x00000004 //Incorrect BIND Status for given command
#define SMPP_ESME_RALYBND		0x00000005 //ESME Already in Bound State
#define SMPP_ESME_RINVPRTFLG	0x00000006 //Invalid Priority Flag
#define SMPP_ESME_RINVREGDLVFLG	0x00000007 //Invalid Registered Delivery Flag
#define SMPP_ESME_RSYSERR		0x00000008 //System Error

#define SMPP_ESME_RINVSRCADR	0x0000000A //Invalid Source Address
#define SMPP_ESME_RINVDSTADR	0x0000000B //Invalid Dest Addr
#define SMPP_ESME_RINVMSGID		0x0000000C //Message ID is invalid
#define SMPP_ESME_RBINDFAIL		0x0000000D //Bind Failed
#define SMPP_ESME_RINVPASWD		0x0000000E //Invalid Password
#define SMPP_ESME_RINVSYSID		0x0000000F //Invalid System ID

#define SMPP_ESME_RCANCELFAIL	0x00000011 //Cancel SM Failed

#define SMPP_ESME_RREPLACEFAIL	0x00000013 //Replace SM Failed

#define SMPP_ESME_RMSGQFUL		0x00000014 //Message Queue Full
#define SMPP_ESME_RINVSERTYP	0x00000015 //Invalid Service Type

#define SMPP_ESME_RINVNUMDESTS	0x00000033 //Invalid number of destinations
#define SMPP_ESME_RINVDLNAME	0x00000034 //Invalid Distribution List name

#define SMPP_ESME_RINVDESTFLAG	0x00000040 //Destination flag is invalid (submit_multi)

#define SMPP_ESME_RINVSUBREP	0x00000042 //Invalid submit with replace request (i.e. submit_sm with replace_if_present_flag set)
#define SMPP_ESME_RINVESMCLASS	0x00000043 //Invalid esm_class field data
#define SMPP_ESME_RCNTSUBDL		0x00000044 //Cannot Submit to Distribution List
#define SMPP_ESME_RSUBMITFAIL	0x00000045 //submit_sm or submit_multi failed

#define SMPP_ESME_RINVSRCTON	0x00000048 //Invalid Source address TON
#define SMPP_ESME_RINVSRCNPI	0x00000049 //Invalid Source address NPI
#define SMPP_ESME_RINVDSTTON	0x00000050 //Invalid Destination address TON
#define SMPP_ESME_RINVDSTNPI	0x00000051 //Invalid Destination address NPI

#define SMPP_ESME_RINVSYSTYP	0x00000053 //Invalid system_type field
#define SMPP_ESME_RINVREPFLAG	0x00000054 //Invalid replace_if_present flag
#define SMPP_ESME_RINVNUMMSGS	0x00000055 //Invalid number of messages

#define SMPP_ESME_RTHROTTLED	0x00000058 //Throttling error (ESME has exceeded allowed message limits)

#define SMPP_ESME_RINVSCHED		0x00000061 //Invalid Scheduled Delivery Time
#define SMPP_ESME_RINVEXPIRY	0x00000062 //Invalid message validity period (Expiry time)
#define SMPP_ESME_RINVDFTMSGID	0x00000063 //Predefined Message Invalid or Not Found
#define SMPP_ESME_RX_T_APPN		0x00000064 //ESME Receiver Temporary App Error Code
#define SMPP_ESME_RX_P_APPN		0x00000065 //ESME Receiver Permanent App Error Code
#define SMPP_ESME_RX_R_APPN		0x00000066 //ESME Receiver Reject Message Error Code
#define SMPP_ESME_RQUERYFAIL	0x00000067 //query_sm request failed

#define SMPP_ESME_RINVOPTPARSTREAM	0x000000C0 //Error in the optional part of the PDU Body.
#define SMPP_ESME_ROPTPARNOTALLWD	0x000000C1 //Optional Parameter not allowed
#define SMPP_ESME_RINVPARLEN		0x000000C2 //Invalid Parameter Length.
#define SMPP_ESME_RMISSINGOPTPARAM	0x000000C3 //Expected Optional Parameter missing
#define SMPP_ESME_RINVOPTPARAMVAL	0x000000C4 //Invalid Optional Parameter Value

#define SMPP_ESME_RDELIVERYFAILURE	0x000000FE //Delivery Failure (used for data_sm_resp)
#define SMPP_ESME_RUNKNOWNERR	0x000000FF //Unknown Error


#endif	/* __SMPP_STATUS_HPP__ */

