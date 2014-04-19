@echo off

rem ----------------------------------------------------------
rem --- Setup some environment variables.
rem ----------------------------------------------------------
set CZP_PATH=d:\util\
set CZP_CMD=%CZP_PATH%czp.exe

rem ----------------------------------------------------------
rem --- Call czp (A.K.A. CheezyPing) to update your site
rem --- 
rem --- **** Ping http://www.weblogs.com/ ****
rem ---
rem --- Remember Weblogs.com is the default, no need for it
rem --- on the command line.
rem ----------------------------------------------------------
%CZP_CMD% -s"Some Random Site" -u"http://www.SomeRandomSite.com"

rem ----------------------------------------------------------
rem --- **** Ping http://www.blo.gs/ ****
rem ----------------------------------------------------------
%CZP_CMD% -s"Some Random Site" -u"http://www.SomeRandomSite.com" -p"http://ping.blo.gs/"

set CZP_PATH=
set CZP_CMD=

rem ----------------------------------------------------------------------
rem 1) Replace  - "Some Random Site" with the name of your site.
rem 2) Replace  - "http://www.SomRandomSite.com" with your site URL.
rem 3) Optional - Add -p"http://SiteToPing.URL". Defaults to weblogs.com.
rem ----------------------------------------------------------------------