#include <vga.h>
#include <colors.h>

void main(void){
	clear_screen();
	kprint("This is the first line\n");
	kprint("Testing to see if new line works\n");
	kprint_color("This should be in color green!!!\n", GREEN);
	kprint_color("Just checking to see if this wraps around. This is some garbage text but it should be long enough that the text wraps to the next line\n", RED);
	kprint_color_bg("The background should be white and the text should be black", BLACK, WHITE);
	while(1) {}
}
