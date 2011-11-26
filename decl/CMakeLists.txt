link_directories(
	${GTKMM_LIBRARY_DIRS}
	${GTKSOURCEVIEWMM_LIBRARY_DIRS})

include_directories(
	${GTKMM_INCLUDE_DIRS}
	${GTKSOURCEVIEWMM_INCLUDE_DIRS})

add_executable(
	decl
	main.cpp
	decl.cpp
	decl.h)

target_link_libraries(
	decl
	${GTKMM_LIBRARIES}
	${GTKSOURCEVIEWMM_LIBRARIES})
