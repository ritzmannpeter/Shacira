
#include "FirstHeader.h"
#include "CustomText.h"
#include <qobject.h>

#include "System/Text/cTextTable.h"
static cTextTable * _TextTable = NULL;

extern "C" {

CONST_STRING_T _GetCustomText(ULONG_T text_id)
{
   if (_TextTable == NULL) {
      _TextTable = new cTextTable((TEXT_ENTRY_T*)_CustomText);
   }
   return _TextTable->GetText(text_id);
}

}

/*!
 * this text table contains all application specific texts that should
 * be involved into the Qt specific localization mechanisms
 */
const TEXT_ENTRY_T _CustomText[] = {
   /*!
    * add application specific texts here
    */
   {FIRST_TEXT, QT_TRANSLATE_NOOP("custom", "this is the first text")},
   {SECOND_TEXT, QT_TRANSLATE_NOOP("custom", "this is the second text")},
   {0, NULL}                                                                   
};

