# Add all your champion files in here, separated by spaces
# Include all the sources (must end with *.cc), headers (must end with .hh) and
# README files.
CHAMPION_FILES = champion.cc \
				ducktroop.hh ducktroop.cc \
				ducktroop-baker.hh ducktroop-baker.cc \
				ducktroop-rusher.hh ducktroop-rusher.cc \
				env.hh env.cc \
				strategy.hh strategy.cc \
				strategy-test.hh  strategy-test.cc \
				utils.hh utils.cc 

# ----
# Do not modify the lines below

CHAMPION_FILES += interface.cc api.hh
-include Makefile-cxx

fight:
	stechec2-run config.yml

debug:
	stechec2-run -d 1 config.yml
