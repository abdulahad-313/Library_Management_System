cmake_minimum_required(VERSION 3.19)
project(Library_Management_System LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Sql)

qt_standard_project_setup()

qt_add_executable(Library_Management_System
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    librariyanlogin.h librariyanlogin.cpp librariyanlogin.ui
    memberlogin.h memberlogin.cpp memberlogin.ui
    memberregistration.h memberregistration.cpp memberregistration.ui
    add_book.h add_book.cpp add_book.ui
    return_book.h return_book.cpp return_book.ui
    member_panel.h member_panel.cpp member_panel.ui
    librarian_panal.h librarian_panal.cpp librarian_panal.ui
    alternatingrowdelegate.h
    newbookadd.h newbookadd.cpp newbookadd.ui
    removebook.h removebook.cpp removebook.ui
    addlibrarian.h addlibrarian.cpp addlibrarian.ui
    updatebook.h updatebook.cpp updatebook.ui



)

target_link_libraries(Library_Management_System
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Sql
)

install(TARGETS Library_Management_System
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Library_Management_System
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
