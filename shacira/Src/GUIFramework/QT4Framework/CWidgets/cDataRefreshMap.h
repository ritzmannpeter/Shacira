
#ifndef _cdatarefreshmap_h_
#define _cdatarefreshmap_h_

typedef std::map<VAR_REF_PTR, VAR_REF_PTR> DATA_REFRESH_MAP_T;

class cDataRefreshMap
{
public:
   cDataRefreshMap() {};
   virtual ~cDataRefreshMap() {};
   inline void Clear()
   {
#ifndef QT_PLUGIN
      _RefreshMap.clear();
#endif
   };
   void SetRefreshed(VAR_REF_PTR var_ref)
   {
#ifndef QT_PLUGIN
      _RefreshMap[var_ref] = var_ref;
#endif
   };
   inline void Erase(VAR_REF_PTR var_ref)
   {
#ifndef QT_PLUGIN
      _RefreshMap.erase(var_ref);
#endif
   };
   inline BOOL_T IsRefreshed(VAR_REF_PTR var_ref)
   {
#ifndef QT_PLUGIN
      DATA_REFRESH_MAP_T::const_iterator i = _RefreshMap.find(var_ref);
      if (i != _RefreshMap.cend()) {
         return true;
      }
#endif
      return false;
   };
   inline void RefreshData(ULONG_T data_set, DATA_REFRESH_MAP_PTR pending_refresh_map)
   {
#ifndef QT_PLUGIN
      DATA_REFRESH_MAP_T::const_iterator i = _RefreshMap.begin();
      while (i != _RefreshMap.cend()) {
         VAR_REF_PTR var_ref = (*i).second;
         if (var_ref != NULL && !pending_refresh_map->IsRefreshed(var_ref)) {
            var_ref->NewValue(data_set);
            pending_refresh_map->SetRefreshed(var_ref);
         }
         i++;
      }
#endif
   };
   inline void RefreshBGData(ULONG_T data_set, DATA_REFRESH_MAP_PTR pending_refresh_map)
   {
#ifndef QT_PLUGIN
      DATA_REFRESH_MAP_T::const_iterator i = _RefreshMap.begin();
      while (i != _RefreshMap.cend()) {
         VAR_REF_PTR var_ref = (*i).second;
         if (var_ref != NULL) {
            if (var_ref->IsBackgroundSensitive() && !pending_refresh_map->IsRefreshed(var_ref)) {
               var_ref->NewValue(data_set);
               pending_refresh_map->SetRefreshed(var_ref);
            }
         }
         i++;
      }
#endif
   };
private:
   DATA_REFRESH_MAP_T _RefreshMap;
};

#endif


