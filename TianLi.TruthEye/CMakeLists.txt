# CMakeList.txt: QAppMutRelease 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
project(TianLi.TruthEye)

# 该项目为静态链接Qt5的动态链接库

# Qt5
set(Qt5_DIR "C:/Qt/5.15.7/msvc2019_x64_static/lib/cmake/Qt5")
#set(Qt5_DIR "C:/Qt/5.15.2/msvc2019_64/lib/cmake/Qt5")
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets )
#
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# define QAPP_EXPORTS
add_definitions(-DTIANLI_TRUTHEYE_EXPORTS)

# 添加本地第三方库
include_directories("3rdparty")


# 将源代码添加到此项目的可执行文件。
add_library(${PROJECT_NAME} SHARED 
	"source/TianLi.TruthEye.cpp" 
	"include/TianLi.TruthEye.h"  
	"source/form/te.popup.window.cpp"
	"source/form/te.popup.window.h" 
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets)

# used utf-8 encoding
target_compile_options(${PROJECT_NAME} PRIVATE "/utf-8")

set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。

# 安装Qt依赖
# install(DIRECTORY ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
# install(FILES $<TARGET_FILE:Qt5::Core> DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
# install(FILES $<TARGET_FILE:Qt5::Gui> DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
# install(FILES $<TARGET_FILE:Qt5::Widgets> DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

