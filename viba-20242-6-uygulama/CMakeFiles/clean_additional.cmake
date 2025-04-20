# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\uygulama_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\uygulama_autogen.dir\\ParseCache.txt"
  "uygulama_autogen"
  )
endif()
