#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//because microsoft c compilers do not include a definition of pi
#ifndef M_PI
#define M_PI (3.141592654)
#endif

enum { ARG_NAME, ARG_NSAMPS, ARG_FREQ, ARG_SR, ARG_NARGS };

int main(int argc, char** argv) {
    int i, nsamps;
    double samp, freq, srate;
    double twopi = 2.0 * M_PI;
    double angleincr;
    
    if (argc != ARG_NARGS) {
        fprintf(stderr, "Usage: sinetext2 nsamps freq srate\n"); 
        return 1;
    }
    
    nsamps = atoi(argv[ARG_NSAMPS]);
    freq = atoi(argv[ARG_FREQ]);
    srate = atoi(argv[ARG_SR]);
    angleincr = twopi / nsamps;
    
    for (i = 0; i < nsamps; i++) {
        samp = sin(angleincr * i);
        fprintf(stdout, "%.8lf\n", samp);
    } 
    
    fprintf(stderr, "done\n");
    return 0;
}