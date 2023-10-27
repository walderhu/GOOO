all : *.c *.h
	alias q='make rebuild'
	gcc $^ -o main
	./main

clean : 
	rm main

rebuild : clean all