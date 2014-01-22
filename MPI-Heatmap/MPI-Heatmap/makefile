all: main.o generate_and_run_heatmap.o generate_output.o parse_coordinates.o parse_and_count_hotspots.o
	mpicc -o heatmap main.o generate_and_run_heatmap.o generate_output.o parse_coordinates.o parse_and_count_hotspots.o

main.o: main.c
	mpicc -c main.c

generate_and_run_heatmap.o: generate_and_run_heatmap.c
	mpicc -c generate_and_run_heatmap.c
	
generate_output.o: generate_output.c
	mpicc -c generate_output.c

parse_coordinates.o: parse_coordinates.c
	mpicc -c parse_coordinates.c
	
parse_and_count_hotspots.o: parse_and_count_hotspots.c
	mpicc -c parse_and_count_hotspots.c