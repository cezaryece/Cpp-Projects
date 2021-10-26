#ifndef TSSTRUCT_H
#define TSSTRUCT_H

const int TSlen = 188;

struct __attribute__ ((__packed__)) TSpacket
{
	uchar SyncByte : 8;		//0x47, "G", 8 bitów
	uchar TEI : 1;	//Transport Error Indicator, 1 bit
	uchar PUSI : 1;	//Payload Unit Start Indicator, 1 bit, 1 means start of PES data or PSI otherwise zero only.
	uchar TP : 1;	//Transport Priority, 1 bit, 1 means higher priority than other packets with the same PID
	ushort PID : 13;	//PID, 13 bitów, Packet ID (0x0000 = PAT, 0x0001 = CAT, 0x0010 = NIT, 0x0014 = TDT/TOT (For TDT - Table ID is 0x70. For TOT - Table ID is 0x73)
	uchar ScramblingControl : 2;
						//'00' = Not scrambled.
						// The following per DVB spec:
							//'01' = Reserved for future use,
							//'10' = Scrambled with even key,
							//'11' = Scrambled with odd key
	uchar AFE : 2;	//Adaptation field exist
						//01 = no adaptation fields, payload only
						//10 = adaptation field only
						//11 = adaptation field and payload
	uchar CC : 4;	//Continuity counter
						//Incremented only when a payload is present (I.E. Adaptation field exist is 01 or 11)
	//to wszystko zawiera sie w 32 bitach, tzw. transport stream 4-byte prefix.
	//dalej moze wystapic AdaptationFiels, po którym może wystapić Payload Data - oba o róznej długości
	//Packets are 188 bytes in length
};

struct TSheader
{
	uchar sync_byte;
	uchar transport_error_indicator;
	uchar payload_unit_start_indicator;
	uchar transport_priority;
	uint PID;
	uchar transport_scrambling_control;
	uchar adaptation_field_control;
	uchar continuity_counter;
};

struct __attribute__ ((__packed__)) AdaptationField
{
	uchar Length;		//Number of bytes in the adaptation field immediately following this byte
	unsigned DI : 1;	//Discontinuity indicator
						//Set to 1 if current TS packet is in a discontinuity state with respect to either the continuity counter or the program clock reference
	unsigned RAI : 1;	//Random Access indicator - Set to 1 if the PES packet in this TS packet starts a video/audio sequence
	unsigned ESPI : 1;	//Elementary stream priority indicator - 1 = higher priority
	unsigned PCR : 1;	//1 means adaptation field does contain a PCR field
	unsigned OPCR : 1;	//1 means adaptation field does contain a OPCR field
	unsigned SP : 1;	//Splicing point flag - 1 means presence of splice countdown field in adaptation field
	unsigned TPD : 1;	//Transport private data flag - 1 means presence of private data bytes in adaptation field
	unsigned AFE : 1;	//Adaptation field extension flag - 1 means presence of adaptation field extension
};


//PSI - Program Specific Information
//TS Packets containing PAT information always have PID 0x0000.
//The value 0x0000 of program_number is reserved to specify the PID where to look for Network Information Table (NIT).
//If such a program is not present in PAT the default PID value (0x0010) shall be used for NIT.
//The PAT is assigned PID 0x0000 and table id of 0x00
struct __attribute__ ((__packed__)) PAT //Program Association Table
{
	uchar Pointer;
	uchar TableID;		//0x00
	unsigned Misc : 2;	//Always set to binary '10' because of even parity scrambled
	unsigned Res : 2;//Always set to binary '11'
	unsigned Len : 12;	//Section length - Informs how many programs are listed below by specifying the number of bytes of this section,
						//starting immediately following this field and including the CRC. First two bits must be zero.
	ushort TSid;		//transport stream ID - User defined data. Value not important to demuxers or players
	unsigned Misc2 : 2+5+1+8+8;
						//Versions and support for multiple PATs. Can be 0x040000 for simple streams
	// Na końcu są PATitemy, z zależności od długości sekcji (Len)
};

struct PATheader
{
	unsigned int version_number;
	unsigned int section_length;
	unsigned int section_number;
	unsigned int last_section_number;
	unsigned int current_next_indicator;
};

struct __attribute__ ((__packed__)) PATitem
{
	ushort ProgNum;		//numer programu
	unsigned Res : 3;//Always set to binary '111'
	unsigned PID : 13;	//packets with this PID are assumed to be PMT tables (see below)
};
//po wszystkim na końcu całego PAT
//uint CRC32;			//The PAT should end with a 32-bit CRC

//PMT (Program Map Table)
//This table contains PID numbers of elementary streams associated with the program and it has information about the type of these elementary streams (video, audio, etc).
//In addition it also contains the ECM PID number of the entitlement control message, which is associated with the program.

struct __attribute__ ((__packed__)) PMT //Program Map Table
{
	uchar Pointer;		//Offset of first byte of first field. Usually 0x00
	uchar TableID;		//Always 0x02 for PMT
	unsigned SSI : 1;	//Section syntax indicator
	unsigned Res0 : 1;	//Always set to 0
	unsigned Res1 : 2;	//Always set to binary '11'
	unsigned Len : 12;	//Section length - Number of programs listed below. First two bits always zero.
	ushort ProgNum;
	unsigned Res2 : 2;
	unsigned Ver : 5;	//Incremented by 1 mod 32 each time the table data changes
	unsigned CNI : 1;	//Current Next indicator - If 1, this table is currently valid. If 0, this table will become valid next
	uchar SectionNum;	//Section number - Always 0x00
	uchar LastSN;		//Last Section number - Always 0x00
	unsigned Res3 : 3;
	unsigned PCR_PID : 13;//PID of general timecode stream, or 0x1FFF
	unsigned Res4 : 4;
	unsigned ProgInfL : 12;//Program Info length - Sum size of following program descriptors. First two bits must be zero
	// potem występuje N*8 Program Descriptor
};
struct __attribute__ ((__packed__)) PMTitem
{
	uchar StreamType;
	unsigned Res0 : 3;	//	Always set to binary '111'
	unsigned EPID : 13;	//Elementary PID
	unsigned Res1 : 4;
	unsigned ESInfL : 12;//ES Info length - First two bits must be zero. Entire value may be zero
	//po tym wystepuje N*8 ES Descriptor - 	If ES Info length is zero, this is omitted.
	//oraz 4 bajty CRC32
};

//CAT (Conditional Access Table)
//This table is used for conditional access to the streams. This table provides association with EMM stream.
//When the TS is scrambled then this section contains the EMM PID. This EMM pid is encrypted using the smart card number.
//The PID value is 0x0001

//NIT (Network Information Table)
//This table provides information about the multiplexes and transport streams on a given network.
//Information about the current network uses table_id of 0x40, that about other networks uses table_id of 0x41.
//It is segmented into network information sections and is carried on PID 0x0010. [ref EN300468]
//Also this table contains the private stream information too. For example, TeleText, Subtitle and MHEG

//TDT (Time and Date Table) / TOT (Time Offset Table)
//The TDT provides the UTC (Universal Time) coded as MJD (Modified Julian Date).
//The TOT provides information regarding the local time offset from the UTC time. This is used to define the local time.
//The PID value for both tables is 0x0014.
//For TDT - Table ID is 0x70. For TOT - Table ID is 0x73

#endif // TSSTRUCT_H
