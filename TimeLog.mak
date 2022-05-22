# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=TimeLog - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to TimeLog - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "TimeLog - Win32 Debug" && "$(CFG)" != "TimeLog - Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "test.mak" CFG="TimeLog - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TimeLog - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "TimeLog - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "TimeLog - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "TimeLog - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : "$(OUTDIR)\TimeLog.exe" "$(OUTDIR)\timelog.bsc"

CLEAN : 
	-@erase "$(INTDIR)\getprogramversion.obj"
	-@erase "$(INTDIR)\getprogramversion.sbr"
	-@erase "$(INTDIR)\RegDlg.obj"
	-@erase "$(INTDIR)\RegDlg.sbr"
	-@erase "$(INTDIR)\SmFormat.obj"
	-@erase "$(INTDIR)\SmFormat.sbr"
	-@erase "$(INTDIR)\StatAuswahl.obj"
	-@erase "$(INTDIR)\StatAuswahl.sbr"
	-@erase "$(INTDIR)\Statistik.obj"
	-@erase "$(INTDIR)\Statistik.sbr"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\stdafx.sbr"
	-@erase "$(INTDIR)\TimeLog.obj"
	-@erase "$(INTDIR)\test.pch"
	-@erase "$(INTDIR)\TimeLog.sbr"
	-@erase "$(INTDIR)\TimeLogdlg.obj"
	-@erase "$(INTDIR)\TimeLogdlg.sbr"
	-@erase "$(INTDIR)\TimeLog.res"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\timelog.bsc"
	-@erase "$(OUTDIR)\TimeLog.exe"
	-@erase "$(OUTDIR)\TimeLog.ilk"
	-@erase "$(OUTDIR)\TimeLog.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/test.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\WinDebug/
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /fo"WinDebug/TimeLog.res" /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/TimeLog.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"WinDebug/timelog.bsc"
BSC32_FLAGS=/nologo /o"$(OUTDIR)/timelog.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\getprogramversion.sbr" \
	"$(INTDIR)\RegDlg.sbr" \
	"$(INTDIR)\SmFormat.sbr" \
	"$(INTDIR)\StatAuswahl.sbr" \
	"$(INTDIR)\Statistik.sbr" \
	"$(INTDIR)\stdafx.sbr" \
	"$(INTDIR)\TimeLog.sbr" \
	"$(INTDIR)\TimeLogdlg.sbr"

"$(OUTDIR)\timelog.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"WinDebug/TimeLog.exe"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/TimeLog.pdb" /debug /machine:I386 /out:"$(OUTDIR)/TimeLog.exe" 
LINK32_OBJS= \
	"$(INTDIR)\getprogramversion.obj" \
	"$(INTDIR)\RegDlg.obj" \
	"$(INTDIR)\SmFormat.obj" \
	"$(INTDIR)\StatAuswahl.obj" \
	"$(INTDIR)\Statistik.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\TimeLog.obj" \
	"$(INTDIR)\TimeLogdlg.obj" \
	"$(INTDIR)\TimeLog.res"

"$(OUTDIR)\TimeLog.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TimeLog - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : "$(OUTDIR)\TimeLog.exe" "$(OUTDIR)\test.pch"

CLEAN : 
	-@erase "$(INTDIR)\getprogramversion.obj"
	-@erase "$(INTDIR)\RegDlg.obj"
	-@erase "$(INTDIR)\SmFormat.obj"
	-@erase "$(INTDIR)\StatAuswahl.obj"
	-@erase "$(INTDIR)\Statistik.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\TimeLog.obj"
	-@erase "$(INTDIR)\test.pch"
	-@erase "$(INTDIR)\TimeLogdlg.obj"
	-@erase "$(INTDIR)\TimeLog.res"
	-@erase "$(OUTDIR)\TimeLog.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /Od /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /GX /Od /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/test.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\.
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /fo"WinRel/TimeLog.res" /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/TimeLog.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"WinRel/timelog.bsc"
BSC32_FLAGS=/nologo /o"$(OUTDIR)/timelog.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"WinRel/TimeLog.exe"
# SUBTRACT LINK32 /pdb:none /debug
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/TimeLog.pdb" /machine:I386 /out:"$(OUTDIR)/TimeLog.exe" 
LINK32_OBJS= \
	"$(INTDIR)\getprogramversion.obj" \
	"$(INTDIR)\RegDlg.obj" \
	"$(INTDIR)\SmFormat.obj" \
	"$(INTDIR)\StatAuswahl.obj" \
	"$(INTDIR)\Statistik.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\TimeLog.obj" \
	"$(INTDIR)\TimeLogdlg.obj" \
	"$(INTDIR)\TimeLog.res"

"$(OUTDIR)\TimeLog.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

MTL_PROJ=
################################################################################
# Begin Target

# Name "TimeLog - Win32 Debug"
# Name "TimeLog - Win32 Release"

!IF  "$(CFG)" == "TimeLog - Win32 Debug"

!ELSEIF  "$(CFG)" == "TimeLog - Win32 Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\stdafx.cpp
DEP_CPP_STDAF=\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "TimeLog - Win32 Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/test.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\stdafx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\test.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "TimeLog - Win32 Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /Od /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/test.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\test.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TimeLog.cpp
DEP_CPP_TIMELOG_=\
	".\stdafx.h"\
	".\test.h"\
	".\testdlg.h"\
	

!IF  "$(CFG)" == "TimeLog - Win32 Debug"


"$(INTDIR)\TimeLog.obj" : $(SOURCE) $(DEP_CPP_TIMELOG_) "$(INTDIR)"\
 "$(INTDIR)\test.pch"

"$(INTDIR)\TimeLog.sbr" : $(SOURCE) $(DEP_CPP_TIMELOG_) "$(INTDIR)"\
 "$(INTDIR)\test.pch"


!ELSEIF  "$(CFG)" == "TimeLog - Win32 Release"


"$(INTDIR)\TimeLog.obj" : $(SOURCE) $(DEP_CPP_TIMELOG_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TimeLogdlg.cpp
DEP_CPP_TIMELOGD=\
	"..\TelAr\getprogramversion.h"\
	".\RegDlg.h"\
	".\SmFormat.h"\
	".\StatAuswahl.h"\
	".\Statistik.h"\
	".\stdafx.h"\
	".\test.h"\
	".\testdlg.h"\
	

!IF  "$(CFG)" == "TimeLog - Win32 Debug"


"$(INTDIR)\TimeLogdlg.obj" : $(SOURCE) $(DEP_CPP_TIMELOGD) "$(INTDIR)"\
 "$(INTDIR)\test.pch"

"$(INTDIR)\TimeLogdlg.sbr" : $(SOURCE) $(DEP_CPP_TIMELOGD) "$(INTDIR)"\
 "$(INTDIR)\test.pch"


!ELSEIF  "$(CFG)" == "TimeLog - Win32 Release"


"$(INTDIR)\TimeLogdlg.obj" : $(SOURCE) $(DEP_CPP_TIMELOGD) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TimeLog.rc
DEP_RSC_TIMELOG_R=\
	".\res\TimeLog.ico"\
	".\res\TimeLog.rc2"\
	".\res\uhr.bmp"\
	

"$(INTDIR)\TimeLog.res" : $(SOURCE) $(DEP_RSC_TIMELOG_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\readme.txt

!IF  "$(CFG)" == "TimeLog - Win32 Debug"

!ELSEIF  "$(CFG)" == "TimeLog - Win32 Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SmFormat.cpp
DEP_CPP_SMFOR=\
	".\SmFormat.h"\
	".\stdafx.h"\
	".\test.h"\
	".\testdlg.h"\
	

!IF  "$(CFG)" == "TimeLog - Win32 Debug"


"$(INTDIR)\SmFormat.obj" : $(SOURCE) $(DEP_CPP_SMFOR) "$(INTDIR)"\
 "$(INTDIR)\test.pch"

"$(INTDIR)\SmFormat.sbr" : $(SOURCE) $(DEP_CPP_SMFOR) "$(INTDIR)"\
 "$(INTDIR)\test.pch"


!ELSEIF  "$(CFG)" == "TimeLog - Win32 Release"


"$(INTDIR)\SmFormat.obj" : $(SOURCE) $(DEP_CPP_SMFOR) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RegDlg.cpp
DEP_CPP_REGDL=\
	".\RegDlg.h"\
	".\stdafx.h"\
	".\test.h"\
	

!IF  "$(CFG)" == "TimeLog - Win32 Debug"


"$(INTDIR)\RegDlg.obj" : $(SOURCE) $(DEP_CPP_REGDL) "$(INTDIR)"\
 "$(INTDIR)\test.pch"

"$(INTDIR)\RegDlg.sbr" : $(SOURCE) $(DEP_CPP_REGDL) "$(INTDIR)"\
 "$(INTDIR)\test.pch"


!ELSEIF  "$(CFG)" == "TimeLog - Win32 Release"


"$(INTDIR)\RegDlg.obj" : $(SOURCE) $(DEP_CPP_REGDL) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StatAuswahl.cpp
DEP_CPP_STATA=\
	".\StatAuswahl.h"\
	".\stdafx.h"\
	".\test.h"\
	

!IF  "$(CFG)" == "TimeLog - Win32 Debug"


"$(INTDIR)\StatAuswahl.obj" : $(SOURCE) $(DEP_CPP_STATA) "$(INTDIR)"\
 "$(INTDIR)\test.pch"

"$(INTDIR)\StatAuswahl.sbr" : $(SOURCE) $(DEP_CPP_STATA) "$(INTDIR)"\
 "$(INTDIR)\test.pch"


!ELSEIF  "$(CFG)" == "TimeLog - Win32 Release"


"$(INTDIR)\StatAuswahl.obj" : $(SOURCE) $(DEP_CPP_STATA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Statistik.cpp
DEP_CPP_STATI=\
	".\SmFormat.h"\
	".\StatAuswahl.h"\
	".\Statistik.h"\
	".\stdafx.h"\
	".\test.h"\
	

!IF  "$(CFG)" == "TimeLog - Win32 Debug"


"$(INTDIR)\Statistik.obj" : $(SOURCE) $(DEP_CPP_STATI) "$(INTDIR)"\
 "$(INTDIR)\test.pch"

"$(INTDIR)\Statistik.sbr" : $(SOURCE) $(DEP_CPP_STATI) "$(INTDIR)"\
 "$(INTDIR)\test.pch"


!ELSEIF  "$(CFG)" == "TimeLog - Win32 Release"


"$(INTDIR)\Statistik.obj" : $(SOURCE) $(DEP_CPP_STATI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\tlregist.txt

!IF  "$(CFG)" == "TimeLog - Win32 Debug"

!ELSEIF  "$(CFG)" == "TimeLog - Win32 Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\tlreadme.txt

!IF  "$(CFG)" == "TimeLog - Win32 Debug"

!ELSEIF  "$(CFG)" == "TimeLog - Win32 Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Work\TelAr\getprogramversion.cpp
DEP_CPP_GETPR=\
	"..\TelAr\stdafx.h"\
	

!IF  "$(CFG)" == "TimeLog - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\getprogramversion.obj" : $(SOURCE) $(DEP_CPP_GETPR) "$(INTDIR)"\
 "$(INTDIR)\test.pch"
   $(BuildCmds)

"$(INTDIR)\getprogramversion.sbr" : $(SOURCE) $(DEP_CPP_GETPR) "$(INTDIR)"\
 "$(INTDIR)\test.pch"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "TimeLog - Win32 Release"


"$(INTDIR)\getprogramversion.obj" : $(SOURCE) $(DEP_CPP_GETPR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
