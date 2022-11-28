
#compiler
GCC = g++

#Compilation flags
CFLAGS = -Wall -Wextra -Wpedantic 
#-Werror
LIB_DIR := lib
MODULE := ticketing
BUILD_DIR := build


# Executeable program
PROG := main.exe 
#lib/flights.csv lib/bookings.csv

# create Include variable
INCLUDES := $(MODULE)
#INCLUDES := $(addprefix -I./,$(wildcard $(LIB_DIR)/*))

#INCLUDES := $(addprefix -I./, $(INCLUDES:%/=%))


# Object files
OBJECTS := $(notdir $(wildcard $(MODULE)/*.cpp)) 
OBJECTS := $(addprefix $(BUILD_DIR)/, $(OBJECTS:.cpp=.o))


# Executeable Program
$(PROG): $(OBJECTS)
	echo $(BUILD_DIR)/$@ 
	$(GCC) $^ -o $(BUILD_DIR)/$@ 

# module object file
$(BUILD_DIR)/%.o: $(MODULE)/%.cpp
	$(GCC) $(CFLAGS) -c $< $(INCLUDES) -o $@


# Phony targets
all: .mkbuild $(PROG)

run: all
	@echo ""
	@echo "*********************"
	@echo "Printing the Tickets"
	@echo "*********************"
	@echo ""
	@./$(BUILD_DIR)/$(PROG) ./$(LIB_DIR)/flights.csv ./$(LIB_DIR)/bookings.csv
	
check: .mkbuild $(PROG)
	

clean: clean_doxygen clean_ticket clean_doxygen
	@rm -rf $(BUILD_DIR)
	
clean_doxygen:
	@rm -rf $(html)

doxygen:
	@doxygen

clean_ticket:
	@rm *.txt

.mkbuild:
	@mkdir -p $(BUILD_DIR)
	