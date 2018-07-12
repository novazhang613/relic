INCLUDE(CMakeForceCompiler)

# this one is important
SET(CMAKE_SYSTEM_NAME Generic)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
CMAKE_FORCE_C_COMPILER(arm-none-eabi-gcc GNU)
CMAKE_FORCE_CXX_COMPILER(arm-none-eabi-g++ GNU)

# Where is the target environment.
# THIS IS IMPORTANT.
# To set this variable, look at where your cross compiler is installed with this command:
#   which arm-none-eabi-gcc
# If the result is /home/user/some/path/to/bin/arm-none-eabi-gcc, this path should be set as:
#   /home/user/some/path/to/arm-none-eabi
# Confirm that this directory exists!!
#SET(CMAKE_FIND_ROOT_PATH  /usr/bin/arm-none-eabi)
#SET(CMAKE_FIND_ROOT_PATH   /usr/lib/gcc-arm-none-eabi-4_9-2015q3/arm-none-eabi)
#SET(CMAKE_FIND_ROOT_PATH  /home/yiqun/tools/gcc-arm-none-eabi-7-2017-q4-major/bin/arm-none-eabi-gcc)
SET(CMAKE_FIND_ROOT_PATH  /home/yiqun/tools/gcc-arm-none-eabi-7-2017-q4-major)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
