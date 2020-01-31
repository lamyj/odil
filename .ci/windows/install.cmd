REM WARNING: assume conda is installed

conda update -y -n base -c defaults conda
conda install -y -c conda-forge boost cmake icu jsoncpp ninja pkg-config pybind11 python
if %errorlevel% neq 0 exit /b %errorlevel%
