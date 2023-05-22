import numpy as np
import random

class Prim:
    def _init_(self, veritices, edges):
        self.mst = [] #This will be a graph that represents the minimum spanning tree
        self.edge_in_graph = {k:False for k in range(verticies)} #This will simply define an empty graph of edges we have so far
        self.not_visited_count = verticies
        self.other_edges = list() #This is a lis of other edges that we have not used yet

        random_start_point = random.randint(0, verticies) #Select a random starting node, for the minimum spanning tree, this really doesn't matter
        for i in range(len(edges[random_start_point])):
            self.other_edges.append(edges[random_start_point][i]) #Save the edge information here, we'll sort it by the edge weight after

        sorted(self.other_edges, key=lambda x:x[2]) #This will sort the list by the edge weight

        edge=self.other_edges[0] #Get the first edge here

        #We'll set the verticies of an edge here, and now we will move to the other starting node
        self.edges_in_graph[edges[0]]=True
        self.edges_in_graph[edges[1]]=True
        self.not_visited_count -= 2 #Subtract this from the list, cause these nodes have been found

        #This will be the next starting node
        self.current_node = edges[1]

        del self.other_edges[0] #Delete the first edge, cause that was used, and we don't want to use it again 
        ...
    
    def find_cycle(self, first, second):
        #This will find a cycle in the graph, essentially, it will just check to see if the edge being added makes a cycle
        if self.edge_in_graph[first]:
            #This means the vertex was set to true at some point, which may be fine, we just need to make sure the second node is also not true
            if self.edge_in_graph[second]:
                #This means at some point, these two verticies were already used in the path, and you are closing it to make it a cycle
                return False
            else:
                return True
        else:
            #This means that the vertex has never been added to the list, so there is nothing on the path that exists to determin if it's part of a cycle
            return True

    def start_building_path(self):
        #This will start building the path from the current starting node
        while self.not_visited_count != 0:
            #You essentially want to keep this loop going until you have completely run out of edges
            for i in range(len(edges[self.current_node])):
                #Loop through all the edges of the current start node here
                self.other_edges.append(edges[self.current_node][i])

            sorted(self.other_edges, key=lambda x:x[2])#This will sort again by edge weights

            possible_edge = self.other_edges[0]#Grab the first edge again

            starting_point = 0 #This is the starting point of the current edges

            cycle = self.find_cycle(possible_edge[0], possible_edge[1])

            while not cycle:
                starting_point += 1
                possible_edge = self.other_edges[starting_point]

            #This will set the new edge in the graph to true
            self.edge_in_graph[possible_edge[0]] = True
            self.edge_in_graph[possible_edge[1]] = True

            del self.other_edges[starting_point] #Delete this edge in the graph, we didn't get a cycle, so we don't need it anymore

if __name__ == "__main__":
    verticies = 9 
    input = [[0, 1, 4], [0, 7, 8], [1,7,11], [1,2,8], [2,8,2], [2,3,7], [7,6,1], [7,8,7], [6,8,6],[6,5,2],[5,2,4],[5,3,14],[5,4,10], [3,4,9]]

    edges = {k:[] for k in range(verticies)} #We'll make a dictionary that is associated with each vertex, and the list will be it's edge data, and the weight, it will be sorted by the edge
    for i in input:
        print(i)
        edges[i[0]].append(i) #We'll just append the item to this list here
        edges[i[1]].append([i[1], i[0], i[2]]) #This will save the edge in reverse other, considering this is an undirected graph

    for i in edges:
        #This will sort all the lists here
        lst=edges[i]
        lst=sorted(lst, key=lambda lst:lst[1]) #This is the list that needs to be sorted
        print(lst)
        edges[i]=lst

    print(edges)
