project(d3gtk)

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-2.4)
pkg_check_modules(GTKSOURCEVIEWMM gtksourceviewmm-2.0)

add_subdirectory(decl)
