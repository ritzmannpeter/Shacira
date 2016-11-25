
#ifndef _cguisignal_h_
#define _cguisignal_h_

class cGuiSignal
{
public:
   cGuiSignal(ULONG_T signal_code)
   {
      _SignalCode = signal_code;
   };
   virtual ~cGuiSignal();
   void SetSignalCode(ULONG_T signal_code)
   {
      _SignalCode = signal_code;
   }
   ULONG_T GetSignalCode()
   {
      return _SignalCode;
   }
protected:
   ULONG_T _SignalCode;
};

#endif
