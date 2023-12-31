#Makefile

CC = gcc
CPPFLAGS= `pkg-config --cflags sdl` `pkg-config --cflags gtk+-3.0` -MMD
CFLAGS = -Wall -Wextra -std=c99
LDLIBS = -lSDL -lSDL_image -lm `pkg-config --libs sdl` `pkg-config --libs gtk+-3.0`

# SRC contain all the file we must build
SRC = $(shell find src -type f -name "*.c")

OBJ_DEP_DIR = obj_dep
OBJ = $(patsubst %.c, $(OBJ_DEP_DIR)/%.o, $(SRC))

DEP_DIR = dependence
DEP = $(OBJ:.o=.d)

-include $(DEP)

# All bmp file generate by the program
BMP = $(shell find ./image_data -type f -name "*.bmp") 

# All exec we want to clean
EXEC = OCR

# Shortcut name
SHORTCUT = doc.html

# doxygen repo
DOXYGEN_DIR = doxygen

# doxygen documentation
define generate_doxygen
	@$(RM) -rf $(DOXYGEN_DIR)/html
	@$(RM) $(SHORTCUT)
	doxygen
endef

# Create shortcut to index.html
define generate_shortcut
	@ln -s $(DOXYGEN_DIR)/html/index.html $(SHORTCUT)
endef

# Open documentation in browser
define open_doc
	@xdg-open $(SHORTCUT)
endef

# doxygen documentation and shortcut
.PHONY: doxygen
doxygen:	## Generate html documentation and shortcut doc.html.
	@$(call generate_doxygen)
	@$(call generate_shortcut)

# same as rules doc but open the doc in the default browser
.PHONY: doc
doc: doxygen	## Generate html documentation and open it in your default browser.
	@$(call open_doc)

OCR: $(EXEC).c $(OBJ) ## Generate the executable and launch the interface.

$(OBJ_DEP_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDLIBS) -o $@ -c $<

# Help function to use the makefile
# It "just" detect every rules in this makefile and the print it

help:	## It... display help... obviously.
	@grep -E '^[a-zA-Z0-9]+:.*##' makefile | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-15s\033[0m%s\n", $$1, $$2}'

#default rules is help
.DEFAULT_GOAL := help

# Clean

clean:	## Clean every .o and .d.
	@$(RM) $(OBJ) $(DEP) $(EXEC).o $(EXEC).d

mrproper: clean 	## Clean every .o and .d as well as all generated files.
	@$(RM) $(EXEC) $(BMP) $(SHORTCUT) 
	@$(RM) -rf $(DOXYGEN_DIR)/html
	@$(RM) *.txt
