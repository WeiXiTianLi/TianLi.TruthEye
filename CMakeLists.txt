# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.20)

# 设置第三方目录
set(ThirdPartyDir ${CMAKE_SOURCE_DIR}/third_party)
set(DependentPatryDir ${CMAKE_SOURCE_DIR}/dependent_party)

if (MSVC)
    add_compile_options(/utf-8)
endif()
set(CMAKE_CXX_STANDARD 20)

project ("TianLi.TruthEye")

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 包含目录
include_directories(${PROJECT_SOURCE_DIR}/source)

# 包含子项目
add_subdirectory(source)
