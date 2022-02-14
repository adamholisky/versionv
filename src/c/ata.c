#include "kernel.h"
#include "ata.h"

bool 		primary_ready;

uint16_t	primary_status[256];
uint16_t	* sector_read_buffer;

void ata_initalize( void ) {
	uint32_t	drive_lba_sectors;
	uint32_t	drive_size_bytes;

	sector_read_buffer = kmalloc( sizeof(uint16_t) * 256 );
	primary_ready = false;
	
	outportb( ata_primary_control, 4 );
	outportb( ata_primary_control, 0 );
	outportb( ata_secondary_control, 4 );
	outportb( ata_secondary_control, 0 );

	debugf( "[ATA]     Identify Primary, Drive One:   %s\n", ata_identify( ata_primary, ata_drive_one ) ? "true" : "false"  );
	debugf( "[ATA]     Identify Primary, Drive Two:   %s\n", ata_identify( ata_primary, ata_drive_two ) ? "true" : "false" );
	
	drive_lba_sectors = primary_status[60] | primary_status[61] << 16;
	drive_size_bytes = drive_lba_sectors * 512;
	
	debugf( "[ATA]     Primary 60 and 61:          %X\n", drive_lba_sectors );
	debugf( "[ATA]     Drive size:                 %db\n", drive_size_bytes );
	debugf( "[ATA]     Drive size:                 %dk\n", drive_size_bytes / 1024 );
	debugf( "[ATA]     Drive size:                 %dmb\n", drive_size_bytes / 1024 / 1024 );
	debugf( "[ATA]     byte_to_sector( 20 )        %d, %d\n", byte_to_sector(20), byte_to_offset(20) );
	debugf( "[ATA]     byte_to_sector( 512 )       %d, %d\n", byte_to_sector(512), byte_to_offset(512) );
	debugf( "[ATA]     byte_to_sector( 513 )       %d, %d\n", byte_to_sector(513), byte_to_offset(513) );
}

int ata_identify( uint8_t drive, uint8_t drive_one_or_two ) {
	uint16_t 	port = 0;
	uint8_t		status = 0;
	uint16_t	data = 0;
	int 		result = 0;

	if( drive == ata_primary ) {
		if( drive_one_or_two == ata_drive_one ) {
			outportb( ata_primary_port + ata_reg_hddevsel, 0xA0 );
		} else {
			outportb( ata_primary_port + ata_reg_hddevsel, 0xB0 );
		}
	}

	if( drive == ata_secondary ) {
		if( drive_one_or_two == ata_drive_one ) {
			outportb( ata_secondary_port + ata_reg_hddevsel, 0xA0 );
		} else {
			outportb( ata_secondary_port + ata_reg_hddevsel, 0xB0 );
		}
	}
	
	//debug_f( "A\n" );
	
	switch( drive ) {
		case ata_primary: 
			port = ata_primary_port;
			break;
		case ata_secondary:
			port = ata_secondary_port;
			break;
	}

	outportb( port + ata_reg_command, ata_cmd_identify );

	//debug_f( "0: %X, %X\n", port + ata_reg_command, ata_cmd_identify );

	//debug_f( "0.5\n" );

	status = inportb( port + ata_reg_status );

	//debug_f( "status: 0x%04X\n" );

	if( status ) {
		result = -2;

		while( inportb( port + ata_reg_status ) & ata_sr_busy != 0 ) {

		}

		//debug_f( "1" );
		do {
			status = inportb( port + ata_reg_status );

			if( status & ata_sr_err ) {
				//debug_f( "should ret 0\n" );
				return 0;
			}
		} while( !(status & ata_sr_busy) && !( status & ata_sr_drq ));

		//debug_f( "\nData: \n" );

		for( int i = 0; i < 256; i++ ) {
			data = inportw( port + ata_reg_data );
			primary_status[ i ] = data;
			//debugf( "%d: %04X\n", i, data );
		}

		//debug_f( "\n" );


		result = 1;
	}

	return result;
}