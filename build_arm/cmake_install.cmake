# Install script for directory: /home/yiqun/adi/relic-master-SS

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/relic" TYPE FILE FILES
    "/home/yiqun/adi/relic-master-SS/include/relic_pool.h"
    "/home/yiqun/adi/relic-master-SS/include/relic_epx.h"
    "/home/yiqun/adi/relic-master-SS/include/relic_test.h"
    "/home/yiqun/adi/relic-master-SS/include/relic_arch.h"
    "/home/yiqun/adi/relic-master-SS/include/relic_cp.h"
    "/home/yiqun/adi/relic-master-SS/include/relic_dv.h"
    "/home/yiqun/adi/relic-master-SS/include/relic.h"
    "/home/yiqun/adi/relic-master-SS/include/relic_types.h"
    "/home/yiqun/adi/relic-master-SS/include/relic_ep.h"
    "/home/yiqun/adi/relic-master-SS/include/relic_fpx.h"
    "/home/yiqun/adi/relic-master-SS/include/relic_ed.h"
    "/home/yiqun/adi/relic-master-SS/include/recryptor.h"
    "/home/yiqun/adi/relic-master-SS/include/relic_pp.h"
    "/home/yiqun/adi/relic-master-SS/include/relic_rand.h"
    "/home/yiqun/adi/relic-master-SS/include/relic_fbx.h"
    "/home/yiqun/adi/relic-master-SS/include/relic_ec.h"
    "/home/yiqun/adi/relic-master-SS/include/relic_bench.h"
    "/home/yiqun/adi/relic-master-SS/include/relic_util.h"
    "/home/yiqun/adi/relic-master-SS/include/relic_err.h"
    "/home/yiqun/adi/relic-master-SS/include/relic_label.h"
    "/home/yiqun/adi/relic-master-SS/include/relic_pc.h"
    "/home/yiqun/adi/relic-master-SS/include/relic_md.h"
    "/home/yiqun/adi/relic-master-SS/include/relic_fp.h"
    "/home/yiqun/adi/relic-master-SS/include/relic_eb.h"
    "/home/yiqun/adi/relic-master-SS/include/relic_core.h"
    "/home/yiqun/adi/relic-master-SS/include/relic_bc.h"
    "/home/yiqun/adi/relic-master-SS/include/relic_bn.h"
    "/home/yiqun/adi/relic-master-SS/include/relic_trace.h"
    "/home/yiqun/adi/relic-master-SS/include/relic_fb.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/relic/low" TYPE FILE FILES
    "/home/yiqun/adi/relic-master-SS/include/low/relic_fpx_low.h"
    "/home/yiqun/adi/relic-master-SS/include/low/relic_bn_low.h"
    "/home/yiqun/adi/relic-master-SS/include/low/relic_fb_low.h"
    "/home/yiqun/adi/relic-master-SS/include/low/relic_fp_low.h"
    "/home/yiqun/adi/relic-master-SS/include/low/relic_dv_low.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/relic" TYPE DIRECTORY FILES "/home/yiqun/adi/relic-master-SS/build_arm/include/")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/yiqun/adi/relic-master-SS/build_arm/src/cmake_install.cmake")
  include("/home/yiqun/adi/relic-master-SS/build_arm/test/cmake_install.cmake")
  include("/home/yiqun/adi/relic-master-SS/build_arm/bench/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/yiqun/adi/relic-master-SS/build_arm/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
