pap: pap.cpp
	g++ pap.cpp -o pap

run: pap
	./pap

clean:
	del /Q pap.exe rezultatai.txt