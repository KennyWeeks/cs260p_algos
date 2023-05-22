import numpy as np
import random
class Prim:
    def __init__(self, verticies, edges):
        print("WHAT")
        self.mst = [] #This will be a graph that represents the minimum spanning tree
        self.edge_in_graph = {k:False for k in range(verticies)} #This will simply define an empty graph of edges we have so far
        self.not_visited_count = verticies
        self.other_edges = list() #This is a lis of other edges that we have not used yet

        random_start_point = random.randint(0, verticies-1) #Select a random starting node, for the minimum spanning tree, this really doesn't matter
        for i in range(len(edges[random_start_point])):
            self.other_edges.append(edges[random_start_point][i]) #Save the edge information here, we'll sort it by the edge weight after

        self.other_edges = sorted(self.other_edges, key=lambda x:x[2]) #This will sort the list by the edge weight

        edge=self.other_edges[0] #Get the first edge here

        #We'll set the verticies of an edge here, and now we will move to the other starting node
        self.edge_in_graph[edge[0]]=True
        self.edge_in_graph[edge[1]]=True
        self.not_visited_count -= 2 #Subtract this from the list, cause these nodes have been found

        #We know because we picked the edge this is correct, so we can simply pick the next node, and make that our current node
        self.current_node = edge[1]

        del self.other_edges[0] #Delete the first edge, cause that was used, and we don't want to use it again 

        self.edges = edges #Save this for later

        #These these edges from the graph, we won't need them anymore, and we don't want them accidentaly pulled in cause this will cause a problem
        edge_index_one = self.edges[edge[0]].index(edge)
        edge_index_two = self.edges[edge[1]].index([edge[1], edge[0], edge[2]])

        del self.edges[edge[0]][edge_index_one]
        del self.edges[edge[1]][edge_index_two]

        self.value = edge[2] #THis will be the value

        print("THis is the starting node " + str(random_start_point))
        print("This is the edge " + str(edge))
        print("-----------")




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
            print("This is the current node -- " + str(self.current_node))
            for i in range(len(self.edges[self.current_node])):
                #Loop through all the edges of the current start node here
                self.other_edges.append(self.edges[self.current_node][i])
            self.other_edges = sorted(self.other_edges, key=lambda x:x[2])

            possible_edge = self.other_edges[0]#Grab the first edge again

            starting_point = 0 #This is the starting point of the current edges

            cycle = self.find_cycle(possible_edge[0], possible_edge[1])

            while not cycle:
                del self.other_edges[starting_point] #This will delete this current node from the other edges because it forms a cycle, so we for sure do not waant it
                index_of_opposite = -1
                try:
                    index_of_opposite = self.other_edges.index([possible_edge[1], possible_edge[0], possible_edge[2]])
                except:
                    index_of_opposite = -1

                if index_of_opposite != -1:
                    print("This happened")
                    del self.other_edges[index_of_opposite]

                print(str(possible_edge) + " formed a cycle")
                edge_index_one = self.edges[possible_edge[0]].index(possible_edge)
                edge_index_two = self.edges[possible_edge[1]].index([possible_edge[1], possible_edge[0], possible_edge[2]])

                del self.edges[possible_edge[0]][edge_index_one]
                del self.edges[possible_edge[1]][edge_index_two]

                possible_edge = self.other_edges[starting_point]
                print("This is the new possible_edge " + str(possible_edge))

                cycle = self.find_cycle(possible_edge[0], possible_edge[1])

            #This will set the new edge in the graph to true
            self.current_node = possible_edge[1] #So we want to look at the next vertex, which if this is done, will not have been visited
            self.not_visited_count -= 1 #This will decrement the visited counter till it reaches 0.
            self.edge_in_graph[possible_edge[0]] = True
            self.edge_in_graph[possible_edge[1]] = True

            edge_index_one = self.edges[possible_edge[0]].index(possible_edge)
            edge_index_two = self.edges[possible_edge[1]].index([possible_edge[1], possible_edge[0], possible_edge[2]])

            del self.edges[possible_edge[0]][edge_index_one]
            del self.edges[possible_edge[1]][edge_index_two]

            self.value += possible_edge[2] #This will get the last edge and it's weight

            del self.other_edges[starting_point] #Delete this edge in the graph, we didn't get a cycle, so we don't need it anymore


            index_of_opposite = -1
            try:
                index_of_opposite = self.other_edges.index([possible_edge[1], possible_edge[0], possible_edge[2]])
            except:
                index_of_opposite = -1

            if index_of_opposite != -1:
                print("This happened")
                del self.other_edges[index_of_opposite]