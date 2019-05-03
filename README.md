
## Usage

This software provides a systematic computational framework to detect supercoils of bacterial chromosome. 


#### Installation

Simply put "supercoil-master.zip" in any directory.

```
unzip supercoil-master.zip && rm unzip supercoil-master.zip
```

Enter the folder "supercoil" and type "make" then the compiled codes are within the same directory as the source.


#### Inputs and outputs

The major program in the provided package is \`supercoil\`, it can parse two 
formats of files, discrete data and continuous data, and examples for each
are provided. 

- See help and look at all available options.

```
./supercoil -h
```

-  Run the program just consider pathway and microarray information

```
./supercoil -i DATA/NC_000913.expr -j DATA/NC_000913.ptt  -o DATA/NC_000913.gi.operon -p DATA/NC_000913.pathway -n 0.3 -g 0.5 -t 15
```

- Run the program considering NAP binding sites and HEGs besides pathway and microarray

```
./supercoil -i DATA/NC_000913.expr -j DATA/NC_000913.ptt  -o DATA/NC_000913.gi.operon -p DATA/NC_000913.pathway -a DATA/NC_000913.NAP -e DATA/NC_000913.HEG -D DATA/expression-value -n 0.3 -g 0.5 -t 15
```

- Identify the weight parameters dynamically, i.e.,train the parameters (n, g, t) optimizing the accurracy of NAP binding sites mapping

```
./supercoil -i DATA/NC_000913.expr -j DATA/NC_000913.ptt  -o DATA/NC_000913.gi.operon -p DATA/NC_000913.pathway -a DATA/NC_000913.NAP -e DATA/NC_000913.HEG -D DATA/expression-value -M
```

- To get some basic stats

```
perl analysis_dynamic.pl DATA/NC_000913.expr.dynamic > DATA/NC_000913.expr.dynamic.stat
```

#### Changelog

Version 1.0
prototype of algorithm
2011.11.30


#### Contact

Any questions, problems, bugs are welcome and should be dumped to
Qin Ma <Qin.Ma@osumc.edu>

Creation: Dec. 16, 2011


