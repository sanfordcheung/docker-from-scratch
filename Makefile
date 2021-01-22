container: clean_container
	gcc -o container container.c

demo: clean_demo
	gcc -o demo demo.c

infloop: clean_infloop
	gcc -o infloop infloop.c

oom: clean_oom
	gcc -o oom oom.c

clean_container:
	rm -f container

clean_demo:
	rm -f demo

clean_infloop:
	rm -f infloop

clean_oom:
	rm -f oom