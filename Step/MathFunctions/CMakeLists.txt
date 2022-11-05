add_library(MathFunctions mysqrt.cpp)  # 指定源文件生成lib文件
# 我们希望其它链接到当前lib的include指定目录，而lib自能不include该目录，需要使用INTERFACE
# INTERFACE意味着消费者需要而生产者不需要
target_include_directories(MathFunctions INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(MathFunctions tutorial_compiler_flags)