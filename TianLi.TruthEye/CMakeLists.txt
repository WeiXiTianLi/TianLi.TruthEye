# CMakeList.txt: QAppMutRelease 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
project(TianLi.TruthEye VERSION 1.0.0)

# 该项目为静态链接Qt5的动态链接库
# Qt5
set(Qt5VER "qt-5.15.2-lite-release-static")
set(Qt5_DIR "${ThridPatryDir}/${Qt5VER}/lib/cmake/Qt5")
#set(Qt5_DIR "E:/Qt/5.15.7/msvc2019_64_static/lib/cmake/Qt5")
find_package(Qt5 COMPONENTS Core Gui Widgets FbSupport FontDatabaseSupport  REQUIRED)
#
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# define QAPP_EXPORTS
add_definitions(-DTIANLI_TRUTHEYE_EXPORTS)

# 添加本地第三方库
include_directories("3rdparty")
include_directories("3rdparty/cpr/include")
include_directories("3rdparty/spdlog/include")
# 添加库搜索路径
link_directories("3rdparty/cpr/lib")
link_directories("3rdparty/spdlog/lib")

if(MSVC)
    set(VERSION_RC "${CMAKE_BINARY_DIR}/impl.version.rc")
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/source/impl.version.rc.in
                   "${VERSION_RC}")
endif()

set(MSVC_RUNTIME_LIBRARY "MultiThreaded")

# vcpkg
# 将源代码添加到此项目的可执行文件。
add_library(${PROJECT_NAME} SHARED ${VERSION_RC}
	"source/TianLi.TruthEye.cpp" 
	"include/TianLi.TruthEye.h"  
	"source/form/te.popup.window.cpp"
	"source/form/te.popup.window.h" 

)

#set_target_properties(${PROJECT_NAME}  PROPERTIES INTERFACE_LINK_LIBRARIES "MultiThreaded$<$<CONFIG:Debug>:Debug>")

#set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded")




# link 3rdparty lib
target_link_libraries(${PROJECT_NAME} PRIVATE tianli.cpr tianli.libcurl Crypt32)
target_link_libraries(${PROJECT_NAME} PRIVATE tianli.spdlog $<$<BOOL:${MSVC}>:ws2_32>)
# show all qt5 module
message(STATUS "Qt5::Core: ${Qt5Core_VERSION}")
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets )

# used utf-8 encoding
target_compile_options(${PROJECT_NAME} PRIVATE "/utf-8")

add_subdirectory(inface)

