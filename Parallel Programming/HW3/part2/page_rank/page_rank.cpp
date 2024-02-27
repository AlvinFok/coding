#include "page_rank.h"

#include <stdlib.h>
#include <cmath>
#include <omp.h>
#include <utility>
#include<stdio.h>

#include "../common/CycleTimer.h"
#include "../common/graph.h"


// pageRank --
//
// g:           graph to process (see common/graph.h)
// solution:    array of per-vertex vertex scores (length of array is num_nodes(g))
// damping:     page-rank algorithm's damping parameter
// convergence: page-rank algorithm's convergence threshold
//
void pageRank(Graph g, double *solution, double damping, double convergence)
{

  // initialize vertex weights to uniform probability. Double
  // precision scores are used to avoid underflow for large graphs
  
  int numNodes = num_nodes(g);
  double equal_prob = 1.0 / numNodes;
  // int no_edges_vertrx = 0;
  // int *no_edges_vertrx_array = (int*)malloc(sizeof(int) * numNodes);
  
  
  #pragma omp parallel for
  for (int i = 0; i < numNodes; ++i)
  {
    solution[i] = equal_prob;
  }
  // #pragma omp parallel for
  // for(int i = 0; i < numNodes; i++){
  //   if(outgoing_size(g,i) == 0){
  //     #pragma omp critical
  //     {
  //       no_edges_vertrx_array[no_edges_vertrx] = i;
  //       no_edges_vertrx++;
  //     }
      
  //   }
  // }
  
  bool converged = false;
  double *solution_new = (double*)malloc(sizeof(double) * numNodes);
  double sum = 0.f, old_sum = 0.f,global_diff=0.f;
  double alpha = (1.f - damping) / numNodes;
  
  while(!converged){
    old_sum = 0.f;
    // #pragma omp parallel for reduction(+:old_sum)
    // for(int i = 0; i < no_edges_vertrx; i++){
    //   old_sum += damping * solution[no_edges_vertrx_array[i]] / numNodes;
    // }
    
    #pragma omp parallel for reduction(+:sum, old_sum)
    for(int i = 0; i < numNodes; i++){
      
      sum = 0.f;
      const Vertex* begin = incoming_begin(g,i);
      const Vertex* end = incoming_end(g,i);
      /*-----------------------------------------------------------------
      score_new[vi] = sum over all nodes vj reachable from incoming edges
                          { score_old[vj] / number of edges leaving vj  }
      -------------------------------------------------------------------*/
      for(const Vertex* j =begin ; j != end; j++){
        sum += solution[*j] / outgoing_size(g,*j);
      }
      /*------------------------------------------------------------------
      score_new[vi] = (damping * score_new[vi]) + (1.0-damping) / numNodes;
      ---------------------------------------------------------------------*/
      solution_new[i] = damping * sum + alpha;
      // solution_new[i] += old_sum;
      
      if (outgoing_size(g, i) == 0)
        old_sum += solution[i];
    }
    
    /*-------------------------------------------------------------------
    score_new[vi] += sum over all nodes v in graph with no outgoing edges
                          { damping * score_old[v] / numNodes }
    ---------------------------------------------------------------------*/
      
    global_diff = 0.f;
    #pragma omp parallel for reduction(+:global_diff)
    for(int i = 0; i < numNodes; i++){
      solution_new[i] += damping * old_sum / numNodes;
      global_diff += abs(solution_new[i] - solution[i]);
      solution[i] = solution_new[i];
    }

    converged = (global_diff < convergence);
  }
  free(solution_new);
  /*
     For PP students: Implement the page rank algorithm here.  You
     are expected to parallelize the algorithm using openMP.  Your
     solution may need to allocate (and free) temporary arrays.

     Basic page rank pseudocode is provided below to get you started:
  
     // initialization: see example code above
     score_old[vi] = 1/numNodes;

     while (!converged) {

       // compute score_new[vi] for all nodes vi:
       score_new[vi] = sum over all nodes vj reachable from incoming edges
                          { score_old[vj] / number of edges leaving vj  }
       score_new[vi] = (damping * score_new[vi]) + (1.0-damping) / numNodes;

       score_new[vi] += sum over all nodes v in graph with no outgoing edges
                          { damping * score_old[v] / numNodes }

       // compute how much per-node scores have changed
       // quit once algorithm has converged

       global_diff = sum over all nodes vi { abs(score_new[vi] - score_old[vi]) };
       converged = (global_diff < convergence)
     }

   */
  
}
