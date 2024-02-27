@echo off

del log.txt

::生成发布版本路径的文件夹，删除旧的bin文件
IF NOT EXIST .\Release mkdir .\Release
cd Release
del *.bin

cd ..

::选择芯片类型
set pro=RL6432

copy "Output\RL6432\%pro%_Project.bin" "Release\" >>log.txt

::获得完整名字，包含机型，软件版本，Git/SVN版本，系统日期和时间

for /f "tokens=3" %%a in ('findstr /c:"#define _PRODUCT_ID_SEL" "Project\Header\User_Project_Option.h"') do (
set "fn0=%%~a"
)

::获得代码写的SVN信息 
for /f "tokens=3" %%a in ('findstr /c:"#define FW_VERSION" "Project\Header\User_Project_Option.h"') do (
set "fn1=%%~a"
)

for /f "tokens=3" %%a in ('findstr /c:"#define _MAIN_VERSION" "Project\Header\User_Project_Option.h"') do (
set "fn2=%%~a"
)

for /f "tokens=3" %%a in ('findstr /c:"#define _TEST_VERSION" "Project\Header\User_Project_Option.h"') do (
set "fn3=%%~a"
)

set hh=%time:~0,2%
if /i %hh% LSS 10 (set hh=0%time:~1,1%)

::获得SVN Update后的SVN版本信息
for /f "delims=" %%i in ('svn info ^| findstr "Revision"') do set rev=%%i
set rev=%rev:~10%

::set "name=%pro%_%fn0%_%fn1%%fn2%_SVN%rev%_%date:~0,4%%date:~5,2%%date:~8,2%_%hh%%time:~3,2%
set "name=%pro%_%fn0%_%fn1%_%fn2%_%fn3%%date:~0,4%%date:~5,2%%date:~8,2%

cd Release 
::bin文件改名  
::ren *.bin "%name%.bin"

::添加临时文件夹然后压缩文件夹
mkdir temp

copy "*.bin" "temp\"  >>..\log.txt

set Sz=C:\Program Files\7-Zip\7z.exe
set Save=Backup
set Com=temp\

for /f "delims=" %%a in ('dir /a-d/s/b "%Com%"') do "%Sz%" a "%Save%\%%~na.7z" "%%~a" >>..\log.txt
del /s /Q temp\ >>..\log.txt
rd temp >>..\log.txt

::压缩文件夹文件改名
cd Backup 
del FW_%name%.7z 
ren %pro%_Project.7z "FW_%name%.7z" 