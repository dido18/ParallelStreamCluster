//
// Created by dido-ubuntu on 12/02/16.
//

#include "Collector.h"
#include "ff/node.hpp"

using namespace std;
using namespace ff;


Points * Collector::svc(Points * centers) {

    cout <<"Collector has received the centers"<<endl;

    if( finalCenters->num + centers->num > clustersize ){
        cout<<"Collector: no more space for centers ..." << endl;
        ff_send_out(EOS);
    }
    //centers->to_string();

    int k = finalCenters->num;

    for (int i = 0; i < centers->num; ++ i) {
            memcpy( finalCenters->p[k].coord, centers->p[i].coord, centers->dim * sizeof(float));
            finalCenters->p[k].weight = centers->p[i].weight;
            finalCenters->p[k].ID = centers->p[i].ID;
            //finalCenters->p[k].assign = centers->p[i].assign;
            //finalCenters->p[k].cost = centers->p[i].cost;
            //centerIDs[k] = i + offset;
        k++;
    }
    sc.printInfoTime();

    finalCenters->num +=  centers->num;
    delete centers;

    return GO_ON;
//
};

void Collector::svc_end() {

    long kFinal = sc.findCenters(finalCenters);


    cout<<"Collector: found " << kFinal << " centers" <<endl;

    sc.contcenters(finalCenters);

    finalCenters->to_string();
}
