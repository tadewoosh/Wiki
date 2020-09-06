# Preface
This article describes the steps necessary to create a working Eclipse project capable of making use of a Makefile containing instructions for compiling a RTEMS project and flashing the MCU. This is based on Eclipse Photon Release (4.8.0).

# Download and run Eclipse
1.  Download from [Eclipse Packages](https://www.eclipse.org/downloads/packages/).  
2.  Extract it and open a terminal window in the eclipse folder.  
3.  Run `./eclipse` from the terminal window.  
This is crucial if Eclipse is to see the correct PATH vairable containing the location of `arm-rtems-4.11-gcc` binary necessary to build the executable as well as other.

# Create a project
4.  In the welcome screen click the `Create a new C prjoject`.  
5.  Enter a name for the project.  
6.  Select `Project type -> Makefile project -> Empty Project` with `-- Other Toolchain --` and click Finish.  
7.  Import from filesystem or create source files as well as a Makefile.  
8.  Run the `Build` command using the Eclipse button. Check if the ELF file is generated.  
To enable automatic saving of files before build navigate to `Windows -> Preferences -> General -> Workspace -> Build` and check the `Save automatically before build` checkbox.
9.  Select `Project -> Clean...` and check if the cleaning works.  

# Configure the Run tool
10.  In order to run the `make install` command from the Eclipse environment, which flashes the MCU and runs the program configure the External Tools.  
11.  Create a New configuration, then in Main tab fill the Location with `/usr/bin/make` and select the working directory as the place where the Makefile is (the project directory).  
12.  In the Arguments section type `install` and close the window.
13.  Click the Run New_Configuration button and check if the Console window shows the openocd output.