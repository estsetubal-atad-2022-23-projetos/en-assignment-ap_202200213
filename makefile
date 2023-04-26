default:
	gcc -o prog main.c stringWrap.c input.c listArrayList.c listElem.c mapArrayList.c mapElem.c -lm
debug:
	gcc -g -o prog main.c stringWrap.c input.c listArrayList.c listElem.c mapArrayList.c mapElem.c -lm
clean:
	rm -f prog