
#ifndef _$(appname)FrameImpl_h_
#define _$(appname)FrameImpl_h_

#include "$(appname)Frame.h"

/*!
 * implementation of the SHACIRA application frame
 * it inherits from a form of type CAppFrame that
 * is contained in the file $(appname).ui
 * $(appname).h and $(appname).cpp are generated
 * by Qt's uic and moc tools both files must be added
 * to the build environment.
 *
 */

class $(appname)FrameImpl : public $(appname)Frame
{
   Q_OBJECT
public:
   /*!
    * constructor
    */
   $(appname)FrameImpl(QWidget * parent = 0, const char * name = 0, WFlags f = 0);
   /*!
    * destructor
    */
   virtual ~$(appname)FrameImpl();
   /*!
    * Creates the list of pages that must be managed by the application frame
    */
   virtual PageList * CreatePageList(QWidget * parent);
   /*!
    * Returns a pointer to the container widget that shows a selected information page
    * normally a CFrame or QFrame typed widget
    */
   virtual CFrame * GetPageContainer();
   /*!
    * Returns a pointer to a widget of type CFixText that should hold
    * the title of a selected information page.
    */
   virtual CFixText * GetPageHeader();
   /*!
    * Returns a pointer to a widget of type CFixText that should hold
    * the status information of the application.
    */
   virtual CFixText * GetStatusBar();
   /*!
    * Not cleared yet !!
    */
   virtual void Object(TRANSIENT_OBJECT_PTR object);
   /*!
    * Method to display informations or errors synchronously within the
    * GUI. The standard behaviour is to display a QMessageBox
    * 
    */
   virtual void Message(BOOL_T async,
                        CONST_STRING_T message,
                        CONST_STRING_T details = NULL,
                        CONST_STRING_T param1 = NULL,
                        CONST_STRING_T param2 = NULL,
                        CONST_STRING_T param3 = NULL,
                        CONST_STRING_T param4 = NULL);
   /*!
    * Method to display errors synchronously within the
    * GUI. The standard behaviour is to display a QMessageBox.
    * This method will be especially used for cError events.
    * 
    */
   virtual void Message(BOOL_T async,
                        ERROR_REF_T error);
   /*!
    * Creates the form that should be displayed during application startup.
    */
   CStartupForm * CreateStartupForm();
protected slots:
   /*!
    * ths slot will be called before a language change operation and
    * and can be used to execute application specific actions in this sitaution.
    */
   virtual void languageChange();
};

#endif



