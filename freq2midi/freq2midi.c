#include <stdio.h>
#include <math.h>

double midi_to_freq(double, double, double, double);

int main(){
    double fracmidi;
    double semitone_ratio = 0;
    double c0;
    double c5;
    double lower_freq;
    double upper_freq;
    double whole_semi_diff;
    double partial_diff;
    int midinote;
    
    //given frequency
    double frequency = 898.11;
    
    semitone_ratio = pow(2, (1 / 12.0));
    c5 = 220.0 * pow(semitone_ratio, 3);
    c0 = c5 * pow(0.5, 5);
    
    fracmidi = log(frequency / c0) / log(semitone_ratio);
    midinote = (int) (fracmidi + 0.5);
    
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