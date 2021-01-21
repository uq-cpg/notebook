TEX_CMD   := latexmk
OPTIONS   := -shell-escape -synctex=1 -interaction=nonstopmode \
			-file-line-error -pdf -g
TEX_FILES := $(wildcard *.tex)
MAIN      := main.tex
SOURCES   := $(shell find $(SOURCEDIR) -name '*.cc') \
		     $(shell find $(SOURCEDIR) -name '*.cpp') \
		     $(shell find $(SOURCEDIR) -name '*.h') \
		     $(shell find $(SOURCEDIR) -name '*.hpp') \
		     $(shell find $(SOURCEDIR) -name 'Makefile')


main.pdf: $(TEX_FILES) $(SOURCES)
	$(TEX_CMD) $(OPTIONS) $(MAIN)