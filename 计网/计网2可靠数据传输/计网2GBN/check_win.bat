@echo off
:: appname ������
:: inputname �����ļ���
:: outputname ����ļ���
:: resultname �������̨����ض����ļ���

set appname="C:\Users\dell\source\repos\����2GBN\Debug\����2.exe"
set inputname="C:\Users\dell\source\repos\����2GBN\input.txt"
set outputname="C:\Users\dell\source\repos\����2GBN\output.txt"
set resultname="C:\Users\dell\source\repos\����2GBN\result.txt"

for /l %%i in (1,1,10) do (
    echo Test %appname% %%i:
    %appname% > %resultname% 2>&1
    fc /N %inputname% %outputname%
)
pause