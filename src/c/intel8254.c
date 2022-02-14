#include "kernel.h"
#include "pci.h"
#include "intel8254.h"

void intel8254_initalize( void ) {
	pci_header * device = pci_get_header_by_device_id( 0x100E );

	if( device == NULL ) {
		debugf( "Could not find PCI entry for intel8254.\n" );
		return;
	} else {
		k_log( sys_intel8254, level_info, "Found" );
	}

	pci_bist_register * bist = (pci_bist_register *)&(device->bist);

	debugf( "Class: %02X   Subclass: %02X   Prog IF: %02X   Revision: %02X   Vendor: %04X   Device ID: %04X\n",
			device->class_code, device->subclass, device->prog_if, device->revision_id, device->vendor_id, device->device_id );

	debugf( "Bist:\n" );
	debugf_bit_array( device->bist );

	debugf( "Interrupt line: 0x%02X\n", device->interrupt_line );
	debugf( "Interrupt pin: 0x%02X\n", device->interrupt_pin );
	debugf( "Bar0: 0x%08X\n", device->bar0 );
	debugf( "Bar1: 0x%08X\n", device->bar1 );
	debugf( "Bar2: 0x%08X\n", device->bar2 );
	debugf( "Bar3: 0x%08X\n", device->bar3 );
	debugf( "Bar4: 0x%08X\n", device->bar4 );
	debugf( "Bar5: 0x%08X\n", device->bar5 );
	debugf( "Command:\n" );
	debugf_bit_array( device->command );
	debugf( "Status:\n" );
	debugf_bit_array( device->status );
	debugf( "Capabilities:\n" );
	debugf_bit_array( device->capabilities_pointer );
}