#ifndef xAODAnaHelpers_JetCalibrator_H
#define xAODAnaHelpers_JetCalibrator_H

// EL include(s)
#include <EventLoop/Algorithm.h>

// Infrastructure include(s):
#include "xAODRootAccess/Init.h"
#include "xAODRootAccess/TEvent.h"
#include "xAODRootAccess/TStore.h"

// CP interface includes
#include "PATInterfaces/SystematicRegistry.h"
#include "PATInterfaces/SystematicSet.h"
#include "PATInterfaces/SystematicVariation.h"

// external tools include(s):
#include "JetCalibTools/JetCalibrationTool.h"
#include "JetSelectorTools/JetCleaningTool.h"
#include "JetUncertainties/JetUncertaintiesTool.h"

class JetCalibrator : public EL::Algorithm
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
public:
  std::string m_name;
  std::string m_configName;

  bool m_debug;           //!
  bool m_DC14;            //!

  // configuration variables
  std::string m_inContainerName;        //!
  std::string m_outContainerName;       //!

  std::string m_jetAlgo;                //!
  std::string m_outputAlgo;             //!
  std::string m_calibConfigData;        //!
  std::string m_calibConfigFullSim;     //!
  std::string m_calibConfigAFII;        //!
  std::string m_calibConfig;            //!
  std::string m_calibSequence;          //!
  std::string m_jetCalibCutLevel;   //!
  std::string m_uncertConfig;           //!
  // sort after calibration
  bool    m_sort;                   //!

  // systematics
  std::string m_systName;
  float m_systVal;
  bool m_runSysts;

private:
  xAOD::TEvent *m_event;  //!
  xAOD::TStore *m_store;  //!
  int m_numEvent;         //!
  int m_numObject;        //!

  bool m_isMC;
  bool m_isFullSim;

  std::string m_jetUncertAlgo;          //!

  std::string m_outSCContainerName;     //!
  std::string m_outSCAuxContainerName;  //!

  std::vector<CP::SystematicSet> m_systList; //!

  // tools
  JetCalibrationTool    * m_jetCalibration; //!
  JetCleaningTool       * m_jetCleaning;    //!
  JetUncertaintiesTool  * m_jetUncert;      //!

  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)
public:
  // Tree *myTree; //!
  // TH1 *myHist; //!


  // this is a standard constructor
  JetCalibrator ();
  JetCalibrator (std::string name, std::string configName, std::string systName = "", float systVal = 0);

  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob (EL::Job& job);
  virtual EL::StatusCode fileExecute ();
  virtual EL::StatusCode histInitialize ();
  virtual EL::StatusCode changeInput (bool firstFile);
  virtual EL::StatusCode initialize ();
  virtual EL::StatusCode execute ();
  virtual EL::StatusCode postExecute ();
  virtual EL::StatusCode finalize ();
  virtual EL::StatusCode histFinalize ();

  // these are the functions not inherited from Algorithm
  virtual EL::StatusCode configure ();

  // this is needed to distribute the algorithm to the workers
  ClassDef(JetCalibrator, 1);
};

#endif
