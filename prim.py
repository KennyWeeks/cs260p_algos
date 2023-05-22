import numpy as np
import random
from stuff import Prim

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
    p = Prim(verticies, edges)
    p.start_building_path()
    print("This is the final value -- " + str(p.value))
