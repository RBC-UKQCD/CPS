#ifndef __QIOREADMUON__
#define __QIOREADMUON__

#include <util/qio_general.h>

CPS_START_NAMESPACE
using namespace std;

#ifndef USE_QIO
class qio_readMuon: private qio_init {

 private:

  char *cname;

 public:

  qio_readMuon(int argc, char *argv[]): qio_init(argc, argv), cname("qio_readMuon"){}

  virtual ~qio_readMuon(){
  }

  void read(char *infile, Lattice &lat, Rcomplex *muon, int count, int volFormat=0){
      ERR.NotImplemented(cname,"read()");
	}

#if 0
 private:
  void qio_openInput(char *filename, int volFormat){
      ERR.NotImplemented(cname,"qio_openInput()");
	}
  

  void qio_closeInput(){
      ERR.NotImplemented(cname,"qio_closeInput()");
	}
#endif

};

#else

class qio_readMuon: private qio_init {

 private:

  char *cname;

 public:

  qio_readMuon(int argc, char *argv[]): qio_init(argc, argv), cname("qio_readMuon"){}

  virtual ~qio_readMuon(){
    #ifdef DEBUG_Init
    printf("finished qio_readMuon\n");
    #endif //DEBUG_Init
  }

  void read(char *infile, Lattice &lat, Rcomplex *muon, int count, int volFormat=QIO_VOLFMT);

 private:

  QIO_Reader *qio_Input;

  void qio_openInput(char *filename, int volFormat);

  void qio_closeInput()
    { QIO_close_read(qio_Input);}

};
#endif //USE_QIO


CPS_END_NAMESPACE
#endif // __QIOREADMUON__



