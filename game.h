#include <signal.h>

#define INTERVAL 500000

void handleInput(int c);
void timer_setup(void);
void signal_setup(void);
void signal_handler(int signum);
void init_color_pairs(void);
void init_fixed_pieces(void);
void removeLine(int line);
void checkLine(int line);
