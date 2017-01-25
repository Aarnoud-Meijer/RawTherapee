/*
 *  This file is part of RawTherapee.
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
 *
 *  2014 Jacques Desmis <jdesmis@gmail.com>
 */

#pragma once

#include <gtkmm.h>
#include "adjuster.h"
#include "toolpanel.h"
#include "curveeditor.h"
#include "curveeditorgroup.h"
#include "thresholdadjuster.h"
#include "colorprovider.h"
#include "guiutils.h"
#include "options.h"
#include "toolpanel.h"
//#include "../rtengine/imagedata.h"
//#include <memory>


class WavelListener
{

public:
    virtual ~WavelListener() {}
    virtual Glib::ustring GetCurrentImageFilePath() = 0;
    virtual void savelabReference (Glib::ustring fname) {}
};


class Wavelet :
    public ToolParamBlock,
    public ThresholdAdjusterListener,
    public AdjusterListener,
    public CurveListener,
    public ColorProvider,
    public rtengine::WaveletListener,
    public FoldableToolPanel
{
public:
    Wavelet ();
    virtual ~Wavelet ();

    bool wavComputed_ ();
    void adjusterChanged (ThresholdAdjuster* a, double newBottom, double newTop);
    void adjusterChanged (Adjuster* a, double newval);
    void adjusterChanged2 (ThresholdAdjuster* a, int newBottomL, int newTopL, int newBottomR, int newTopR);
    void autoOpenCurve ();
    void curveChanged (CurveEditor* ce);
    void read (const rtengine::procparams::ProcParams* pp, const ParamsEdited* pedited = nullptr);
    void setAdjusterBehavior (bool multiplieradd, bool thresholdadd, bool threshold2add, bool thresadd, bool chroadd, bool chromaadd, bool contrastadd, bool skinadd, bool reschroadd, bool tmrsadd, bool resconadd, bool resconHadd, bool thradd, bool thrHadd, bool skyadd, bool edgradadd, bool edgvaladd, bool strengthadd, bool gammaadd, bool edgedetectadd, bool edgedetectthradd, bool edgedetectthr2add);
    void setBatchMode (bool batchMode);
    void setDefaults  (const rtengine::procparams::ProcParams* defParams, const ParamsEdited* pedited = nullptr);
    void setEditProvider (EditDataProvider *provider);
    void updateToolState (std::vector<int> &tpOpen);
    void write (rtengine::procparams::ProcParams* pp, ParamsEdited* pedited = nullptr);
    void writeOptions (std::vector<int> &tpOpen);
    void retinexMethodChanged();
    void retinexMethodproChanged();
    void shapMethodChanged();
    void minmaxChanged (double cdma, double cdmin, double mini, double maxi, double Tmean, double Tsigma, double Tmin, double Tmax);
    bool minmaxComputed_ ();
    void updateLabel      ();
    void updateTrans      ();

    void setWavelListener (WavelListener* ipl)
    {
        walistener = ipl;
    }

    void inputeChanged ();
    void mFile_Reset        ();
    void savelabPressed ();

private:
    void foldAllButMe (GdkEventButton* event, MyExpander *expander);
    /*    MyFileChooserButton* ipDialog;
        std::auto_ptr<FileChooserLastFolderPersister> ipDialogPersister;
        sigc::connection   ipc;
        Gtk::RadioButton*  ifromfile;
        Glib::ustring      oldip;
        Gtk::Button*        saveRef;
        Glib::ustring lastRefFilename;
    */
    Glib::ustring lastlabFilename;

    Glib::ustring      oldip;

    virtual void colorForValue (double valX, double valY, enum ColorCaller::ElemType elemType, int callerId, ColorCaller* caller);
    void BAmethodChanged ();
    void NPmethodChanged ();
    void BackmethodChanged ();
    void CHSLmethodChanged ();
    void CHmethodChanged ();
    void CLmethodChanged ();
    void DirmethodChanged ();
    void EDmethodChanged ();
    void HSmethodChanged ();
    void LmethodChanged ();
    void mergevMethodChanged ();
    void mergMethodChanged ();
    void mergBMethodChanged ();
    void mergMethod2Changed ();

    void MedgreinfChanged ();
    void TMmethodChanged ();
    void TilesmethodChanged ();
    void usharpmethodChanged ();
    void ushamethodChanged ();
    void avoidToggled ();
    void cbenabToggled ();
    void contrastMinusPressed ();
    void contrastPlusPressed ();
    void daubcoeffmethodChanged ();
    void enabledChanged ();
    void linkedgToggled ();
    void lipstToggled ();
    void medianToggled ();
    void medianlevToggled ();
    void neutralPressed ();
    void neutral_pressed ();
    void neutral2_pressed       ();
    void neutralchPressed ();
    void tmrToggled ();
    void updatewavLabel ();
    void wavChanged (double nlevel);

    void HSmethodUpdateUI();
    void CHmethodUpdateUI();
//  void CHSLmethodChangedUI();
    void EDmethodUpdateUI();
    void NPmethodUpdateUI();
    void BAmethodUpdateUI();
    void TMmethodUpdateUI();
//  void BackmethodUpdateUI();
    void CLmethodUpdateUI();
//  void TilesmethodUpdateUI();
//  void daubcoeffmethodUpdateUI();
//  void MedgreinfUpdateUI();
//  void DirmethodUpdateUI();
//  void LmethodUpdateUI();
    void adjusterUpdateUI (Adjuster* a);
    void enabledUpdateUI ();
    void medianlevUpdateUI ();
    void cbenabUpdateUI ();
    void lipstUpdateUI ();

    void enableToggled (MyExpander *expander);

    CurveEditorGroup* const curveEditorG;

    CurveEditorGroup* const CCWcurveEditorG;
    CurveEditorGroup* const CCWcurveEditorT;
    CurveEditorGroup* const CCWcurveEditorgainT;
    CurveEditorGroup* const CCWcurveEditormerg;
    CurveEditorGroup* const CCWcurveEditormerg2;
    CurveEditorGroup* const CCWcurveEditorsty;
    CurveEditorGroup* const CCWcurveEditorsty2;
    CurveEditorGroup* const curveEditorsty;

    CurveEditorGroup* const curveEditorRES;
    CurveEditorGroup* const curveEditorGAM;
    Gtk::HSeparator* const separatorCB;
    Gtk::HSeparator* const separatorNeutral;
    Gtk::HSeparator* const separatoredge;
    Gtk::HSeparator* const separatorRT;
    Gtk::HSeparator* const separatorsty;
    Gtk::HSeparator* const separatorsty2;
    Gtk::HSeparator* const separatorsty3;

    CurveEditorGroup* const opaCurveEditorG;
    FlatCurveEditor* opacityShapeRG;
    CurveEditorGroup* const opacityCurveEditorG;
    FlatCurveEditor* opacityShapeBY;
    CurveEditorGroup* const opacityCurveEditorW;
    CurveEditorGroup* const opacityCurveEditorWL;
    FlatCurveEditor* opacityShape;
    FlatCurveEditor* opacityShapeWL;
    FlatCurveEditor* hhshape;
    FlatCurveEditor* Chshape;
    DiagonalCurveEditor* clshape;

    FlatCurveEditor* ccshape;
    FlatCurveEditor* cTshape;
    FlatCurveEditor* cTgainshape;
    FlatCurveEditor* cmergshape;
    FlatCurveEditor* cmerg2shape;
    FlatCurveEditor* cstyshape;
    FlatCurveEditor* cstyshape2;
    FlatCurveEditor* shstyshape;

    Gtk::CheckButton* const median;
    Gtk::CheckButton* const medianlev;
    Gtk::CheckButton* const linkedg;
    Gtk::CheckButton* const cbenab;
    Gtk::CheckButton* const lipst;
    Gtk::CheckButton* const avoid;
    Gtk::CheckButton* const tmr;

    Gtk::Button *mFileReset;
    Gtk::Button* savelab;
    Gtk::Button* neutral2;


    Gtk::Button* const neutralchButton;
    Adjuster* correction[9];
    Adjuster* correctionch[9];
    Adjuster* balmer[9];
    Adjuster* balmer2[9];

    Adjuster* const rescon;
    Adjuster* const resconH;
    Adjuster* const reschro;
    Adjuster* const tmrs;
    Adjuster* const gamma;
    Adjuster* const sup;
    Adjuster* const sky;
    Adjuster* const thres;
    Adjuster* const chroma;
    Adjuster* const chro;
    Adjuster* const contrast;
    Adjuster* const thr;
    Adjuster* const thrH;
    Adjuster* const skinprotect;
    Adjuster* const edgrad;
    Adjuster* const edgval;
    Adjuster* const edgthresh;
    Adjuster* const strength;
    Adjuster* const balance;
    Adjuster* const iter;
    Adjuster* const mergeL;
    Adjuster* const mergeC;

    Adjuster* greenlow;
    Adjuster* bluelow;
    Adjuster* greenmed;
    Adjuster* bluemed;
    Adjuster* greenhigh;
    Adjuster* bluehigh;
    Adjuster* balanleft;
    Adjuster* balanhig;
    Adjuster* sizelab;
    Adjuster* dirV;
    Adjuster* dirH;
    Adjuster* dirD;
    Adjuster* balmerch;
    Adjuster* shapedetcolor;
    Adjuster* balmerres;
    Adjuster* balmerres2;
    Adjuster* blend;
    Adjuster* blendc;
    Adjuster* grad;
    Adjuster* offs;
    Adjuster* str;
    Adjuster* neigh;
    Adjuster* vart;
    Adjuster* limd;
    Adjuster* chrrt;
    Adjuster* scale;
    Adjuster* gain;


    ThresholdAdjuster* const hueskin;
    ThresholdAdjuster* const hueskin2;
    ThresholdAdjuster* const hueskinsty;
    ThresholdAdjuster* const hllev;
    ThresholdAdjuster* const bllev;
    ThresholdAdjuster* const pastlev;
    ThresholdAdjuster* const satlev;
    ThresholdAdjuster* const edgcont;
    ThresholdAdjuster* const level0noise;
    ThresholdAdjuster* const level1noise;
    ThresholdAdjuster* const level2noise;
    ThresholdAdjuster* const level3noise;

    Adjuster* const threshold;
    Adjuster* const threshold2;
    Adjuster* const edgedetect;
    Adjuster* const edgedetectthr;
    Adjuster* const edgedetectthr2;
    Adjuster* const edgesensi;
    Adjuster* const edgeampli;
    Adjuster* const highlights;
    Adjuster* const h_tonalwidth;
    Adjuster* const shadows;
    Adjuster* const s_tonalwidth;
    Adjuster* const radius;
    Adjuster* const shapind;

    MyComboBoxText* const Lmethod;
    sigc::connection  Lmethodconn;
    MyComboBoxText* const CHmethod;
    sigc::connection  CHmethodconn;
    MyComboBoxText* const CHSLmethod;
    sigc::connection  CHSLmethodconn;
    MyComboBoxText* const EDmethod;
    sigc::connection  EDmethodconn;
    MyComboBoxText* const BAmethod;
    sigc::connection  BAmethodconn;
    MyComboBoxText* const NPmethod;
    sigc::connection  NPmethodconn;
    MyComboBoxText* const TMmethod;
    sigc::connection  TMmethodconn;
    MyComboBoxText* const HSmethod;
    sigc::connection  HSmethodconn;
    MyComboBoxText* const CLmethod;
    sigc::connection  CLmethodconn;
    MyComboBoxText* const Backmethod;
    sigc::connection  Backmethodconn;
    MyComboBoxText* const Tilesmethod;
    sigc::connection  Tilesmethodconn;
    MyComboBoxText* const daubcoeffmethod;
    sigc::connection  daubcoeffmethodconn;
    MyComboBoxText* const Dirmethod;
    sigc::connection  Dirmethodconn;
    MyComboBoxText* const Medgreinf;
    sigc::connection  MedgreinfConn;
    MyComboBoxText* const usharpmethod;
    sigc::connection  usharpmethodconn;
    MyComboBoxText* const ushamethod;
    sigc::connection  ushamethodconn;
    MyComboBoxText* const shapMethod;
    sigc::connection  shapMethodConn;
    MyComboBoxText* const retinexMethod;
    sigc::connection retinexMethodConn;
    MyComboBoxText*   retinexMethodpro;
    sigc::connection retinexMethodproConn;
    MyComboBoxText* const mergMethod;
    sigc::connection  mergMethodConn;
    MyComboBoxText* const  mergMethod2;
    sigc::connection  mergMethod2Conn;
    MyComboBoxText* const mergevMethod;
    sigc::connection  mergevMethodConn;
    MyComboBoxText* const mergBMethod;
    sigc::connection  mergBMethodConn;

    Gtk::Frame* const chanMixerHLFrame;
    Gtk::Frame* const chanMixerMidFrame;
    Gtk::Frame* const chanMixerShadowsFrame;
    Gtk::Frame* const gainFrame;
    Gtk::Frame* const tranFrame;
    Gtk::Frame* const gaussFrame;
    Gtk::Frame* const balMFrame;
    Gtk::Frame* const shaFrame;

    Gtk::Label* const wavLabels;
    Gtk::Label* const labmC;
    Gtk::Label* const labmNP;
    Gtk::Label* const labmdh;
    Gtk::Label* const labmdhpro;
    Gtk::Label* const labretifin;
    Gtk::Label* const labmmg1;
    Gtk::Label* const labmmg2;
    Gtk::Label* const labmmg;
    Gtk::Label* const labmmgB;
    Gtk::Label* const mMLabels;
    Gtk::Label* const transLabels;
    Gtk::Label* const transLabels2;
    Gtk::Label* const usharpLabel;
    Gtk::Label* const inLabel;

    double nextmin;
    double nextmax;
    double nextminiT;
    double nextmaxiT;
    double nextmeanT;
    double nextminT;
    double nextmaxT;
    double nextsigma;
    double nextmergeL;
    double nextmergeC;
    double nextL;
    double nextC;

    MyExpander* const expchroma;
    MyExpander* const expcontrast;
    MyExpander* const expedge;
    MyExpander* const expfinal;
    MyExpander* const expgamut;
    MyExpander* const expnoise;
    MyExpander* const expresid;
    MyExpander* const expsettings;
    MyExpander* const exptoning;
    MyExpander* const expreti;
    MyExpander* const expmerge;
    MyExpander* const expsettingreti;
    MyExpander* const expTCresi;
    MyExpander* const expedg1;
    MyExpander* const expedg2;
    MyExpander* const expedg3;

    Gtk::HBox* const neutrHBox;
    Gtk::HBox* const usharpHBox;
    Gtk::HBox* const dhbox;
    Gtk::HBox* const dhboxpro;
    Gtk::HBox* const mg1box;
    Gtk::HBox* const mg2box;
    Gtk::HBox* const hbin;
    Gtk::HBox* const mgbox;
    Gtk::HBox* const neutrHBox2;
    Gtk::HBox* const labretifinbox;
    Gtk::HBox* const mgBbox;

    Gtk::VBox* const mgVBox;
    bool inChanged;

    bool b_filter_asCurrent;
    MyFileChooserButton *inputeFile;

    WavelListener*  walistener;

    sigc::connection enableChromaConn, enableContrastConn, enableEdgeConn,  enableEdge3Conn, enableFinalConn, enableTCConn;
    sigc::connection enableNoiseConn, enableResidConn, enableToningConn, enableMergeConn, enableretiConn;
    sigc::connection medianConn, avoidConn, tmrConn, medianlevConn, linkedgConn, lipstConn, cbenabConn, neutralconn;
    sigc::connection neutralPressedConn, neutral2conn;
    sigc::connection contrastPlusPressedConn;
    sigc::connection contrastMinusPressedConn;
    sigc::connection neutralchPressedConn;
    sigc::connection inFile;

    bool lastmedian, lastmedianlev, lastlinkedg, lastavoid, lastlipst, lasttmr, lastcbenab;
    int nextnlevel;
};
