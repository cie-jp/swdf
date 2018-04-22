all	:
	g++ -std=c++11 main.cpp -I../../include -I$(CDF_LIBRARY_PATH)/include -L$(CDF_LIBRARY_PATH)/lib -L../.. -lCLDIA -lcdf -lz -O3
	./a.out > EEG_DATA.txt

anal	:
	g++ -std=c++11 main2.cpp -I../../include -I$(CDF_LIBRARY_PATH)/include -L$(CDF_LIBRARY_PATH)/lib -L../.. -lCLDIA -lcdf -lz -O3
	./a.out > sample.txt
