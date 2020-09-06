# RTEMS TMS570 tutorial

## Preface
RTEMS 4.11 on Linux (Linux Mint 19 "Tara"), compiling `Hello World`, programming TMS570 with UniFlash, checking using FTDI USB-UART.

## Environment preparation
The environment is prepared via exporting needed variables:
```
export RTEMS_MAKEFILE_PATH=/opt/rtems/4.11/arm-rtems4.11/tms570
```
and adding to PATH:
```
export PATH="/opt/rtems/4.11/bin:${PATH}"
```
In order not to have to use above stated commands every time one opens a terminal edit ./bashrc:
```
sudo nano ~/.bashrc
```
and append it with:
```
export PATH="/opt/rtems/4.11/bin:${PATH}"
export RTEMS_MAKEFILE_PATH=/opt/rtems/4.11/arm-rtems4.11/tms570
```
Create a dir for the RTEMS binaries and libs:
```
sudo mkdir /opt/rtems
```
Change the permissions to allow for easy access:
```
sudo chmod 777 /opt/rtems
```
Then run `apt` in order to get the necessary packages:
```
sudo apt-get update
sudo apt-get install -y --no-install-recommends binutils make patch gcc g++ gdb pax python2.7-dev zlib1g-dev git bison flex texinfo bzip2 xz-utils unzip libtinfo-dev
```
Add a link for the python:
```
ln -T /usr/bin/python2.7 /usr/bin/python
```
The environment should be properly configured for RTEMS 4.12.

## Building the crosscompiler
Create the RTEMS sources directory and navigate to it:
```
mkdir -p $HOME/dev/rtems
cd $HOME/dev/rtems
```
Clone the appropriate git branch:
```
git clone --branch 4.11.3 --depth 1 git://git.rtems.org/rtems-source-builder.git rsb
cd rsb
```
Check the environment with:
```
./source-builder/sb-check
```
Build the crosscompiler:
```
cd rtems
../source-builder/sb-set-builder --prefix=/opt/rtems/4.11 4.11/rtems-arm
```
The above takes a while..

# Kernel compilation
Navigate to:
```
cd $HOME/dev/rtems
```
clone the kernel from the appropriate git branch:
```
git clone --branch 4.11.3 --depth 1 git://git.rtems.org/rtems.git kernel
cd kernel
```
Run the booststrap:
```
./bootstrap -c && ./bootstrap -p && ../rsb/source-builder/sb-bootstrap
```
Create a directory for the BSP you wish to install:
```
cd .. && mkdir tms570 && cd tms570 
```
Now run the configuration command for RTEMS chosing architecture (arm) and BSP (TMS570):
```
../kernel/configure  --target=arm-rtems4.11 --prefix=/opt/rtems/4.11 --enable-rtems-inlines --disable-multiprocessing --enable-cxx --enable-rdbg --enable-maintainer-mode --enable-tests=samples --disable-networking --enable-posix --enable-itron --disable-ada --disable-expada --disable-multilib --disable-docs --enable-rtemsbsp="tms570ls3137_hdk" --enable-rtems-debug TMS570_USE_HWINIT_STARTUP=1
```
Finish the process with compilation and installation:
```
make && make install
```
## Using example projects
In the location of your choice clone the following git:
```
git clone https://github.com/RTEMS/examples-v2.git
```
and navigate to:
```
cd examples-v2/hello/
```
Run the compilation command:
```
make
```
This should build the `Hello world` example. The result you can find in:
```
cd hello_world_c/o-optimize/
```
The file `helo.exe` found there is in fact an ELF file. If one wishes to convert it to a binary use:
```
arm-rtems4.11-objcopy -S -O binary hello.exe hello.bin
```
## Flashing the TMS570

For flash programming you use the TI program `UniFlash`, which is available also for linux download. Install the program and follow the GUI instructions. Note, that UniFlash requires `.bin` files, so the us e of `arm-rtems4.11-objcopy` is necessary.