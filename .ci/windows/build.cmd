set BUILD_DIR=%WORKSPACE%\build
set INSTALL_DIR=%WORKSPACE%\install

mkdir %BUILD_DIR%
mkdir %INSTALL_DIR%

cd %BUILD_DIR%

cmake ^
  -G Ninja ^
  -DBUILD_TESTING=OFF -DBUILD_EXAMPLES=OFF ^
  -DWITH_DCMTK=OFF ^
  -DCMAKE_INSTALL_PREFIX=%INSTALL_DIR% ^
  -DCMAKE_BUILD_TYPE=Release ^
  -DPYTHON_EXECUTABLE=%PYTHON% ^
  ${CMAKE_OPTIONS} ^
  ..
if %errorlevel% neq 0 exit /b %errorlevel%

cmake --build . --config Release --target install
if %errorlevel% neq 0 exit /b %errorlevel%

cd %WORKSPACE%
