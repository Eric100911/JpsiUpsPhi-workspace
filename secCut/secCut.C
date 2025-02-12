#define secCut_cxx
#include "/home/storage0/users/chiwang/storage2/CMS-Analysis/JpsiUpsPhi/workspace/secCut/secCut.h"
#include "/home/storage0/users/chiwang/storage2/CMS-Analysis/JpsiUpsPhi/workspace/includes/ParticleCand.C"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <memory>
#include <cstdio>

// Include the header file for the roofit.
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooPlot.h"
#include "RooGaussian.h"
#include "RooArgList.h"
#include "RooFitResult.h"
#include "RooChebychev.h"

#define CUT_DR

void secCut::Loop()
{
    if (fChain == 0) return;

    Long64_t nentries = fChain->GetEntriesFast();\
    
    printf("Entries: %lld\n", nentries);

    const unsigned int nBins = 20;
    const unsigned int nBin_cut = 20;
    const unsigned int nCandsAllowed = 20;

    // Use Roofit to draw the plot with proper error bars.
    // Define mass histograms for Jpsi, Phi and Pri passing the cut. Using Roofit.
    RooRealVar Jpsi_mass_var("Jpsi1_mass_cut", "Jpsi1_mass_cut", 2.5, 3.5);
    RooRealVar Ups_mass_var("Jpsi2_mass_cut", "Jpsi2_mass_cut", 2.5, 3.5);
    RooRealVar Phi_mass_var("Phi_mass_cut","Phi_mass_cut", 8.0, 12.0);
    RooRealVar Pri_mass_var("Pri_mass_cut","Pri_mass_cut", 0.0, 100.0);

    // Define dataset for Jpsi, Phi and Pri passing the cut. Using Roofit.
    RooDataSet Jpsi_mass_set_multi("Jpsi_mass_set_multi", "Jpsi_mass_set_multi", RooArgList(Jpsi_mass_var));
    RooDataSet Ups_mass_set_multi("Ups_mass_set_multi", "Ups_mass_set_multi", RooArgList(Ups_mass_var));
    RooDataSet Phi_mass_set_multi("Phi_mass_set_multi", "Phi_mass_set_multi", RooArgList(Phi_mass_var));
    RooDataSet Pri_mass_set_multi("Pri_mass_set_multi", "Pri_mass_set_multi", RooArgList(Pri_mass_var));

    // Define dataset for Jpsi, Phi and Pri passing the cut. Using Roofit. Removed the multiple candidates.
    RooDataSet Jpsi_mass_set("Jpsi_mass_set", "Jpsi_mass_set", RooArgList(Jpsi_mass_var));
    RooDataSet Ups_mass_set("Ups_mass_set", "Ups_mass_set", RooArgList(Ups_mass_var));
    RooDataSet Phi_mass_set("Phi_mass_set", "Phi_mass_set", RooArgList(Phi_mass_var));
    RooDataSet Pri_mass_set("Pri_mass_set", "Pri_mass_set", RooArgList(Pri_mass_var));

    // --- Register your cut parameters here  ---

    double Jpsi_Ups_DR_max = 10.0;
    double Jpsi_Phi_DR_max    = 10.0;
    double Ups_Phi_DR_max    = 10.0;

    double Jpsi_Ups_DR_min = 0.0;
    double Jpsi_Phi_DR_min = 0.0;
    double Ups_Phi_DR_min  = 0.0;

    double Ups_pT_min = 6.0;
    double Ups_mu_pT_min = 4.0;

    bool Ups_mu_require_medium = true;
    bool Ups_mu_require_loose  = false;
    bool Ups_mu_require_tight  = false;


    // --- End of cut parameters registration ---

    Long64_t nbytes = 0, nb = 0;
    for(Long64_t jentry=0; jentry<nentries;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        // if (Cut(ientry) < 0) continue;


        // Marker set to show the progress.
        if(jentry % 500 == 0){
            printf("Processing entry %ld\n", jentry);
        }

        #ifdef TRY_E4

        if(jentry == 10000){
            break;
        }

        #endif

        // Loop over all candidates.

        std::vector<std::shared_ptr<ParticleCand> > CandList;
        ParticleCand tempCand;
        ParticleCand::PartIdxList_t tempList;
        double temp_massChi2;

        for (unsigned int iCand = 0; iCand < Jpsi_mass->size(); iCand++){
            bool passCut = true;

            // Calculate the DRs
            double Jpsi_Ups_DR = sqrt((Jpsi_eta->at(iCand) - Ups_eta->at(iCand)) * (Jpsi_eta->at(iCand) - Ups_eta->at(iCand))
                                    + (Jpsi_phi->at(iCand) - Ups_phi->at(iCand)) * (Jpsi_phi->at(iCand) - Ups_phi->at(iCand)));
            double Jpsi_Phi_DR = sqrt((Jpsi_eta->at(iCand) - Phi_eta->at(iCand)) * (Jpsi_eta->at(iCand) - Phi_eta->at(iCand)) 
                                    + (Jpsi_phi->at(iCand) - Phi_phi->at(iCand)) * (Jpsi_phi->at(iCand) - Phi_phi->at(iCand)));
            double Ups_Phi_DR  = sqrt(( Ups_eta->at(iCand) - Phi_eta->at(iCand)) * ( Ups_eta->at(iCand) - Phi_eta->at(iCand))
                                     +( Ups_phi->at(iCand) - Phi_phi->at(iCand)) * ( Ups_phi->at(iCand) - Phi_phi->at(iCand)));

            // Apply DR cuts

            #ifdef CUT_DR

            if (Jpsi_Ups_DR < Jpsi_Ups_DR_min || Jpsi_Ups_DR > Jpsi_Ups_DR_max){
                passCut = false;
            }

            if (Jpsi_Phi_DR < Jpsi_Phi_DR_min || Jpsi_Phi_DR > Jpsi_Phi_DR_max){
                passCut = false;
            }

            if (Ups_Phi_DR < Ups_Phi_DR_min || Ups_Phi_DR > Ups_Phi_DR_max){
                passCut = false;
            }

            #endif

            // Apply Upsilon cuts
            if (Ups_pt->at(iCand) < Ups_pT_min){
                passCut = false;
            }

            // Apply muon cuts
            if (Ups_mu_1_pt->at(iCand) < Ups_mu_pT_min || Ups_mu_2_pt->at(iCand) < Ups_mu_pT_min){
                passCut = false;
            }

            if (Ups_mu_require_medium && (!Ups_mu_1_isPatMediumMuon->at(iCand) || !Ups_mu_2_isPatMediumMuon->at(iCand))){
                passCut = false;
            }

            if (Ups_mu_require_loose && (!Ups_mu_1_isPatLooseMuon->at(iCand) || !Ups_mu_2_isPatLooseMuon->at(iCand))){
                passCut = false;
            }

            if (Ups_mu_require_tight && (!Ups_mu_1_isPatTightMuon->at(iCand) || !Ups_mu_2_isPatTightMuon->at(iCand))){
                passCut = false;
            }

            if (!passCut){
                continue;
            }

            // Fill the temporary candidate.
            tempList.clear();
            tempCand.Clear();
            tempCand.SetId(iCand);

            tempList.push_back(Jpsi_mu_1_Idx->at(iCand));
            tempList.push_back(Jpsi_mu_2_Idx->at(iCand));
            tempList.push_back(Ups_mu_1_Idx->at(iCand));
            tempList.push_back(Ups_mu_2_Idx->at(iCand));
            tempCand.AddParticle(ParticleCand::PartType::Muon, tempList);
            tempList.clear();
            tempList.push_back(Phi_K_1_Idx->at(iCand));
            tempList.push_back(Phi_K_2_Idx->at(iCand));
            tempCand.AddParticle(ParticleCand::PartType::Track, tempList);
            tempList.clear();

            temp_massChi2 = (Jpsi_massDiff->at(iCand) / Jpsi_massErr->at(iCand)) * (Jpsi_massDiff->at(iCand) / Jpsi_massErr->at(iCand)) +
                             (Ups_massDiff->at(iCand) /  Ups_massErr->at(iCand)) *  (Ups_massDiff->at(iCand) /  Ups_massErr->at(iCand)) +
                             (Phi_massDiff->at(iCand) /  Phi_massErr->at(iCand)) *  (Phi_massDiff->at(iCand) /  Phi_massErr->at(iCand));

            tempCand.SetScore(temp_massChi2);
            CandList.push_back(std::make_shared<ParticleCand>(tempCand));
        }
        if(CandList.size() == 0){
            continue;
        }
        // Save all filtered candidates to the tree.
        for (auto cand: CandList){
            filtered_Jpsi_mass->push_back(Jpsi_mass->at(cand->GetId()));
            filtered_Jpsi_massErr->push_back(Jpsi_massErr->at(cand->GetId()));
            filtered_Jpsi_massDiff->push_back(Jpsi_massDiff->at(cand->GetId()));
            filtered_Jpsi_ctau->push_back(Jpsi_ctau->at(cand->GetId()));
            filtered_Jpsi_ctauErr->push_back(Jpsi_ctauErr->at(cand->GetId()));
            filtered_Jpsi_Chi2->push_back(Jpsi_Chi2->at(cand->GetId()));
            filtered_Jpsi_ndof->push_back(Jpsi_ndof->at(cand->GetId()));
            filtered_Jpsi_VtxProb->push_back(Jpsi_VtxProb->at(cand->GetId()));
            filtered_Jpsi_px->push_back(Jpsi_px->at(cand->GetId()));
            filtered_Jpsi_py->push_back(Jpsi_py->at(cand->GetId()));
            filtered_Jpsi_pz->push_back(Jpsi_pz->at(cand->GetId()));
            filtered_Jpsi_phi->push_back(Jpsi_phi->at(cand->GetId()));
            filtered_Jpsi_eta->push_back(Jpsi_eta->at(cand->GetId()));
            filtered_Jpsi_pt->push_back(Jpsi_pt->at(cand->GetId()));
            filtered_Jpsi_mu_1_Idx->push_back(Jpsi_mu_1_Idx->at(cand->GetId()));
            filtered_Jpsi_mu_2_Idx->push_back(Jpsi_mu_2_Idx->at(cand->GetId()));

            filtered_Phi_mass->push_back(Phi_mass->at(cand->GetId()));
            filtered_Phi_massErr->push_back(Phi_massErr->at(cand->GetId()));
            filtered_Phi_massDiff->push_back(Phi_massDiff->at(cand->GetId()));
            filtered_Phi_ctau->push_back(Phi_ctau->at(cand->GetId()));
            filtered_Phi_ctauErr->push_back(Phi_ctauErr->at(cand->GetId()));
            filtered_Phi_Chi2->push_back(Phi_Chi2->at(cand->GetId()));
            filtered_Phi_ndof->push_back(Phi_ndof->at(cand->GetId()));
            filtered_Phi_VtxProb->push_back(Phi_VtxProb->at(cand->GetId()));
            filtered_Phi_px->push_back(Phi_px->at(cand->GetId()));
            filtered_Phi_py->push_back(Phi_py->at(cand->GetId()));
            filtered_Phi_pz->push_back(Phi_pz->at(cand->GetId()));
            filtered_Phi_phi->push_back(Phi_phi->at(cand->GetId()));
            filtered_Phi_eta->push_back(Phi_eta->at(cand->GetId()));
            filtered_Phi_pt->push_back(Phi_pt->at(cand->GetId()));
            filtered_Phi_K_1_Idx->push_back(Phi_K_1_Idx->at(cand->GetId()));
            filtered_Phi_K_2_Idx->push_back(Phi_K_2_Idx->at(cand->GetId()));

            filtered_Pri_mass->push_back(Pri_mass->at(cand->GetId()));
            filtered_Pri_massErr->push_back(Pri_massErr->at(cand->GetId()));
            filtered_Pri_ctau->push_back(Pri_ctau->at(cand->GetId()));
            filtered_Pri_ctauErr->push_back(Pri_ctauErr->at(cand->GetId()));
            filtered_Pri_Chi2->push_back(Pri_Chi2->at(cand->GetId()));
            filtered_Pri_ndof->push_back(Pri_ndof->at(cand->GetId()));
            filtered_Pri_VtxProb->push_back(Pri_VtxProb->at(cand->GetId()));
            filtered_Pri_px->push_back(Pri_px->at(cand->GetId()));
            filtered_Pri_py->push_back(Pri_py->at(cand->GetId()));
            filtered_Pri_pz->push_back(Pri_pz->at(cand->GetId()));
            filtered_Pri_phi->push_back(Pri_phi->at(cand->GetId()));
            filtered_Pri_eta->push_back(Pri_eta->at(cand->GetId()));
            filtered_Pri_pt->push_back(Pri_pt->at(cand->GetId()));

            filtered_Ups_mass->push_back(Ups_mass->at(cand->GetId()));
            filtered_Ups_massErr->push_back(Ups_massErr->at(cand->GetId()));
            filtered_Ups_massDiff->push_back(Ups_massDiff->at(cand->GetId()));
            filtered_Ups_Chi2->push_back(Ups_Chi2->at(cand->GetId()));
            filtered_Ups_ndof->push_back(Ups_ndof->at(cand->GetId()));
            filtered_Ups_VtxProb->push_back(Ups_VtxProb->at(cand->GetId()));
            filtered_Ups_px->push_back(Ups_px->at(cand->GetId()));
            filtered_Ups_py->push_back(Ups_py->at(cand->GetId()));
            filtered_Ups_pz->push_back(Ups_pz->at(cand->GetId()));
            filtered_Ups_phi->push_back(Ups_phi->at(cand->GetId()));
            filtered_Ups_eta->push_back(Ups_eta->at(cand->GetId()));
            filtered_Ups_pt->push_back(Ups_pt->at(cand->GetId()));
            filtered_Ups_mu_1_Idx->push_back(Ups_mu_1_Idx->at(cand->GetId()));
            filtered_Ups_mu_2_Idx->push_back(Ups_mu_2_Idx->at(cand->GetId()));

            // For the muons: copy the corresponding muon information.
            filtered_Jpsi_mu_1_px->push_back(Jpsi_mu_1_px->at(cand->GetId()));
            filtered_Jpsi_mu_1_py->push_back(Jpsi_mu_1_py->at(cand->GetId()));
            filtered_Jpsi_mu_1_pz->push_back(Jpsi_mu_1_pz->at(cand->GetId()));
            filtered_Jpsi_mu_1_pt->push_back(Jpsi_mu_1_pt->at(cand->GetId()));
            filtered_Jpsi_mu_1_eta->push_back(Jpsi_mu_1_eta->at(cand->GetId()));
            filtered_Jpsi_mu_1_phi->push_back(Jpsi_mu_1_phi->at(cand->GetId()));
            filtered_Jpsi_mu_1_isPatSoftMuon->push_back(Jpsi_mu_1_isPatSoftMuon->at(cand->GetId()));
            filtered_Jpsi_mu_1_isPatLooseMuon->push_back(Jpsi_mu_1_isPatLooseMuon->at(cand->GetId()));
            filtered_Jpsi_mu_1_isPatMediumMuon->push_back(Jpsi_mu_1_isPatMediumMuon->at(cand->GetId()));
            filtered_Jpsi_mu_1_isPatTightMuon->push_back(Jpsi_mu_1_isPatTightMuon->at(cand->GetId()));

            filtered_Jpsi_mu_2_px->push_back(Jpsi_mu_2_px->at(cand->GetId()));
            filtered_Jpsi_mu_2_py->push_back(Jpsi_mu_2_py->at(cand->GetId()));
            filtered_Jpsi_mu_2_pz->push_back(Jpsi_mu_2_pz->at(cand->GetId()));
            filtered_Jpsi_mu_2_pt->push_back(Jpsi_mu_2_pt->at(cand->GetId()));
            filtered_Jpsi_mu_2_eta->push_back(Jpsi_mu_2_eta->at(cand->GetId()));
            filtered_Jpsi_mu_2_phi->push_back(Jpsi_mu_2_phi->at(cand->GetId()));
            filtered_Jpsi_mu_2_isPatSoftMuon->push_back(Jpsi_mu_2_isPatSoftMuon->at(cand->GetId()));
            filtered_Jpsi_mu_2_isPatLooseMuon->push_back(Jpsi_mu_2_isPatLooseMuon->at(cand->GetId()));
            filtered_Jpsi_mu_2_isPatMediumMuon->push_back(Jpsi_mu_2_isPatMediumMuon->at(cand->GetId()));
            filtered_Jpsi_mu_2_isPatTightMuon->push_back(Jpsi_mu_2_isPatTightMuon->at(cand->GetId()));

            filtered_Ups_mu_1_px->push_back(Ups_mu_1_px->at(cand->GetId()));
            filtered_Ups_mu_1_py->push_back(Ups_mu_1_py->at(cand->GetId()));
            filtered_Ups_mu_1_pz->push_back(Ups_mu_1_pz->at(cand->GetId()));
            filtered_Ups_mu_1_pt->push_back(Ups_mu_1_pt->at(cand->GetId()));
            filtered_Ups_mu_1_eta->push_back(Ups_mu_1_eta->at(cand->GetId()));
            filtered_Ups_mu_1_phi->push_back(Ups_mu_1_phi->at(cand->GetId()));
            filtered_Ups_mu_1_isPatSoftMuon->push_back(Ups_mu_1_isPatSoftMuon->at(cand->GetId()));
            filtered_Ups_mu_1_isPatLooseMuon->push_back(Ups_mu_1_isPatLooseMuon->at(cand->GetId()));
            filtered_Ups_mu_1_isPatMediumMuon->push_back(Ups_mu_1_isPatMediumMuon->at(cand->GetId()));
            filtered_Ups_mu_1_isPatTightMuon->push_back(Ups_mu_1_isPatTightMuon->at(cand->GetId()));

            filtered_Ups_mu_2_px->push_back(Ups_mu_2_px->at(cand->GetId()));
            filtered_Ups_mu_2_py->push_back(Ups_mu_2_py->at(cand->GetId()));
            filtered_Ups_mu_2_pz->push_back(Ups_mu_2_pz->at(cand->GetId()));
            filtered_Ups_mu_2_pt->push_back(Ups_mu_2_pt->at(cand->GetId()));
            filtered_Ups_mu_2_eta->push_back(Ups_mu_2_eta->at(cand->GetId()));
            filtered_Ups_mu_2_phi->push_back(Ups_mu_2_phi->at(cand->GetId()));
            filtered_Ups_mu_2_isPatSoftMuon->push_back(Ups_mu_2_isPatSoftMuon->at(cand->GetId()));
            filtered_Ups_mu_2_isPatLooseMuon->push_back(Ups_mu_2_isPatLooseMuon->at(cand->GetId()));
            filtered_Ups_mu_2_isPatMediumMuon->push_back(Ups_mu_2_isPatMediumMuon->at(cand->GetId()));
            filtered_Ups_mu_2_isPatTightMuon->push_back(Ups_mu_2_isPatTightMuon->at(cand->GetId()));

            // Kaons from phi
            filtered_Phi_K_1_px->push_back(Phi_K_1_px->at(cand->GetId()));
            filtered_Phi_K_1_py->push_back(Phi_K_1_py->at(cand->GetId()));
            filtered_Phi_K_1_pt->push_back(Phi_K_1_pt->at(cand->GetId()));
            filtered_Phi_K_1_eta->push_back(Phi_K_1_eta->at(cand->GetId()));
            filtered_Phi_K_1_phi->push_back(Phi_K_1_phi->at(cand->GetId()));

            filtered_Phi_K_2_px->push_back(Phi_K_2_px->at(cand->GetId()));
            filtered_Phi_K_2_py->push_back(Phi_K_2_py->at(cand->GetId()));
            filtered_Phi_K_2_pz->push_back(Phi_K_2_pz->at(cand->GetId()));
            filtered_Phi_K_2_pt->push_back(Phi_K_2_pt->at(cand->GetId()));
            filtered_Phi_K_2_eta->push_back(Phi_K_2_eta->at(cand->GetId()));
            filtered_Phi_K_2_phi->push_back(Phi_K_2_phi->at(cand->GetId()));    
        }
        filteredTree->Fill();
        // To plot in parallel: multi candidates allowed and non-overlap candidate only.
        // For all candidates, store them all.
        for (auto cand: CandList){
            Jpsi_mass_var.setVal(Jpsi_mass->at(cand->GetId()));
            Ups_mass_var.setVal(Ups_mass->at(cand->GetId()));
            Phi_mass_var.setVal(Phi_mass->at(cand->GetId()));
            Pri_mass_var.setVal(Pri_mass->at(cand->GetId()));

            Jpsi_mass_var.setError(Jpsi_massErr->at(cand->GetId()));
            Ups_mass_var.setError(Ups_massErr->at(cand->GetId()));
            Phi_mass_var.setError(Phi_massErr->at(cand->GetId()));
            Pri_mass_var.setError(Pri_massErr->at(cand->GetId()));

            Jpsi_mass_set_multi.add(RooArgSet(Jpsi_mass_var));
            Ups_mass_set_multi.add(RooArgSet(Ups_mass_var));
            Phi_mass_set_multi.add(RooArgSet(Phi_mass_var));
            Pri_mass_set_multi.add(RooArgSet(Pri_mass_var));
        }

        // For non-overlap candidates, store them.
        std::vector<std::shared_ptr<ParticleCand> > CandList_nonOverlap;
        std::sort(CandList.begin(), CandList.end(),
            [](std::shared_ptr<ParticleCand> cand1, std::shared_ptr<ParticleCand> cand2){
                return cand1->GetScore() < cand2->GetScore();
            }
        ); 
        for (auto& cand: CandList){
            if(CandList_nonOverlap.size() == 0){
                CandList_nonOverlap.push_back(cand);
            }
            else{
                bool isOverlap = false;
                for (auto& cand_nonOverlap: CandList_nonOverlap){
                    if(cand->Overlap(*cand_nonOverlap)){
                        isOverlap = true;
                        break;
                    }
                }
                if(!isOverlap){
                    CandList_nonOverlap.push_back(cand);
                }
            }
        }
        for( auto cand: CandList_nonOverlap){
            Jpsi_mass_var.setVal(Jpsi_mass->at(cand->GetId()));
            Ups_mass_var.setVal(Ups_mass->at(cand->GetId()));
            Phi_mass_var.setVal(Phi_mass->at(cand->GetId()));
            Pri_mass_var.setVal(Pri_mass->at(cand->GetId()));

            Jpsi_mass_var.setError(Jpsi_massErr->at(cand->GetId()));
            Ups_mass_var.setError(Ups_massErr->at(cand->GetId()));
            Phi_mass_var.setError(Phi_massErr->at(cand->GetId()));
            Pri_mass_var.setError(Pri_massErr->at(cand->GetId()));

            Jpsi_mass_set.add(RooArgSet(Jpsi_mass_var));
            Ups_mass_set.add(RooArgSet(Ups_mass_var));
            Phi_mass_set.add(RooArgSet(Phi_mass_var));
            Pri_mass_set.add(RooArgSet(Pri_mass_var));
        }
        ClearBranches();
    }

    // Draw the histograms.
    TCanvas *c1 = new TCanvas("c1", "c1", 1600, 1200);
    c1->Divide(2,2);
    RooPlot* Jpsi_mass_frame = Jpsi_mass_var.frame(nBins);
    RooPlot* Ups_mass_frame = Ups_mass_var.frame(nBins);
    RooPlot* Phi_mass_frame = Phi_mass_var.frame(nBins);
    RooPlot* Pri_mass_frame = Pri_mass_var.frame(nBins);
    Jpsi_mass_set_multi.plotOn(Jpsi_mass_frame);
    Ups_mass_set_multi.plotOn(Ups_mass_frame);
    Phi_mass_set_multi.plotOn(Phi_mass_frame);
    Pri_mass_set_multi.plotOn(Pri_mass_frame);
    c1->cd(1);
    Jpsi_mass_frame->Draw();
    c1->cd(2);
    Ups_mass_frame->Draw();
    c1->cd(3);
    Phi_mass_frame->Draw();
    c1->cd(4);
    Pri_mass_frame->Draw();
    c1->SaveAs("secCut_multi.pdf");
    c1->SaveAs("secCut_multi.png");

    // Draw the histograms for the non-overlap candidates.
    TCanvas *c2 = new TCanvas("c2", "c2", 1600, 1200);
    c2->Divide(2,2);
    RooPlot* Jpsi_mass_frame_nonOverlap = Jpsi_mass_var.frame(nBins);
    RooPlot* Ups_mass_frame_nonOverlap = Ups_mass_var.frame(nBins);
    RooPlot* Phi_mass_frame_nonOverlap = Phi_mass_var.frame(nBins);
    RooPlot* Pri_mass_frame_nonOverlap = Pri_mass_var.frame(nBins);
    Jpsi_mass_set.plotOn(Jpsi_mass_frame_nonOverlap);
    Ups_mass_set.plotOn(Ups_mass_frame_nonOverlap);
    Phi_mass_set.plotOn(Phi_mass_frame_nonOverlap);
    Pri_mass_set.plotOn(Pri_mass_frame_nonOverlap);
    c2->cd(1);
    Jpsi_mass_frame_nonOverlap->Draw();
    c2->cd(2);
    Ups_mass_frame_nonOverlap->Draw();
    c2->cd(3);
    Phi_mass_frame_nonOverlap->Draw();
    c2->cd(4);
    Pri_mass_frame_nonOverlap->Draw();
    c2->SaveAs("secCut_nonOverlap.pdf");
    c2->SaveAs("secCut_nonOverlap.png");

    // Save the output tree.
    TFile *outputFile = new TFile("filtered_data_secCut.root", "RECREATE");
    filteredTree->Write();
    outputFile->Close();
}
