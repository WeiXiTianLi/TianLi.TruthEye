# CMakeList.txt: QApp.cli 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
project(TianLi.TruthEye.c.test)


# 将源代码添加到此项目的可执行文件。
add_executable (${PROJECT_NAME} "main.cpp")

# 添加依赖项
target_link_libraries(${PROJECT_NAME} TianLi.TruthEye.Inface)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
