BUILD_TYPE ?= RELWITHDEBINFO
BUILD_DIR := build_type/$(shell echo ${BUILD_TYPE} | tr a-z A-Z)

.PHONY: all
all:
	@$(MAKE) --no-print-directory -C $(BUILD_DIR)

.PHONY: unit_test
unit_test:
	@$(MAKE) box123_unit_test --no-print-directory -C $(BUILD_DIR)

.PHONY: test
test: unit_test
	@echo -e "\nBuild Type: ${BUILD_TYPE}"
	@./build_output/${BUILD_TYPE}/unit_test/box123_unit_test --show_progress=yes --log_level=nothing

.PHONY: test_detailed
test_detailed: all
	@echo -e "\nBuild Type: ${BUILD_TYPE}"
	@./build_output/${BUILD_TYPE}/unit_test/box123_unit_test --build_info=yes --log_level=all

.PHONY: update
update:
	@echo "Build Type: ${BUILD_TYPE}"
	@cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ../../

.PHONY: clean
clean:
	@$(MAKE) --no-print-directory -C $(BUILD_DIR) clean

