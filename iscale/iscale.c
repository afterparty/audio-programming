#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[]) {
    
    int notes, i;
    int ismidi = 0;
    int write_interval = 0;
    int err = 0;
    double startval, basefreq, ratio;
    FILE* fp;
    double intervals[25];
    char flag;
    
    while (argc > 1) {
        if (argv[1][0] == '-') {
            flag = argv[1][1];
            if( flag == 'm') 
                ismidi = 1;
            else if (flag == 'i')
                write_interval = 1;
            else {
                printf("Error: incorrect flag option %s \n", argv[1]);
                return 1;
            }
            argc--;
            argv++;
        }
        else {
            break; 
        }
    }
    
    if( argc < 3 ) {
        printf("Error: this program takes at least 2 arguments");
        printf("Usage: itable [-m][-i] N startval [outfile.txt]\n");
        return 1;
    }   
    
    notes = atoi(argv[1]);
    if (notes < 1 || notes > 24) {
        printf("Error: N out of range. Must be between 1 and 24\n");
        return 1;
    }
    
    startval = atof(argv[2]);
    
    if (ismidi){
        if (startval > 127.0) {
            printf("Error: MIDI startval must be <= 127\n");
            return 1;
        }
        if (startval < 0.0) {
            printf("Error: MIDI startval must be >= 0\n");
            return 1;
        }
    }
    else {
        if (startval <= 0.0) {
            printf("Error: frequency startval must be positive\n");
            return 1;
        }
    }
    
    fp = NULL;
    if (argc == 4) {
        fp = fopen(argv[3], "w");
        if (fp == NULL) {
            printf("Warning: unable to create file %s \n", argv[3]);
            perror(" ");
        }
    }
    
    if (ismidi) {
        double c0, c5;
        ratio = pow(2.0, 1.0 / 12.0);
        c5 = 220.0 * pow(ratio,3);
        c0 = c5 * pow(0.5, 4);
        basefreq = c0 * pow(ratio, startval);
    }
    else {
        basefreq = startval;
    }
    
    ratio = pow(2.0, 1.0/notes);
    for (i = 0; i <= notes; i++) {
        intervals[i] = basefreq;
        basefreq *= ratio;
    }
    
    for(i = 0; i <= notes; i++) {
        if(write_interval)
            printf("%d:\t%f\t%f\n", i , pow(ratio,i), intervals[i]);
        else 
            printf("%d:\t%f\n", i, intervals[i]);
        
        if (fp){
            if (write_interval)
                err = fprintf(fp, "%d:\t%f\t%f\n", i, pow(ratio,i), intervals[i]);
        }
    }
    
    
    return 0;
}