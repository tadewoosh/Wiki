# Co tu znajdę?
Znajdziesz tu proces przygotowywania środowiska RTEMS 4.11 na platformie Linux (tu: Linux Mint 19 "Tara"). Będzie on zawierał wszystkie kroki, które trzeba wykonać by uruchomić na sprzęcie program Hello World, w tym przypadku na platformie opartej o STM32F4 (płytka Discovery F4 i USB-UART od FTDI).

# Przygotowanie środowiska
W celu przygotowania środowiska należy utworzyć zmienną systemową:
```
export RTEMS_MAKEFILE_PATH=/opt/rtems/4.11/arm-rtems4.11/stm32f4
```
I dodać do ścieżki katalog:
```
export PATH="/opt/rtems/4.11/bin:${PATH}"
```
W celu usunięcia konieczności dodawania ich do każdego otwartego terminala edytujemy plik ./bashrc:
```
sudo nano ~/.bashrc
```
I na końcu dodajemy poniższe linijki.
```
export PATH="/opt/rtems/4.11/bin:${PATH}"
export RTEMS_MAKEFILE_PATH=/opt/rtems/4.11/arm-rtems4.11/stm32f4
```
Należy również stworzyć katalog:
```
sudo mkdir /opt/rtems
```
I nadać mu odpowiednie uprawnienia, dla ułatwienia:
```
sudo chmod 777 /opt/rtems
```
Na koniec instalujemy potrzebne paczki:
```
sudo apt-get update
sudo apt-get install -y --no-install-recommends binutils make patch gcc g++ gdb pax python2.7-dev zlib1g-dev git bison flex texinfo bzip2 xz-utils unzip libtinfo-dev
```
I dodajemy link:
```
ln -T /usr/bin/python2.7 /usr/bin/python
```
# Budowanie kroskompilatora
Tworzymy katalog rtemsa i przechodzimy do niego.
```
mkdir -p $HOME/dev/rtems
cd $HOME/dev/rtems
```
Następnie klonujemy odpowiednią gałąź z gita i przechodzimy do utworzonego folderu.
```
git clone --branch 4.11.3 --depth 1 git://git.rtems.org/rtems-source-builder.git rsb
cd rsb
```
Sprawdzamy, czy środowisko jest OK wywołując:
```
./source-builder/sb-check
```
Powinno odpowiedzieć, że jest OK, jeśli czegoś mu brakuje to należy to doinstalować.  
Następnie przechodzimy do katalogu rtems i budujemy kroskompilator.
```
cd rtems
../source-builder/sb-set-builder --prefix=/opt/rtems/4.11 4.11/rtems-arm
```
Budowanie trochę potrwa...

# Budowanie jądra
Przechodzimy do katalogu:
```
cd $HOME/dev/rtems
```
i klonujemy odpowiednią gałąź rtemsa po czym przechodzimy do utworzonego katalogu:
```
git clone --branch 4.11.3 --depth 1 git://git.rtems.org/rtems.git kernel
cd kernel
```
Uruchamiamy boostrapa
```
./bootstrap -c && ./bootstrap -p && ../rsb/source-builder/sb-bootstrap
```
Tworzymy katalog dla odpowiedniej wersji BSP:
```
cd .. && mkdir stm32f4 && cd stm32f4 
```
I uruchamiamy konfigurację instalatora podając architekturę (arm) i odpowiednie BSP (stm32f4)
```
../kernel/configure --prefix=/opt/rtems/4.11 --target=arm-rtems4.11 --enable-rtemsbsp=stm32f4 --enable-posix --enable-cxx
```
Na koniec uruchamiamy budowanie wywołując:
```
make && make install
```
# Tworzenie projektu za pomocą przykładów.
W wybranym przez siebie katalogu pobieramy paczkę przykładów:
```
git clone https://github.com/RTEMS/examples-v2.git
```
Przechodzimy do katalogu
```
cd examples-v2/hello/
```
I tam wywołujemy polecenie
```
make
```
Powinno to zbudować przykład Hello World. Wynik znajdziemy w katalogu:
```
cd hello_world_c/o-optimize/
```
W postaci pliku `helo.exe`. Jest to plik ELF. Jeśli chcemy go zamienić na bin używamy polecenia:
```
arm-rtems4.11-objcopy -S -O binary hello.exe hello.bin
```
# Przygotowanie sprzętu
Po podłączeniu płytki discovery i przejściówki USB-UART należy sprawdzić, czy system prawidłowo je widzi.
Polecenie
```
lsusb
```
powinno znaleźć nam `Bus 001 Device 013: ID 0483:3748 STMicroelectronics ST-LINK/V2` a także `Bus 001 Device 012: ID 0403:6001 Future Technology Devices International, Ltd FT232 USB-Serial (UART) IC`.  
Następnie musmiy nadać odpowiednie uprawnienia terminalowi `ttyUSB0` który powinien był pojawić się w katalogu `/dev`:
```
sudo chmod 777 /dev/ttyUSB0
```
dzięki temu nie trzeba wywoływać poniższego polecenia z prawami administratora. W oddzielnym oknie terminala uruchamiamy
```
screen /dev/ttyUSB0 115200
```
Działanie przejściówki USB-UART można sprawdzić zwierając TX z RXem i wpisując znaki do okna `screen`. Jeśli wpisywane  znaki pojawiają się w tym oknie to przejściówka działa.  
Ostatnim krokiem jest podłączenie wejścia RX przejściówki z pinem TX USARTa 3 na discovery (pin PD8).

# Flashowanie STM32
Do flashowania używamy programu openocd. Po jego instalacji powinniśmy mieć dostęp do plików konfiguracyjnych dla odpowiednich procesorów i płytek w katalogu `/usr/share/openocd/scripts`. Jeśli programujemy za pomocą pliku bin a nie ELF to należy podać adres flasha, w tym przypadku jest to '0x08000000'. Całość polega na uruchomieniu polecenia:
```
openocd -f /usr/share/openocd/scripts/board/stm32f4discovery.cfg -c "program o-optimize/hello.bin exit 0x08000000"
```
Po jego prawidłowej realizacji i resecie mikrokontrolera na ekranie screen powinniśmy zobaczyć tekst powitalny Hello World.

# Tworzenie własnego projektu
Do wybranego przez siebie katalogu kopiujemy np. plik hello.c z przykładów. Tworzymy tam również Makefile.  
[Makefile](/uploads/d60920f24a84e4d3413cf6522e7e4a6b/Makefile)  
Wywołanie polecenia `make` powinno zbudować projekt i stworzyć plik hello.bin.  
Wywołanie polecenia `make install` powinno istniejący plik hello.bin skopiować do pamięci flash mikrokontrolera a następnie go zresetować uruchamiając program.  
Wywołanie polecenia `make reconfigure` powinno przekonfigurować rtemsa w celu aktualizacji zmian w BSP.
Wywołanie polecenia `make clean` powinno posprzątać po kompilacji usuwając wszelkie pliki tymczasowe a także plik wynikowy.