@echo off
chcp 65001 > nul
setlocal

rem 获取批处理所在的文件夹路径
for %%i in ("%~dp0.") do set "BatchFolder=%%~fi"

rem 构建 SexyBeach3PlusCN.exe 的完整路径
set "ProgramPath=%BatchFolder%\SexyBeach3PlusCN.exe"

rem 删除兼容性模式设置
reg delete "HKCU\Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers" /v "%ProgramPath%" /f >nul 2>&1

if %errorlevel% equ 0 (
    echo 关闭兼容模式成功！
) else (
    echo 关闭兼容模式失败！

)
set "CurrentDir=%~dp0"
cd /d "%CurrentDir%"
del jrxoff.bat
