# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/appmtgDeckBuilder_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/appmtgDeckBuilder_autogen.dir/ParseCache.txt"
  "appmtgDeckBuilder_autogen"
  )
endif()
