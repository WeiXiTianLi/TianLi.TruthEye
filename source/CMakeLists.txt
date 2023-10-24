project(TianLi.TruthEye VERSION 1.1.1)

# Qt5
set(Qt5VER "qt-5.15.2-lite-release-static")
set(Qt5_DIR "${ThirdPartyDir}/${Qt5VER}/lib/cmake/Qt5")
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# define QAPP_EXPORTS
add_definitions(-DTIANLI_TRUTHEYE_EXPORTS)

# 添加本地第三方库
include_directories(${DependentPatryDir}/meojson/include)
include_directories(${ThirdPartyDir}/cpr/include)
include_directories(${ThirdPartyDir}/spdlog/include)
# 添加库搜索路径
link_directories(${ThirdPartyDir}/cpr/lib)
link_directories(${ThirdPartyDir}/spdlog/lib)

if(MSVC)
    set(VERSION_RC "${CMAKE_BINARY_DIR}/impl.version.rc")
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/impl.version.rc.in "${VERSION_RC}")
endif()

# 将源代码添加到此项目的可执行文件。
add_library(${PROJECT_NAME} SHARED ${VERSION_RC}
	"../include/TianLi.TruthEye.h" 
	"TianLi.TruthEye.cpp"  
	"form/te.popup.window.cpp"
	"form/te.popup.window.h" 
)

set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded")

# link 3rdparty lib
target_link_libraries(${PROJECT_NAME} PRIVATE tianli.cpr tianli.libcurl Crypt32)
target_link_libraries(${PROJECT_NAME} PRIVATE tianli.spdlog $<$<BOOL:${MSVC}>:ws2_32>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets )

# used utf-8 encoding
target_compile_options(${PROJECT_NAME} PRIVATE "/utf-8")

# copy version.rc to output dir
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${CMAKE_CURRENT_SOURCE_DIR}/version"
		$<TARGET_FILE_DIR:${PROJECT_NAME}>)

