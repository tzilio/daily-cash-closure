CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags gtk+-3.0`
LDFLAGS = `pkg-config --libs gtk+-3.0` -lxlsxwriter
TARGET_SYS = sistema_caixa
TARGET_MRG = merge_files

# Diretórios e arquivos para o sistema principal
SRCS_SYS = src/main.c src/gui.c src/data.c src/callbacks.c src/user_file.c
OBJS_SYS = $(SRCS_SYS:.c=.o)

# Arquivo fonte e objeto para o merge
SRCS_MRG = src/merge_files.c
OBJS_MRG = $(SRCS_MRG:.c=.o)

# Compilação dos dois alvos
all: $(TARGET_SYS)

$(TARGET_SYS): $(OBJS_SYS)
	$(CC) -o $@ $^ $(LDFLAGS)

merge: $(TARGET_MRG)

$(TARGET_MRG): $(OBJS_MRG)
	$(CC) -o $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_SYS) $(OBJS_MRG) $(TARGET_SYS) $(TARGET_MRG)

purge:
	rm -f reports/*.csv $(TARGET_SYS) $(TARGET_MRG)
	rm -f *.csv

.PHONY: all clean purge merge

