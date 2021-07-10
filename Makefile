all	:
	g++  -I./ -I./eigen-3.3.8/ ./main.cpp ./srcs/crandom.cpp -O3
	g++ -o csv_mod csv_mod.cpp
	./a.out
	./csv_mod wdf.csv
	./wdf-graph-color wdf.csv.mod
	./csv_mod mean.csv
	./wdf-graph-color mean.csv.mod
	./csv_mod lower.csv
	./wdf-graph-color lower.csv.mod
	./csv_mod upper.csv
	./wdf-graph-color upper.csv.mod
