/*

  This macro will add histograms multiplied by their cross-section
  from a list of root files and write them
  to a target root file. The target file is newly created and must not be
  identical to one of the source files.


  Author: Sven A. Schmidt, sven.schmidt@cern.ch
  Date:   13.2.2001

  Editing Author: Michael B. Anderson, mbanderson@hep.wisc.edu
  Date:  July 12, 2007

  This code is based on the hadd.C example by Rene Brun and Dirk Geppert,
  which had a problem with directories more than one level deep.
  (see macro hadd_old.C for this previous implementation).

  The macro from Sven has been enhanced by
     Anne-Sylvie Nicollerat <Anne-Sylvie.Nicollerat@cern.ch>
   to automatically add Trees (via a chain of trees).

  To use this macro, modify the file names in function hadd.

  NB: This macro is provided as a tutorial.
      Use $ROOTSYS/bin/hadd to merge many histogram files

 */


#include <string.h>
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TKey.h"
#include "Riostream.h"

TList *FileList;
TFile *Target;

void MergeRootfile( TDirectory *target, TList *sourcelist, double crossArray[] );

// List of Cross-sections divided by num of events produced
double crossSections[7] = {
          4.316E8/74405.,
          4.409E6/158343.,
          3.001E5/114908.,
          1.295E4/88840.,
          5.965E1/73606.,
          1.296E0/72979.,
          0.01164/80118.};

void haddPoster_200() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()

  Target = TFile::Open( "Hadd_C_CombinedPileUp_200.root", "RECREATE" );

  FileList = new TList();

  // ************************************************************
  // List of Files

  FileList->Add( TFile::Open("AnalysisPosterOutputs/AnalysisOutput-100-250-PileUp-200.root") );  // 1
  FileList->Add( TFile::Open("AnalysisPosterOutputs/AnalysisOutput-250-500-PileUp-200.root") );  // 2
  FileList->Add( TFile::Open("AnalysisPosterOutputs/AnalysisOutput-500-1000-PileUp-200.root") );  // 3
  FileList->Add( TFile::Open("AnalysisPosterOutputs/AnalysisOutput-1000-2500-PileUp-200.root") ); // 4
  FileList->Add( TFile::Open("AnalysisPosterOutputs/AnalysisOutput-2500-4000-PileUp-200.root") );// 5
  FileList->Add( TFile::Open("AnalysisPosterOutputs/AnalysisOutput-4000-6000-PileUp-200.root") );// 6
  FileList->Add( TFile::Open("AnalysisPosterOutputs/AnalysisOutput-6000-Inf-PileUp-200.root") );// 7


  // ************************************************************

  MergeRootfile( Target, FileList, crossSections );


}

void MergeRootfile( TDirectory *target, TList *sourcelist, double crossArray[] ) {

  //  cout << "Target path: " << target->GetPath() << endl;
  TString path( (char*)strstr( target->GetPath(), ":" ) );
  path.Remove( 0, 2 );



  TFile *first_source = (TFile*)sourcelist->First();


  first_source->cd( path );
  TDirectory *current_sourcedir = gDirectory;
  //gain time, do not add the objects in the list in memory
  Bool_t status = TH1::AddDirectoryStatus();
  TH1::AddDirectory(kFALSE);

  // loop over all keys in this directory
  TChain *globChain = 0;
  TIter nextkey( current_sourcedir->GetListOfKeys() );
  TKey *key, *oldkey=0;
  while ( (key = (TKey*)nextkey())) {

    //keep only the highest cycle number for each key
    if (oldkey && !strcmp(oldkey->GetName(),key->GetName())) continue;

    // read object from first source file
    first_source->cd( path );
    TObject *obj = key->ReadObj();

    if ( obj->IsA()->InheritsFrom( "TH1" ) ) {
      // descendant of TH1 -> merge it

      cout << "Merging histogram " << obj->GetName() << endl;
      TH1 *h1 = (TH1*)obj;

//      cout << "file " << first_source->GetName() << endl;

      // Scale by the cross-section factor
      h1->Scale(crossArray[0]);
//	    cout << "Cross array " << crossArray[0] << endl;


      // loop over all source files and add the content of the
      // correspondant histogram to the one pointed to by "h1"
      TFile *nextsource = (TFile*)sourcelist->After( first_source );

      int q = 1; // This keeps track of which
                 // cross section factor to use

      while ( nextsource ) {
//      cout << "file " << nextsource->GetName() << endl;

        // make sure we are at the correct directory level by cd'ing to path
        nextsource->cd( path );
        TKey *key2 = (TKey*)gDirectory->GetListOfKeys()->FindObject(h1->GetName());

        if (key2) {
           TH1 *h2 = (TH1*)key2->ReadObj();

	   // Scale by the cross section factor
           // before adding.
           h2->Scale(crossArray[q]);
//           cout << "Cross array " << crossArray[q] << endl;
           h1->Add( h2 );
           q++;
           delete h2;
        }

        nextsource = (TFile*)sourcelist->After( nextsource );
      }
    }
    else if ( obj->IsA()->InheritsFrom( "TTree" ) ) {

      // loop over all source files create a chain of Trees "globChain"
      const char* obj_name= obj->GetName();

      globChain = new TChain(obj_name);
      globChain->Add(first_source->GetName());
      TFile *nextsource = (TFile*)sourcelist->After( first_source );
      //      const char* file_name = nextsource->GetName();
      // cout << "file name  " << file_name << endl;
     while ( nextsource ) {

       globChain->Add(nextsource->GetName());
       nextsource = (TFile*)sourcelist->After( nextsource );
     }

    } else if ( obj->IsA()->InheritsFrom( "TDirectory" ) ) {
      // it's a subdirectory

      cout << "Found subdirectory " << obj->GetName() << endl;

      // create a new subdir of same name and title in the target file
      target->cd();
      TDirectory *newdir = target->mkdir( obj->GetName(), obj->GetTitle() );

      // newdir is now the starting point of another round of merging
      // newdir still knows its depth within the target file via
      // GetPath(), so we can still figure out where we are in the recursion
      MergeRootfile( newdir, sourcelist, crossSections );

    } else {

      // object is of no type that we know or can handle
      cout << "Unknown object type, name: "
           << obj->GetName() << " title: " << obj->GetTitle() << endl;
    }

    // now write the merged histogram (which is "in" obj) to the target file
    // note that this will just store obj in the current directory level,
    // which is not persistent until the complete directory itself is stored
    // by "target->Write()" below
    if ( obj ) {
      target->cd();

      //!!if the object is a tree, it is stored in globChain...
	if(obj->IsA()->InheritsFrom( "TTree" ))
          globChain->Merge(target->GetFile(),0,"keep");
	else
	obj->Write( key->GetName() );
    }

  } // while ( ( TKey *key = (TKey*)nextkey() ) )

  // save modifications to target file
  target->SaveSelf(kTRUE);
  TH1::AddDirectory(status);
}
