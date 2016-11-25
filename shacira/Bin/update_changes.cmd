@echo off
cd ..
svn update
svn log . -v >changes.txt
