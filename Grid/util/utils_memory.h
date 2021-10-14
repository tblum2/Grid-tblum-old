#ifndef _UTILS_MEMORY_H_
#define _UTILS_MEMORY_H_
#include </usr/include/sys/sysinfo.h>

NAMESPACE_BEGIN(Grid);

//Print memory usage
inline void printMem(const std::string &reason = "", int node=9999){
 
  std::cout << GridLogDebug << "printMem node " << node << ": " << reason << std::endl;

  struct sysinfo myinfo;
  sysinfo(&myinfo);
  double total_mem = myinfo.mem_unit * myinfo.totalram;
  total_mem /= (1024.*1024.);
  double free_mem = myinfo.mem_unit * myinfo.freeram;
  free_mem /= (1024.*1024.);
  
  std::cout << GridLogDebug<< "printMem node " << node << ": Memory: total: " << total_mem << " MB"
 	    << " avail: " << free_mem << " MB, used " 
	    << total_mem-free_mem << " MB" << std::endl;
}

NAMESPACE_END(Grid);
 
#endif
