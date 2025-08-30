#include <vga.h>
#include <colors.h>

void main(void){
	clear_screen();
	kprint("This is the first line\n");
	kprint("Hi my name is Akash\n");
	kprint("Testing to see if new line works\n");
	kprint_color("This should be in color green!!!\n", GREEN);
	kprint_color("Just checking to see if this wraps around you know, so i am gonna blabber some stuff and you are just gonna have to deal with it. i am making a lot of typos, i should learn typing, touch typing specifically\n", RED);
	kprint_color_bg("The background should be white and the text should be black", BLACK, WHITE);
	while(1) {}
}
