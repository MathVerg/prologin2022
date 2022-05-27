# Add all your champion files in here, separated by spaces
# Include all the sources (must end with *.cc), headers (must end with .hh) and
# README files.
CHAMPION_FILES = champion.cc utils.hh utils.cc

# ----
# Do not modify the lines below

fight:
	stechec2-run config.yml

CHAMPION_FILES += interface.cc api.hh
-include Makefile-cxx
