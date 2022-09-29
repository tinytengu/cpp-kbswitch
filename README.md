# kbswitch

This is a **Windows-targetted** script to force the English keyboard layout to switch to Korean, because I just suffer from having two Latin layouts - English (US) and Korean (English) at the same time.

> It does not work with CMD and PowerShell properly, but it works just fine with Windows Terminal.

## How to compile
Since it's written specifically for Windows and the code is literally ~60 lines long, I've just used "cl.exe" from Windows SDK (I believe).
```cmd
cl kbswitch.cpp
```