// Example code
//
// Assuming fastjet is installed and the fastjet-config is available under your $PATH
//
// To compile this code
// g++ -o example example.cc `fastjet-config --cxxflags --libs` -I/Path/To/CORE `root-config --cflags --libs`


#include "CORE/CMS3.cc"
#include "Math/VectorUtil.h"
#include "fastjet/ClusterSequence.hh"

//##############################################################################
vector<PseudoJet> cluster_jets(vector<LorentzVector> seeds, JetAlgorithm algo=kt_algorithm)
{
    vector<PseudoJet> particles;

    for (LorentzVector& lv : seeds)
        particles.push_back(PseudoJet(lv.px(), lv.py(), lv.pz(), lv.e()));

    // choose a jet definition
    JetDefinition jet_def(algo, 0.4);

    // run the clustering, extract the jets
    ClusterSequence cs(particles, jet_def);
    vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets());

    return jets;
}

//##############################################################################
int main()
{
    // Open up a CMS3 file
    TFile* file = new TFile("/hadoop/cms/store/group/snt/run2_moriond17/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/V08-00-16/merged_ntuple_1.root");
    TTree* tree = (TTree*) file->Get("Events");

    // Set the CMS3 tree to the CMS3 global class instance
    cms3.Init(tree);

    // Get the first event
    tree->LoadTree(0);
    cms3.GetEntry(0);

    vector<LorentzVector> pf_p4s;
    for (auto& p4 : cms3.pfcands_p4())
    {
    }

    // Cluster jets by anti-kt algorithm from pf candidates
    vector<PseudoJet> jets = cluster_jets(pf_p4s, antikt_algorithm);

    for (auto& jet : jets)
    {
        cout << jets.pt() << endl;
    }

    return 0;
}
