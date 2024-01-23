# Curvature
The goal of this project is to be able to compute the Ricci flows in a graph (cite paper). 

## Building the project
To build the project : 
`cmake --build .`


## Run on BGP graphs
In order to run the algorithm on a BGP graph (format graphml). Run the following command: 
`./Bgp -P result_directory -G graph_name -NI Number_of_Ricci_flow_iterations ` 

**-P** result_directory **-G** graph_name **-NI** Number_of_Ricci_flow_iterations

**( -P** /home/Curvature/Results **-G** /home/Curvature/data/graph.graphml **-NI** 30 **)**

### countries_BGP : to compute the Ricci flow on countries



