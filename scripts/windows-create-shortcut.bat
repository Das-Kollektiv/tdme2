@if "%~1" == "" goto usage
@if "%~2" == "" goto usage
@echo off
SETLOCAL ENABLEDELAYEDEXPANSION
SET Esc_LinkDest=%2
SET Esc_LinkTarget=%1
SET cSctVBS=CreateShortcut.vbs
((
  echo Set oWS = WScript.CreateObject^("WScript.Shell"^)
  echo Set oFSO = CreateObject^("Scripting.FileSystemObject"^)
  echo sLinkFile = oWS.ExpandEnvironmentStrings^(!Esc_LinkDest!^)
  echo Set oLink = oWS.CreateShortcut^(sLinkFile^)
  echo oLink.TargetPath = oWS.ExpandEnvironmentStrings^(!Esc_LinkTarget!^)
  echo oLink.WorkingDirectory = oFSO.GetParentFolderName^(oLink.TargetPath!^)
  echo oLink.IconLocation = oLink.WorkingDirectory ^& "\resources\win32\app.ico"
  echo oLink.Save
)1>!cSctVBS!
cscript //nologo .\!cSctVBS!
DEL !cSctVBS! /f /q
)1>>nul 2>>&1
goto :eof
:usage
@echo Syntax
@echo     shortcut "#target#" "#name#"
@echo Parameters
@echo     target    : The path and file name of the application/document to open.
@echo     name      : The path and file name (.LNK) of the shortcut file.