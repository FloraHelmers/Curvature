import pandas as pd 
import networkx as nx 
from tqdm import tqdm
import os 

save_node_dataframe = False 
resultpath = "country_graphs"


global_graphs = ["2008graphdumps1199167200.1199170800.graphml", "2010graphdumps1262844000.1262847600.graphml", "2014graphdumps1388556000.1388559600.graphml", "2018graphdumps1527832800.1527836400.graphml","2023graphdumps1702188000.1702191600.graphml"]
print([path[7:11] for path in ["graphs/"+gg for gg in global_graphs]][4])
for path in [gg for gg in global_graphs].reversed():
#for path in ["graphs/2023graphdumps1702188000.1702191600.graphml"]:
    print(path)

    year = int(path[7:11])
    print(f"Starting {year} {path}")
    G = nx.read_graphml(path)
    
    print(f"Create nodes dataframe {year}")
    nodes_dict = []
    for i, j in G.nodes(data=True):
        d = j.copy()
        d["ID"] = i
        nodes_dict.append(d)
    for i, j, k in G.edges(data=True):
        if "addCount" in k.keys():
            del k["addCount"]
        if "prefcount" in k.keys():
            del k["prefcount"]  
    nx.write(f"{year}cleaned.graphml")
    
    print("Graph prepared")
    df_nodes = pd.DataFrame.from_dict(nodes_dict)
    if save_node_dataframe:
        df_nodes.to_csv(f"{resultpath}/{year}nodes.csv")

    for country_code in tqdm(df_nodes["Country"].unique()):
        print(f"Doing {country_code}")
        df_country_nodes = df_nodes.loc[df_nodes.Country == country_code]
        country_nodes = set(df_country_nodes["ID"])
        for id in df_country_nodes["ID"]:
            country_nodes = country_nodes.union(G.neighbors(id))
        G_country = nx.induced_subgraph(G, country_nodes)  
        

        if not os.path.isdir(f"{resultpath}/{country_code}"):
            os.mkdir(f"{resultpath}/{country_code}")
        nx.write_graphml(G_country, f"{resultpath}/{country_code}/{year}{country_code}.graphml")