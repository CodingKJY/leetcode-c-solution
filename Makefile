# =========================================================
# ======== Environment Variables
# =========================================================
SDIR := src

# =========================================================
# ======== Sources
# =========================================================
PROG_SRCS_y += $(SDIR)/main.c
PROBLEM_NUMBERS = $(notdir $(shell ls $(SDIR)/[0-9]*_*.c 2>/dev/null | sed 's/_.*\.c//' | sort -n))

# =========================================================
# ======== Targets
# =========================================================
TARGET    := test
CC        := $(CROSS_COMPILE)gcc
CFLAGS    := -O2 -I$(CURDIR)/include
LDFLAGS   := -lm
PROG_SRCS   := $(PROG_SRCS_y)

# =========================================================
# ======== Recipes
# =========================================================
list:
	@echo "Available LeetCode problems:"
	@echo "=========================="
	@for num in $(PROBLEM_NUMBERS); do \
		for f in $(SDIR)/$$num\_*.c; do \
			[ -f "$$f" ] || continue; \
			filename=$$(basename $$f); \
			title=$$(echo $$filename | sed 's/^[0-9]*_//' | sed 's/\.c$$//' | tr '_' ' '); \
			echo "  make $$num  - $$title"; \
			break; \
		done \
	done

define PROBLEM_RULE
$(1): $(shell ls $(SDIR)/$(1)_*.c 2>/dev/null | head -1)
	@if [ -z "$$<" ]; then \
		echo "Error: No file found for problem $(1)"; \
		echo "Expected filename pattern: $(1)_*.c"; \
		exit 1; \
	fi
	@echo "Compiling LeetCode problem $(1)"
	$(CC) $(CFLAGS) -o $(TARGET) $(PROG_SRCS) $$< $(LDFLAGS) || exit 1
	@echo "✓ Compiled successfully"
	@echo "------ Run Test ------"
	@./test
endef
$(foreach num,$(PROBLEM_NUMBERS),$(eval $(call PROBLEM_RULE,$(num))))

temp:
	@if [ -z "$(PROB)" ]; then \
		echo "Usage: make temp PROB=\"<number>. <problem_name>\""; \
		echo "Example: make temp PROB=\"1751. Maximum Number of Events That Can Be Attended II\""; \
		exit 1; \
	fi; \
	number=$$(echo "$(PROB)" | cut -d'.' -f1); \
	name=$$(echo "$(PROB)" | cut -d' ' -f2-); \
	filename="$${number}_$$(echo "$$name" | sed 's/ /_/g').c"; \
	if [ -f $(CURDIR)/src/$$filename ]; then \
		echo "Problem solution exists"; \
	else \
		cp src/template.c "src/$$filename"; \
	fi; \

clean:
	rm -rf  $(TARGET)

.PHONY: list clean