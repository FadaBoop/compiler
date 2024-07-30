COMP = g++ -o
name = main
app = $(name).cpp 
all: build run
debug: build run clean
.SILENT: build run clean

build:
	$(COMP) $(name) $(app)

run:
	./$(name)

bin:
ifeq ($(name),main)
	@echo "Name 'main' is not allowed."
else
	$(COMP) $(name) $(app).cpp
	sudo mv $(name) /usr/bin
endif

clean:
	rm -f $(name)

