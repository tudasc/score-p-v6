# Score-P modified for Clang PIRA

This version of Score-P is modified to use the Clang / LLVM 9.0 plugin that we developed.
It can be obtained [here](https://git.rwth-aachen.de/tuda-sc/projects/llvm-instrumentation) if you already have persmission.
If you do not already have permission, please contact me @ jan-patrick.lehr@tu-darmstadt.de.
Before building this version od Score-P you need to adjust the path to the LLVM plugin.
This is set as a ```#define LLVM_PLUGIN_PATH ABS/PATH/TO/BUILD/plugin.so``` in the file ```src/tools/instrumenter/scorep_instrumenter_compiler.cpp```.

Thereafter, you can configure the Score-P version using the command line

```
mkdir build && cd build
../configure --disable-gcc-plugin --prefix=WHATEVER
```

Note: for now, we need to disable the GCC plugin, as we added the Clang commands in similar places.
If you want to be able to run experiments with GCC plugin and our plugin, you need two separate installations of Score-P.


Score-P
-------
The Score-P (Scalable Performance Measurement Infrastructure for
Parallel Codes) measurement infrastructure is a highly scalable and
easy-to-use tool suite for profiling, event trace recording, and
online analysis of HPC applications.

To build Score-P you usually just need to do

  mkdir _build
  cd _build
  ../configure
  # study configure summary output
  make
  make install

Please have a look at INSTALL for further configure and build options.
Please consult OPEN_ISSUES for known deficiencies.

After make install you will find html and pdf documentation as well as
usage examples under $(prefix)/share/doc/scorep.

Have fun!

Please report bugs to <support@score-p.org>.
