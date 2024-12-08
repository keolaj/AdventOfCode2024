# CMakeList.txt : CMake project for adventofcode, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("adventofcode")

# Add source to this project's executable.
add_executable (adventofcode "adventofcode.cpp" "adventofcode.h"  "days/day8/day8.h" "days/day8/day8.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET adventofcode PROPERTY CXX_STANDARD 23)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc-")

# TODO: Add tests and install targets if needed.
