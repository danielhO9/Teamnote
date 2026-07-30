LATEXCMD ?= pdflatex
LATEXFLAGS ?= -interaction=nonstopmode -halt-on-error -shell-escape -output-directory=build/
export TEXINPUTS=.:content/tex/:
export max_print_line=1048576

.DEFAULT_GOAL := teamnote

help:
	@echo "Build the GENGFaker team note."
	@echo ""
	@echo "Available commands are:"
	@echo "	make fast          - build once"
	@echo "	make teamnote      - build twice for a stable table of contents"
	@echo "	make check         - validate import paths and build the document"
	@echo "	make clean         - remove intermediate build files"
	@echo "	make veryclean     - also remove generated PDFs"
	@echo "	make showexcluded  - list source files not included in the document"

fast: | build
	$(LATEXCMD) $(LATEXFLAGS) content/teamnote.tex </dev/null
	cp build/teamnote.pdf teamnote.pdf

teamnote: test-session.pdf | build
	$(LATEXCMD) $(LATEXFLAGS) content/teamnote.tex </dev/null
	$(LATEXCMD) $(LATEXFLAGS) content/teamnote.tex </dev/null
	cp build/teamnote.pdf teamnote.pdf

clean:
	rm -rf build
	rm -f header.tmp

veryclean: clean
	rm -f teamnote.pdf test-session.pdf

.PHONY: help fast teamnote check clean veryclean showexcluded

build:
	mkdir -p build/

check:
	python3 scripts/check_imports.py
	$(MAKE) teamnote

test-session.pdf: content/test-session/test-session.tex content/test-session/chapter.tex | build
	$(LATEXCMD) $(LATEXFLAGS) content/test-session/test-session.tex </dev/null
	cp build/test-session.pdf test-session.pdf

showexcluded: build
	grep -RoPh '^\s*\\kactlimport{\K.*' content/ | sed 's/.$$//' > build/headers_included
	find ./content \( -name "*.h" -o -name "*.py" -o -name "*.java" \) | grep -vFf build/headers_included
