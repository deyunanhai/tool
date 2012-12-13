SRC_DIR = .
OBJ_DIR = obj
PROG_FLODERS = \
	JSTools

all: recursive
	@for i in $(PROG_FLODERS); do \
		$(MAKE) -C "$$i"; \
	done

recursive:

clean:
	for i in $(PROG_FLODERS); do \
		rm -rf $(OBJ_DIR)
	done
