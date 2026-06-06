#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include <string>
#include "platform.h"

// 空格
#define upspace 3
#define leftspace 4

inline void go(int x, int y) {
	platform::gotoxy((x + leftspace) * 2, y + upspace);
}

inline void dire_mark() {
	puts("\t      N");
	puts("\t      |");
	puts("\t W----|----E");
	puts("\t      |");
	puts("\t      S");
}

inline void a3_hell_print() {
	puts("				_________");
	puts("				|       |");
	puts("				|深   渊|");
	puts("				|_______|");
	puts("		 		  |   |");
	puts("		 		  |   |");
	puts("		 		  |   |");
	puts("		 		  |   |");
	puts("		 		  |   |    彼");
	puts("		 		  |   |");
	puts("		 		  |   |    岸");
	puts("		 		  |   |");
	puts("		 		  |   |    花");
	puts("				  |   |");
	puts("		 		  |   |    群");
	puts("		 		  |   |");
	puts("		 		  |   |");
	puts("		 		  |   |");
	puts("		 		  |   |");
	puts("			    ______|___|______");
	puts("			    |               |");
	puts("			    |     前  殿    |");
	puts("			    |_______________|");
	puts("		 		  |   |");
	puts("			 _________|___|_________");
	puts("			 |                     |");
	puts("			 |       大   殿       |");
	puts("			 |_____________________|");
	puts("				  |   |");
	puts("		  ____________  __|___|____");
	puts("		  |          |__|         |");
	puts("		  | 后 花 园 |__|  后 殿  |");
	puts("		  |__________|	|_________|");
	puts("		      |  |");
	puts("	 	 _____|__|____");
	puts("		 |           |");
	puts("		 |地 狱 乏 火|");
	puts("		 |___________|");
	go(-4, 15); dire_mark(); go(-4, 37);
	go(-4, 15);
	dire_mark();
	go(-4, 37);
}

#endif // PRINT_H
