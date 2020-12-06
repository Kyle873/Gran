TARGET  = Gran

OBJS    = CSV.o \
          Memory.o \
          Nova.o \
          Settings.o \
          Log.o \
          Font.o \
          Main.o \
          Thread.o \
          Input.o \
          Draw.o \
          Menu.o

LIBS    = -lm \
          -lSceCtrl_stub \
          -lSceDisplay_stub \
          -lSceLibc_stub

PREFIX  = arm-vita-eabi
CC      = $(PREFIX)-gcc
CFLAGS  = -Wl,-q -Wall -O2 -g -nostartfiles -std=c11
ASFLAGS = $(CFLAGS)

IP      = 192.168.0.248:1337

all: $(TARGET).suprx

%.suprx: %.velf
	vita-make-fself $< $@

%.velf: %.elf
	vita-elf-create $< $@

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

clean:
	@rm -rf $(TARGET).suprx $(TARGET).velf $(TARGET).elf $(OBJS)

send: $(TARGET).suprx
	curl -T $(TARGET).suprx ftp://$(IP)/ur0:/tai/$(TARGET).suprx
	@echo "$(TARGET) sent."
