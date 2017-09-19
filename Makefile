IDIR =.
CC=gcc
CFLAGS=-I$(IDIR) -L/opt/appdynamics-sdk-native/sdk_lib/lib

ODIR=obj

LIBS=-lappdynamics_native_sdk

DEPS = 

_OBJ = c_app.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

c_app: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~