# Preface
This is the boot process as executed for TMS570ls3137_hdk BSP.  

First, the start.S file is called as the entry point.

# start.S
Location: `~/dev/rtems/kernel/c/src/lib/libbsp/arm/shared/start/start.S`  
Assembly file, startup with basic ISR Table, calls `boot_card()` located in bootcard.c.

# boot_card()
Location: `~/dev/rtems/kernel/c/src/lib/libbsp/shared/bootcard.c`  
Description: This is the C entry point for ALL RTEMS BSPs.  It is invoked from the assembly language initialization file usually called start.S.  It provides the framework for the BSP initialization sequence.  
Executed functions:  
[bsp_start();](rtems-boot#bsp_start) - Invoke Board Support Package initialization routine written in C.  
[bsp_work_area_initialize();](rtems-boot#bsp_work_area_initialize) - Initialize the RTEMS Workspace and the C Program Heap.  
[rtems_initialize_data_structures();](rtems-boot#rtems_initialize_data_structures) - Initialize RTEMS data structures.  
[bsp_libc_init();](rtems-boot#bsp_libc_init) - Initialize the C library for those BSPs using the shared framework.  
[bsp_pretasking_hook();](rtems-boot#bsp_pretasking_hook )- Let the BSP do any required initialization.  
[rtems_initialize_before_drivers();](rtems-boot#rtems_initialize_before_drivers) - Let RTEMS perform initialization it requires before drivers are allowed to be initialized.  
[bsp_predriver_hook();](rtems-boot#bsp_predriver_hook) - Execute BSP specific pre-driver hook. Drivers haven't gotten to initialize yet so this is a good chance to initialize buses, spurious interrupt handlers, etc..  
[rtems_initialize_device_drivers();](rtems-boot#rtems_initialize_device_drivers) - Initialize all device drivers.  
[bsp_postdriver_hook();](rtems-boot#bsp_postdriver_hook) - Invoke the postdriver hook.  This normally opens /dev/console for use as stdin, stdout, and stderr.  
[rtems_initialize_start_multitasking();](rtems-boot#rtems_initialize_start_multitasking) - Complete initialization of RTEMS and switch to the first task. Global C++ constructors will be executed in the context of that task.

# bsp_start()
Location: `~/dev/rtems/kernel/c/src/lib/libbsp/arm/tms570/startup/bspstart.c`  
Description:  Invoke Board Support Package initialization routine written in C. *My comment*  
Executed functions:  
[tms570_initialize_and_clear();](rtems-boot#tms570_initialize_and_clear)  
[tms570_pom_remap();](rtems-boot#tms570_pom_remap)  
[bsp_interrupt_initialize();](rtems-boot#bsp_interrupt_initialize) 

# bsp_work_area_initialize()
Location: `~/dev/rtems/kernel/c/src/lib/libbsp/shared/bspgetworkarea.c`   
Description: Initialize the RTEMS Workspace and the C Program Heap. *Calculates the RAM amount from the `bsp_uboot_board_info` structure or `RamBase` and `RamSize` symbols from linker scripts. Initializes the heap*  
Executed functions:  
[bsp_work_area_initialize_default( (void *) work_base, ram_end - work_base );](rtems-boot#bsp_work_area_initialize_default)  

# rtems_initialize_data_structures()
Location: `~/dev/rtems/kernel/cpukit/sapi/src/exinit.c`   
Description: Initialize RTEMS data structures. *My comment*  
Executed functions:  
[_System_state_Handler_initialization( FALSE );](_System_state_Handler_initialization)  
`_CPU_Initialize();` - Initialize any target architecture specific support as early as possible  
`_Debug_Manager_initialization();`  
`_API_extensions_Initialization();`  
`_Thread_Dispatch_initialization();`  
`_User_extensions_Handler_initialization();`  
`_ISR_Handler_initialization();` - File: ~/dev/rtems/kernel/cpukit/score/src/isr.c  
`_Objects_Information_table[OBJECTS_INTERNAL_API]` = _Internal_Objects; -    * Initialize the internal support API and allocator Mutex  
`_API_Mutex_Initialization( 2 );`  
`_API_Mutex_Allocate( &_RTEMS_Allocator_Mutex );`  
`_API_Mutex_Allocate( &_Once_Mutex );`  
`_Watchdog_Handler_initialization();`  
`_TOD_Handler_initialization();`  
`_Thread_Handler_initialization();`  
`_Scheduler_Handler_initialization();`  
`_SMP_Handler_initialize();`  
`_CPU_set_Handler_initialization();`  
`_RTEMS_API_Initialize();`  
`_Extension_Manager_initialization();`  
`_POSIX_API_Initialize();`  
`_System_state_Set( SYSTEM_STATE_BEFORE_MULTITASKING );`  
`_Thread_Create_idle(); - Creation of first thread. Multi threading possible after this point`  

# bsp_libc_init()
Location: `~/dev/rtems/kernel/c/src/lib/libbsp/shared/bsplibc.c`   
Description: Initialize the C library for those BSPs using the shared framework.  
Executed functions:  
`(*rtems_libio_init_helper)();` - Init the RTEMS libio facility to provide UNIX-like system calls for use by newlib (ie: provide open, close, etc). Uses malloc() to get area for the iops, so must be after malloc init.  
`libc_init();` - Set up for the libc handling. * Defined as `extern`, not to be found inside RTEMS.*  

# bsp_pretasking_hook()
Location: `~/dev/rtems/kernel/c/src/lib/libbsp/shared/bsppretaskinghook.c`   
Description: Let the BSP do any required initialization. *Empty function.*  

# rtems_initialize_before_drivers()
Location: `~/dev/rtems/kernel/cpukit/sapi/src/exinit.c`   
Description: Let RTEMS perform initialization it requires before drivers are allowed to be initialized. *Possibly empty*  
Executed functions:  

# bsp_predriver_hook()
Location: `~/dev/rtems/`   
Description: Execute BSP specific pre-driver hook. Drivers haven't gotten to initialize yet so this is a good chance to initialize buses, spurious interrupt handlers, etc.. *My comment*  
Executed functions:  

# rtems_initialize_device_drivers()
Location: `~/dev/rtems/kernel/c/src/lib/libbsp/shared/bsppretaskinghook.c`   
Description: Initialize all device drivers. *My comment*  
Executed functions:  
`_IO_Initialize_all_drivers();` - Initialize I/O drivers. *Runs `rtems_io_initialize( major, 0, NULL );` for `_IO_Number_of_drivers` times. This calls `callouts` from the `_IO_Driver_address_table[device_no].initialization_entry`. This is set up in `~/dev/rtems/tms570/arm-rtems4.11/tms570ls3137_hdk/lib/include/rtems/confdefs.h`. There the table of drivers is populated using `#ifdefs` for example  
`#ifdef CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER` inserts a `CONSOLE_DRIVER_TABLE_ENTRY` to the table. *
`_API_extensions_Run_postdriver();` - The API extensions are supposed to create user initialization tasks.  

# bsp_postdriver_hook()
Location: `~/dev/rtems/`   
Description: Invoke the postdriver hook.  This normally opens /dev/console for use as stdin, stdout, and stderr. *My comment*  
Executed functions:  

# rtems_initialize_start_multitasking()
Location: `~/dev/rtems/`   
Description: Complete initialization of RTEMS and switch to the first task. Global C++ constructors will be executed in the context of that task. *My comment*  
Executed functions:  

**************************************************************************************************************

## tms570_initialize_and_clear()
Location: `~/dev/rtems/kernel/c/src/lib/libbsp/arm/tms570/pom/tms570-pom.c`   
Description:  
Executed functions:  

## tms570_pom_remap()
Location: `~/dev/rtems/kernel/c/src/lib/libbsp/arm/tms570/pom/tms570-pom.c`  
Description:  
Executed functions:  

## bsp_interrupt_initialize()
Location: `~/dev/rtems/kernel/c/src/lib/libbsp/shared/src/irq-generic.c`  
Description:  
Executed functions:  

## bsp_work_area_initialize_default
Location: `~/dev/rtems/kernel/c/src/lib/libbsp/shared/include/bootcard.h`  
Description: *Static inline, fills Heap_Area structure with passed arguments of area_begin and size.*  
Executed functions:
[_Workspace_Handler_initialization(&area, 1, NULL);]
[RTEMS_Malloc_Initialize(&area, 1, NULL);]