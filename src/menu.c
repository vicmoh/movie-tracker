/***************************
 * Name: Vicky Mohammad
 * ID: 0895381
 ***************************/

#include "menu.h"

void printMenu(){
	printf("\n\n1) Add Video\n");
	printf("2) Watch Video\n");
	printf("3) Display\n");
	printf("9) Quit\n");
	printf("Please input a menu selection:\n");
}//end func

char* getVName() { size_t strSize = 80; char * line = malloc(sizeof(line)*strSize);
	printf("Please enter the video name:\n");
	fgets(line,strSize,stdin);
	//check the string size
	size_t len = strlen(line)-1;
	//malloc the size of  the string
	char* r = malloc(sizeof(char) * len); 
	strncpy(r,line, len);
	//print added
	printf("Added '%s'\n", r);
	return r;
}//end func

Video* getVideo(){
	char* name = getVName();
	Video* video = createVideo(name);
	return video;
}//end func

int addVideo(Heap * heap, Video* v){
	if( v ) {
		insertHeapNode(heap,v);
	}//end if
	return 0;
}//end func

int watchVideo(Heap * heap) {
	Video* v = getVideo();
	if( v ) {
		void * value = search(heap, v);	
		if( value ){
			Video* foundValue = (Video*)value;
			modifyTimesViewed(foundValue,1);
		}//end if
	}//end if
	return 0;
}//end func
