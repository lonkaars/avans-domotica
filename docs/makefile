PANDOC = pandoc
CAT = cat
M4 = m4
RM = rm -f
CHROME = chromium
CURL = curl
PUP = pup

SRCS = $(wildcard *.md)
HTML_T = $(patsubst %.md,%.html, $(SRCS))
PDF_T = $(patsubst %.md,%.pdf, $(SRCS))

.PRECIOUS: %.toc

all: $(HTML_T)

gen/paged.polyfill.js:
	$(CURL) -Ls https://unpkg.com/pagedjs/dist/paged.polyfill.js > $@

gen/start.html: gen/start.m4 gen/style.css
	$(M4) -I gen $< > $@

%.html: %.md %.toc gen/start.html gen/paged.polyfill.js
	$(PANDOC) $< --to=html | $(CAT) gen/start.html $(word 2,$^) - gen/end.html > $@

%.toc: %.md
	$(PANDOC) $< -s --toc --to=html 2> /dev/null | $(PUP) '#TOC' | sed -r 's/<(.?)ul>/<\1ol>/g' > $@

%.pdf: %.html
	$(CHROME) --headless --print-to-pdf=$@ $< 2> /dev/null

clean:
	$(RM) $(HTML_T) $(PDF_T) gen/start.html gen/paged.polyfill.js
