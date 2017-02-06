#ifndef _CHAR_TABLE_H
#define _CHAR_TABLE_H

const uint8_t BasicFont[][5] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 		//32	20
	0x00, 0x00, 0x5F, 0x00, 0x00, 		//33	21
	0x00, 0x07, 0x00, 0x07, 0x00, 		//34	22
	0x14, 0x7F, 0x14, 0x7F, 0x14, 		//35	23
	0x24, 0x2A, 0x7F, 0x2A, 0x12, 		//36	24
	0x23, 0x13, 0x08, 0x64, 0x62, 		//37	25
	0x36, 0x49, 0x56, 0x20, 0x50, 		//38	26
	0x00, 0x08, 0x07, 0x03, 0x00, 		//39	27
	0x00, 0x1C, 0x22, 0x41, 0x00, 		//40	28
	0x00, 0x41, 0x22, 0x1C, 0x00, 		//41	29
	0x2A, 0x1C, 0x7F, 0x1C, 0x2A, 		//42	2A
	0x08, 0x08, 0x3E, 0x08, 0x08, 		//43	2B
	0x00, 0x80, 0x70, 0x30, 0x00, 		//44	2C
	0x08, 0x08, 0x08, 0x08, 0x08, 		//45	2D
	0x00, 0x00, 0x60, 0x60, 0x00, 		//46	2E
	0x20, 0x10, 0x08, 0x04, 0x02, 		//47	2F
	0x3E, 0x51, 0x49, 0x45, 0x3E, 		//48	30
	0x00, 0x42, 0x7F, 0x40, 0x00, 		//49	31
	0x72, 0x49, 0x49, 0x49, 0x46, 		//50	32
	0x21, 0x41, 0x49, 0x4D, 0x33, 		//51	33
	0x18, 0x14, 0x12, 0x7F, 0x10, 		//52	34
	0x27, 0x45, 0x45, 0x45, 0x39, 		//53	35
	0x3C, 0x4A, 0x49, 0x49, 0x31, 		//54	36
	0x41, 0x21, 0x11, 0x09, 0x07, 		//55	37
	0x36, 0x49, 0x49, 0x49, 0x36, 		//56	38
	0x46, 0x49, 0x49, 0x29, 0x1E, 		//57	39
	0x00, 0x00, 0x14, 0x00, 0x00, 		//58	3A
	0x00, 0x40, 0x34, 0x00, 0x00, 		//59	3B
	0x00, 0x08, 0x14, 0x22, 0x41, 		//60	3C
	0x14, 0x14, 0x14, 0x14, 0x14, 		//61	3D
	0x00, 0x41, 0x22, 0x14, 0x08, 		//62	3E
	0x02, 0x01, 0x59, 0x09, 0x06, 		//63	3F
	0x3E, 0x41, 0x5D, 0x59, 0x4E, 		//64	40
	0x7C, 0x12, 0x11, 0x12, 0x7C, 		//65	41
	0x7F, 0x49, 0x49, 0x49, 0x36, 		//66	42
	0x3E, 0x41, 0x41, 0x41, 0x22, 		//67	43
	0x7F, 0x41, 0x41, 0x41, 0x3E, 		//68	44
	0x7F, 0x49, 0x49, 0x49, 0x41, 		//69	45
	0x7F, 0x09, 0x09, 0x09, 0x01, 		//70	46
	0x3E, 0x41, 0x41, 0x51, 0x73, 		//71	47
	0x7F, 0x08, 0x08, 0x08, 0x7F, 		//72	48
	0x00, 0x41, 0x7F, 0x41, 0x00, 		//73	49
	0x20, 0x40, 0x41, 0x3F, 0x01, 		//74	4A
	0x7F, 0x08, 0x14, 0x22, 0x41, 		//75	4B
	0x7F, 0x40, 0x40, 0x40, 0x40, 		//76	4C
	0x7F, 0x02, 0x1C, 0x02, 0x7F, 		//77	4D
	0x7F, 0x04, 0x08, 0x10, 0x7F, 		//78	4E
	0x3E, 0x41, 0x41, 0x41, 0x3E, 		//79	4F
	0x7F, 0x09, 0x09, 0x09, 0x06, 		//80	50
	0x3E, 0x41, 0x51, 0x21, 0x5E, 		//81	51
	0x7F, 0x09, 0x19, 0x29, 0x46, 		//82	52
	0x26, 0x49, 0x49, 0x49, 0x32, 		//83	53
	0x03, 0x01, 0x7F, 0x01, 0x03, 		//84	54
	0x3F, 0x40, 0x40, 0x40, 0x3F, 		//85	55
	0x1F, 0x20, 0x40, 0x20, 0x1F, 		//86	56
	0x3F, 0x40, 0x38, 0x40, 0x3F, 		//87	57
	0x63, 0x14, 0x08, 0x14, 0x63, 		//88	58
	0x03, 0x04, 0x78, 0x04, 0x03, 		//89	59
	0x61, 0x59, 0x49, 0x4D, 0x43, 		//90	5A
	0x00, 0x7F, 0x41, 0x41, 0x41, 		//91	5B
	0x02, 0x04, 0x08, 0x10, 0x20, 		//92	5C
	0x00, 0x41, 0x41, 0x41, 0x7F, 		//93	5D
	0x04, 0x02, 0x01, 0x02, 0x04, 		//94	5E
	0x40, 0x40, 0x40, 0x40, 0x40, 		//95	5F
	0x00, 0x03, 0x07, 0x08, 0x00, 		//96	60
	0x20, 0x54, 0x54, 0x78, 0x40, 		//97	61
	0x7F, 0x28, 0x44, 0x44, 0x38, 		//98	62
	0x38, 0x44, 0x44, 0x44, 0x28, 		//99	63
	0x38, 0x44, 0x44, 0x28, 0x7F, 		//100	64
	0x38, 0x54, 0x54, 0x54, 0x18, 		//101	65
	0x00, 0x08, 0x7E, 0x09, 0x02, 		//102	66
	0x18, 0xA4, 0xA4, 0x9C, 0x78, 		//103	67
	0x7F, 0x08, 0x04, 0x04, 0x78, 		//104	68
	0x00, 0x44, 0x7D, 0x40, 0x00, 		//105	69
	0x20, 0x40, 0x40, 0x3D, 0x00, 		//106	6A
	0x7F, 0x10, 0x28, 0x44, 0x00, 		//107	6B
	0x00, 0x41, 0x7F, 0x40, 0x00, 		//108	6C
	0x7C, 0x04, 0x78, 0x04, 0x78, 		//109	6D
	0x7C, 0x08, 0x04, 0x04, 0x78, 		//110	6E
	0x38, 0x44, 0x44, 0x44, 0x38, 		//111	6F
	0xFC, 0x18, 0x24, 0x24, 0x18, 		//112	70
	0x18, 0x24, 0x24, 0x18, 0xFC, 		//113	71
	0x7C, 0x08, 0x04, 0x04, 0x08, 		//114	72
	0x48, 0x54, 0x54, 0x54, 0x24, 		//115	73
	0x04, 0x04, 0x3F, 0x44, 0x24, 		//116	74
	0x3C, 0x40, 0x40, 0x20, 0x7C, 		//117	75
	0x1C, 0x20, 0x40, 0x20, 0x1C, 		//118	76
	0x3C, 0x40, 0x30, 0x40, 0x3C, 		//119	77
	0x44, 0x28, 0x10, 0x28, 0x44, 		//120	78
	0x4C, 0x90, 0x90, 0x90, 0x7C, 		//121	79
	0x44, 0x64, 0x54, 0x4C, 0x44, 		//122	7A
	0x00, 0x08, 0x36, 0x41, 0x00, 		//123	7B
	0x00, 0x00, 0x77, 0x00, 0x00, 		//124	7C
	0x00, 0x41, 0x36, 0x08, 0x00, 		//125	7D
	0x02, 0x01, 0x02, 0x04, 0x02, 		//126	7E
	0x3C, 0x26, 0x23, 0x26, 0x3C, 		//127	7F
    0x7C, 0x12, 0x11, 0x12, 0x7C, 		//144	90  � //#128
	0x7F, 0x49, 0x49, 0x49, 0x31,		//145	91  �
	0x7F, 0x45, 0x45, 0x45, 0x3A,		//146	92  �
	0x7F, 0x01, 0x01, 0x01, 0x03, 		//147	93  �
	0x60, 0x3F, 0x21, 0x3F, 0x60, 		//148	94  �
	0x7F, 0x49, 0x49, 0x49, 0x41, 		//149	95  �
	0x73, 0x0C, 0x7F, 0x0C, 0x73, 		//150	96  �
	0x21, 0x41, 0x49, 0x4D, 0x33,  		//151	97  �
	0x7F, 0x10, 0x08, 0x04, 0x7F, 		//152	98  �
	0x7E, 0x20, 0x11, 0x08, 0x7E, 		//153	99  �
	0x7F, 0x08, 0x14, 0x22, 0x41, 		//154	9A  �
	0x40, 0x3F, 0x01, 0x01, 0x7F, 		//155	9B  �
	0x7F, 0x06, 0x08, 0x06, 0x7F, 		//156	9C  �
	0x7F, 0x08, 0x08, 0x08, 0x7F,     	//157	9D  �
	0x3E, 0x41, 0x41, 0x41, 0x3E,  		//158	9E  �
	0x7F, 0x01, 0x01, 0x01, 0x7F,		//159	9F  �
	0x7F, 0x09, 0x09, 0x09, 0x06, 		//160	A0  �
	0x3E, 0x41, 0x41, 0x41, 0x22, 		//161	A1  �
	0x03, 0x01, 0x7F, 0x01, 0x03, 		//162	A2  �
	0x61, 0x26, 0x18, 0x06, 0x01, 		//163	A3  �
	0x1C, 0x22, 0x7F, 0x22, 0x1C, 		//164	A4  �
	0x63, 0x14, 0x08, 0x14, 0x63,  		//165	A5  �
	0x3F, 0x20, 0x20, 0x3F, 0x60, 		//166	A6  �
	0x07, 0x08, 0x08, 0x08, 0x7F, 		//167	A7  �
	0x7F, 0x40, 0x7F, 0x40, 0x7F, 		//168	A8  �
	0x3F, 0x20, 0x3F, 0x20, 0x7F, 		//169	A9  �
	0x01, 0x7F, 0x48, 0x48, 0x30, 		//170	AA  �
	0x7F, 0x48, 0x78, 0x00, 0x7F, 		//171	AB  �
	0x7F, 0x48, 0x48, 0x30, 0x00, 		//172	AC  �
	0x41, 0x49, 0x49, 0x2A, 0x1C, 		//173	AD  �
	0x7F, 0x10, 0x3E, 0x41, 0x3E,		//174	AE  �
	0x66, 0x19, 0x09, 0x09, 0x7F, 		//175	AF  �

	0x20, 0x54, 0x54, 0x78, 0x40, 		//176	B0  �
	0x3E, 0x49, 0x45, 0x45, 0x38, 		//177	B1  �
	0x7E, 0x4A, 0x4A, 0x34, 0x00, 		//178	B2  �
	0x7C, 0x04, 0x04, 0x0C, 0x00, 		//179	B3  �
	0x38, 0x45, 0x45, 0x49, 0x3E, 		//180	B4  �
	0x38, 0x54, 0x54, 0x54, 0x18,		//181	B5  �
	0x4C, 0x30, 0x7C, 0x30, 0x4C, 		//182	B6  �
	0x24, 0x42, 0x4A, 0x34, 0x00, 		//183	B7  �
	0x7C, 0x20, 0x10, 0x7C, 0x00, 		//184	B8  �
	0x7C, 0x21, 0x11, 0x7C, 0x00, 		//185	B9  �
	0x7C, 0x10, 0x28, 0x44, 0x00,		//186	BA  �
	0x40, 0x3C, 0x04, 0x04, 0x7C, 		//187	BB  �
	0x7C, 0x08, 0x10, 0x08, 0x7C, 		//188	BC  �
	0x7C, 0x10, 0x10, 0x7C, 0x00,    	//189	BD  �
	0x38, 0x44, 0x44, 0x44, 0x38, 		//190	BE  �
	0x7C, 0x04, 0x04, 0x7C, 0x00, 		//191	BF  �
	0xFC, 0x18, 0x24, 0x24, 0x18, 		//192	C0  �
	0x38, 0x44, 0x44, 0x44, 0x28,  		//193	C1  �
	0x04, 0x04, 0x7C, 0x04, 0x04, 		//194	C2  �
	0x4C, 0x90, 0x90, 0x90, 0x7C,  		//195	C3  �
	0x18, 0x24, 0x7E, 0x24, 0x18, 		//196	C4  �
	0x44, 0x28, 0x10, 0x28, 0x44, 		//197	C5  �
	0x3C, 0x20, 0x20, 0x3C, 0x60, 		//198	C6  �
	0x1C, 0x10, 0x10, 0x7C, 0x00, 		//199	C7  �
	0x7C, 0x40, 0x7C, 0x40, 0x7C,  		//200	C8  �
	0x3C, 0x20, 0x3C, 0x20, 0x7C, 		//201	C9  �
	0x04, 0x7C, 0x50, 0x70, 0x00, 		//202	CA  �
	0x7C, 0x50, 0x70, 0x00, 0x7C,		//203	CB  �
	0x7C, 0x50, 0x70, 0x00, 0x00, 		//204	CC  �
	0x42, 0x42, 0x52, 0x52, 0x3C,		//205	CD  �
	0x7C, 0x10, 0x38, 0x44, 0x38, 		//206	CE  �
	0x40, 0x2C, 0x12, 0x7E, 0x00, 		//207	CF  �
};

// Big numbers font, from 0 to 9 - 96 bytes each.
const uint8_t bigNumbers [][96] = {
{0x00, 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
0xF0, 0xF0, 0xF0, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x01,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x07, 0x03, 0x00, 0x00, 0x00},

{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xF0,
0xF0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},

{0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
0xF0, 0xF0, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0xC1, 0xC0, 0xC0, 0xC0,
0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xE1, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x87, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
0x03, 0x03, 0x83, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00},

{0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
0xF0, 0xF0, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0xC1, 0xC0, 0xC0, 0xC0,
0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xE1, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x81, 0x83, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x87,
0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00},

{0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF0, 0xF0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30,
0xF0, 0xF0, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0,
0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07,
0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0F, 0x0F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00},

{0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
0xF0, 0xF0, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE1,
0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC1, 0x81, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x81, 0x83, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x87,
0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00},

{0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
0xF0, 0xF0, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE1,
0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC1, 0x81, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x87, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x87,
0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00},

{0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
0xF0, 0xF0, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0F, 0x0F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00},

{0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
0xF0, 0xF0, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xE1,
0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xE1, 0xFF, 0xFF, 0xFF, 0x3F, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0x87, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x87,
0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0F, 0x0F, 0x0F, 0x0F,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00},

{0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
0xF0, 0xF0, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE1,
0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xE1, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07,
0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0F, 0x0F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00},

{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x3C, 0x7E, 0x7E, 0x7E, 0x7E, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF8, 0xF8, 0xF8, 0xF8, 0xF0, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};


#endif