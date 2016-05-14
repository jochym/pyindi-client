%module PyIndiServer

%{
  #include <libindiserver.h>
%}


%include <argcargv.i>
%include <cmalloc.i>
%apply (int ARGC, char **ARGV) { (int ac, char *av[]) }

%allocators(ClInfo);

%typemap(varin) DvrInfo *dvrinfo  {
  if (PyList_Check($input)) {
    const size_t size = PyList_Size($input);
    ndvrinfo=size;
    dvrinfo=(DvrInfo *)malloc(size*sizeof(DvrInfo));
    for (int i = 0; i < size; ++i) {
      void *argp = 0 ;
      const int res = SWIG_ConvertPtr(PyList_GetItem($input, i), &argp, $1_descriptor, 0);
      if (!SWIG_IsOK(res)) {
        SWIG_exception_fail(SWIG_ArgError(res), "in method '" "$symname" "', argument " "$argnum"" of type '" "$1_type""'");
      }
      $1[i] = *((DvrInfo *)(argp));
    }
  }
  else {
    // Raise exception
    SWIG_exception_fail(SWIG_TypeError, "Expected list in $symname");
  }
 };
 
%typemap(varout) DvrInfo *dvrinfo {
    $result = PyList_New(ndvrinfo); // Create outer Python list of correct size
    for(size_t i = 0; i < ndvrinfo; ++i)
    {        
      PyList_SET_ITEM($result,i,SWIG_NewPointerObj(SWIG_as_voidptr($1+i), SWIGTYPE_p_DvrInfo,  0 ));
    }

 };

%typemap(varout) ClInfo *clinfo {
    $result = PyList_New(nclinfo); // Create outer Python list of correct size
    for(size_t i = 0; i < nclinfo; ++i)
    {        
      PyList_SET_ITEM($result,i,SWIG_NewPointerObj(SWIG_as_voidptr($1+i), SWIGTYPE_p_ClInfo,  0 ));
    }

 };

%include <libindiserver.h>
