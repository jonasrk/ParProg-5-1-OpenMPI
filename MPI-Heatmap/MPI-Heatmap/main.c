#include "heatmap.h"

int main(int argc, const char * argv[]){
    
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);
    
    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    
    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    
    if (world_rank == 0) {
        
        int width = atoi(argv[1]);
        int height = atoi(argv[2]);
        int rounds = atoi(argv[3]) + 1; //one extra round
        int number_of_coords = 0;
        int* coords = NULL;
        int* hotspots = NULL;
        
        if (argc == 6) number_of_coords = parse_coordinates(argv[5], &coords);
        int number_of_hotspots = parse_and_count_hotspots(argv[4], &hotspots);
        double** heatmap = generate_and_run_heatmap(width, height, rounds, number_of_hotspots, hotspots);
        generate_output(argc, number_of_coords, coords, width, height, *heatmap);
        
//        if(coords != NULL) free(coords);
//        if(hotspots != NULL) free(hotspots);
//        if(*heatmap != NULL) free(*heatmap); // leads to double free or corruption ob submission system
        //TODO does last_round from generate_and_run_heatmap have to be freed to?
        
    }
    
    // Finalize the MPI environment.
    MPI_Finalize();
}

