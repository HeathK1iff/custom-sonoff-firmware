@echo off
:: -------------------------- IP -----------------------------------------::
set /p ip="Ip address of device: "
:: --------------------- Device Name -------------------------------------::
set /p device_name="Please enter device name: "
call :update device_name, %device_name%
:: ----------------------- Model -----------------------------------------::
echo 1. Sonoff Basic
echo 2. Sonoff Mini R2
echo 3. Sonoff POW R2
choice /c 123 /m "Please select model: " 
set /a model=%errorlevel%
call :update model %model%
:: ----------------------- SSID ------------------------------------------::
set /p ssid="SSID:"
call :update ssid %ssid%
:: --------------------- SSID-pass ---------------------------------------::
set /p ssid_pass="SSID passowrd:"
call :update ssid_pass %ssid_pass%
:: ------------------ Save & Restart -------------------------------------::
curl http://%ip%/api/settings/save.do
exit /b 0
:: -------------------- function -----------------------------------------::
:update
for /F "delims=" %%v in ('curl -X POST -d %~2 http://%ip%/api/settings/%~1') do (
if /i "%%v"=="success" (
echo %~1 was updated!!!
) else (
echo Error!!! was not updated
))
exit /b 0
