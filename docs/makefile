PANDOC = pandoc
M4 = m4
RM = rm -f
CHROME = chromium
CURL = curl
PUP = pup

SRCS = $(wildcard *.md)
HTML_T = $(patsubst %.md,%.html, $(SRCS))
PDF_T = $(patsubst %.md,%.pdf, $(SRCS))

.PRECIOUS: %.toc %.con

all: $(HTML_T)

gen/paged.polyfill.js:
	$(CURL) -Ls https://unpkg.com/pagedjs/dist/paged.polyfill.js > $@

%.con: %.md
	$(PANDOC) $< --to=html > $@

%.toc: %.md
	$(PANDOC) $< -s --toc --to=html 2> /dev/null | $(PUP) '#TOC' | sed -r 's/<(.?)ul>/<\1ol>/g' > $@

%.html: %.con %.toc gen/doc.m4 gen/paged.polyfill.js gen/style.css
	$(M4) -DNAME=$(basename $<) gen/doc.m4 > $@

%.pdf: %.html
	$(CHROME) --headless --print-to-pdf=$@ $< 2> /dev/null

clean:
	$(RM) $(HTML_T) $(PDF_T) *.toc *.con gen/paged.polyfill.js
