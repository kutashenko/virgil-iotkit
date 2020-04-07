#!/bin/bash

#
#   Global variables
#
SCRIPT_FOLDER="$( cd "$( dirname "$0" )" && pwd )"
. ${SCRIPT_FOLDER}/ish/error.ish

CRYPTO_C_DIR="${SCRIPT_FOLDER}/../ext/virgil-crypto-c"
BUILD_DIR_BASE="${CRYPTO_C_DIR}"
CMAKE_CUSTOM_PARAM="${@}"

if [[ $@ == *"mingw32.toolchain.cmake"* ]]; then
  AR_TOOLS="i686-w64-mingw32-ar"
  OBJ_EXT="obj"
elif [[ $@ == *"android.toolchain.cmake"* ]]; then
  AR_TOOLS="/Users/kutashenko/android-ndk-r20b/toolchains/aarch64-linux-android-4.9/prebuilt/darwin-x86_64/bin/aarch64-linux-android-ar"
  OBJ_EXT="o"
else
  AR_TOOLS="ar"
  OBJ_EXT="o"
  [ "$(arch)" == "x86_64" ] && LIB_ARCH="64" || LIB_ARCH=""
fi

. ${SCRIPT_FOLDER}/ish/lib-utils.ish

#
#   Arguments
#
PLATFORM="host"

#
#   Build
#
function build() {
    local BUILD_TYPE=$1
    local CMAKE_ARGUMENTS=$2
    local CORES=10

    local BUILD_DIR=${BUILD_DIR_BASE}/cmake-build-${PLATFORM}/${BUILD_TYPE}
    local INSTALL_DIR=${BUILD_DIR_BASE}/cmake-build-${PLATFORM}/${BUILD_TYPE}/installed
    local LIBS_DIR=${INSTALL_DIR}/usr/local/lib${LIB_ARCH}

    echo
    echo "===================================="
    echo "=== ${PLATFORM} ${BUILD_TYPE} build"
    echo "=== Output directory: ${BUILD_DIR}"
    echo "===================================="
    echo

    rm -rf ${BUILD_DIR}
    mkdir -p ${BUILD_DIR}
    mkdir -p ${INSTALL_DIR}

    pushd ${BUILD_DIR}
      # prepare to build
      echo "==========="
      echo "=== Run CMAKE "
      echo "==========="
      cmake ${BUILD_DIR_BASE} ${CMAKE_ARGUMENTS} -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -G "Unix Makefiles"
      check_error

      # build all targets
      echo "==========="
      echo "=== Building"
      echo "==========="
      make -j ${CORES}
      check_error

      # install all targets
      echo "==========="
      echo "=== Installing"
      echo "==========="
      make DESTDIR=${INSTALL_DIR} install
      check_error

      pack_libs ${LIBS_DIR} "libed25519.a libmbedcrypto.a libprotobuf-nanopb.a libvsc_common.a libvsc_foundation.a libvsc_foundation_pb.a" "libvscryptoc.a"

    popd
}

# Common CMake arguments for the project
CMAKE_ARGUMENTS="-DCMAKE_CXX_FLAGS='-fvisibility=hidden' -DCMAKE_C_FLAGS='-fvisibility=hidden' \
-DENABLE_CLANGFORMAT=OFF \
-DENABLE_CLANGFORMAT=OFF \
-DVIRGIL_PHP_TESTING=OFF \
-DVIRGIL_LIB_PYTHIA=OFF \
-DVIRGIL_LIB_RATCHET=OFF \
-DVIRGIL_LIB_PHE=OFF \
-DVIRGIL_POST_QUANTUM=OFF \
${CMAKE_CUSTOM_PARAM}"

#
#   Build both Debug and Release
#
build "release" "${CMAKE_ARGUMENTS}"