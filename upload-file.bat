@echo off
set uploadFile=%CD%\output\MySonoffEsp.ino.bin
choice /c yn /m "Do you want to upgrade of device (%1) to firmware(%uploadFile%)"
if %errorlevel%==2 goto cancel
if not exist %uploadFile% goto file_not_found
curl http://%1/api/firmware.do
curl -X POST -F upload=@%uploadFile% -H "Content-Type: multipart/form-data" http://%1/api/firmware.do
exit /b 0
:cancel
echo Operation was canceled.
exit /b 0
:file_not_found
echo File (%uploadFile%) not found
exit /b 0