PANDOC = pandoc
CAT = cat
M4 = m4
RM = rm -f
CHROME = chromium
CURL = curl

SRCS = $(wildcard *.md)
HTML_T = $(patsubst %.md,%.html, $(SRCS))
PDF_T = $(patsubst %.md,%.pdf, $(SRCS))

all: $(HTML_T)

gen/paged.polyfill.js:
	$(CURL) -Ls https://unpkg.com/pagedjs/dist/paged.polyfill.js > $@

gen/start.html: gen/start.m4 gen/style.css
	$(M4) -I gen $< > $@

%.html: %.md gen/start.html
	$(PANDOC) $< --to=html | $(CAT) gen/start.html - gen/end.html > $@

%.pdf: %.html
	$(CHROME) --headless --print-to-pdf=$@ $< 2> /dev/null

clean:
	$(RM) $(HTML_T) $(PDF_T) gen/start.html gen/paged.polyfill.js
