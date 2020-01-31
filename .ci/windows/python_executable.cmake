file(READ "CMakeCache.txt" cache)
string(REGEX MATCH "PYTHON_EXECUTABLE:([^=]+)=([^\n\r]+)" _ "${cache}")
message("${CMAKE_MATCH_2}")
