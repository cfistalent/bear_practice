SUBDIRS = $(shell ls -d */ | grep -v 'bin' | grep -v 'inc')

all:
	@for d in $(SUBDIRS); do (cd $$d && make) || exit 1; done

clean:
	@for d in $(SUBDIRS); do (cd $$d && make clean) || exit 1; done

.PHONY:clean

