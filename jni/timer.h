//
// Created by PASTACORK on 6/28/2016.
//

#ifndef INC_5TACTOE_TIMER_H
#define INC_5TACTOE_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif
#include <time.h>
/*
Source:
http://www.cplusplus.com/forum/beginner/317/
username: alex79roma
*/
// class declaration:
class timer {
	public:
		timer() {
        	resetted = true;
        	running = false;
        	beg = 0;
        	end = 0;
        }
		void start() {
        	if(! running) {
        		if(resetted)
        			beg = (unsigned long) clock();
        		else
        			beg -= end - (unsigned long) clock();
        		running = true;
        		resetted = false;
        	}
        }
		void stop() {
        	if(running) {
        		end = (unsigned long) clock();
        		running = false;
        	}
        }
		void reset() {
        	bool wereRunning = running;
        	if(wereRunning)
        		stop();
        	resetted = true;
        	beg = 0;
        	end = 0;
        	if(wereRunning)
        		start();
        }
		bool isRunning() {
        	return running;
        }
		unsigned long getTime() {
        	if(running)
        		return ((unsigned long) clock() - beg) / CLOCKS_PER_SEC;
        	else
        		return end - beg;
        }
		bool isOver(unsigned long seconds) {
        	return seconds >= getTime();
        }
	private:
		bool           resetted;
		bool           running;
		unsigned long  beg;
		unsigned long  end;
};
// class implementation:
#ifdef __cplusplus
}
#endif


#endif //INC_5TACTOE_TIMER_H
