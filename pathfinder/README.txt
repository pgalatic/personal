pathfinder readme
c Paul Galatic

Pathfinder is a program designed to find all non-looping paths in a graph.

---

Algorithm:
                                                                              |
1. Parse user input into Node objects, building a virtual graph.
2. For every node with neighbors:
	a. Use a dual-stack structure and a depth-first-search algorithm to 
		traverse the graph, keeping track of both the current path as 
		well as all nodes that have yet to be visited.
	b. As paths are found, print them out. Path lengths are in ascending 
		order.
	c. If no paths are found for a certain length, continue.
3. Return.