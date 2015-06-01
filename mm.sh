#!/bin/sh

PROJECT_REPO_DIR=$(dirname $(readlink -e ${0}))
cd "${PROJECT_REPO_DIR}"

if [ ${#} -ne 1 ]; then
    echo "Expected number of arguments is: 1, got: ${#}"
    exit 1
fi

if [ "${1}" != "clang" ] && [ "${1}" != "gcc" ]; then
    echo "Expected 'clang' or 'gcc' argument, got: '${1}'"
    exit 1
fi

BUILD_DIR="build/${1}"
mkdir -p "${BUILD_DIR}"

if [ "${1}" == "clang" ]; then
    cd "${BUILD_DIR}"
    export CC=/usr/bin/clang
    export CXX=/usr/bin/clang++
    cmake -DCMAKE_USER_MAKE_RULES_OVERRIDE=${PROJECT_REPO_DIR}/cmake/ClangOverrides.cmake ../../
    exit 0
fi

if [ "${1}" == "gcc" ]; then
    cd "${BUILD_DIR}"
    cmake ../../
    exit 0
fi
