/*
 *  This file is part of RawTherapee.
 *
 *  Copyright (c) 2004-2010 Gabor Horvath <hgabor@rawtherapee.com>
 *
 *  RawTherapee is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 *  RawTherapee is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RawTherapee.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _TONECURVE_H_
#define _TONECURVE_H_

#include <gtkmm.h>
#include "adjuster.h"
#include "toolpanel.h"
#include "curveeditor.h"
#include "curveeditorgroup.h"
#include "mycurve.h"
#include "guiutils.h"

class ToneCurve : public Gtk::VBox, public AdjusterListener, public FoldableToolPanel, public rtengine::AutoExpListener, public CurveListener {

  protected:
    Gtk::HBox* abox;
    Gtk::ToggleButton* autolevels;
    MySpinButton* sclip;
    Adjuster* expcomp;
    Adjuster* brightness;
    Adjuster* black;
    Adjuster* hlcompr;
    Adjuster* hlcomprthresh;
    Adjuster* shcompr;
    Adjuster* contrast;
	Adjuster* saturation;

    bool clipDirty, lastAuto;
    sigc::connection autoconn;
    CurveEditorGroup* curveEditorG;
    DiagonalCurveEditor* shape;

    // used temporarily in eventing
    double nextExpcomp;
	int nextBrightness;
	int nextContrast;
    int nextBlack;
    int nextHlcompr;
    int nextHlcomprthresh;
  
  public:

    ToneCurve ();

    void read                (const rtengine::procparams::ProcParams* pp, const ParamsEdited* pedited=NULL);
    void write               (rtengine::procparams::ProcParams* pp, ParamsEdited* pedited=NULL);
    void setDefaults         (const rtengine::procparams::ProcParams* defParams, const ParamsEdited* pedited=NULL);
    void setBatchMode        (bool batchMode);
    void setAdjusterBehavior (bool expadd, bool hlcompadd, bool hlcompthreshadd, bool bradd, bool blackadd, bool shcompadd, bool contradd, bool satadd);
    void trimValues           (rtengine::procparams::ProcParams* pp);


    void adjusterChanged (Adjuster* a, double newval);
    void autolevels_toggled ();
    void clip_changed ();
    bool clip_changed_ ();
    void waitForAutoExp ();
    void autoExpChanged (double expcomp, int bright, int contr, int black, int hlcompr, int hlcomprthresh);
    bool autoExpComputed_ ();
    void enableAll ();
    void curveChanged ();
    void expandCurve (bool isExpanded);
    bool isCurveExpanded ();
    void updateCurveBackgroundHistogram (LUTu & histToneCurve, LUTu & histLCurve, LUTu & histRed, LUTu & histGreen, LUTu & histBlue, LUTu & histLuma);
};

#endif
