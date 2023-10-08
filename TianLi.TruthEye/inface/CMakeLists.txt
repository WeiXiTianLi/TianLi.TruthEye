# CMakeList.txt: QAppMutRelease 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
project(TianLi.TruthEye.Inface)

# define 
add_definitions(-DTIANLI_TRUTHEYE_EXPORTS)
add_definitions(-DTIANLI_TRUTHEYE_IMPL)

# 添加本地第三方库
include_directories("3rdparty")
include_directories("3rdparty/cpr/include")
# 添加库搜索路径
link_directories("3rdparty/cpr/lib")


set(MSVC_RUNTIME_LIBRARY "MultiThreaded")

# vcpkg
# 将源代码添加到此项目的可执行文件。
add_library(${PROJECT_NAME} SHARED 
	"TianLi.TruthEye.Inface.cpp" 
)


set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")

# link 3rdparty lib
target_link_libraries(${PROJECT_NAME} PRIVATE tianli.libcurl Crypt32)
target_link_libraries(${PROJECT_NAME} PRIVATE tianli.cpr-d)

# used utf-8 encoding
target_compile_options(${PROJECT_NAME} PRIVATE "/utf-8")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()


