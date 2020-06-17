#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

class ActorGraph {
  protected:
    // TODO: add data structures used in actor graph

    // map: movie -> list of actors in movie
    // unordered_map<string, vector<string>> movies;
    // actor -> list of the pair of actor's neighbor and what movie
    // unordered_map<string, vector<pair<string, string>>> neighbors;

    class Movie;

  public:
    // map: movie -> list of actors in movie
    unordered_map<string, vector<string>> movies;
    // actor -> list of the pair of actor's neighbor and what movie
    unordered_map<string, vector<pair<string, string>>> neighbors;
    // // aSet make sure its visited
    // set<string> aSet;
    /* TODO */
    ActorGraph();

    /* TODO */
    bool buildGraph(istream& is);

    /* TODO */
    void BFS(const string& fromActor, const string& toActor,
             string& shortestPath);

    /* TODO */
    ~ActorGraph();
};

#endif  // ACTORGRAPH_HPP
