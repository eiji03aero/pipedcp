MAIN_NAME = pipedcp

.PHONY: build
build:
	@cd build \
		&& make

.PHONY: build-cmake
build-cmake:
	@cd build \
		&& cmake ..

.PHONY: test
test:
	@cd build \
		&& ctest

.PHONY: test-unit
test-unit:
	@cd build \
		&& $(MAKE) $(TEST_NAME) \
		&& ./$(TEST_NAME)

.PHONY: dev
dev:
	@cd build \
		&& make $(MAIN_NAME)\
		&& ./$(MAIN_NAME)

.PHONY: watch
watch:
	@reflex \
		-r '(\.cpp|\.h)' \
		-s $(MAKE) $(COMMAND)

.PHONY: clean
clean:
	@rm -rf ./build/*
