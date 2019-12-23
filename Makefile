NAME = rconf
OBJS = rconf-cli.o rconf.o
CFLAGS = -Wall -O2 -fstack-protector-strong -fpie -D_FORTIFY_SOURCE=2

$(NAME): $(OBJS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -vf $(NAME) *.o
