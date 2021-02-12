CC = g++
CPPFLAGS = -std=c++11 -g -Wall
OBJTS = main.o distribution.o transportation.o order.o product.o location.o 

main: $(OBJTS)

main.o: distribution.h order.h product.h location.h

distribution.o: distribution.h

transportation.o: transportation.h

order.o: order.h

product.o: product.h

location.o: location.h

.PHONY: clean
clean:
	$(info -- cleaning the directory --)
	rm -f *.o
	rm -f main
