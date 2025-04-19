# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/vibaben_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/vibaben_autogen.dir/ParseCache.txt"
  "vibaben_autogen"
  )
endif()
