#!/bin/sh
#
# Before running this, look at arm-non-eabi.cmake and configure your environment appropriately.

##############################
#### FOR ARM ARCHITECTURE ####
##############################

cmake -DCMAKE_TOOLCHAIN_FILE=arm-none-eabi.cmake \
      -DSHLIB=off \
      -DWORD=32 \
      -DARCH=ARM \
			-DCHECK=off \
			-DQUIET=on \
			-DWITH="EB;DV;FB;BN;MD" \
			-DSTRIP=on \
			-DSEED=ZERO \
			-DFB_PRECO=off \
       		-DVERBS=off \
			-DFB_METHD="LODAH;TABLE;BASIC;BASIC;BASIC;BASIC;BASIC;SLIDE;BASIC" \
			-DEB_METHD="PROJC;LWNAF;LWNAF;INTER" \
       		-DEB_PRECO=off \
      ..

#			-DFB_POLYN="233" \
# 			-DWITH="EB;DV;FB;BN;MD" \
## 			-DYIQUN=on \
# 			-DFB_METHD="LODAH;TABLE;QUICK;QUICK;QUICK;BASIC;BASIC;SLIDE;QUICK" \
##[YQ: after loading through the methods]
# 			-DFB_METHD="LODAH;TABLE;QUICK;QUICK;QUICK;QUICK;EXGCD;SLIDE;BASIC" \
# 			-DEB_METHD="PROJC;LWNAF;LWNAF;INTER" \
#			-DEC_METHD="CHAR2" \
##
#
##### FOR x86 ARCHITECTURE ####
###############################
#
#cmake -DSHLIB=off \
#      -DWORD=64 \
#			-DCHECK=off \
#			-DWITH="EB;DV;FB;BN;MD" \
#			-DSTRIP=on \
#			-DSEED=ZERO \
#			-DFB_PRECO=off \
# 			-DFB_METHD="LODAH;TABLE;BASIC;BASIC;BASIC;BASIC;BASIC;SLIDE;BASIC" \
#			-DDEBUG=on \
#			-DEB_METHD="PROJC;LWNAF;LWNAF;INTER" \
#      ..
#
###			-DFB_METHD="LODAH;TABLE;QUICK;QUICK;QUICK;BASIC;BASIC;SLIDE;QUICK" \
