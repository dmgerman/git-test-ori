MAN1_TXT=$(wildcard git-*.txt)
MAN7_TXT=git.txt

DOC_HTML=$(patsubst %.txt,%.html,$(MAN1_TXT) $(MAN7_TXT))

DOC_MAN1=$(patsubst %.txt,%.1,$(MAN1_TXT))
DOC_MAN7=$(patsubst %.txt,%.7,$(MAN7_TXT))

prefix=$(HOME)
bin=$(prefix)/bin
mandir=$(prefix)/man
man1=$(mandir)/man1
man7=$(mandir)/man7

INSTALL=install

#
# Please note that there is a minor bug in asciidoc.
# The version after 6.0.3 _will_ include the patch found here:
#   http://marc.theaimsgroup.com/?l=git&m=111558757202243&w=2
#
# Until that version is released you may have to apply the patch
# yourself - yes, all 6 characters of it!
#

all: html man

html: $(DOC_HTML)


man: man1 man7
man1: $(DOC_MAN1)
man7: $(DOC_MAN7)

install:
	$(INSTALL) -m755 -d $(dest)/$(man1) $(dest)/$(man7)
	$(INSTALL) $(DOC_MAN1) $(dest)/$(man1)
	$(INSTALL) $(DOC_MAN7) $(dest)/$(man7)

# 'include' dependencies
git-diff-%.txt: diff-format.txt diff-options.txt
	touch $@

clean:
	rm -f *.xml *.html *.1 *.7

%.html : %.txt
	asciidoc -b xhtml11 -d manpage $<

%.1 %.7 : %.xml
	xmlto man $<

%.xml : %.txt
	asciidoc -b docbook -d manpage $<
