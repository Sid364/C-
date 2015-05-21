set(SOURCE_FILES
    ../include/Player.hpp
	../include/Card.h
	../include/Rules.h
	../include/Exceptions.h
	../include/ComputerPlayer.h
	../include/Desk.h
	../include/HumanPlayer.h
	Card.cpp
    Rules.cpp
    Desk.cpp
    Main.cpp
    HumanPlayer.cpp
    ComputerPlayer.cpp
)
add_executable(Pokerex ${SOURCE_FILES})
add_library(PokerImpl ${SOURCE_FILES} )