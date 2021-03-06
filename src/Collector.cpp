//
// Created by dido-ubuntu on 12/02/16.
//

#include "Collector.h"
#include "Helper.h"


using namespace std;
using namespace ff;

Points * Collector::svc(Points * centers) {

#ifdef PRINTINFO
    cout <<"Collector has received "<< centers->num<<" centers "<<endl;
    //centers->to_string();
#endif

    if(finalCenters->num + centers->num > clustersize ){
        cout<<"Collector: no more space for centers ..." << endl;
        ff_send_out(EOS);
    }

    if(centers->num == 0)
        ff_send_out(EOS);

    int k = finalCenters->num;

    //copy centers
    for (int i=0; i < centers->num; ++i) {
            memcpy( finalCenters->p[k].coord, centers->p[i].coord, centers->dim * sizeof(float));
            finalCenters->p[k].weight = centers->p[i].weight;
        //finalCenters->p[k].weight = 1.0; //prova dido
            finalCenters->p[k].ID = centers->p[i].ID;
            //finalCenters->p[k].assign = centers->p[i].assign;
            //finalCenters->p[k].cost = centers->p[i].cost;
            //centerIDs[k] = i + offset;
        k++;
    }

    long num = centers->num;

    finalCenters->addNumberPoints(num);

    delete centers;

    return GO_ON;

};

void Collector::svc_end() {

    long kFinal;

    kFinal = sc.findCenters(finalCenters);

#ifdef PRINTINFO
    cout<<"Collector finish local search on final centers " <<endl;
#endif
    sc.contcenters(finalCenters);

#ifdef PRINTINFO
    cout<<"Collector finish cont center:"<< endl;
#endif
    sc.myOutcenterIDs(finalCenters, outFile);

#ifdef PRINTINFO
    cout<<"Collector " << finalCenters->num <<" points in "<<finalCenters->dim <<" dimension" <<endl;
#endif


    free(centerBlock);
    delete finalCenters;

}
