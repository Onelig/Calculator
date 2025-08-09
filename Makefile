BUILD_DIR = build

all: install

install:
	@echo "=== INSTALLATION ==="
	@conan install . --build=missing
	@conan build .

clean:
	@echo "Cleaning build directories..."
	@if [ -d $(BUILD_DIR) ]; then \
		rm -rf $(BUILD_DIR); fi