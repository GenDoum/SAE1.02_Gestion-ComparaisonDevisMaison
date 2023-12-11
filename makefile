GCCFLAGS = -Wall -Wextra -pedantic -Isrc -g -MMD -MP
BUILD_DIR = build
SOURCES = $(shell find src -name '*.c')
TARGETS = $(patsubst %.c, %.o, $(SOURCES))
TARGETS := $(addprefix $(BUILD_DIR)/, $(TARGETS))
APP_NAME = app
DOXYGEN_CONFIG = docs/Doxyfile.in

GREEN = \033[0;32m
RESET = \033[0m

# Règle pour générer les dépendances
$(BUILD_DIR)/%.d: %.c
	@mkdir -p $(@D)
	@$(CC) $(GCCFLAGS) -MM -MF $@ -MP -MT $(BUILD_DIR)/$*.o -MT $@ $(CPPFLAGS) $(CFLAGS) $<

all: $(APP_NAME)

$(APP_NAME): $(TARGETS)
	@gcc $(GCCFLAGS) -o $(APP_NAME) $(TARGETS)
	@echo -e build done.

$(TARGETS): $(SOURCES)
	@mkdir -p $(@D)
	@gcc $(GCCFLAGS) -c $(patsubst %.o, %.c, $(@:$(BUILD_DIR)/%=%)) -o $@

# Inclure les fichiers de dépendance générés
-include $(TARGETS:.o=.d)

# Ajout de la règle pour afficher les dépendances
show-dependencies:
	@cat $(TARGETS:.o=.d)

clean:
	@rm -rf $(BUILD_DIR) $(APP_NAME)
	@rm -rf docs/html docs/latex
	@echo clean done.

docs:
	@doxygen $(DOXYGEN_CONFIG)
	@echo docs done.