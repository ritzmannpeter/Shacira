
#include "FirstHeader.h"
#include "qtgui"
#include "RobotGUI.h"

BOOL_T _GUIInit(ULONG_T step, cContext * context)
{
    if (step == SH_PRE_UI_INSTANTIATION) {
    }

    if (step == SH_POST_UI_INSTANTIATION) {
    }

    if (step == SH_PRE_CONTEXT_PROPAGATION) {
    }

    if (step == SH_POST_CONTEXT_PROPAGATION) {
    }

    if (step == SH_PRE_UI_START) {
    }

    if (step == SH_PRE_CCS_SERVICE_STARTUP) {
    }

    if (step == SH_POST_CCS_SERVICE_STARTUP) {
    }

    if (step == SH_PRE_INITIALIZE_UI_DATA) {
    }

    if (step == SH_POST_INITIALIZE_UI_DATA) {
    }

    return true;
}


ULONG_T DarkConstState(cContext * _context, WIDGET_PTR _widget, 
	LONG_T const_state, CONST_STRING_T s)
{
   return const_state;
}

ULONG_T PlausMinMax(cContext * _context, WIDGET_PTR _widget, CONST_STRING_T _input, 
	DOUBLE_T min, DOUBLE_T max)
{
   return 0;
}

