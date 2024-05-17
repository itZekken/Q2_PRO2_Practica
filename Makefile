OPCIONS = -std=c++11
OPCIONS1 = -std=c++11 -D_GLIBCXX_DEBUG
OPCIONS2 = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Proceso.o CPU.o Cluster.o Prioridad.o Area_de_espera.o
	g++ -o program.exe program.o Proceso.o CPU.o Cluster.o Prioridad.o Area_de_espera.o

Proceso.o:  Proceso.cc Proceso.hh
	g++ -c Proceso.cc $(OPCIONS2)

CPU.o:  CPU.cc CPU.hh
	g++ -c CPU.cc $(OPCIONS2)

Cluster.o:  Cluster.cc Cluster.hh
	g++ -c Cluster.cc $(OPCIONS2)

Prioridad.o:  Prioridad.cc Prioridad.hh
	g++ -c Prioridad.cc $(OPCIONS2)

Area_de_espera.o: Area_de_espera.cc Area_de_espera.hh
	g++ -c Area_de_espera.cc $(OPCIONS2)

program.o: program.cc
	g++ -c program.cc $(OPCIONS2)

clean:
	rm *.o
	rm *.exe

tar:
	tar -cvf practica.tar *.cc *.hh Makefile
