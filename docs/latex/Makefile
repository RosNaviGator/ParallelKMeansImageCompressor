LATEX_CMD ?= pdflatex
MKIDX_CMD ?= makeindex
BIBTEX_CMD ?= bibtex
LATEX_COUNT ?= 8
MANUAL_FILE ?= refman


OUTPUT_PDF_NAME ?= doxygen.pdf
OUTPUT_PDF_PATH ?= ../../


all: $(OUTPUT_PDF_PATH)/$(OUTPUT_PDF_NAME)

pdf: $(OUTPUT_PDF_PATH)/$(OUTPUT_PDF_NAME)

$(OUTPUT_PDF_PATH)/$(OUTPUT_PDF_NAME): clean $(MANUAL_FILE).tex
	$(LATEX_CMD) $(MANUAL_FILE)
	$(MKIDX_CMD) $(MANUAL_FILE).idx
	$(LATEX_CMD) $(MANUAL_FILE)
	latex_count=$(LATEX_COUNT) ; \
	while grep -E -s 'Rerun (LaTeX|to get cross-references right|to get bibliographical references right)' $(MANUAL_FILE).log && [ $$latex_count -gt 0 ] ;\
	do \
		echo "Rerunning latex...." ;\
		$(LATEX_CMD) $(MANUAL_FILE) ;\
		latex_count=`expr $$latex_count - 1` ;\
	done
	$(MKIDX_CMD) $(MANUAL_FILE).idx
	$(LATEX_CMD) $(MANUAL_FILE)
	# Create the output directory if it doesn't exist
	mkdir -p $(OUTPUT_PDF_PATH)
	# Move and rename the PDF to the specified path and name
	mv $(MANUAL_FILE).pdf $(OUTPUT_PDF_PATH)/$(OUTPUT_PDF_NAME)

clean:
	rm -f *.ps *.dvi *.aux *.toc *.idx *.ind *.ilg *.log *.out *.brf *.blg *.bbl $(MANUAL_FILE).pdf
