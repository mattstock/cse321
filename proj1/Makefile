
all: proj1


validate: proj1 reference.txt
	@./proj1 > output.txt
	@diff -u0 output.txt reference.txt > diff.out
	@echo "PASS"

clean:
	rm -f diff.out output.txt proj1 proj1.o *~

