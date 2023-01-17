PROG = gnss_uart_read
SRCS = gnss_uart_read.c

CLEANFILES = $(PROG)

# Add / change option in CFLAGS and LDFLAGS
#CFLAGS += -Wall $(shell pkg-config --cflags gtk+-3.0)
CFLAGS += -Wall 
#LDFLAGS += $(shell pkg-config --libs)
#LDFLAGS += $(shell pkg-config --libs gtk+-3.0)

all: $(PROG)

$(PROG): $(SRCS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(CLEANFILES) $(patsubst %.c,%.o, $(SRCS))
