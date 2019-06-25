all : 
	incltouch.x
	make -C src/
	make -C tst/
	make -C options/
	make -C database/
	make -C obj/

PHONY : clean

clean :
	rm obj/*.?
	rm *.x

