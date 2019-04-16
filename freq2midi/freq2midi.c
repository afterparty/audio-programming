/*
    The Audio Programming Book
    Exercise: 1.2.6
*/

#include <stdio.h>
#include <math.h>

double midi_to_freq(double, double, double, double);

int main(){
    double fracmidi,c0,c5,lower_freq,upper_freq,whole_semi_diff,partial_diff,semitone_ratio = 0,note_freq_diff;
    int midinote;
    char message[256];
    char* result;
    
    //given frequency
    double frequency = 440.0;
    
    semitone_ratio = pow(2, (1 / 12.0));
    c5 = 220.0 * pow(semitone_ratio, 3);
    c0 = c5 * pow(0.5, 5);
    
    printf("Enter Frequency Note: \n"); 
    result = fgets(message, sizeof(message), stdin);
    
    // check if no response
    if (result == NULL) {
        printf("There was an error reading the input. \n");
        return 1;
    }
    // check if empty
    if (message[0] == '\0'){
        printf("Peace \n");
        return 1;
    }
    frequency = atoi(message);
    
    fracmidi = log(frequency / c0) / log(semitone_ratio);
    midinote = (int) (fracmidi + 0.5);
    printf("%f \n", midinote);
    
    lower_freq = midi_to_freq((double) midinote, semitone_ratio, frequency, c0);
    upper_freq = midi_to_freq(((double) midinote + 1), semitone_ratio, frequency, c0);
    note_freq_diff = upper_freq - lower_freq;
    partial_diff = frequency - lower_freq;
    
    double pitch_bend_per = fabs((partial_diff / note_freq_diff) * 100);
    
    printf("The pitch bend of %d is %f %\n,", midinote, pitch_bend_per);
}

double midi_to_freq(double midi, double ratio, double current_freq, double c0){
    return 440 * (pow(2, ((midi - 69) / 12)));
}

// equation for getting frequency from midi note :: 440*(pow (2, (($f1-69)/12)))