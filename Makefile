THIS_FILE := $(abspath $(lastword $(MAKEFILE_LIST)))
REPO_DIR := $(patsubst %/,%,$(dir $(THIS_FILE)))

.PHONY: all usage

all: usage

usage:
	@echo "Use 'make clang' or 'make gcc'."

#########
# clang #
#########

CLANG_BUILD_DIR := $(REPO_DIR)/build/clang
PREPARE_CLANG_BUILD_DIR_STAMP := $(CLANG_BUILD_DIR)/.prepare_clang_build_dir.stamp
PREPARE_CLANG_MAKE_FILES_STAMP := $(CLANG_BUILD_DIR)/.prepare_clang_make_files.stamp

.PHONY: clang prepare-clang build-clang clean-clang

clang: prepare-clang build-clang

prepare-clang: $(PREPARE_CLANG_BUILD_DIR_STAMP) $(PREPARE_CLANG_MAKE_FILES_STAMP)

build-clang:
	@$(MAKE) -C "$(CLANG_BUILD_DIR)"

$(PREPARE_CLANG_BUILD_DIR_STAMP):
	@mkdir -p "$(CLANG_BUILD_DIR)"
	@touch $@

$(PREPARE_CLANG_MAKE_FILES_STAMP): $(PREPARE_CLANG_BUILD_DIR_STAMP)
	@cd "$(CLANG_BUILD_DIR)" && CC=/usr/bin/clang CXX=/usr/bin/clang++ cmake -DCMAKE_USER_MAKE_RULES_OVERRIDE=$(REPO_DIR)/cmake/ClangOverrides.cmake ../../
	@touch $@

clean-clang:
	@rm -rf "$(CLANG_BUILD_DIR)"

#######
# gcc #
#######

GCC_BUILD_DIR := $(REPO_DIR)/build/gcc
PREPARE_GCC_BUILD_DIR_STAMP := $(GCC_BUILD_DIR)/.prepare_gcc_build_dir.stamp
PREPARE_GCC_MAKE_FILES_STAMP := $(GCC_BUILD_DIR)/.prepare_gcc_make_files.stamp

.PHONY: gcc prepare-gcc build-gcc clean-gcc

gcc: prepare-gcc build-gcc

prepare-gcc: $(PREPARE_GCC_BUILD_DIR_STAMP) $(PREPARE_GCC_MAKE_FILES_STAMP)

build-gcc:
	@$(MAKE) -C "$(GCC_BUILD_DIR)"

$(PREPARE_GCC_BUILD_DIR_STAMP):
	@mkdir -p "$(GCC_BUILD_DIR)"
	@touch $@

$(PREPARE_GCC_MAKE_FILES_STAMP): $(PREPARE_GCC_BUILD_DIR_STAMP)
	@cd "$(GCC_BUILD_DIR)" && cmake ../../
	@touch $@

clean-gcc:
	@rm -rf "$(GCC_BUILD_DIR)"

##########
# common #
##########

BUILD_DIR := $(REPO_DIR)/build

.PHONY: build-all clean-all

build-all: build-clang build-gcc

clean-all: clean-clang clean-gcc
	@rmdir $(BUILD_DIR)
