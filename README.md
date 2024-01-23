# Curvature
The goal of this project is to be able to compute the Ricci flows in a graph (cite paper). 

To build the project : 
`cmake --build .`

In order to run the algorithm on a BGP graph (format graphml). Run the following command: 
`./Bgp -P result_directory -G graph_name -NI Number_of_Ricci_flow_iterations ` 

**-P** result_directory **-G** graph_name **-NI** Number_of_Ricci_flow_iterations

**( -P** /home/Curvature/Results **-G** /home/Curvature/data/graph.graphml **-NI** 30 **)**




