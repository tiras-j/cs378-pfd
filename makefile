FILES :=                              \
    .travis.yml                       \
    PFD-tests/ezo55-RunPFD.in   \
    PFD-tests/ezo55-RunPFD.out  \
    PFD-tests/ezo55-TestPFD.c++ \
    PFD-tests/ezo55-TestPFD.out \
    PFD.c++                       \
    PFD.h                         \
    PFD.log                       \
    html                              \
    RunPFD.c++                    \
    RunPFD.in                     \
    RunPFD.out                    \
    TestPFD.c++                   \
    TestPFD.out

ifeq ($(CXX), clang++)
    COVFLAGS := --coverage
    GCOV     := gcov-4.6
else
    CXX      := g++-4.8
    COVFLAGS := -fprofile-arcs -ftest-coverage
    GCOV     := gcov-4.8
endif

CXXFLAGS := -pedantic -std=c++11 -Wall
LDFLAGS  := -lgtest -lgtest_main -pthread
VALGRIND := valgrind

all: RunPFD TestPFD RunPFD.out TestPFD.out

check:
	@for i in $(FILES);                                         \
	do                                                          \
        [ -e $$i ] && echo "$$i found" || echo "$$i NOT FOUND"; \
    done

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f RunPFD
	rm -f RunPFD.out
	rm -f TestPFD
	rm -f TestPFD.out

config:
	git config -l

test: RunPFD.out TestPFD.out

PFD-tests:
	git clone https://github.com/cs378-summer-2015/PFD-tests.git

html: Doxyfile PFD.h PFD.c++ RunPFD.c++ TestPFD.c++
	doxygen Doxyfile

PFD.log:
	git log > PFD.log

Doxyfile:
	doxygen -g

RunPFD: PFD.h PFD.c++ RunPFD.c++
	$(CXX) $(CXXFLAGS) PFD.c++ RunPFD.c++ -o RunPFD

RunPFD.out: RunPFD
	./RunPFD < RunPFD.in > RunPFD.out
	diff RunPFD.out ./PFD-tests/ezo55-RunPFD.out

SpherePFD: SpherePFD.c++
	$(CXX) $(CXXFLAGS) SpherePFD.c++ -o SpherePFD

SpherePFD.out: SpherePFD
	rm -f SpherePFD.out
	./SpherePFD < RunPFD.in > SpherePFD.out
	diff SpherePFD.out ./PFD-tests/ezo55-RunPFD.out

TestPFD: PFD.h PFD.c++ TestPFD.c++
	$(CXX) $(COVFLAGS) $(CXXFLAGS) PFD.c++ TestPFD.c++ -o TestPFD $(LDFLAGS)

TestPFD.out: TestPFD
	$(VALGRIND) ./TestPFD  >  TestPFD.out 2>&1
	$(GCOV) -b PFD.c++     >> TestPFD.out
	$(GCOV) -b TestPFD.c++ >> TestPFD.out
	cat TestPFD.out

UpdateEID:
	cp ./RunPFD.in ./PFD-tests/ezo55-RunPFD.in
	cp ./RunPFD.out ./PFD-tests/ezo55-RunPFD.out
	cp ./TestPFD.c++ ./PFD-tests/ezo55-TestPFD.c++
	cp ./TestPFD.out ./PFD-tests/ezo55-TestPFD.out