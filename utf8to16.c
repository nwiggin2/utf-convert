/*File: utf8to16.c */
#include <stdio.h>

int main(void){
	int ch1,ch2,ch3,ch4,byte1,byte2,byte3,unicode,flag=1,code1,code2,code3,code4,B,B1,B2,A1,A2;
	while (((ch1 = getchar()) != EOF) && flag == 1){
		flag = 0;
		if (ch1 <= 0x7F){                                          //encoding to utf16 in 2 bytes
			putchar(ch1 >> 8);                                  //if encoding in utf8 was in 1 byte
			putchar(ch1);
			flag = 1;
		}
		else if ((ch1 & 0xE0) == 0xC0){                            //if encoding in utf8 was in 2 bytes
		    if (((ch2 = getchar()) != EOF) && ((ch2 & 0xC0) == 0x80)){
				code1 = ch1 & 0x1F; 
				code2 = ch2 & 0x3F; 
                            unicode = (code1 << 6) | code2;
				if (unicode >= 0x80 && unicode <= 0x7FF){
					putchar(unicode >> 8);                    
					putchar(unicode & 0xFF);                  
					flag = 1;
				}
				
			}
			
		}                                    
		else if ((ch1 & 0xF0) == 0xE0){                              //if encoding in utf8 was in 3 bytes
			if (((ch2 = getchar()) != EOF) && ((ch2 & 0xC0) == 0x80)){
				if (((ch3 = getchar()) != EOF) && ((ch3 & 0xC0) == 0x80)){
					code1 = ch1 & 0xF;
					code2 = ch2 & 0x3F;
					code3 = ch3 & 0x3F;                         
					unicode = (code1 << 12) | (code2 << 6) | code3;
					if ((unicode >= 0x800 && unicode <0xD800) || (unicode > 0xDFFF && unicode <= 0xFFFF)){
						putchar(unicode >> 8);                     
						putchar(unicode & 0xFF);                   
						flag = 1;
					}
					
				}
				                                     
			}
		                                        
		}
		else if ((ch1 & 0xF8) == 0xF0){                                         //encoding to utf16 in 4 bytes if encoding in utf8 was in 4 bytes
			if (((ch2 = getchar()) != EOF) && ((ch2 & 0xC0) == 0x80)){             
				if (((ch3 = getchar()) != EOF) && ((ch3 & 0xC0) == 0x80)){
					if (((ch4 = getchar()) != EOF) && ((ch4 & 0xC0) == 0x80)){
						code1 = ch1 & 0x7;
						code2 = ch2 & 0x3F;
						code3 = ch3 & 0x3F;
						code4 = ch4 & 0x3F;                                     
						unicode = (code1 << 18) | (code2 << 12) |(code3 << 6) | code4;
						if (unicode >= 0x10000 && unicode <= 0x10FFFF){
							B = unicode - 0x10000;
							B1 = B >> 10;
							B2 = B & 0x3FF;
							A1 = B1 + 0xD800;
							A2 = B2 + 0xDC00;
							putchar(A1 >> 8);
							putchar(A1 & 0xFF);
							putchar(A2 >> 8);
							putchar(A2 &0xFF);
							flag = 1;
						}
						
					}
					
				}
				
			}                             
			
		}
		if (flag == 0)
			printf("invalid data\n");
	}
	return 0;
}

