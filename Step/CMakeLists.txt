cmake_minimum_required(VERSION 3.15)  # 设定cmake最低版本
project(Tutorial VERSION 1.0)  # 设定项目名称和版本
set(CMAKE_CXX_STANDARD 11)  # 设置cpp标准
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Tutorial tutorial.cpp)  # 指定项目对应的可执行文件入口

# 启用编译器警告，通过表达式生成器完成
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")  # 通过COMPILE_LANG_AND_ID判断环境，并为gcc_like_cxx赋值
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")  # 同上

# 定义interface library，用其作为载体传递编译属性。只要模块用target_link_libraries链接了该interface library，则会应用其上的编译属性。
# 配合表达式生成器判断编译环境，并赋予不同的编译参数
# BUILD_INTERFACE表达式使得flags不会传递到已安装项目，而仅仅作用于
add_library(tutorial_compiler_flags INTERFACE
        "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"  # 判断gcc_like_cxx 为true则输出后面内容
        "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
        )  # 定义 interface library
target_compile_features(tutorial_compiler_flags INTERFACE cxx_std_11)  # 设置 interface library 编译属性

option(USE_MYMATH "Use tutorial provided math implementation" ON)  # 默认值要在h.in文件前option，否则不会被应用
configure_file(TutorialConfig.h.in TutorialConfig.h)  # 从.in文件复制内容，填充内部变量并生成目标文件

if (USE_MYMATH)  # 条件语句
    add_subdirectory(MathFunctions)  # 使得cmake能递归处理子目录
    list(APPEND EXTRA_LIBS MathFunctions)  # 设置变量
endif ()

target_include_directories(Tutorial PUBLIC "${PROJECT_BINARY_DIR}")  # 将目标文件与库文件进行链接
target_link_libraries(Tutorial PUBLIC ${EXTRA_LIBS} tutorial_compiler_flags)  # 指定某个目标对应要链接的链接库