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

#ifndef __RW_NDEF_EMU_H__
#define __RW_NDEF_EMU_H__

typedef void T4T_NDEF_EMU_Callback_t(unsigned char*, unsigned short);

void T4T_NDEF_EMU_Reset(void);
void T4T_NDEF_EMU_Next(unsigned char *pCmd, unsigned short Cmd_size, unsigned char *Rsp, unsigned short *pRsp_size);

// #ifdef CARDEMU_SUPPORT
// #ifndef NO_NDEF_SUPPORT
/*
 * Register NDEF message to be exposed to remote NFC reader Device
 * - pMessage: pointer to the NDEF message
 * - Message_size: NDEF message size
 * - pCb: pointer to function to be called back when tag has been written
 * return NFC_SUCCESS or NFC_ERROR
 */
  bool T4T_NDEF_EMU_SetMessage(unsigned char* pMessage, unsigned short Message_size, T4T_NDEF_EMU_Callback_t* pCb);
// #endif
// #endif

#endif
