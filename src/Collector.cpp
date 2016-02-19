//
// Created by dido-ubuntu on 12/02/16.
//

#include "Collector.h"
#include "Helper.h"


//#define NO_PRINT
#define PROFILE

#ifdef PROFILE
    double service_time = 0;
    double service_count=0;
    double prec = Helper::gettime();
#endif

using namespace std;
using namespace ff;

Points * Collector::svc(Points * centers) {

#ifdef PROFILE
    double now = Helper::gettime();
    service_time += now - prec;
    prec = now;
    service_count++;
#endif

#ifndef NO_PRINT
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

    Helper::TIME_SERVICE = service_time / service_count;

    long kFinal;

    //cout<< "=======Collector final points ===================="<< endl;
    ///finalCenters->to_string();
   // cout<< "======= end collector final points ================"<< endl;


    kFinal = sc.findCenters(finalCenters);

#ifndef NO_PRINT
    cout<<"Collector finish local search on final centers " <<endl;
#endif
    sc.contcenters(finalCenters);

#ifndef NO_PRINT
    cout<<"Collector  finish cont center:"<< endl;
    //finalCenters->to_string();
#endif
    sc.myOutcenterIDs(finalCenters,outFile);

#ifdef PROFILE
#ifndef NO_PRINT
    cout<<"Service Time : " << service_time/service_count << " s" <<endl;
#endif
#endif

    free(centerBlock);
    delete finalCenters;

}
