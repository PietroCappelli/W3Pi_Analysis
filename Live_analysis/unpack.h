#include <cstdio>
#include <cstdint>
#include <fstream>
#include <math.h>
#include <sys/stat.h>
#include "UnpackerBase.h"

// template<typename U>
inline void readheader(
  std::fstream &fin, uint64_t &header, uint16_t &run, uint16_t &bx, uint32_t &orbit, bool &good, uint16_t &npuppi) {
  fin.read(reinterpret_cast<char *>(&header), sizeof(uint64_t));
  npuppi = header & 0xFFF;
  bx = (header >> 12) & 0xFFF;
  orbit = (header >> 24) & 0X3FFFFFFF;
  run = (header >> 54);
  good = (header & (1llu << 61));
}
inline void assignpdgid(uint8_t pid, short int &pdgid) {
  static constexpr int16_t PDGIDS[8] = {130, 22, -211, 211, 11, -11, 13, -13};
  pdgid = PDGIDS[pid];
}
inline bool readpid(const uint64_t data, short int &pdgid) {
  uint8_t pid = (data >> 37) & 0x7;
  assignpdgid(pid, pdgid);
  return (pid > 1);
}

inline void readshared(const uint64_t data, float &pt, float &eta, float &phi) {  
  uint16_t ptint = data & 0x3FFF;
  pt = ptint * 0.25;

  int etaint = ((data >> 25) & 1) ? ((data >> 14) | (-0x800)) : ((data >> 14) & (0xFFF));
  eta = etaint * M_PI / 720.;

  int phiint = ((data >> 36) & 1) ? ((data >> 26) | (-0x400)) : ((data >> 26) & (0x7FF));
  phi = phiint * M_PI / 720.;
}

inline void readcharged(const uint64_t data, float &z0, float &dxy, uint16_t &quality) {  
  int z0int = ((data >> 49) & 1) ? ((data >> 40) | (-0x200)) : ((data >> 40) & 0x3FF);
  z0 = z0int * .05; 

  int dxyint = ((data >> 57) & 1) ? ((data >> 50) | (-0x100)) : ((data >> 50) & 0xFF);
  dxy = dxyint * 0.05;           
  quality = (data >> 58) & 0x7;  
}

inline void readneutral(const uint64_t data, float &wpuppi, uint16_t &id) {
  int wpuppiint = (data >> 23) & 0x3FF;
  wpuppi = wpuppiint / 256;
  id = (data >> 13) & 0x3F;
}

inline void readevent(std::fstream &fin, uint64_t &header,uint16_t &run,uint16_t &bx,uint32_t &orbit, bool &good,uint16_t &npuppi,uint64_t (&data)[255],
              float (&pt)[255],float (&eta)[255],float (&phi)[255],short int (&pdgid)[255],
              float (&z0)[255],float (&dxy)[255],uint16_t (&quality)[255],float (&wpuppi)[255], uint16_t (&id)[255]) {
  readheader(fin, header, run, bx, orbit, good, npuppi);
  if (header!=0){	  
	if (npuppi)
	    fin.read(reinterpret_cast<char *>(&data[0]), npuppi * sizeof(uint64_t));
	  for (uint16_t i = 0; i < npuppi; ++i) {
	    readshared(data[i], pt[i], eta[i], phi[i]);
	    if (readpid(data[i], pdgid[i])) {
	      readcharged(data[i], z0[i], dxy[i], quality[i]);
	      wpuppi[i] = 0;
	      id[i] = 0;
	    } else {
	      readneutral(data[i], wpuppi[i], id[i]);
	      z0[i] = 0;
	      dxy[i] = 0;
	      quality[i] = 0;
	    }
	  }
  }
}

inline void printReport(const UnpackerBase::Report &rep) {
  float inrate = rep.bytes_in / (1024. * 1024.) / rep.time;
  printf(
      "Done in %.2fs. Event rate: %.1f kHz (40 MHz / %.1f), input data rate %.1f MB/s (%.1f "
      "Gbps)\n",
      rep.time,
      rep.entries / rep.time / 1000.,
      (40e6 * rep.time / rep.entries),
      inrate,
      inrate * 8 / 1024.);
  if (rep.bytes_out) {
    float outrate = rep.bytes_out / (1024. * 1024.) / rep.time;
    float ratio = rep.bytes_out / rep.bytes_in;
    printf(
        "Input file size: %.2f MB, Output file size: %.2f MB, File size ratio: %.3f, output data rate %.1f MB/s "
        "(%.1f "
        "Gbps)\n\n",
        rep.bytes_in / (1024. * 1024.),
        rep.bytes_out / (1024. * 1024.),
        ratio,
        outrate,
        outrate * 8 / 1024);
  } else {
    printf("\n");
  }
}

inline UnpackerBase::Report makeReport(float treal,
                                       unsigned long int entries,
                                       const std::vector<std::string> &infiles,
                                       const std::string &outfile) {
  float insize = 0, outsize = 0;
  struct stat stat_buf;
  for (auto &infile : infiles) {
    int rc = stat(infile.c_str(), &stat_buf);
    insize += ((rc == 0) ? stat_buf.st_size : 0);
  };
  if (!outfile.empty()) {
    int rc = stat(outfile.c_str(), &stat_buf);
    outsize = ((rc == 0) ? stat_buf.st_size : 0);
  }
  return UnpackerBase::Report(entries, treal, insize, outsize);
}

