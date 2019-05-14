#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//because microsoft c compilers do not include a definition of pi
#ifndef M_PI
#define M_PI (3.141592654)
#endif

enum { ARG_NAME, ARG_OUTFILE, ARG_DUR, ARG_HZ, ARG_SR, ARG_SLOPE, ARG_NARGS };

int main(int argc, char** argv) {
    int i, nsamps;
    double samp, freq, srate, k, a, x, slope;
    double twopi = 2.0 * M_PI;
    double angleincr;
    double maxsamp = 0.0;
    FILE* fp = NULL;
    
    if (argc != ARG_NARGS) {
        fprintf(stderr, "Usage: sinetext2 nsamps freq srate slope\n"); 
        return 1;
    }
    
    fp = fopen(argv[ARG_OUTFILE], w);
    if (fp = NULL) {
        fprintf(stderr, "Error creating output file %s\n", argv[ARG_OUTFILE]);
        return 1;
    }
    
    dur = atoi(argv[ARG_DUR]);
    freq = atoi(argv[ARG_HZ]);
    srate = atoi(argv[ARG_SR]);
    slope = atoi(argv[ARG_SLOPE]);
    nsamps = (int) (dur * srate);
    angleincr = twopi * freq / srate;
    k = dur / nsamps;
    a = exp(-k / slope);
    x = 1.0;
    
    for (i = 0; i < nsamps; i++) {
        samp = sin(angleincr * i);
        x *= a;
        samp *= x;
        fprintf(stdout, "%.8lf\n", samp);
    }
    
    fclose(fp);
    fprintf(stderr, "done\n");
    return 0;
}