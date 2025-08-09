#ifndef _H_POSITION_H_
#define _H_POSITION_H_

struct position_s {
    float lon;
    float lat;
    float elevation;
    int time; //timestamp
};

typedef position_s position ;

#endif
