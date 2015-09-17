#ifndef PMVS3_EXPAND_H
#define PMVS3_EXPAND_H

#include <vector>
#include <queue>
#include <list>
#include "patchOrganizerS.h"
#include <CL/cl.h>

namespace PMVS3 {
class CfindMatch;
  
class Cexpand {
 public:
  Cexpand(CfindMatch& findMatch);
  ~Cexpand() {};

  void init(void);
  void run(void);
  void initCLProgram(void);

  float computeRadius(const Patch::Cpatch& patch);
  
 protected:
  int expandSub(const Patch::Ppatch& orgppatch, const int id,
                const Vec4f& canCoord);
  
  int updateCounts(const Patch::Cpatch& patch);
  
  int checkCounts(Patch::Cpatch& patch);
  
  void findEmptyBlocks(const Patch::Ppatch& ppatch,
                       std::vector<std::vector<Vec4f> >& canCoords);
 protected:

  std::priority_queue<Patch::Ppatch, std::vector<Patch::Ppatch>, P_compare>
    m_queue;
  
  CfindMatch& m_fm;
  
  //-----------------------------------------------------------------
  // thread related
  //-----------------------------------------------------------------  
  void expandThread(void);
  static void* expandThreadTmp(void* arg);

  void optimizeThread(void);
  static void* optimizeThreadTmp(void *arg);

  // Number of trials
  std::vector<int> m_ecounts;
  // Number of failures in the prep
  std::vector<int> m_fcounts0;
  // Number of failures in the post processing
  std::vector<int> m_fcounts1;
  // Number passes
  std::vector<int> m_pcounts;

  // OpenCL
  cl_program m_clProgram;

};
};

#endif // PMVS3_EXPAND_H
