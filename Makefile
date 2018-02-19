# Author: Svätopluk Hanzel
# Created on May the 4th, 2017 (pun intended)

include Makefile.vars

.PHONY: clean

all: gui cli docs

merlin:
	make -f Makefile.merlin

# Geneartes the GUI version of this application
gui: generate-gui make-gui
generate-gui: $(PROJECT_FILE)
	$(QMAKE) $(PROJECT_FILE) -spec linux-g++ MAKEFILE=$(GUI_MAKEFILE) OBJECTS_DIR=$(GUI_BUILD_DIR) MOC_DIR=$(GUI_BUILD_DIR) UI_DIR=$(GUI_BUILD_DIR) RCC_DIR=$(GUI_BUILD_DIR) DESTDIR=$(GUI_RELEASE_DIR)
make-gui:
	make -f $(GUI_MAKEFILE)
	mv $(GUI_RELEASE_DIR)/$(PROJECT_NAME) $(GUI_RELEASE_DIR)/$(GUI_BINARY)


# Generates the CLI version of this application
cli: generate-cli make-cli
generate-cli: $(PROJECT_FILE)
	$(QMAKE) $(PROJECT_FILE) -spec linux-g++ MAKEFILE=$(CLI_MAKEFILE) OBJECTS_DIR=$(CLI_BUILD_DIR) MOC_DIR=$(CLI_BUILD_DIR) UI_DIR=$(CLI_BUILD_DIR) RCC_DIR=$(CLI_BUILD_DIR) DESTDIR=$(CLI_RELEASE_DIR) DEFINES+=KLONDIKE_CLI
make-cli:
	make -f $(CLI_MAKEFILE)
	mv $(CLI_RELEASE_DIR)/$(PROJECT_NAME) $(CLI_RELEASE_DIR)/$(CLI_BINARY)

run: gui cli
	$(GUI_RELEASE_DIR)/$(GUI_BINARY) &
	$(CLI_RELEASE_DIR)/$(CLI_BINARY)

#
# Generate documentation
#

# alias
doxygen: docs
docs:
	doxygen

# Cleans build files
clean:
	rm -rf './build';
	rm -rf './docs';
	test -f $(GUI_MAKEFILE) && rm $(GUI_MAKEFILE) || true
	test -f $(CLI_MAKEFILE) && rm $(CLI_MAKEFILE) || true

pack:
	tar zcf xhanze10.tar.gz src/ examples/ Makefile Makefile.vars Makefile.merlin Doxyfile README.txt
