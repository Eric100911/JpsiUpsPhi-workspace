#include "/home/storage0/users/chiwang/storage2/CMS-Analysis/JpsiUpsPhi/workspace/includes/ParticleCand.C"
#include "secCut.C"

//#define RUN_JOB

void runSecCut(){
    TChain *chain = new TChain("outputTree","");
    #ifdef RUN_JOB
    chain->Add("JOB_DATA");
    #else
    chain->Add("/home/storage0/users/chiwang/storage2/CMS-Analysis/JpsiUpsPhi/workspace/preCut/preCut_2023_half.root");
    #endif
    secCut mySecCut(chain);
    mySecCut.Loop();
}
