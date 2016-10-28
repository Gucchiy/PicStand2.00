# Microsoft Developer Studio Project File - Name="PicStand" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PicStand - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "PicStand.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "PicStand.mak" CFG="PicStand - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "PicStand - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "PicStand - Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PicStand - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 vfw32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "PicStand - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 vfw32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "PicStand - Win32 Release"
# Name "PicStand - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Canvas.cpp
# End Source File
# Begin Source File

SOURCE=.\CanvasItem.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomButton.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomizeWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\Dibutils.cpp
# End Source File
# Begin Source File

SOURCE=.\ExpandShortcut.cpp
# End Source File
# Begin Source File

SOURCE=.\Global.cpp
# End Source File
# Begin Source File

SOURCE=.\IdeaTech.cpp
# End Source File
# Begin Source File

SOURCE=.\IJLWrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\PicStand.cpp
# End Source File
# Begin Source File

SOURCE=.\PicStand.rc
# End Source File
# Begin Source File

SOURCE=.\PicStandWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\Picture.cpp
# End Source File
# Begin Source File

SOURCE=.\PictureFileDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StatusWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\StayButton.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TrayIcon.cpp
# End Source File
# Begin Source File

SOURCE=.\VersionInfoDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Canvas.h
# End Source File
# Begin Source File

SOURCE=.\CanvasItem.h
# End Source File
# Begin Source File

SOURCE=.\CustomButton.h
# End Source File
# Begin Source File

SOURCE=.\CustomizeWnd.h
# End Source File
# Begin Source File

SOURCE=.\Dibutils.h
# End Source File
# Begin Source File

SOURCE=.\ExpandShortcut.h
# End Source File
# Begin Source File

SOURCE=.\Global.h
# End Source File
# Begin Source File

SOURCE=.\IdeaTech.h
# End Source File
# Begin Source File

SOURCE=.\ijl.h
# End Source File
# Begin Source File

SOURCE=.\IJLWrapper.h
# End Source File
# Begin Source File

SOURCE=.\PicStand.h
# End Source File
# Begin Source File

SOURCE=.\PicStandWnd.h
# End Source File
# Begin Source File

SOURCE=.\Picture.h
# End Source File
# Begin Source File

SOURCE=.\PictureFileDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StatusWnd.h
# End Source File
# Begin Source File

SOURCE=.\StayButton.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TrayIcon.h
# End Source File
# Begin Source File

SOURCE=.\VersionInfoDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Graphics\Back00.BMP
# End Source File
# Begin Source File

SOURCE=.\Graphics\Back01.BMP
# End Source File
# Begin Source File

SOURCE=.\Graphics\Back02.BMP
# End Source File
# Begin Source File

SOURCE=.\res\Default.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\Graphics\Menu00.BMP
# End Source File
# Begin Source File

SOURCE=.\Graphics\Menu01.BMP
# End Source File
# Begin Source File

SOURCE=.\Graphics\Menu03.BMP
# End Source File
# Begin Source File

SOURCE=.\Graphics\Next00.BMP
# End Source File
# Begin Source File

SOURCE=.\Graphics\Next01.BMP
# End Source File
# Begin Source File

SOURCE=.\Graphics\Next02.BMP
# End Source File
# Begin Source File

SOURCE=.\res\PicStand.ico
# End Source File
# Begin Source File

SOURCE=.\res\PicStand.rc2
# End Source File
# Begin Source File

SOURCE=.\Graphics\rgb_blue.bmp
# End Source File
# Begin Source File

SOURCE=.\Graphics\rgb_gree.bmp
# End Source File
# Begin Source File

SOURCE=.\Graphics\rgb_red.bmp
# End Source File
# Begin Source File

SOURCE=.\Graphics\Status00.BMP
# End Source File
# Begin Source File

SOURCE=.\Graphics\Status01.BMP
# End Source File
# Begin Source File

SOURCE=.\Graphics\StayDown00.BMP
# End Source File
# Begin Source File

SOURCE=.\Graphics\StayDown01.BMP
# End Source File
# Begin Source File

SOURCE=.\Graphics\StayUp00.BMP
# End Source File
# Begin Source File

SOURCE=.\Graphics\StayUp01.BMP
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\ijl15.lib
# End Source File
# End Target
# End Project
