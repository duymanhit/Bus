# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Research\Bus

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Research\Bus\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\Bus.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\Bus.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\Bus.dir\flags.make

CMakeFiles\Bus.dir\src\Source.cpp.obj: CMakeFiles\Bus.dir\flags.make
CMakeFiles\Bus.dir\src\Source.cpp.obj: ..\src\Source.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Research\Bus\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Bus.dir/src/Source.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Bus.dir\src\Source.cpp.obj /FdCMakeFiles\Bus.dir\ /FS -c D:\Research\Bus\src\Source.cpp
<<

CMakeFiles\Bus.dir\src\Source.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Bus.dir/src/Source.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx64\x64\cl.exe > CMakeFiles\Bus.dir\src\Source.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Research\Bus\src\Source.cpp
<<

CMakeFiles\Bus.dir\src\Source.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Bus.dir/src/Source.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Bus.dir\src\Source.cpp.s /c D:\Research\Bus\src\Source.cpp
<<

# Object files for target Bus
Bus_OBJECTS = \
"CMakeFiles\Bus.dir\src\Source.cpp.obj"

# External object files for target Bus
Bus_EXTERNAL_OBJECTS =

Bus.exe: CMakeFiles\Bus.dir\src\Source.cpp.obj
Bus.exe: CMakeFiles\Bus.dir\build.make
Bus.exe: CMakeFiles\Bus.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Research\Bus\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Bus.exe"
	"C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\Bus.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x64\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x64\mt.exe --manifests -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1427~1.291\bin\Hostx64\x64\link.exe /nologo @CMakeFiles\Bus.dir\objects1.rsp @<<
 /out:Bus.exe /implib:Bus.lib /pdb:D:\Research\Bus\cmake-build-debug\Bus.pdb /version:0.0 /machine:x64 /debug /INCREMENTAL /subsystem:console   -LIBPATH:C:\PROGRA~1\IBM\ILOG\CPLEX_~3\cplex\lib\X64_WI~1\stat_mdd  -LIBPATH:C:\PROGRA~1\IBM\ILOG\CPLEX_~3\concert\lib\X64_WI~1\stat_mdd  -LIBPATH:C:\PROGRA~1\IBM\ILOG\CPLEX_~3\CPOPTI~1\lib\X64_WI~1\stat_mdd  ilocplex.lib concert.lib cplex12100.lib cp.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\Bus.dir\build: Bus.exe

.PHONY : CMakeFiles\Bus.dir\build

CMakeFiles\Bus.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Bus.dir\cmake_clean.cmake
.PHONY : CMakeFiles\Bus.dir\clean

CMakeFiles\Bus.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" D:\Research\Bus D:\Research\Bus D:\Research\Bus\cmake-build-debug D:\Research\Bus\cmake-build-debug D:\Research\Bus\cmake-build-debug\CMakeFiles\Bus.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\Bus.dir\depend

