/********* TEST32.C - source file for test32.exe **********/

#include "windows.h"
#include "test32.h"

/**----------------- WinMain ----------------------------**/
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, 
   LPSTR lpCmdLine, int nShow)
{
   DialogBox(hInst, MAKEINTRESOURCE(DISPLAY_DLG), NULL, 
      DisplayDlgProc);
   return 0;
} /* WinMain */

/**------------------ DisplayDlgProc --------------------**/
BOOL CALLBACK DisplayDlgProc(HWND hDlg, UINT uMsg,
   WPARAM wParam, LPARAM lParam)
{
   char Buffer[64+1], TmpBuffer[64+1], i;

   switch (uMsg)
   {
      case WM_INITDIALOG:
         VDDScannerCommand(CMD_IOCTL_SCSIINQ, Buffer, 64);
         wsprintf(TmpBuffer, "%c", Buffer[0]+'0');
         SetDlgItemText(hDlg, ID_SCSIINQ, TmpBuffer);

         VDDScannerCommand(CMD_WRITE, "\x01B*s10E", 64);
         VDDScannerCommand(CMD_READ, Buffer, (ULONG)64);
         for (i=8; i <=12; i++) TmpBuffer[i-8] = Buffer[i];
         TmpBuffer[i-8] = '\0';
         SetDlgItemText(hDlg, ID_MODELNUM, TmpBuffer);
         return TRUE;

      case WM_COMMAND:
         if (wParam == IDOK) EndDialog(hDlg, TRUE);
         return TRUE;

      default:  return FALSE;
   }
   return TRUE;
} /* DisplayDlgProc */
