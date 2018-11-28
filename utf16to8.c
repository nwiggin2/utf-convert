/*File: utf16to8.c */
#include <stdio.h>

int main(void){                 
	int ch1,ch2,ch3,ch4,code1,code2,unicode,flag=1,highsur,lowsur;
	while (((ch1 = getchar()) != EOF) && (flag == 1)){
		if ((ch2 = getchar()) == EOF)                      		     	//required byte does not exist
			flag = 0;
		if (flag == 1){
			code1 = (ch1 << 8) + ch2;
			if ((code1 <= 0xD7FF) || (((code1 >= 0xE000) && (code1 <= 0xFFFF)))){       //checks if reading 2 bytes is enough because of utf16
				if (code1 <= 0x007F)							   		//encoding in 1 byte
					putchar(code1);		
				else if (code1 <= 0x07FF){					   		    //encoding in 2 bytes
					putchar((code1 >> 6) | 0x00C0);
					putchar((code1 & 0x003F) | 0x0080);
				}
				else{                                          		    //encoding in 3 bytes 
					putchar((code1 >> 12) | 0x00E0);
					putchar(((code1 >> 6) & 0x003F) + 0x0080);
					putchar((code1 & 0x003F) | 0x0080);
				}
			} 
			else if ((code1 >= 0xD800) && (code1 <= 0xDBFF)){           //if true it must read 2 more bytes because of utf16
				if ((ch3 = getchar()) != EOF){						
					if ((ch4 = getchar()) != EOF){
						code2 = (ch3 << 8) + ch4;
						if ((code2 >= 0xDC00) && (code2 <= 0xDFFF)){
							highsur = code1 - 0xD800;                         //10 bits of high surrogate
							lowsur = code2 - 0xDC00;                          //10 bits of low surrogate
							unicode = ((highsur << 10) + lowsur) + 0x10000; 
							putchar((unicode >> 18) + 0xF0);               	 //encoding in 4 bytes
							putchar(((unicode >> 12) & 0x3F) + 0x80);
							putchar(((unicode >> 6) & 0x3F) + 0x80);
							putchar((unicode & 0x3F) + 0x80);
						}
						else                                                 //wrong byte sequence because of utf16
							flag = 0;
					}
					else                                                     //required fourth byte does not exist
						flag = 0;
				}
				else                                                         //required third byte does not exist
					flag = 0;
			}	
			else			                                                 //unicode characters do not exist in [0xD800,0xDFFF] or >0x10FFFF									             
				flag = 0;
		}
		if (flag == 0)
			printf("invalid data\n");
	}
	return 0;
}
