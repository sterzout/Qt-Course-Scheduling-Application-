cmake_minimum_required(VERSION 3.10)

# Project name and settings
project(ProjectTemplate)
set(CMAKE_CXX_STANDARD 17)

# Add source files
set(SOURCES
    admin.cpp
    admincoursedecision.cpp
    adminselectaction.cpp
    adminstudentaction.cpp
    course.cpp
    coursecatalog.cpp
    coursepage.cpp
    coursetimetable.cpp
    createaccountpage.cpp
    falltermpage.cpp
    loginorcreate.cpp
    main.cpp
    mainwindow.cpp
    notifications.cpp
    prerequisitepage.cpp
    student.cpp
    studentprogresscheck.cpp
    tst_course.cpp
    user.cpp
    wintertermpage.cpp
)

# Add headers
set(HEADERS
    Admin.h
    admincoursedecision.h
    adminproxy.h
    adminselectaction.h
    adminstudentaction.h
    course.h
    coursecatalog.h
    coursepage.h
    coursetimetable.h
    createaccountpage.h
    falltermpage.h
    loginorcreate.h
    mainwindow.h
    notifications.h
    prerequisitepage.h
    student.h
    studentprogresscheck.h
    user.h
    wintertermpage.h
)

# Add GoogleTest
add_subdirectory(/Users/sterzout/Documents/THIRD YEAR/project-deliverable-2-terzout-s-team-main/code/googletest build)

# Include directories
include_directories(/Users/sterzout/Documents/THIRD YEAR/project-deliverable-2-terzout-s-team-main/code/googletest/googletest/include)
include_directories(/Users/sterzout/Documents/THIRD YEAR/project-deliverable-2-terzout-s-team-main/code/googletest/googlemock/include)

# Add the executable
add_executable(ProjectTemplate ${SOURCES} ${HEADERS})

# Link GoogleTest libraries
target_link_libraries(ProjectTemplate gtest gmock pthread)
