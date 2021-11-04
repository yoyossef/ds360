ifeq ($(PREFIX),)
    PREFIX := ~/.local
endif

ds360: ds360.cpp
	g++ -Wall -o ds360 ds360.cpp

install: ds360
	install -m 555 ds360 $(PREFIX)/bin/
	install -m 444 ds360.service $(HOME)/.config/systemd/user/
	systemctl --user daemon-reload

uninstall:
	rm -f $(PREFIX)/bin/ds360
	rm -f $(HOME)/.config/systemd/user/ds360.service
	systemctl --user daemon-reload
	sudo rm -f /usr/lib/udev/rules.d/80-ds360.rules
	sudo udevadm control --reload