BUILD_TYPE ?= RELWITHDEBINFO
BUILD_TYPE_LC := $(shell echo $(BUILD_TYPE) | tr A-Z a-z)
BUILD_DIR := build_type/$(BUILD_TYPE_LC)
OUTPUT_DIR := build_output/$(BUILD_TYPE_LC)
OUTPUT_BIN_DIR := $(OUTPUT_DIR)/bin
OUTPUT_LIB_DIR := $(OUTPUT_DIR)/lib
OUTPUT_UNIT_TEST_DIR := $(OUTPUT_DIR)/unit_test
OUTPUT_DIR_JS := build_output/javascript
ECHO := /bin/echo

###############################################################################
# all
###############################################################################

all: check_build_type_directory \
     make_bin_lib_directories \
     make_unit_test_directory \
     build_all
.PHONY: all \
        check_build_type_directory \
        make_bin_lib_directories \
        make_unit_test_directory \
        build_all

check_build_type_directory:
	@test -d $(BUILD_DIR) || ($(ECHO) -e "\nError: $(BUILD_DIR) is missing, execute:\nmake update BUILD_TYPE=$(BUILD_TYPE_LC)\n" && exit 1)
	@$(ECHO)

make_bin_lib_directories:
	@mkdir -p $(OUTPUT_BIN_DIR)
	@mkdir -p $(OUTPUT_LIB_DIR)

make_unit_test_directory:
	@mkdir -p $(OUTPUT_UNIT_TEST_DIR)

build_all:
	@$(ECHO) "build type: $(BUILD_TYPE_LC)"
	@$(MAKE) --no-print-directory -C $(BUILD_DIR)

###############################################################################
# update
###############################################################################

update: make_build_type_directory \
        call_cmake
.PHONY: update \
        make_build_type_directory \
        call_cmake

make_build_type_directory:
	@mkdir -p $(BUILD_DIR)

call_cmake:
	@$(ECHO) "Build Type: $(BUILD_TYPE_LC)"
	@cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE_LC) ../../

###############################################################################
# native
###############################################################################

native: check_build_type_directory \
        make_bin_lib_directories \
        build_box123
.PHONY: build_box123

build_box123:
	@$(MAKE) box123 --no-print-directory -C $(BUILD_DIR)

###############################################################################
# javascript
###############################################################################

javascript: make_javascript_output_directory \
            build_box123_javascript

.PHONY: make_javascript_output_directory \
        build_box123_javascript

make_javascript_output_directory:
	@mkdir -p $(OUTPUT_DIR_JS)

build_box123_javascript:
	/home/pepi/src/git/emscripten/emcc \
		-O1 \
		-I libbox123logger \
		-I libbox123video  \
		-I include \
		-I libbox123eventlogic \
		box123/*.cpp libbox123*/*.cpp -o $(OUTPUT_DIR_JS)/box123.html

###############################################################################
# run
###############################################################################

run: native \
     run_box123
.PHONY: run_box123

run_box123:
	@$(ECHO) -e "\nBuild Type: $(BUILD_TYPE_LC)"
	@./$(OUTPUT_BIN_DIR)/box123

###############################################################################
# test
###############################################################################

test: check_build_type_directory \
      make_unit_test_directory \
      build_unit_test \
      run_unit_test
.PHONY: test \
        make_unit_test_directory \
        build_unit_test \
        run_unit_test

build_unit_test:
	@$(MAKE) box123_unit_test --no-print-directory -C $(BUILD_DIR)

run_unit_test:
	@$(ECHO) -e "\nBuild Type: $(BUILD_TYPE_LC)"
	@./$(OUTPUT_UNIT_TEST_DIR)/box123_unit_test --show_progress=yes --log_level=nothing

###############################################################################
# test_detailed
###############################################################################

test_detailed: check_build_type_directory \
               build_unit_test \
               run_unit_test_detailed
.PHONY: run_unit_test_detailed

run_unit_test_detailed:
	@$(ECHO) -e "\nBuild Type: $(BUILD_TYPE_LC)"
	@./$(OUTPUT_UNIT_TEST_DIR)/box123_unit_test --build_info=yes --log_level=all

###############################################################################
# clean
###############################################################################

clean: check_build_type_directory \
       cmake_clean
.PHONY: cmake_clean

cmake_clean:
	@$(MAKE) --no-print-directory -C $(BUILD_DIR) clean

###############################################################################
# clean_all
###############################################################################

clean_all: clean_output \
           check_build_type_directory \
           cmake_clean \
           clean_build_type_directory
.PHONY: clean_output \
        clean_build_type_directory

clean_output:
	@rm -rf $(OUTPUT_DIR)
	@test -z "$(ls build_output)" && rm -rf build_output

clean_build_type_directory:
	@rm -rf $(BUILD_DIR)
	@test -z "$(ls build_type)" && rm -rf build_type
