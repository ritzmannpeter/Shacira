
#include "memviewimpl.h"
#include "qlineedit.h"
#include "qtextedit.h"

MemViewImpl::MemViewImpl( QWidget* parent, const char* name, WFlags fl )
    : MemView( parent, name, fl )
{
   connect((QObject*)changeBtn, SIGNAL(clicked()), SLOT(ChangeValue()));
   _RefreshTimer = new QTimer(this);
   connect(_RefreshTimer, SIGNAL(timeout()), SLOT(ShowMem()));
   _RefreshTimer->start(100);
}

MemViewImpl::~MemViewImpl()
{
}

#define ADDRESS_RANGE   0x200
#define ROW_SIZE        0x10

void MemViewImpl::ShowMem()
{
   QString data_text;
   QString address_text;
   if (_Memory.GetMemory() == NULL) {
      Data->setText("");
      Address->setText("");
      return;
   }
   char address_width = _Memory.GetAddressWidth();
   int values = ADDRESS_RANGE / address_width;
   for (int i=0; i<values; i++) {
      ULONG_T value = _Memory.GetValue(i);
      int ypos = (i / (ROW_SIZE/address_width));
      int xpos = (i % (ROW_SIZE/address_width));
      char sval[64] = {0};
      switch (address_width) {
      case 1:
         sprintf(sval, "%02.02x", value);
         break;
      case 2:
         sprintf(sval, "%04.04x", value);
         break;
      case 4:
         sprintf(sval, "%08.08x", value);
         break;
      default:
         sprintf(sval, "%d", value);
         break;
      }
      if (xpos == 0) {
         if (ypos > 0) {
            data_text += "\n";
            address_text += "\n";
         }
         char aval[64] = {0};
         int start_addr = i + _Memory.GetAddress();
         sprintf(aval, "%04.04x", start_addr);
         address_text += aval;
      } else {
         data_text += " ";
      }
      data_text += sval;
   }
   Data->setText(data_text);
   Address->setText(address_text);
}

void MemViewImpl::dataChange()
{
   QString sval = ViewMemory->text();
   _Memory.SetMemoryName(sval);
   ULONG_T lval = atol(ViewAddress->text());
   _Memory.SetAddress(lval);
   lval = atol(ViewAddressWidth->text());
   _Memory.SetAddressWidth((UCHAR_T)lval);
}

void MemViewImpl::ChangeValue()
{
   ULONG_T address = atol(InputAddress->text());
   ULONG_T value = atol(InputValue->text());
   _Memory.SetValue(address, value);
}
