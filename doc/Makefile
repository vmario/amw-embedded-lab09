.PHONY: all clean

TARGET = manual.pdf
SOURCE = manual.md hysteresis.svg

all: $(TARGET)

$(TARGET): $(SOURCE)
	pandoc $< -o $@ --template eisvogel --listings --metadata date="`date +%F`"

clean:
	rm -f $(TARGET)
