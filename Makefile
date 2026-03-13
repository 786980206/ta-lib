# Thin wrapper around CMake so you can run `make <target>` from the project root.
#
# Usage:
#   make                  Build library + all tools
#   make test             C reference regression tests
#   make regtest          Full cross-language regression tests
#   make regtest-only     Codegen verification only (skip C tests)
#   make servers          Generate + compile JSON-RPC language servers
#   make clean            Remove build directory
#   make help             Show all targets

BUILD_DIR  := cmake-build
BUILD_TYPE ?= Release
CMAKE_ARGS ?=
JOBS       ?= 4

# Ensure cmake-build exists and is configured
$(BUILD_DIR)/Makefile:
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) $(CMAKE_ARGS)

# Reconfigure if CMakeLists.txt changes
$(BUILD_DIR)/Makefile: CMakeLists.txt

.PHONY: all build test regtest regtest-only servers generate ta_regtest gen_code ta_codegen clean help

all: $(BUILD_DIR)/Makefile
	cd $(BUILD_DIR) && make -j$(JOBS)

build: all

ta_regtest: $(BUILD_DIR)/Makefile
	cd $(BUILD_DIR) && make ta_regtest -j$(JOBS) && make ensure_ta_regtest_in_bin

gen_code: $(BUILD_DIR)/Makefile
	cd $(BUILD_DIR) && make gen_code -j$(JOBS) && make ensure_gen_code_in_bin

generate: $(BUILD_DIR)/Makefile
	cd $(BUILD_DIR) && make ta_codegen_generate

servers: $(BUILD_DIR)/Makefile
	cd $(BUILD_DIR) && make ta_codegen_servers

ta_codegen: $(BUILD_DIR)/Makefile
	cd $(BUILD_DIR) && make ta_codegen_bin

test: $(BUILD_DIR)/Makefile
	cd $(BUILD_DIR) && make test

regtest: $(BUILD_DIR)/Makefile
	cd $(BUILD_DIR) && make regtest

regtest-only: $(BUILD_DIR)/Makefile
	cd $(BUILD_DIR) && make regtest-only

install: $(BUILD_DIR)/Makefile
	cd $(BUILD_DIR) && make install

package: $(BUILD_DIR)/Makefile
	cd $(BUILD_DIR) && make package

clean:
	rm -rf $(BUILD_DIR)

help:
	@echo "TA-Lib Build Targets"
	@echo ""
	@echo "  Building:"
	@echo "    make                Build library + all tools (default)"
	@echo "    make ta_regtest     Build the regression test runner"
	@echo "    make gen_code       Build the legacy C code generator"
	@echo "    make ta_codegen     Build the Rust codegen tool"
	@echo "    make generate       Generate per-function source for all backends"
	@echo "    make servers        Generate all source + compile JSON-RPC language servers"
	@echo ""
	@echo "  Testing:"
	@echo "    make test           C reference regression tests"
	@echo "    make regtest        Full pipeline: servers + C tests + codegen verification"
	@echo "    make regtest-only   Codegen verification only (skip C tests)"
	@echo ""
	@echo "  Other:"
	@echo "    make install        Install to system"
	@echo "    make package        Create distribution package"
	@echo "    make clean          Remove cmake-build/"
	@echo ""
	@echo "  Options:"
	@echo "    BUILD_TYPE=Debug    Set cmake build type (default: Release)"
	@echo "    JOBS=8              Parallel jobs (default: 4)"
