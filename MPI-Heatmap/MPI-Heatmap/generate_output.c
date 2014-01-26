#include "heatmap.h"

int generate_output(int argc, int number_of_coords, int* coords, int width, int height, double* heatmap){
    
    MPI_File fph;
    MPI_Status status;
    char buffer;
    
    MPI_Datatype fileview = MPI_CHAR;
    MPI_File_open(MPI_COMM_SELF, "output.txt", MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fph);
    
    MPI_File_set_view(fph, (MPI_Offset)0, MPI_CHAR, fileview, "native", MPI_INFO_NULL);
    
    if (argc == 6){
        for (int coord = 0; coord < number_of_coords; coord++){
            char buf[9];
            snprintf(buf, sizeof(buf), "%f", heatmap[coords[coord*2]*height+coords[coord*2+1]]);
            MPI_File_write(fph, &buf, 8, MPI_CHAR, &status);
            buffer = (char) '\n';
            MPI_File_write(fph, &buffer, 1, MPI_CHAR, &status);}}
    else {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++){
                if (heatmap[(x*height)+y] > 0.9) {
                    buffer = 'X';
                    MPI_File_write(fph, &buffer, 1, MPI_CHAR, &status);}
                else {
                    int int_value = (int)((heatmap[(x*height)+y]+0.09)*10)/1;
                    buffer = (char)(((int)'0')+int_value);
                    MPI_File_write(fph, &buffer, 1, MPI_CHAR, &status);}}
            buffer = '\n';
            MPI_File_write(fph, &buffer, 1, MPI_CHAR, &status);}}
MPI_File_close(&fph);

return 0;}