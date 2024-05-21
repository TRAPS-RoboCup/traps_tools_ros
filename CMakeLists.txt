# Copyright 2024 TRAPS

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.8)
project(traps_tools)

add_compile_options(-O2)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

file(GLOB exec_files
  LIST_DIRECTORIES false
  RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
  "src/*")

file(GLOB_RECURSE lib_files
  LIST_DIRECTORIES false
  RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
  "src/*/*")

foreach(exec_file IN LISTS exec_files)
  get_filename_component(exec "${exec_file}" NAME_WE)
  file(GLOB_RECURSE exec_lib_files
    LIST_DIRECTORIES false
    RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "src/${PROJECT_NAME}/${exec}/*")
  ament_auto_add_executable(${exec}
    "${exec_file}" "${exec_lib_files}")
  target_compile_features(${exec} PUBLIC c_std_99 cxx_std_17)
  set(execs ${exec};${execs})
  list(REMOVE_ITEM lib_files "${exec_lib_files}")
endforeach(exec_file)

if(lib_files)
  add_library(lib "${lib_files}")
  target_include_directories(lib PRIVATE "include")
  foreach(exec IN LISTS execs)
    target_link_libraries(${exec} lib)
  endforeach(exec)
endif()

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_auto_package()
