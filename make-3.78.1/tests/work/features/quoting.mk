SHELL = /bin/sh
TEXFONTS = NICEFONT
DEFINES = -DDEFAULT_TFM_PATH=\".:$(TEXFONTS)\"
test: ; @"echo" 'DEFINES = $(DEFINES)'
