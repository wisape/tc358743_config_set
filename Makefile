#export CC = arm-none-linux-gnueabi-gcc
export CC = gcc

CFLAGS= -I./ -fPIC -Wall -lm

src_file += 	tc358743_init.c  \
				tc358743_test.c


tc_vcam: $(src_file)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	@rm tc_vcam
