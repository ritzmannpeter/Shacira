
#include "CDirectoryView.h"
#include "CAppFrame.h"

FileSystemModel::FileSystemModel(QObject * parent)
   : QFileSystemModel(parent)
{
}

FileSystemModel::~FileSystemModel()
{
}

int FileSystemModel::columnCount(const QModelIndex & parent) const
{
//   return QFileSystemModel::columnCount(parent);
   return 1;
}

QVariant FileSystemModel::data(const QModelIndex & index, int role) const
{
   QVariant data = QFileSystemModel::data(index, role);
   return data;
}

FileSystemProxyModel::FileSystemProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

FileSystemProxyModel::~FileSystemProxyModel()
{
}

bool FileSystemProxyModel::filterAcceptsRow(int source_row, const QModelIndex & source_parent) const
{
   FileSystemModel * source_model = static_cast<FileSystemModel*>(this->sourceModel());
   QModelIndex source_index = source_model->index(source_row, 0, source_parent);
   QString node_name = source_model->data(source_index).toString();
   if (node_name[0] == '.') {
      return false;
   } else {
      return true;
   }
}

bool FileSystemProxyModel::lessThan(const QModelIndex & left, const QModelIndex & right) const
{
   return QSortFilterProxyModel::lessThan(left, right);
}


#ifdef _CWIDGET_PLUGIN_
/*
 *  Hook for designer plugin registration
 */
#include "pluginfactory.h"
SH_PLUGIN_REGISTER(InputWidget, \
                   CDirectoryView, \
                   ICON_SET("listview"), \
                   "widget to display directory structure")
#endif

#ifdef doku
QDir::Dirs	0x001	List directories that match the filters.
QDir::AllDirs	0x400	List all directories; i.e. don't apply the filters to directory names.
QDir::Files	0x002	List files.
QDir::Drives	0x004	List disk drives (ignored under Unix).
QDir::NoSymLinks	0x008	Do not list symbolic links (ignored by operating systems that don't support symbolic links).
QDir::NoDotAndDotDot	0x1000	Do not list the special entries "." and "..".
QDir::NoDot	0x2000	Do not list the special entry ".".
QDir::NoDotDot	0x4000	Do not list the special entry "..".
QDir::AllEntries	Dirs | Files | Drives	List directories, files, drives and symlinks (this does not list broken symlinks unless you specify System).
QDir::Readable	0x010	List files for which the application has read access. The Readable value needs to be combined with Dirs or Files.
QDir::Writable	0x020	List files for which the application has write access. The Writable value needs to be combined with Dirs or Files.
QDir::Executable	0x040	List files for which the application has execute access. The Executable value needs to be combined with Dirs or Files.
QDir::Modified	0x080	Only list files that have been modified (ignored on Unix).
QDir::Hidden	0x100	List hidden files (on Unix, files starting with a ".").
QDir::System	0x200	List system files (on Unix, FIFOs, sockets and device files are included; on Windows, .lnk files are included)
QDir::CaseSensitive	0x800	The filter should be case sensitive.
#endif

CDirectoryView::CDirectoryView(QWidget * parent, const char * name, WIDGET_FLAGS_TYPE f)
   : QTreeView(parent),
     CWidgetBase(this),
     _model(NULL),
     _proxy_model(NULL)
{
   setObjectName(name);
   CONSTRUCT_WIDGET
   _VarRef = NULL;
   _VarView = NULL;

   QDir::Filters filters = QDir::Drives | QDir::Dirs | QDir::NoDotAndDotDot;
//   QDir::Filters filters = QDir::Drives;

#undef USE_PROXY_MODEL
#ifdef USE_PROXY_MODEL
   _model = new FileSystemModel(this);
   _model->setFilter(filters);
   _model->setRootPath("");
   _proxy_model = new FileSystemProxyModel(this);
   _proxy_model->setSourceModel(_model);
   setModel(_proxy_model);
#else
   _model = new FileSystemModel(this);
   _model->setFilter(filters);
   _model->setRootPath("");
   setModel(_model);
#endif
   setAnimated(false);
   setIndentation(20);
//   setSortingEnabled(true);
}

CDirectoryView::~CDirectoryView( ) 
{
}

void CDirectoryView::mousePressEvent(QMouseEvent * e)
{
   if (!HelpActive()) {
      QTreeView::mousePressEvent(e);
   }
}

void CDirectoryView::mouseReleaseEvent(QMouseEvent * e)
{
   if (HelpActive()) {
      SetHelpIds();
   } else {
      QTreeView::mouseReleaseEvent(e);
   }
}


// GUI related virtual methods

void CDirectoryView::View()
{
}

// CCS related virtual methods

void CDirectoryView::CCSSetContext(NODE_PTR node, CONTEXT_PTR context)
{
   CCSInitializeVarRef(_VarSpec, _VarRef, _VarView, 0);
}

void CDirectoryView::CCSNewValue(CONST_STRING_T value, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size)
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
WMETHOD_VOID_EPILOG
#endif
}

void CDirectoryView::CCSNewValue(BUF_T buf, ULONG_T id, ULONG_T time_offset,
                            UCHAR_T data_type, ULONG_T size)
{
}

void CDirectoryView::CCSEvent(TRANSIENT_OBJECT_PTR object)
{
}

void CDirectoryView::DelayedLanguageChange()
{
#ifndef QT_PLUGIN
WMETHOD_PROLOG
WMETHOD_VOID_EPILOG
#endif
}

