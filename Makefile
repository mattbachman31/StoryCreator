#
# Specifiy the target
all:	Program1

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
Program1:	Word.o Sentence.o Paragraph.o Story.o Program1.o
	g++ -o Program1 Word.o Sentence.o Paragraph.o Story.o Program1.o

# Specify how the object files should be created from source files
Program1.o:	Program1.cpp
	g++ -std=c++11 -c Program1.cpp

# Specify how the object files should be created from source files
Word.o:	Word.cpp
	g++ -std=c++11 -c Word.cpp

# Specify how the object files should be created from source files
Sentence.o:	Sentence.cpp
	g++ -std=c++11 -c Sentence.cpp
	
# Specify how the object files should be created from source files
Paragraph.o:	Paragraph.cpp
	g++ -std=c++11 -c Paragraph.cpp
	
# Specify how the object files should be created from source files
Story.o:	Story.cpp
	g++ -std=c++11 -c Story.cpp


# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o *~ Program1
