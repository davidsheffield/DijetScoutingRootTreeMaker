#ifndef DIJETSCOUTINGROOTTREEMAKER_DIJETSCOUTINGTREEPRODUCER_H
#define DIJETSCOUTINGROOTTREEMAKER_DIJETSCOUTINGTREEPRODUCER_H

// System include files
#include <iostream>
#include <vector>

// CMSSW include files
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/Scouting/interface/ScoutingParticle.h"
#include "DataFormats/Scouting/interface/ScoutingPFJet.h"
#include "DataFormats/Scouting/interface/ScoutingVertex.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "HLTrigger/HLTcore/interface/TriggerExpressionData.h"
#include "HLTrigger/HLTcore/interface/TriggerExpressionEvaluator.h"
#include "HLTrigger/HLTcore/interface/TriggerExpressionParser.h"

// Root include files
#include "TLorentzVector.h"
#include "TTree.h"


class DijetScoutingTreeProducer : public edm::EDAnalyzer
{
public:
    explicit DijetScoutingTreeProducer(edm::ParameterSet const& cfg);
    virtual ~DijetScoutingTreeProducer();

private:
    virtual void beginJob();
    virtual void analyze(edm::Event const& iEvent, edm::EventSetup const& iSetup);
    virtual void endJob();

    void initialize();
    // For JECs
    bool doJECs_;
    edm::FileInPath L1corrAK4_DATA_, L2corrAK4_DATA_, L3corrAK4_DATA_,
        ResCorrAK4_DATA_, L1corrAK8_DATA_, L2corrAK8_DATA_, L3corrAK8_DATA_,
        ResCorrAK8_DATA_;
    edm::FileInPath L1corrAK4_MC_, L2corrAK4_MC_, L3corrAK4_MC_, L1corrAK8_MC_,
        L2corrAK8_MC_, L3corrAK8_MC_;
    JetCorrectorParameters *L1ParAK4_DATA;
    JetCorrectorParameters *L2ParAK4_DATA;
    JetCorrectorParameters *L3ParAK4_DATA;
    JetCorrectorParameters *L2L3ResAK4_DATA;
    FactorizedJetCorrector *JetCorrectorAK4_DATA;
    JetCorrectorParameters *L1ParAK4_MC;
    JetCorrectorParameters *L2ParAK4_MC;
    JetCorrectorParameters *L3ParAK4_MC;
    FactorizedJetCorrector *JetCorrectorAK4_MC;
    JetCorrectorParameters *L1ParAK8_DATA;
    JetCorrectorParameters *L2ParAK8_DATA;
    JetCorrectorParameters *L3ParAK8_DATA;
    JetCorrectorParameters *L2L3ResAK8_DATA;
    FactorizedJetCorrector *JetCorrectorAK8_DATA;
    JetCorrectorParameters *L1ParAK8_MC;
    JetCorrectorParameters *L2ParAK8_MC;
    JetCorrectorParameters *L3ParAK8_MC;
    FactorizedJetCorrector *JetCorrectorAK8_MC;
    //---- configurable parameters --------
    double ptMinAK4_,ptMinAK8_,ptMinCA8_;
    edm::EDGetTokenT<ScoutingPFJetCollection> srcJetsAK4_;
    edm::EDGetTokenT<ScoutingVertexCollection> srcVrtx_;
    edm::EDGetTokenT<double> srcRho_, srcMET_;
    edm::InputTag srcJetsAK4Calo_, srcJetsAK4PFCluster_,
        srcJetsAK4PFCalo_, srcJetsAK8_, srcJetsCA8_, srcPU_,
        srcGenInfo_, srcGenJetsAK4_, srcGenJetsAK8_, srcGenJetsCA8_,
        srcPrunedGenParticles_;
    edm::Service<TFileService> fs_;
    TTree *outTree_;

    //---- TRIGGER -------------------------
    triggerExpression::Data triggerCache_;
    std::vector<triggerExpression::Evaluator*> vtriggerSelector_;
    std::vector<std::string> vtriggerAlias_, vtriggerSelection_;
    TH1F *triggerPassHisto_, *triggerNamesHisto_, *puHisto_;
    //---- output TREE variables ------
    //---- global event variables -----
    int   run_, evt_, nVtx_, lumi_;
    int   nJetsAK4_, nJetsAK8_, nJetsCA8_, nGenJetsAK4_, nGenJetsAK8_, nGenJetsCA8_;
    float rho_, met_, metSig_;
    float htAK4_, mjjAK4_, dEtajjAK4_, dPhijjAK4_;
    float htAK8_, mjjAK8_, dEtajjAK8_, dPhijjAK8_;
    float htCA8_, mjjCA8_, dEtajjCA8_, dPhijjCA8_;
    std::vector<bool> *triggerResult_;

    //---- NOISE FILTERS -------------------------
    /* triggerExpression::Data noiseFilterCache_; */

    /* triggerExpression::Evaluator *HBHENoiseFilter_Selector_; */
    /* triggerExpression::Evaluator *CSCHaloNoiseFilter_Selector_; */
    /* triggerExpression::Evaluator *HCALlaserNoiseFilter_Selector_; */
    /* triggerExpression::Evaluator *ECALDeadCellNoiseFilter_Selector_; */
    /* triggerExpression::Evaluator *GoodVtxNoiseFilter_Selector_; */
    /* triggerExpression::Evaluator *TrkFailureNoiseFilter_Selector_; */
    /* triggerExpression::Evaluator *EEBadScNoiseFilter_Selector_; */
    /* triggerExpression::Evaluator *ECALlaserNoiseFilter_Selector_; */
    /* triggerExpression::Evaluator *TrkPOGNoiseFilter_Selector_; */
    /* triggerExpression::Evaluator *TrkPOG_manystrip_NoiseFilter_Selector_; */
    /* triggerExpression::Evaluator *TrkPOG_toomanystrip_NoiseFilter_Selector_; */
    /* triggerExpression::Evaluator *TrkPOG_logError_NoiseFilter_Selector_; */

    bool passFilterHBHE_;
    bool passFilterCSCHalo_;
    bool passFilterHCALlaser_;
    bool passFilterECALDeadCell_;
    bool passFilterGoodVtx_;
    bool passFilterTrkFailure_;
    bool passFilterEEBadSc_;
    bool passFilterECALlaser_;
    bool passFilterTrkPOG_;
    bool passFilterTrkPOG_manystrip_;
    bool passFilterTrkPOG_toomanystrip_;
    bool passFilterTrkPOG_logError_;

    //---- jet and genJet variables --------------
    std::vector<float> *ptAK4_, *jecAK4_, *etaAK4_, *phiAK4_, *massAK4_, *energyAK4_, *areaAK4_, *chfAK4_, *nhfAK4_, *phfAK4_, *elfAK4_, *mufAK4_, *nemfAK4_, *cemfAK4_;
    std::vector<int> *idLAK4_, *idTAK4_, *chHadMultAK4_, *chMultAK4_, *neHadMultAK4_, *neMultAK4_, *phoMultAK4_;
    std::vector<float> *hf_hfAK4_, *hf_emfAK4_, *hofAK4_;
    //std::vector<float> *cutbasedJetId_, *fullJetId_, *fullJetDiscriminant_;
    std::vector<float> *ptGenAK4_, *etaGenAK4_, *phiGenAK4_, *massGenAK4_, *energyGenAK4_;
    std::vector<float> *ptAK4matchCaloJet_, *emfAK4matchCaloJet_;
    std::vector<float> *ptAK4Calo_, *jecAK4Calo_, *etaAK4Calo_, *phiAK4Calo_, *massAK4Calo_, *energyAK4Calo_, *areaAK4Calo_, *emfAK4Calo_;
    std::vector<float> *ptAK4PFCluster_, *jecAK4PFCluster_, *etaAK4PFCluster_, *phiAK4PFCluster_, *massAK4PFCluster_, *energyAK4PFCluster_, *areaAK4PFCluster_;
    std::vector<float> *ptAK4PFCalo_, *jecAK4PFCalo_, *etaAK4PFCalo_, *phiAK4PFCalo_, *massAK4PFCalo_, *energyAK4PFCalo_, *areaAK4PFCalo_, *emfAK4PFCalo_;

    std::vector<float> *ptAK8_, *jecAK8_, *etaAK8_, *phiAK8_, *massAK8_, *energyAK8_, *areaAK8_, *chfAK8_, *nhfAK8_, *phfAK8_, *elfAK8_, *mufAK8_, *nemfAK8_, *cemfAK8_, *massPrunedAK8_, *massSoftDropAK8_, *dR_AK8_, *tau1AK8_, *tau2AK8_, *tau3AK8_ ;
    std::vector<int> *idLAK8_, *idTAK8_, *chHadMultAK8_, *chMultAK8_, *neHadMultAK8_, *neMultAK8_, *phoMultAK8_;
    std::vector<float> *hf_hfAK8_, *hf_emfAK8_, *hofAK8_;
    std::vector<float> *ptGenAK8_, *etaGenAK8_, *phiGenAK8_, *massGenAK8_, *energyGenAK8_;

    std::vector<float> *ptCA8_, *jecCA8_, *etaCA8_, *phiCA8_, *massCA8_, *energyCA8_, *chfCA8_, *nhfCA8_, *phfCA8_, *elfCA8_, *mufCA8_, *massPrunedCA8_, *dR_CA8_, *tau1CA8_, *tau2CA8_, *tau3CA8_ ;
    std::vector<int> *idLCA8_, *idTCA8_;
    std::vector<float> *ptGenCA8_, *etaGenCA8_, *phiGenCA8_, *massGenCA8_, *energyGenCA8_;

    //---- MC variables ---------------
    std::vector<float> *npu_;
    std::vector<int> *Number_interactions;
    std::vector <int> *OriginBX;

    //-----gen particles from hard scattering ------

    float ptHat_;
    int processID_;
    float weight_;
    std::vector<float> *gen_eta, *gen_phi, *gen_p, *gen_px, *gen_py, *gen_pz, *gen_pt, *gen_energy,  *gen_vx, *gen_vy, *gen_vz;
    std::vector<int> *gen_numDaught, *gen_status, *gen_index, *gen_motherIndex, *gen_pdgId;  

};

#endif
