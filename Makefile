ifeq ($(PREFIX),)
    PREFIX := ~/.local
endif

ds360: ds360.cpp
	g++ -Wall -o ds360 ds360.cpp

install: ds360
	install -m 555 ds360 $(PREFIX)/bin/