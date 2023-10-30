all : *.c *.h
	alias q='make rebuild'
	gcc $^ -o Z_main
	./Z_main

clean : 
	rm Z_main

rebuild : clean all