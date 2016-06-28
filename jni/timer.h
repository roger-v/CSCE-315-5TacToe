//
// Created by PASTACORK on 6/28/2016.
//

#ifndef INC_5TACTOE_TIMER_H
#define INC_5TACTOE_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif
#include <iostream>
#include <time.h>
/*
Source:
http://www.cplusplus.com/forum/beginner/317/
username: alex79roma
*/
// class declaration:
class timer {
	public:
		timer();
		void           start();
		void           stop();
		void           reset();
		bool           isRunning();
		unsigned long  getTime();
		bool           isOver(unsigned long seconds);
	private:
		bool           resetted;
		bool           running;
		unsigned long  beg;
		unsigned long  end;
};
// class implementation:

timer::timer() {
	resetted = true;
	running = false;
	beg = 0;
	end = 0;
}

void timer::start() {
	if(! running) {
		if(resetted)
			beg = (unsigned long) clock();
		else
			beg -= end - (unsigned long) clock();
		running = true;
		resetted = false;
	}
}

void timer::stop() {
	if(running) {
		end = (unsigned long) clock();
		running = false;
	}
}

void timer::reset() {
	bool wereRunning = running;
	if(wereRunning)
		stop();
	resetted = true;
	beg = 0;
	end = 0;
	if(wereRunning)
		start();
}

bool timer::isRunning() {
	return running;
}

unsigned long timer::getTime() {
	if(running)
		return ((unsigned long) clock() - beg) / CLOCKS_PER_SEC;
	else
		return end - beg;
}

bool timer::isOver(unsigned long seconds) {
	return seconds >= getTime();
}
#ifdef __cplusplus
}
#endif


#endif //INC_5TACTOE_TIMER_H
