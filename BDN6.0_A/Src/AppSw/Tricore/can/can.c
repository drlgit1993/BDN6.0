#include"can.h"

#define    USER_CAN_ID                      (0x10)

IfxMultican_Can can;

IfxMultican_Can_Node canSrcNode;
IfxMultican_Can_Node canDstNode;

IfxMultican_Can_MsgObj canSrcMsgObj;
IfxMultican_Can_MsgObj canDstMsgObj;


void bsp_Can_Init(void)
{
	IfxMultican_Can_Config canConfig;
	IfxMultican_Can_initModuleConfig(&canConfig, &MODULE_CAN);

	// initialize module
	IfxMultican_Can_initModule(&can, &canConfig);


	// create CAN node config
	IfxMultican_Can_NodeConfig canNodeConfig;
	IfxMultican_Can_Node_initConfig(&canNodeConfig, &can);
	canNodeConfig.baudrate = 1000000; // 1 MBaud

	// Source Node
	canNodeConfig.nodeId = IfxMultican_NodeId_0;
	canNodeConfig.rxPin = &IfxMultican_RXD0B_P20_7_IN;
	canNodeConfig.rxPinMode = IfxPort_InputMode_pullUp;
	canNodeConfig.txPin = &IfxMultican_TXD0_P20_8_OUT;
	canNodeConfig.txPinMode = IfxPort_OutputMode_pushPull;
	// initialise the node
	IfxMultican_Can_Node_init(&canSrcNode, &canNodeConfig);

	// Destination Node
	canNodeConfig.nodeId = IfxMultican_NodeId_1;
	canNodeConfig.rxPin = &IfxMultican_RXD1B_P14_1_IN;
	canNodeConfig.rxPinMode = IfxPort_InputMode_pullUp;
	canNodeConfig.txPin = &IfxMultican_TXD1_P14_0_OUT;
	canNodeConfig.txPinMode = IfxPort_OutputMode_pushPull;
	// initialise the node
	IfxMultican_Can_Node_init(&canDstNode, &canNodeConfig);

   // create message object config
   IfxMultican_Can_MsgObjConfig canMsgObjConfig;
   IfxMultican_Can_MsgObj_initConfig(&canMsgObjConfig, &canSrcNode);
   // assigned message object:
   canMsgObjConfig.msgObjId = 0;
   canMsgObjConfig.messageId = USER_CAN_ID;
   canMsgObjConfig.acceptanceMask = 0x7FFFFFFFUL;
   canMsgObjConfig.frame = IfxMultican_Frame_transmit;
   canMsgObjConfig.control.messageLen = IfxMultican_DataLengthCode_8;
   canMsgObjConfig.control.extendedFrame = FALSE;
   canMsgObjConfig.control.matchingId = TRUE;
   // initialize message object
   IfxMultican_Can_MsgObj_init(&canSrcMsgObj, &canMsgObjConfig);

   IfxMultican_Can_MsgObj_initConfig(&canMsgObjConfig, &canDstNode);
  // assigned message object:
   canMsgObjConfig.msgObjId = 1;
   canMsgObjConfig.messageId = USER_CAN_ID;
   canMsgObjConfig.acceptanceMask = 0x7FFFFFFFUL;
   canMsgObjConfig.frame = IfxMultican_Frame_receive;
   canMsgObjConfig.control.messageLen = IfxMultican_DataLengthCode_8;
   canMsgObjConfig.control.extendedFrame = FALSE;
   canMsgObjConfig.control.matchingId = TRUE;
   // initialize message object
   IfxMultican_Can_MsgObj_init(&canDstMsgObj, &canMsgObjConfig);

}
void CAN_ReceiveSingle(uint32 id, uint32 *p_high, uint32 *p_low)
{

	uint32 wait_count = 1000;
	// Receiving Data
	// Initialise the message structure with dummy values, will be replaced by the received values
	IfxMultican_Message rxMsg;
	// start with invalid values
	IfxMultican_Message_init(&rxMsg, 0xdead, 0xdeadbeef, 0xdeadbeef, IfxMultican_DataLengthCode_8);
	// wait until Multican received a new message
	while( !IfxMultican_Can_MsgObj_isRxPending(&canDstMsgObj) && wait_count-->0);
	if(wait_count == 0)
		return;
	// read message
	IfxMultican_Status readStatus = IfxMultican_Can_MsgObj_readMessage(&canDstMsgObj, &rxMsg);

	// if new data is been received report an error
	if((readStatus & IfxMultican_Status_newData) && (rxMsg.id == id))
	{
		*p_high = rxMsg.data[0];
		*p_low = rxMsg.data[1];
	}
}
void CAN_SendSingle(uint32 id, uint32 high, uint32 low)
{
	// Initialise the message strcture
	IfxMultican_Message txMsg;
	IfxMultican_Message_init(&txMsg, id, low, high, IfxMultican_DataLengthCode_8);

	// Transmit Data
	while( IfxMultican_Can_MsgObj_sendMessage(&canSrcMsgObj, &txMsg) == IfxMultican_Status_notSentBusy );
}

