# Usage #
This software provides a systematic computational framework to detect supercoils of bacterial chromosome.

# Installation #
Simply put "supercoil1.0.tar.gz" in any directory,

> _$ tar zxvf supercoil1.0.tar.gz_

enter the folder "supercoil1.0" and type "_make_" then the compiled codes are within the same directory as the source.

# Inputs and outputs #
The major program in the provided package is `supercoil`, it can parse two formats of files, discrete data and continuous data, and examples for each are provided.
  * See help and look at all available options.

> _$ ./supercoil -h_

  * run the program just consider pathway and microarray information

> _$ ./supercoil -i DATA/NC\_000913.expr -j DATA/NC\_000913.ptt  -o DATA/NC\_000913.gi.operon -p DATA/NC\_000913.pathway -n 0.3 -g 0.5 -t 15_

  * run the program considering NAP binding sites and HEGs besides pathway and microarray

> _$ ./supercoil -i DATA/NC\_000913.expr -j DATA/NC\_000913.ptt  -o DATA/NC\_000913.gi.operon -p DATA/NC\_000913.pathway -a DATA/NC\_000913.NAP -e DATA/NC\_000913.HEG -D DATA/expression-value -n 0.3 -g 0.5 -t 15_

  * identify the weight parameters dynamically, i.e., train the parameters (n, g, t) optimizing the accurracy of NAP binding sites mapping

> _$ ./supercoil -i DATA/NC\_000913.expr -j DATA/NC\_000913.ptt  -o DATA/NC\_000913.gi.operon -p DATA/NC\_000913.pathway -a DATA/NC\_000913.NAP -e DATA/NC\_000913.HEG -D DATA/expression-value -M_

  * to get some basic stats
> _$ perl analysis\_dynamic.pl DATA/NC\_000913.expr.dynamic > DATA/NC\_000913.expr.dynamic.stat_

# Changelog #
Version 1.0
- prototype of algorithm
2011.11.30

# Contact #
Any questions, problems, bugs are welcome and should be dumped to
Qin Ma <maqin@uga.edu>

Creation: Dec. 16, 2011