default:
	gcc -o prog main.c stringWrap.c input.c listArrayList.c listElem.c mapLinkedList.c mapElem.c utils.c -lm
debug:
	gcc -g -o prog main.c stringWrap.c input.c listArrayList.c listElem.c mapLinkedList.c mapElem.c utils.c -lm
clean:
	rm -f prog