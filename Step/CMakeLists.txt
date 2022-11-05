cmake_minimum_required(VERSION 3.0)  # 设定cmake最低版本
project(Tutorial VERSION 1.0)  # 设定项目名称和版本
set(CMAKE_CXX_STANDARD 11)  # 设置cpp标准
add_executable(Tutorial tutorial.cpp)  # 指定项目对应的可执行文件入口

option(USE_MYMATH "Use tutorial provided math implementation" OFF)  # 默认值要在h.in文件前option，否则不会被应用
configure_file(TutorialConfig.h.in TutorialConfig.h)  # 从.in文件复制内容，填充内部变量并生成目标文件

if (USE_MYMATH)  # 条件语句
    add_subdirectory(MathFunctions)  # 使得cmake能递归处理子目录
    list(APPEND EXTRA_LIBS MathFunctions)  # 设置变量
    list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/MathFunctions" ${EXTRA_INCLUDES})  # 设置变量
endif ()

target_include_directories(Tutorial PUBLIC "${PROJECT_BINARY_DIR}" ${EXTRA_INCLUDES})  # 告诉链接器要链接文件的位置，以build文件夹为根目录检索
target_link_libraries(Tutorial PUBLIC ${EXTRA_LIBS})  # 指定某个目标对应要链接的链接库