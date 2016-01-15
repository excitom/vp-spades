#ifndef _VPOLE_H_
#define _VPOLE_H_

#include <afxole.h>         // MFC OLE classes
#include <afxdisp.h>        // MFC OLE automation classes
#ifndef WIN32
  // Ole stuff
  #include <ole2.h>
  #include <olectl.h>

  #include "compobj.h"
  #include "olectlid.h"
  #include "OLENLS.H"       // dispatch intarface definition
#else
  #include "winreg.h"         // Registry definition
  #include <afxodlgs.h>       // MFC OLE dialog classes
#endif
#include "Str816.h"         // Helper classes for work with OLESTR

// GUID of interface that can be queried from VP sink.
// Object shoud use this interface for communication with VP.
// const IID BASED_CODE IID_IVpComm =
// { 0xB196B283, 0xBAB4, 0x101A, { 0xB6, 0x9C, 0x00, 0xAA, 0x00, 0x34, 0x1D, 0x05 } };

EXTERN_C const GUID CDECL BASED_CODE IID_IVpComm;

// Vp interface
// Through this interface game object can send
// commands & requests to VP.

interface IVpComm : public IUnknown
{
// Commands & Requests from objects to VP
public:
  virtual STDMETHODIMP_(short) LeaveGroup() = 0;
  virtual STDMETHODIMP_(short) Send(long Id, short SendType, LPCTSTR Message, BSTR* Data) = 0;
  virtual STDMETHODIMP_(short) SendToService(long ServiceId, long SrvSendType,
                                             LPCTSTR Message, BSTR* Data, long ReqId) = 0;
  virtual STDMETHODIMP_(short) EnumMembers(long Id, short MaxLevel) = 0;
  virtual STDMETHODIMP_(short) QueryService(long* Id, short* VpType) = 0;
  virtual STDMETHODIMP_(short) GetPresenceInfo(long Id, BSTR* Nickname, BSTR* Fullname,
                                               BSTR* Location, BSTR* Email) = 0;
  virtual STDMETHODIMP_(LPCTSTR) GetPlaceName() = 0;

// VP service methods
public:
  virtual STDMETHODIMP_(void) GetParentWnd(long* ParentWnd) = 0;
  virtual STDMETHODIMP_(void) SetGameWnd(long GameWnd) = 0;
  virtual STDMETHODIMP_(void) DupAvatar(long ParentWnd, short Seat) = 0;
  virtual STDMETHODIMP_(void) SetAvatarPos(short Seat, short Left, short Top,
                                           short Width, short Height) = 0;
};

// Subkey into HKEY_CLASSES_ROOT registry entry for
// registration object as VpGame
#ifdef WIN32
  #define SUBKEY_VPGAME_REG     "Software\\Ubique\\VpGames32"
#else
  #define SUBKEY_VPGAME_REG     "Software\\Ubique\\VpGames16"
#endif

#endif //_VPOLE_H_


