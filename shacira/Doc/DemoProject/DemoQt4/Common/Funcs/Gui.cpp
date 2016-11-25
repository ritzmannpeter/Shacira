
#include "FirstHeader.h"
#include "System/Database/cContext.h"
#include "System/Database/cVariable.h"
#include "System/Database/cUnitDef.h"
#include "cappframe.h"
#include "cpage.h"
#include "GUI.h"
#include "cpushbutton.h"

/// this is a demo implementation of Shacira  GUI functions

cUserInfo user_info;

CAppFrame * _SharedAppFrame = NULL;
#define APP_FRAME (_SharedAppFrame)


BOOL_T _GUIInit(ULONG_T step, cContext * context)
{
    if (step == SH_POST_CCS_SERVICE_STARTUP) {
    }
    
    return true;
}

void _ShareAppframe(CAppFrame * app_frame)
{
   _SharedAppFrame = app_frame;
   CWidgetBase::SetAppFrame(app_frame);
}

// dark functions

static bool on = true;

ULONG_T DarkConstState(cContext * _context, WIDGET_PTR _widget, LONG_T const_state)
{
   cVariable * variable = _context->Variable("matrix1");
   cVarRef * var_ref = _context->VarRef("matrix1[0][0]");
   if (variable != NULL) {
      float matrix_value = 0;
      variable->Get(matrix_value, 0, 0);
      var_ref->GetValue(matrix_value);
      if (matrix_value > 0) {
         return elementInvisible;
      } else {
         return elementFree;
      }
   }
   if (const_state == elementInvisible) {
      if (on) {
         on = false;
         return elementDisabled;
      } else {
         on = true;
         return elementInvisible;
      }
   } else {
      return const_state;
   }
}

// plausibility functions

ULONG_T IndexPlausFunction(cContext * _context, WIDGET_PTR _widget, CONST_STRING_T _input, 
	LONG_T dimension)
{
   cVariable * variable = _context->Variable("matrix1");
   if (variable != NULL) {
      LONG_T value = atol(_input);
      LONG_T dim_size = 0;
      if (dimension == 0) {
         dim_size = variable->DimSize(0);
      } else if (dimension == 1) {
         dim_size = variable->DimSize(1);
      } else {
         throw cError("invalid dimension", 0);
      }
      if (value < 0 || value >= dim_size - 1) {
         throw cError("invalid input", 0);
      }
   } else {
      throw cError("got no variable", 0);
   }
   CAppFrame * app_frame = APP_FRAME;
   if (app_frame != NULL) {
      app_frame->Refresh(DATA_REFRESH, true);
   }
   return actionProceed;
}

// button functions

ULONG_T Decrement(cContext * _context, WIDGET_PTR _widget, 
	LONG_T dimension)
{
   
   CAppFrame * app_frame = APP_FRAME;
   cVariable * variable = _context->Variable("matrix1");
   if (variable != NULL) {
      LONG_T value = 0;
      cVariable * index = NULL;
      if (dimension == 0) {
         index = _context->Variable("index1");
         if (index != NULL) {
            index->Get(value);
         } else {
            throw cError("no index variable", 0);
         }
      } else if (dimension == 1) {
         index = _context->Variable("index2");
         if (index != NULL) {
            index->Get(value);
         } else {
            throw cError("no index variable", 0);
         }
      } else {
         throw cError("invalid dimension", 0);
      }
      if (value > 0) {
         value--;
         index->Set(value);
      }
   } else {
      throw cError("got no variable", 0);
   }
   if (app_frame != NULL) {
      app_frame->Refresh(DATA_REFRESH, true);
   }
   return 0;
}

ULONG_T Increment(cContext * _context, WIDGET_PTR _widget, 
	LONG_T dimension)
{
   cVariable * variable = _context->Variable("matrix1");
   if (variable != NULL) {
      LONG_T value = 0;
      cVariable * index = NULL;
      LONG_T dim_size = 0;
      if (dimension == 0) {
         dim_size = variable->DimSize(0);
         index = _context->Variable("index1");
         if (index != NULL) {
            index->Get(value);
         } else {
            throw cError("no index variable", 0);
         }
      } else if (dimension == 1) {
         dim_size = variable->DimSize(1);
         index = _context->Variable("index2");
         if (index != NULL) {
            index->Get(value);
         } else {
            throw cError("no index variable", 0);
         }
      } else {
         throw cError("invalid dimension", 0);
      }
      if (value < dim_size - 1) {
         value++;
         index->Set(value);
      }
   } else {
      throw cError("got no variable", 0);
   }
   CAppFrame * app_frame = APP_FRAME;
   if (app_frame != NULL) {
      app_frame->Refresh(DATA_REFRESH, true);
   }
   return 0;
}


ULONG_T SetMatrix(cContext * _context, WIDGET_PTR _widget, 
	CONST_STRING_T var_name)
{
   cVariable * variable = _context->Variable(var_name);
   if (variable != NULL) {
      FLOAT_T value = 0;
      LONG_T dim0_size = variable->DimSize(0);
      LONG_T dim1_size = variable->DimSize(1);
      for (int i=0; i<dim0_size; i++) {
         for (int j=0; j<dim1_size; j++) {
            value = ((FLOAT_T)i) + ((FLOAT_T)j/10);
            variable->Set(value, i, j);
         }
      }
   } else {
      throw cError("got no variable", 0);
   }
   return 0;
}

ULONG_T ResetMatrix(cContext * _context, WIDGET_PTR _widget, 
	CONST_STRING_T var_name)
{
   cVariable * variable = _context->Variable(var_name);
   if (variable != NULL) {
      FLOAT_T value = 0;
      LONG_T dim0_size = variable->DimSize(0);
      LONG_T dim1_size = variable->DimSize(1);
      for (int i=0; i<dim0_size; i++) {
         for (int j=0; j<dim1_size; j++) {
            variable->Set((FLOAT_T)0, i, j);
         }
      }
   } else {
      throw cError("got no variable", 0);
   }
   return 0;
}

ULONG_T ExecuteCommand(cContext * _context, WIDGET_PTR _widget, 
	CONST_STRING_T pgm, LONG_T cmd)
{
   _context->ExecuteCommand(pgm, cmd);
   return 0;
}

ULONG_T ExecuteCommand2(cContext * _context, WIDGET_PTR _widget, 
	CONST_STRING_T pgm, LONG_T cmd)
{
   return 0;
}

ULONG_T CopyIndex(cContext * _context, WIDGET_PTR _widget, CONST_STRING_T _input)
{
   long index1 = atol(_input);
   cVariable * index1_variable = _context->Variable("index1");
   if (index1_variable != NULL) {
      cVariable * index2_variable = _context->Variable("index2");
      if (index2_variable != NULL) {
//         index1_variable->Get(index1);
         index2_variable->Set(index1);
      }
   }
   return actionProceed;

}


ULONG_T SetFrench(cContext * _context, WIDGET_PTR _widget)
{
   CAppFrame * app_frame = APP_FRAME;
   if (app_frame != NULL) {
      app_frame->SetNewLanguage("fr");
   }
   return actionProceed;
}

#include "Test/sys_filehandlingwizard_sub.h"
#include "Test/clp_stackturnfeedzeroadjustwizard_sub.h"

ULONG_T SetLanguage(cContext * _context, WIDGET_PTR _widget, 
	CONST_STRING_T language)
{
   CAppFrame * app_frame = APP_FRAME;
   if (app_frame != NULL) {
      app_frame->SetNewLanguage(language);
      cVariable * variable = _context->Variable("act_language");
      if (variable != NULL) {
         variable->Set(CONST_STRING(app_frame->ActLanguage()));
      }
   }
   return actionProceed;
}

ULONG_T SetLang(cContext * _context, WIDGET_PTR _widget, CONST_STRING_T _input)
{
   CAppFrame * app_frame = APP_FRAME;
   if (app_frame != NULL) {
      int ival = atoi(_input);
      if (ival == 1) {
         app_frame->SetNewLanguage("fr");
      } else if (ival == 2) {
         app_frame->SetNewLanguage("en-US");
      } else if (ival == 3) {
         app_frame->SetNewLanguage("default");
      }
   }
   return actionProceed;
}

ULONG_T PlausLang(cContext * _context, WIDGET_PTR _widget, CONST_STRING_T _input)
{
   int ival = atoi(_input);
   if (ival == 2) {
   } else {
      throw cError(0, 0, "invalid input only 2 valid");
   }
   return actionProceed;
}

ULONG_T SwitchUnit(cContext * _context, WIDGET_PTR _widget)
{
   CAppFrame * app_frame = APP_FRAME;
   if (app_frame != NULL) {
      cUnitDef * unit_def = _context->UnitDef("MMInch");
      if (unit_def != NULL) {
         int state = unit_def->GetState();
         if (state == 0) {
            unit_def->SetState(1);
         } else {
            unit_def->SetState(0);
         }
         app_frame->Refresh(DATA_REFRESH, true);
      }
   }
   return 0;
}


