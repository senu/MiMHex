CXX = g++
OPTIONS = -Wall -W -Wextra -Wshadow -O0 -ggdb 
INCLUDE_DIR = -I ../lib -I ../implementation
DEST_DIR = .

all: benchmark main gather_patterns

benchmark:
	$(CXX) $(OPTIONS) $(INCLUDE_DIR) -o $(DEST_DIR)/hex_benchmark main_benchmark.cpp

main:
	$(CXX) $(OPTIONS) $(INCLUDE_DIR) -o $(DEST_DIR)/hex main.cpp

gather_patterns:
	$(CXX) $(OPTIONS) $(INCLUDE_DIR) -o $(DEST_DIR)/gather_patterns gather_patterns.cpp

clean:
	rm -f ${DEST_DIR}/hex ${DEST_DIR}/hex_benchmark ${DEST_DIR}/gather_patterns
