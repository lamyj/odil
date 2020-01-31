set BUILD_DIR=%WORKSPACE%\build
set INSTALL_DIR=%WORKSPACE%\install

cd %BUILD_DIR%

echo %PYTHON%
for /f "tokens=*" %%a in ( '%PYTHON% -c "from distutils.sysconfig import *; print(get_python_lib(True, prefix=\"\"))"' ) do set PYTHONPATH=%INSTALL_DIR%\%%a
if %errorlevel% neq 0 exit /b %errorlevel%
echo %PYTHONPATH%

set PATH=%PATH%;%INSTALL_DIR%\bin

echo "WARNING: no DCMTK package is available on Windows; not running tests"

REM ctest -T Test
REM if %errorlevel% neq 0 exit /b %errorlevel%
REM 
REM %PYTHON% -m unittest discover -s %WORKSPACE%/tests/python/
REM if %errorlevel% neq 0 exit /b %errorlevel%
REM 
REM cd %WORKSPACE%
