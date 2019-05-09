
# Supercoil: Bacterial chromosome folding structure under different conditions

## Abstract
The circular chromosome of Escherichia coli has been suggested to fold into a collection of sequentially consecutive domains, genes in each of which tend to be co-expressed. It has also been suggested that such domains, forming a partition of the genome, are dynamic with respect to the physiological conditions. However, little is known about which DNA segments of the E. coli genome form these domains and what determines the boundaries of these domain segments. We present a computational model here to partition the circular genome into consecutive segments, theoretically suggestive of the physically folded supercoiled domains, along with a method for predicting such domains under specified conditions. Our model is based on a hypothesis that the genome of E. coli is partitioned into a set of folding domains so that the total number of unfoldings of these domains in the folded chromosome is minimized, where a domain is unfolded when a biological pathway, consisting of genes encoded in this DNA segment, is being activated transcriptionally. Based on this hypothesis, we have predicted seven distinct sets of such domains along the E. coli genome for seven physiological conditions, namely exponential growth, stationary growth, anaerobiosis, heat shock, oxidative stress, nitrogen limitation and SOS responses. These predicted folding domains are highly stable statistically and are generally consistent with the experimental data of DNA binding sites of the nucleoid-associated proteins that assist the folding of these domains, as well as genome-scale protein occupancy profiles, hence supporting our proposed model. Our study established for the first time a strong link between a folded E. coli chromosomal structure and the encoded biological pathways and their activation frequencies.

**Cite us:** Qin M, Yanbin Y, Mark A.S, Han Z, Guojun L, and Ying X. Computational analyses of transcriptomic data reveal the dynamic organization of the Escherichia coli chromosome under different conditions. *Nucleic Acids Res.* 2013 Jun; 41(11): 5594–5603.  doi: 10.1093/nar/gkt261

## Environment
Linux system is recommended.
Ubuntu 18.04.2 LTS is used for testing. (5/9/2019)

# Usage

## Installation

Simply put "supercoil-master.zip" in any directory.

```
unzip supercoil-master.zip && rm unzip supercoil-master.zip
```

Enter the folder "supercoil-master" and type "make" then the compiled codes are within the same directory as the source.

```
cd supercoil-master
make
```


## Inputs and outputs

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

## Changelog

Version 1.0
prototype of algorithm
2011.11.30


## Contact

Any questions, problems, bugs are welcome and should be dumped to
Qin Ma <Qin.Ma@osumc.edu>

Creation: Dec. 16, 2011


