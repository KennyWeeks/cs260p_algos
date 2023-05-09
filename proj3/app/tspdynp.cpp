#include "tspdynp.hpp"
#include <iostream> // for debug purposes
#include <climits> // for UINT_MAX
#include <string>
#include <cmath>


// Solve TSP exactly, using dynamic programming.
// The grading script will use this exact function signature, so do not change it!
// The graph is given as an adjacency matrix, HOWEVER, no edges have a cost of '0'.
// The value graph[i][j] tells you the cost of an edge from i TO j.  This graph is directed.
// 		However, if graph[i][j]==0, this means there is no edge from i to j, instead of having one of that cost.
long find_other_path(std::vector<unsigned>& journey, std::vector<long>& visited, const std::vector<std::vector<long>>& graph, unsigned n) {
	//Something in visited is broken, essentially because it is memory, there can be multiple instances that are screwing with it, cause we aren't even getting to the end of the graph
	for(int i = 0; i < n; i++) {
		std::cout << visited[i] << " ";
	}
	std::cout << std::endl;

	if(journey.size() == n) {
		long last_element = journey[journey.size() - 1];
		journey.push_back(0);
		if(graph[last_element][0] == 0) {
			std::cout << "What is the element we are looking at at the end " << last_element << std::endl;
			return UINT_MAX;
		} else {
			std::cout << "This is the last element " << last_element << std::endl;
			return graph[last_element][0];
		}
	} else {
		std::cout << "We get to here " << std::endl;
		long best_value = UINT_MAX;
		long last_element = journey[journey.size() - 1];
		std::vector<unsigned> temp_journey;
		std::vector<unsigned> min_journey;
		for(int j = 0; j < n; j++) {
			//This will be the same here
			temp_journey = journey;
			temp_journey.push_back(j);
			if(visited[j] != -1 and graph[last_element][j] != 0) {
				//This means if the node hasn't already been visited and it has an edge, go down that edge
				visited[j] = -1;
				long t = graph[last_element][j] + find_other_path(temp_journey, visited, graph, n);
				//std::cout << "This is a test " << t << std::endl;
				best_value = std::min(best_value, t);
				//And then down here, you want to have a journey that you save if the new best path is found
				if(best_value == t) {
					min_journey = temp_journey;
				}
				visited[j] = 0;
			}
		}

		journey = min_journey;

		return best_value;
	}

}

long move_through_bit_mask(long i, const std::vector<std::vector<long>> & graph, int mask, std::vector<std::vector<long>> & memo, unsigned n, std::vector<unsigned> & journey) {
	//So we want to start at 0
	if((1 << i | 1) == mask) {
		//This means we have only the starting node and the another node
		if(graph[0][i] == 0) {
			return UINT_MAX;
		} else {
			journey.push_back(0);
			journey.push_back(i);
			return graph[0][i];
		}
	}

	if(memo[i][mask] != UINT_MAX) {
		if(memo[i][mask] == 0) {
			return UINT_MAX;
		} else {
			return memo[i][mask];
		}
	}

	long p_value = UINT_MAX;

	
	std::vector<unsigned> min_journey;

	for(int j = 1; j < n; j++) {
		std::vector<unsigned> temp_journey;
		if((mask & (1 << j)) != 0 and j != i and j != 0) {
			if(graph[j][i] == 0) {
				//This means that a path doesn't exist 
				continue;
			}
			long t = move_through_bit_mask(j, graph, mask ^ (1 << i), memo, n, temp_journey) + graph[j][i];
			std::cout << "This is the starting i " << i <<  " THis is the path " << j << " This is the value " << t << std::endl;
			p_value = std::min(p_value, t);
			if(p_value == t) {
				min_journey = temp_journey;
			}
		}
	}
	min_journey.push_back(i);
	std::cout << "This is for the visiting node " << i << std::endl;
	for(int j = 0; j < min_journey.size(); j++) {
		std::cout << min_journey[j] << " ";
	}
	std::cout << std::endl;
	journey = min_journey;
	memo[i][mask] = (p_value == 0) ? UINT_MAX : p_value;;
	return (p_value == 0) ? UINT_MAX : p_value;
}

std::vector<unsigned> tsp_dynamic_program(const std::vector<std::vector<long>> & graph, unsigned n)
{
	std::vector<unsigned> journey; 
	std::vector<unsigned> min_journey;

	int size = 1 << (n);
	std::cout << size << std::endl;
	std::vector<std::vector<long>> memo (n, std::vector<long>(size, UINT_MAX));
	long final_value = UINT_MAX;
	for(int i = 1; i < n; i++) {
		long t = move_through_bit_mask(i, graph, (1 << n) - 1, memo, n, journey) + graph[i][0];
		final_value = std::min(final_value, t);
		if(final_value == t) {
			min_journey = journey;
			min_journey.push_back(i);
		}
	}

	std::cout << final_value << std::endl;
	for(int i = 0; i < n; i++) {
		std::cout << min_journey[i] << " ";
	}
	std::cout << std::endl;

	return journey; 
}


// Returns the cost of the journey described here.
long costOfJourney(const std::vector<std::vector<long>> & graph, const std::vector<unsigned> & journey)
{
	long cost = 0;
	auto current = journey[0];
	auto starting = current;
	long size = journey.size();
	for(long j = 1; j < size; j++) {
		auto next = journey[j];
		cost += graph[current][next];
		current = next;
	}
	cost += graph[current][starting]; //This is a loop around, so that last directed connection is accounted for
	return cost;
}

