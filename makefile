ku: ku.c
	gcc -o ku ku.c

install: ku
	cp -rf ku /usr/bin/

remove:
	rm -rf /usr/bin/ku

clean:
	rm -rf ku

.PHONY: clean
