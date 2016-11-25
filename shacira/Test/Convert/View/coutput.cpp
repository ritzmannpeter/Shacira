
#include "FirstHeader.h"
#include "View/coutput.h"

class COutputLine : public QListViewItem
{
public:
   COutputLine(QListView * parent, const char * text, QListViewItem * after = NULL)
      : QListViewItem(parent, after)
   {
      _Text = text;
      setText(0, _Text);
   };
   ~COutputLine()
   {
   };
   QString Text()
   {
      return _Text;
   };
private:
   QString _Text;
public:
};

COutput::COutput(QWidget * parent)
 : QListView(parent)
{
   _LastLine = NULL;
   addColumn("Meldungen");
   setSorting(-1);
}

COutput::~COutput()
{
}

void COutput::AddLine(const char * line)
{
   COutputLine * output_line = NULL;
   if (_LastLine == NULL) {
      output_line = new COutputLine(this, line);
   } else {
      output_line = new COutputLine(this, line, _LastLine);
   }
   _LastLine = output_line;
   ensureItemVisible(output_line);
}

void COutput::Clear()
{
   _LastLine = NULL;
   clear();
}

