/******************************************************************************
*	kernel.ld
*	 by Alex Chadwick
*    Modified based dwelch example
*
*	A linker script for generation of raspberry pi kernel images.
******************************************************************************/

MEMORY {
    ram : ORIGIN = 0x8000, LENGTH = 0x18000
}

SECTIONS {
	/*
	* First and formost we need the .init section, containing the IVT.
	*/
	.init : {*(.init)} > ram
	
	/* 
	* We allow room for the ATAGs and the stack and then start our code at
	* 0x8000.
	*/
	.text : {*(.text)} > ram
	
	/* 
	* Next we put the data.
	*/
	.data : {*(.data)} > ram

	/* 
	* Next we put the rodata.
	*/
	.rodata : {*(.rodata)} > ram

	/*
	* Finally comes everything else. A fun trick here is to put all other 
	* sections into this section, which will be discarded by default.
	*/
	/DISCARD/ : {
		*(*)
	}
}
