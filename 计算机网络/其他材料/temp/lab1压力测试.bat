SETLOCAL
rem 压力测试，替换(1,1,1200)中的100为测试数
rem url替换为http://10.14.122.65/web.html

set url=http://222.20.102.208/web.html
set cmd1= curl %url%

for /L %%i in (1,1,100) do %cmd1% 
ENDLOCAL
pause
