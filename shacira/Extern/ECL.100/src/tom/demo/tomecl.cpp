#include "tom/et_tomate.hpp"
#include "tom/et_tools.hpp"

#include "base/eb_file.hpp"
#include "base/eb_prof.hpp"


char *tf_file(char *line, Tom_TYPE *tt)
{
   char file[100];
   char dir[100];
   int attr;

   while (isspace(*line)) { line++; }

   switch (tt->value) {
   case 1:
      if ( Tom_GetArg(&line, file, sizeof(file)) &&
         Tom_GetInt(&line, &attr) ) {
         int mask[3]={
            cFileFind::MASK_ALL,
            cFileFind::MASK_FILE,
            cFileFind::MASK_DIR
         };
         cFileFind ff(file,mask[attr]);
         while (ff.findNext()) {
            if (ff.isDir()) {
               cout << ff.getFileSpec() << " <DIR>" << endl;
             } else {
               cout << ff.getFileSpec() << " " << ff.getSize() << endl;
            }
         }
      }
      break;
   case 2:
      if ( Tom_GetArg(&line, file, sizeof(file)) &&
           Tom_GetArg(&line, dir,  sizeof(dir)) ) {

         cFileFind ff(file,dir);
         int count = 0;
         while (ff.findNext()) {
            count++;
            if (ff.isDir()) {
               cout << ff.getFileSpec() << " <DIR>" << endl;
             } else {
               cout << ff.getFileSpec() << " " << ff.getSize() << endl;
            }
         }
         Tom_printf("%d Files found\n",count);
      }
      break;

   case 3: // cString::Replace
      {
         char text[100], from[20], to[20];
         if (Tom_GetStr(&line, text, sizeof(text)) &&
             Tom_GetStr(&line, from, sizeof(from)) &&
             Tom_GetStr(&line, to,   sizeof(to)) ) {
            cString str(text);
            Tom_printf("--> %s\n",(const char *)str.Replace(from, to));
         }
      }
      break;

   }


   return line;
}

//
// EB_PROF
//
char *tf_prof(char *line, Tom_TYPE *tt)
{
   static cProfile *prof = NULL;
   static cString main_app = "default_app";
   char buf[100],key[100],app[100],*ptr;

   while (isspace(*line)) { line++; }

   switch (tt->value) {

   case cTomate::TOM_IDINIT: /*1*/
      if (*line == '\0') {
         ptr = NULL;
         //Tom_printf("Filename missing\n");
         //return NULL;
      } else if (Tom_GetArg(&line,buf,sizeof(buf))) {
         ptr = buf;
      } else {
         return NULL;
      }
      if (prof != NULL) { delete prof; }
      prof = new cProfile(ptr);
      break;

   case cTomate::TOM_IDEXIT: /*2*/
      if (prof != NULL) { delete prof; prof = NULL; }
      break;

   case 10: // List ...
      if (*line) { // ... keys
         cProfile::ITERATOR key_it;
         cString key,val;
         Tom_GetStr(&line,buf,sizeof(buf));
         if (!prof->getKeyList(key_it,buf)) {
            Tom_printf("keylist [%s] not available\n",buf);
            return NULL;
         }
         Tom_printf("[%s]\n",buf);
         while ((key=prof->getNext(key_it)).Length()) {
            val = prof->read(buf,key);
            Tom_printf("  %s = %s\n",(const char *)key,(const char *)val);
         }
      } else { // ... apps
         cProfile::ITERATOR app_it,key_it;
         cString app,key,val;
         if (!prof->getAppList(app_it)) {
            Tom_printf("applist [%s] not available\n",buf);
            return NULL;
         }
         while ((app=prof->getNext(app_it)).Length()) {
            if (!prof->getKeyList(key_it,app)) {
               Tom_printf("keylist [%s] not available\n",app);
            } else {
               Tom_printf("[%s]\n",(const char *)app);
               while ((key=prof->getNext(key_it)).Length()) {
                  val = prof->read(app,key);
                  Tom_printf("  %s = %s\n",(const char *)key,(const char *)val);
               }
            }
         }

      }
      break;

   case 11: // select
      if (*line) {
         Tom_GetStr(&line,buf,sizeof(buf));
         main_app = buf;
      }
      Tom_printf("[%s] selected\n",(const char *)main_app);
      break;

   case 12: // set
      if ( Tom_GetStr(&line,key,sizeof(key)) &&
           Tom_GetStr(&line,buf,sizeof(buf)) ) {
         if (prof->write(main_app, key, buf)) {
            Tom_printf("[%s] %s = %s ... ok\n",
                       (const char *)main_app,key,buf);
         } else {
            Tom_printf("not really\n");
         }
      }
      break;

   case 15: // del
      if ( Tom_GetStr(&line,key,sizeof(key))) {
         if (prof->write(main_app,key)) {
            Tom_printf("[%s] %s ... removed\n",
                       (const char *)main_app,key);
         } else {
            Tom_printf("not really\n");
         }
      }
      break;

   case 16: // delapp
      if ( Tom_GetStr(&line,key,sizeof(key))) {
         if (prof->write(key)) {
            Tom_printf("[%s] ... removed\n",key);
         } else {
            Tom_printf("not really\n");
         }
      }
      break;

   case 13: // get
      if (Tom_GetStr(&line,key,sizeof(key))) {
         cString val = prof->read(main_app,key);
         Tom_printf( val.Length() ? "[%s] %s = %s\n" : "[%s] %s not defined\n",
                     (const char *)main_app,(const char *)key,(const char *)val);
      }
      break;

   case 14: // file
      break;

   case 17:
      if (Tom_GetStr(&line,app,sizeof(app))) {
         if (Tom_GetStr(&line,key,sizeof(key))) {
            Tom_printf("exist(%s,%s) = %d\n", app, key, prof->exist(app,key));
         } else {
            Tom_printf("exist(%s) = %d\n", app, prof->exist(app));
         }
      } else {
         Tom_printf("exist() = %d\n", prof->exist());
      }
   
      break;
   
   }

   return line;
}

static Tom_TYPE tt_prof[] = {
   Tom_UW(tf_prof,10, 1,"List - list all ")
   Tom_COMMENT("List <appname> - list application")

   Tom_COMMENT("App - show name of selected application")
   Tom_UW(tf_prof,11, 1,"App <appname> - select application")
   Tom_UW(tf_prof,12, 1,"Set <keyname> <value> - set key of selected application")
   Tom_UW(tf_prof,15, 1,"Del <keyname> - remove key of selected application")
   Tom_UW(tf_prof,16, 4,"DELApp <appname> remove application")
   Tom_UW(tf_prof,13, 2,"Get <keyname> - get key of selected application")
   //Tom_UW(tf_prof,14, 3,"File <ininame> - select new profile")
   Tom_UW(tf_prof,17, 1,"Exist [<appname> [<keyname]] - test availibility")

   Tom_GATES(tf_prof,tf_prof,"Profiles")
};

/*
 * Haupt-Tabelle:
 */
Tom_TYPE _haupt[] = {
   Tom_COMMENT( "----- Schwerpunkte:" )
   Tom_UW(tf_file, 1,3,"DIR <filemask> <code>" )
   Tom_UW(tf_file, 2,3,"SUB <filemask> <dirmask>")
   Tom_UW(tf_file, 3,3,"REPlace <text> <from> <to> - cString::Replace")

   Tom_COMMENT( "-----" )
   Tom_LEVEL(tt_prof, 1,"Profile <inifile>")

   Tom_PROMPT( "TomECL" )
};


/*
 * Immer-und-ueberall-Funktionen:
 */
static Tom_TYPE _escape[] = {
   Tom_PARAM( _haupt ,       1,"# ... - Befehle der Hauptstufe" )
   Tom_PARAM( ToTo_Root() ,    1,"$ ... - Tom-Tools" )
   Tom_ENDE()
};

/*
 * So sieht der Aufruf der Tomate aus:
 */
int main( int argc, char *argv[] )
{
   cTomate tom;
   //Tom_Init( ToCo_Init() );
   //ToTo_Init();

   tom.Start( (Tom_TYPE*)_haupt , (Tom_TYPE*)_escape );

   //ToTo_Exit();
   //Tom_Exit();

   return 0;
}


