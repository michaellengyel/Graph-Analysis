# Graph-Analysis

**Current commands required to execute:**<br/>

$ g++ -o main Main.cpp Graph.cpp IOHandler.cpp  
$ ./main<br/>

**INFO:**  
1. Dijkstra was implemented in such a way as to support the saving of the paths. Architecture also supports the implementation of arbitrary edge weights (currently only supports weights of value 1).  
2. Minimum possible number of colors needed to color graph is calculated. The solution also gives the color of every node in the graph. A recursive algorithm was purposefully NOT chosen.  
3. The Hamilton cycle serch uses a form of backtracking instead of a naive algorithm. Backtracking was implemented without recursion. The final results give "No path found" if a solution doesn't exist, or the number of solutions and their path ID's if it does. Currently a bug exists which will cause the algorithm to run endlessly in certain graphs.<br/>
4. All algorithms are implemented in such a way as to allow the usage of arbitrary graphs and arbitrary starting and (if applicable) ending point.

**TODO:**  
1. Setup command line arguments for arbitrary input file.  
2. Setup project layout (src, include, data...).  
3. Patch bug in Hamilton Cycle causis endless serches in some cases.  
4. Refactor Graph Coloring logic.  
5. Refactor Hamilton Cycle logic.  
6. Implement graph sanity checks in Matrix.cpp (e.g node can't connect to itself).  
7. Refactor all **for** loops to use iterators.  
8. Refector Node struct. The Id variable is not needed. Change m_cost to a more generic names, since the same variable is used for different purposes in the three algorithms.  
9. In the Graph Coloring algorithm m_cost = 0 is reserved for designating the node as uncolored (open). This should be changed by using the values of the Sate enum to store this information.
