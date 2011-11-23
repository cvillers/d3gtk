link_directories(
	${GTKMM_LIBRARY_DIRS})

include_directories(
	${GTKMM_INCLUDE_DIRS})

add_executable(
	pda
	pda.cpp
	pda.h)

target_link_libraries(
	pda
	${GTKMM_LIBRARIES})
