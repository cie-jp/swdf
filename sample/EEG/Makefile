all	:
	g++ -std=c++11 main.cpp -I../../include -I$(CDF_LIBRARY_PATH)/include -L$(CDF_LIBRARY_PATH)/lib -L../.. -lCLDIA -lcdf -lz -O3
	./a.out > EEG_DATA.txt

nmf	:
	g++ -std=c++11 nmf3.cpp -I../../include -I$(CDF_LIBRARY_PATH)/include -L$(CDF_LIBRARY_PATH)/lib -L../.. -lCLDIA -lcdf -lz -O3
	./a.out

spec	:
	g++ -std=c++11 spec.cpp -I../../include -I$(CDF_LIBRARY_PATH)/include -L$(CDF_LIBRARY_PATH)/lib -L../.. -lCLDIA -lcdf -lz -O3
	./a.out

nn	:
	g++ -std=c++11 nn.cpp -I../../include -I$(CDF_LIBRARY_PATH)/include -L$(CDF_LIBRARY_PATH)/lib -L../.. -lCLDIA -lcdf -lz -O3
	./a.out

plot_wave	:
	g++ -std=c++11 plot_wave.cpp -I../../include -I$(CDF_LIBRARY_PATH)/include -L$(CDF_LIBRARY_PATH)/lib -L../.. -lCLDIA -lcdf -lz -O3
	./a.out
