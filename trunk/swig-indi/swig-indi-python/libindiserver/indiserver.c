
#include "libindiserver.h"

int
main (int ac, char *av[])
{


	/* log startup */
	logStartup(ac, av);

	/* save our name */
	me = av[0];

#ifdef OSX_EMBEDED_MODE

  char logname[128];
  snprintf(logname, 128, LOGNAME, getlogin());
  fprintf(stderr, "switching stderr to %s", logname);
  freopen(logname, "w", stderr);

  fifo.name = FIFONAME;
  verbose = 1;
  ac = 0;

#else

	/* crack args */
	while ((--ac > 0) && ((*++av)[0] == '-')) {
	    char *s;
	    for (s = av[0]+1; *s != '\0'; s++)
		switch (*s) {
		case 'l':
		    if (ac < 2) {
			fprintf (stderr, "-l requires log directory\n");
			usage();
		    }
		    ldir = *++av;
		    ac--;
		    break;
		case 'm':
		    if (ac < 2) {
			fprintf (stderr, "-m requires max MB behind\n");
			usage();
		    }
		    maxqsiz = 1024*1024*atoi(*++av);
		    ac--;
		    break;
		case 'p':
		    if (ac < 2) {
			fprintf (stderr, "-p requires port value\n");
			usage();
		    }
		    port = atoi(*++av);
		    ac--;
		    break;
    case 'f':
        if (ac < 2) {
            fprintf (stderr, "-f requires fifo node\n");
            usage();
        }
        fifo.name = *++av;
        ac--;
        break;
		case 'v':
		    verbose++;
		    break;
		default:
		    usage();
		}
	}
#endif


	/* at this point there are ac args in av[] to name our drivers */
        if (ac == 0 && !fifo.name)
            usage();

	/* take care of some unixisms */
	noZombies();
	noSIGPIPE();

	/* realloc seed for client pool */
	clinfo = (ClInfo *) malloc (1);
	nclinfo = 0;

	/* create driver info array all at once since size never changes */
    ndvrinfo = ac;
	dvrinfo = (DvrInfo *) calloc (ndvrinfo, sizeof(DvrInfo));

	/* start each driver */
        while (ac-- > 0) {
            strncpy(dvrinfo[ac].name, *av++, MAXINDINAME);
	    startDvr (&dvrinfo[ac]);
        }

	/* announce we are online */
	indiListen();

        /* Load up FIFO, if available */
        indiFIFO();

	/* handle new clients and all io */
	while (1)
	    indiRun();

	/* whoa! */
	fprintf (stderr, "unexpected return from main\n");
	return (1);
}
