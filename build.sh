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

cd "build/${1}"
make
