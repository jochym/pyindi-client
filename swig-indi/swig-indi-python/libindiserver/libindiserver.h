
#include <lilxml.h>
#include <indiapi.h>
#include "fq.h"

#define INDIPORT        7624            /* default TCP/IP port to listen */
#define	REMOTEDVR	(-1234)		/* invalid PID to flag remote drivers */
#define MAXSBUF     512
#define	MAXRBUF		4096		/* max read buffering here */
#define	MAXWSIZ		4096		/* max bytes/write */
#define	DEFMAXQSIZ	64		/* default max q behind, MB */

#ifdef OSX_EMBEDED_MODE
#define LOGNAME "/Users/%s/Library/Logs/indiserver.log"
#define FIFONAME "/tmp/indiserverFIFO"
#endif


/* associate a usage count with queuded client or device message */
typedef struct {
    int count;				/* number of consumers left */
    unsigned long cl;			/* content length */
    char *cp;				/* content: buf or malloced */
    char buf[MAXWSIZ];		/* local buf for most messages */
} Msg;

/* BLOB handling, NEVER is the default */
typedef enum {B_NEVER=0, B_ALSO, B_ONLY} BLOBHandling;

/* device + property name */
typedef struct {
    char dev[MAXINDIDEVICE];
    char name[MAXINDINAME];
    BLOBHandling blob;			/* when to snoop BLOBs */
} Property;


/* record of each snooped property
typedef struct {
    Property prop;
    BLOBHandling blob;
} Property;
*/

struct Indififo
{
    const char *name;                      /* Path to FIFO for dynamic startups & shutdowns of drivers */
    int fd;
    //FILE *fs;
} fifo;

/* info for each connected client */
typedef struct {
    int active;				/* 1 when this record is in use */
    Property *props;			/* malloced array of props we want */
    int nprops;				/* n entries in props[] */
    int allprops;			/* saw getProperties w/o device */
    BLOBHandling blob;			/* when to send setBLOBs */
    int s;				/* socket for this client */
    LilXML *lp;				/* XML parsing context */
    FQ *msgq;				/* Msg queue */
    unsigned int nsent;				/* bytes of current Msg sent so far */
} ClInfo;
 ClInfo *clinfo;			/*  malloced pool of clients */
 int nclinfo;			/* n total (not active) */

/* info for each connected driver */
typedef struct {
    char name[MAXINDINAME];		/* persistent name */
    char envDev[MAXSBUF];
    char envConfig[MAXSBUF];
    char envSkel[MAXSBUF];
    char envPrefix[MAXSBUF];
    //char dev[MAXINDIDEVICE];		/* device served by this driver */
    char **dev;             /* device served by this driver */
    int ndev;               /* number of devices served by this driver */
    int active;				/* 1 when this record is in use */
    Property *sprops;			/* malloced array of props we snoop */
    int nsprops;			/* n entries in sprops[] */
    int pid;				/* process id or REMOTEDVR if remote */
    int rfd;				/* read pipe fd */
    int wfd;				/* write pipe fd */
    int efd;				/* stderr from driver, if local */
    int restarts;			/* times process has been restarted */
    LilXML *lp;				/* XML parsing context */
    FQ *msgq;				/* Msg queue */
    unsigned int nsent;			/* bytes of current Msg sent so far */
} DvrInfo;
 DvrInfo *dvrinfo;		/* malloced array of drivers */
 int ndvrinfo;			/* n total */

 char *me;			/* our name */
 int port = INDIPORT;		/* public INDI port */
 int verbose;			/* chattiness */
 int lsocket;			/* listen socket */
 char *ldir;			/* where to log driver messages */
 int maxqsiz = (DEFMAXQSIZ*1024*1024); /* kill if these bytes behind */

extern void logStartup(int ac, char *av[]);
extern void usage (void);
extern void noZombies (void);
extern void noSIGPIPE (void);
extern void indiFIFO(void);
extern void indiRun (void);
extern void indiListen (void);
extern void newFIFO(void);
extern void newClient (void);
extern int newClSocket (void);
extern void shutdownClient (ClInfo *cp);
extern int readFromClient (ClInfo *cp);
extern void startDvr (DvrInfo *dp);
extern void startLocalDvr (DvrInfo *dp);
extern void startRemoteDvr (DvrInfo *dp);
extern int openINDIServer (char host[], int indi_port);
extern void shutdownDvr (DvrInfo *dp, int restart);
extern int isDeviceInDriver(const char *dev, DvrInfo *dp);
extern void q2RDrivers (const char *dev, Msg *mp, XMLEle *root);
extern void q2SDrivers (int isblob, const char *dev, const char *name, Msg *mp,
    XMLEle *root);
extern int q2Clients (ClInfo *notme, int isblob, const char *dev, const char *name,
    Msg *mp, XMLEle *root);
extern void addSDevice (DvrInfo *dp, const char *dev, const char *name);
extern Property *findSDevice (DvrInfo *dp, const char *dev, const char *name);
extern void addClDevice (ClInfo *cp, const char *dev, const char *name, int isblob);
extern int findClDevice (ClInfo *cp, const char *dev, const char *name);
extern int readFromDriver (DvrInfo *dp);
extern int stderrFromDriver (DvrInfo *dp);
extern int msgQSize (FQ *q);
extern void setMsgXMLEle (Msg *mp, XMLEle *root);
extern void setMsgStr (Msg *mp, char *str);
extern void freeMsg (Msg *mp);
extern Msg *newMsg (void);
extern int sendClientMsg (ClInfo *cp);
extern int sendDriverMsg (DvrInfo *cp);
extern void crackBLOB (const char *enableBLOB, BLOBHandling *bp);
extern void crackBLOBHandling(const char *dev, const char *name, const char *enableBLOB, ClInfo *cp);
extern void traceMsg (XMLEle *root);
extern char *indi_tstamp (char *s);
extern void logDMsg (XMLEle *root, const char *dev);
extern void Bye(void);
