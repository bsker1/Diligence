Diligence: main.o Player.o Enemy.o functions.o
	g++ main.o Player.o Enemy.o functions.o -o Diligence

main.o:
	g++ -c main.cpp

Player.o:
	g++ -c Player.cpp

Enemy.o:
	g++ -c Enemy.cpp

functions.o:
	g++ -c functions.cpp

clean:
	rm *.o Diligence

cleanwin:
	del *.o Diligence.exe