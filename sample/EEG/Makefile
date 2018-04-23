all	:
	g++ -std=c++11 main.cpp -I../../include -I$(CDF_LIBRARY_PATH)/include -L$(CDF_LIBRARY_PATH)/lib -L../.. -lCLDIA -lcdf -lz -O3
	./a.out > EEG_DATA.txt

nmf	:
	g++ -std=c++11 nmf3.cpp -I../../include -I$(CDF_LIBRARY_PATH)/include -L$(CDF_LIBRARY_PATH)/lib -L../.. -lCLDIA -lcdf -lz -O3
	./a.out
