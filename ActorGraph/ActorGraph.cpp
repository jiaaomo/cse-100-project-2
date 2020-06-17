#include "ActorGraph.hpp"

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;
// Since I didn't create any nodes class
// everything will create on the stack when the methods call
ActorGraph::ActorGraph() {}

/* Build the actor graph from dataset file.
 * Each line of the dataset file must be formatted as:
 * ActorName <tab> MovieName <tab> Year
 * Two actors are connected by an undirected edge if they have worked in a movie
 * before.
 */
bool ActorGraph::buildGraph(istream& is) {
    bool readHeader = false;

    while (is) {
        string s;
        if (!getline(is, s)) break;

        // skip the header of the file
        if (!readHeader) {
            readHeader = true;
            continue;
        }

        // read each line of the dataset to get the movie actor relation
        istringstream ss(s);
        vector<string> record;
        while (ss) {
            string str;
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        // if format is wrong, skip current line
        if (record.size() != 3) {
            continue;
        }

        // extract the information
        string actor(record[0]);
        string title(record[1]);
        int year = stoi(record[2]);

       
        // TODO: we have an actor/movie relationship to build the graph
        string newYear = to_string(year);

        string newTitle = title + "#@" + newYear;
        movies[newTitle].push_back(actor);
    }
    // actor's Nei, actor's Mov
    for (auto& mA : movies) {
        vector<string> actors = mA.second;  // neigbors' movies
        for (auto const& actor : actors) {  // for each
            for (auto const& actorNeighbor : actors) {
                if (actor == actorNeighbor) {
                    continue;
                } else {
                    // cout << actor << " : " << actorNeighbor << endl;
                    neighbors[actorNeighbor].push_back(
                        make_pair(actor, mA.first));
                }
            }
        }
    }
    // if failed to read the file, clear the graph and return
    if (!is.eof()) {
        cerr << "Failed to read " << endl;
        return false;
    }
    return true;
}

/* TODO */
void ActorGraph::BFS(const string& fromActor, const string& toActor,
                     string& shortestPath) {
    // check both actors are in the map
    if (neighbors.find(fromActor) == neighbors.end() ||
        neighbors.find(toActor) == neighbors.end()) {
        cout << "Actor is not in the map! " << endl;
        return;
    }
    pair<string, string> aPair;
    aPair.first = "(" + fromActor + ")";
    aPair.second = fromActor;
    //
    cout << "Before: " << shortestPath << endl;

    // queue contains pair of <path, actorNei>
    queue<pair<string, string>> toExpl;
    set<string> aSet;

    string final;
    toExpl.push(aPair);
    while (!toExpl.empty()) {
        pair<string, string> newPair = toExpl.front();
        toExpl.pop();
        string path = newPair.first;
        string curr = newPair.second;
        if (curr == toActor) {
            shortestPath = path;
            cout << shortestPath << endl;
            final = shortestPath;
            return;
        } else {
            if (aSet.count(curr)) {
                continue;
            }
            aSet.insert(curr);
            for (auto elem : neighbors[curr]) {
                if (aSet.count(elem.first)) {
                    continue;
                }
                string newPath = path + "--[" + elem.second + "]-->" + "(" +
                                 elem.first + ")";
                toExpl.push(make_pair(newPath, elem.first));
            }
            // cout << "the new Path: " << newPath << endl;
        }
    }
}

// Since everything created in the stack
// the graph will get auto deleted after code run
ActorGraph::~ActorGraph() {}
