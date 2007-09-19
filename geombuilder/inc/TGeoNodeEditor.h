// @(#):$Id: TGeoNodeEditor.h,v 1.1 2006/06/13 15:27:11 brun Exp $
// Author: M.Gheata 

/*************************************************************************
 * Copyright (C) 1995-2002, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TGeoNodeEditor
#define ROOT_TGeoNodeEditor

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//  TGeoNodeEditor                                                    //
//                                                                      //
//  Editor for a TGeoNode.                                            //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#ifndef ROOT_TGButton
#include "TGWidget.h"
#endif
#ifndef ROOT_TGedFrame
#include "TGedFrame.h"
#endif

class TGeoNode;
class TGeoVolume;
class TGeoMatrix;
class TGTextEntry;
class TGNumberEntry;
class TGTab;
class TGComboBox;
class TGTextButton;
class TGPictureButton;
class TGCheckButton;
class TGeoTabManager;

class TGeoNodeEditor : public TGedFrame {

protected:

   TGeoNode            *fNode;              // Node object
   TGeoTabManager      *fTabMgr;            // Tab manager
   Bool_t               fIsEditable;        // Flag that the medium can be changed
   TGTextEntry         *fNodeName;          // Node name text entry
   TGNumberEntry       *fNodeNumber;        // Copy number 
   TGeoVolume          *fSelectedVolume;    // Selected volume
   TGLabel             *fLSelVolume;        // Selected volume label
   TGPictureButton     *fBSelVolume;        // Button for selecting a volume
   TGeoVolume          *fSelectedMother;    // Selected mother
   TGLabel             *fLSelMother;        // Selected mother label
   TGPictureButton     *fBSelMother;        // Button for selecting a mother volume
   TGeoMatrix          *fSelectedMatrix;    // Selected matrix
   TGLabel             *fLSelMatrix;        // Selected matrix label
   TGPictureButton     *fBSelMatrix;        // Button for selecting a matrix
   TGTextButton        *fEditMother;        // Check button for editing mother volume
   TGTextButton        *fEditVolume;        // Check button for volume editing
   TGTextButton        *fEditMatrix;        // Check button for matrix editing
   TGTextButton        *fApply;             // Apply-Button to accept changes
   TGTextButton        *fCancel;            // Cancel-Button
   TGTextButton        *fUndo;              // Undo-Button

   virtual void   ConnectSignals2Slots();   // Connect the signals to the slots

public:
   TGeoNodeEditor(const TGWindow *p, Int_t id,               
                  Int_t width = 140, Int_t height = 30,
                  UInt_t options = kChildFrame,
                  Pixel_t back = GetDefaultFrameBackground());
   virtual ~TGeoNodeEditor();
   virtual void   SetModel(TVirtualPad *pad, TObject *obj, Int_t event);

   void           DoEditMother();
   void           DoEditVolume();
   void           DoEditMatrix();
   void           DoSelectMother();
   void           DoSelectVolume();
   void           DoSelectMatrix();
   void           DoNodeName();
   void           DoNodeNumber();
   void           DoApply();
   void           DoUndo();
   
   ClassDef(TGeoNodeEditor,0)   // TGeoNode editor
};   
  
#endif                    
