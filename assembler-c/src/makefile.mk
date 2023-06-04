OBJDIR = D:/Desktop/Assembler/assembler-c/src/gitignore

a.exe: $(OBJDIR)/utilities.o $(OBJDIR)/preAssembler.o $(OBJDIR)/symbolTable.o $(OBJDIR)/firstRide.o $(OBJDIR)/secondRide.o $(OBJDIR)/utilRide2.o $(OBJDIR)/outputFiles.o $(OBJDIR)/assembler.o $(OBJDIR)/debugger.o $(OBJDIR)/dataUtils.o
	gcc $^ -o a.exe

$(OBJDIR)/utilities.o: D:/Desktop/Assembler/assembler-c/src/utils/generalUtils/utilities.c
	gcc -c $< -o $@

$(OBJDIR)/preAssembler.o: D:/Desktop/Assembler/assembler-c/src/algorithm/preAssembler/preAssembler.c
	gcc -c $< -o $@

$(OBJDIR)/symbolTable.o: D:/Desktop/Assembler/assembler-c/src/algorithm/symbols/symbolTable.c
	gcc -c $< -o $@

$(OBJDIR)/firstRide.o: D:/Desktop/Assembler/assembler-c/src/algorithm/ride1/firstRide.c
	gcc -c $< -o $@

$(OBJDIR)/secondRide.o: D:/Desktop/Assembler/assembler-c/src/algorithm/ride2/secondRide.c
	gcc -c $< -o $@

$(OBJDIR)/utilRide2.o: D:/Desktop/Assembler/assembler-c/src/utils/ride2Utils/utilRide2.c
	gcc -c $< -o $@

$(OBJDIR)/outputFiles.o: D:/Desktop/Assembler/assembler-c/src/algorithm/outputs/outputFiles.c
	gcc -c $< -o $@

$(OBJDIR)/assembler.o: D:/Desktop/Assembler/assembler-c/src/assembler.c
	gcc -c $< -o $@

$(OBJDIR)/debugger.o: D:/Desktop/Assembler/assembler-c/src/algorithm/debugger/debugger.c
	gcc -c $< -o $@

$(OBJDIR)/dataUtils.o: D:/Desktop/Assembler/assembler-c/src/utils/dataUtils/dataUtils.c
	gcc -c $< -o $@
