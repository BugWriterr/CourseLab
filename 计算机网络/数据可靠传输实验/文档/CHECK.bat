@echo off
:: appname ������
:: inputname �����ļ���
:: outputname ����ļ���
:: resultname �������̨����ض����ļ���

set appname="U201714481_2.exe"
set inputname="input.txt"
set outputname="output.txt"
set resultname="result.txt"


for /l %%i in (1,1,10) do (

echo Test %appname% %%i:
    %appname% 3 > %resultname% 2>&1
    fc /N %inputname% %outputname%
)

pause