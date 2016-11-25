#!/bin/sh

#!/bin/sh
# Usage: striplocale <localedir>

localedir=$1
cd $localedir
locales=""
for d in * ; do
  if test -d $d ; then
    locales="$locales $d"
  fi
done
facets="LC_ADDRESS LC_COLLATE LC_CTYPE LC_IDENTIFICATION LC_MEASUREMENT LC_MESSAGES/SYS_LC_MESSAGES LC_MONETARY LC_NAME LC_NUMERIC LC_PAPER LC_TELEPHONE LC_TIME"
ll=""
for l in $locales; do
  for f in $facets; do
    for o in $ll; do
      if cmp -s $l/$f $o/$f 2>/dev/null ; then
        echo "Linking $l/$f"
        rm -f $l/$f
        ln $o/$f $l/$f
        break
      fi
    done
  done
  ll="$ll $l"
done

