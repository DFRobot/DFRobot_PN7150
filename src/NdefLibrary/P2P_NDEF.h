/*
*         Copyright (c), NXP Semiconductors Caen / France
*
*                     (C)NXP Semiconductors
*       All rights are reserved. Reproduction in whole or in part is
*      prohibited without the written consent of the copyright owner.
*  NXP reserves the right to make changes without notice at any time.
* NXP makes no warranty, expressed, implied or statutory, including but
* not limited to any implied warranty of merchantability or fitness for any
*particular purpose, or that the use will not infringe any third party patent,
* copyright or trademark. NXP must not be liable for any loss or damage
*                          arising from its use.
*/

#ifndef __P2P_NDEF_H__
#define __P2P_NDEF_H__

typedef void P2P_NDEF_PushCallback_t (unsigned char*, unsigned short);
typedef void P2P_NDEF_PullCallback_t (unsigned char*, unsigned short, unsigned int);

void P2P_NDEF_Reset(void);
void P2P_NDEF_Next(unsigned char *pCmd, unsigned short Cmd_size, unsigned char *Rsp, unsigned short *pRsp_size);

  /***** P2P dedicated APIs *********************************************/
// #ifdef P2P_SUPPORT
/*
 * Register NDEF message to be sent to remote NFC Peer to peer Device
 * - pMessage: pointer to the NDEF message
 * - Message_size: NDEF message size
 * - pCb: pointer to function to be called back when tag has been sent
 * return NFC_SUCCESS or NFC_ERROR
 */
  bool P2P_NDEF_SetMessage(unsigned char* pMessage, unsigned int Message_size, P2P_NDEF_PushCallback_t* pCb);

  /*
   * Register function called when NDEF message is received from remote NFC Peer to peer Device
   * - pCb: pointer to function to be called back when NDEF message has been received
   */
  void P2P_NDEF_RegisterPullCallback(P2P_NDEF_PullCallback_t* pCb);

// #endif
  
#endif
